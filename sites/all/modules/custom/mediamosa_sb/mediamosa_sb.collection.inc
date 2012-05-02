<?php
/**
 * MediaMosa is a Full Featured, Webservice Oriented Media Management and
 * Distribution platform (http://mediamosa.org)
 *
 * Copyright (C) 2012 SURFnet BV (http://www.surfnet.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, you can find it at:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

/**
 * Form to be used by adding or editing collection.
 *
 * @return
 *   The form array.
 */
function _mediamosa_sb_collection_form($values) {
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Information'),
  );

  $form['basic']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => empty($values['title']) ? '' : $values['title'],
  );

  $form['basic']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#required' => FALSE,
    '#default_value' => empty($values['description']) ? '' : $values['description'],
  );

  return $form;
}

/**
 * The add collection form.
 */
function mediamosa_sb_collection_add_form($form, $form_state) {

  // Set default.
  $form_state += array(
    'values' => array(),
  );

  // Basic form.
  $form = _mediamosa_sb_collection_form($form_state['values']);

  // Submit button.
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validation for add collection form.
 */
function mediamosa_sb_collection_add_form_validation($form, $form_state) {
}

/**
 * Submit for add collection form.
 */
function mediamosa_sb_collection_add_form_submit($form, $form_state) {
  // Data to store.
  $options = array(
    'title' => $form_state['values']['title'],
    'description' => $form_state['values']['description'],
  );

  // Add the collection.
  $coll_id = MediaMosaSbConnectorWrapper::create_collection($options);
  if ($coll_id) {
    drupal_goto(mediamosa_sb::get_collection_detail_url($coll_id));
  }

  // Log the error.
  mediamosa_sb::watchdog_error('Unable to create collection');
}

/**
 * The edit collection form.
 */
function mediamosa_sb_collection_edit_form($form, $form_state, $coll_id) {

  // Get the collection.
  $collection = MediaMosaSbConnectorWrapper::get_collection($coll_id);

  // Can't find collection?
  if (!$collection) {
    mediamosa_sb::watchdog_error("Can't find the collection.");
    return;
  }

  // Find the item array.
  $item = $collection->items->item;

  $form_state += array(
    'values' => array(
      'title' => (string) $collection->items->item->title,
      'description' => (string) $collection->items->item->description,
    ),
  );

  // Basic form.
  $form = _mediamosa_sb_collection_form($form_state['values']);

  $form['coll_id'] = array(
    '#type' => 'value',
    '#value' => $coll_id,
  );

  // Submit button.
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  return $form;
}

/**
 * Validation for edit collection form.
 */
function mediamosa_sb_collection_edit_form_validation($form, $form_state) {
}

/**
 * Submit for add collection form.
 */
function mediamosa_sb_collection_edit_form_submit($form, $form_state) {
  // What was pressed.
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // The collection ID.
  $coll_id = $form_state['values']['coll_id'];

  switch ($op) {
    case t('Save'):
      // Data to store.
      $options = array(
        'title' => $form_state['values']['title'],
        'description' => $form_state['values']['description'],
      );

      // Add the collection.
      MediaMosaSbConnectorWrapper::update_collection($coll_id, $options);
      break;

    case t('Delete'):
      drupal_goto('collection/delete/' . rawurlencode($coll_id));
  }

  // Redirect.
  drupal_goto(mediamosa_sb::get_collection_detail_url($coll_id));
}

/**
 * Deletion confirm.
 *
 * @param $coll_id
 *   ID of the collection to delete.
 */
function mediamosa_sb_collection_delete_confirm_form($form, &$form_state, $coll_id) {

  // Get the collection.
  $collection = MediaMosaSbConnectorWrapper::get_collection($coll_id);

  if (!$collection) {
    drupal_set_message(t('Unable to find collection.'), 'warning');

    // Failed.
    drupal_goto('collections');
  }

  $form['coll_id'] = array(
    '#type' => 'value',
    '#value' => $coll_id,
  );

  return confirm_form($form,
                      t('Are you sure you want to delete this collection?'),
                      url('collection/detail/' . rawurlencode($coll_id), array('absolute' => TRUE)),
                      t('This action cannot be undone.'),
                      t('Delete'), t('Cancel')
  );
}

/**
 * Submit handler for deletion collection.
 *
 * @see mediamosa_sb_collection_delete_confirm_form()
 */
function mediamosa_sb_collection_delete_confirm_form_submit($form, &$form_state) {

  // Remove all links
  $coll_id = $form_state['values']['coll_id'];

  // Get the current user.
  $user_id = mediamosa_ck::session_user_id();

  do {
    // Get the asset_ids.
    $xml = MediaMosaSbConnectorWrapper::get_collection_asset_ids($coll_id);
    if (!$xml) {
      drupal_goto(mediamosa_sb::get_collection_detail_url($coll_id));
    }

    // Collect the asset_ids;
    $asset_ids = array();

    // Collect the asset_ids.
    foreach ($xml->items->item as $item) {
      $asset_ids[] = (string) $item->asset_id;
    }

    if (!empty($asset_ids)) {
      // Delete relations.
      if (!MediaMosaSbConnectorWrapper::delete_collection_asset_relations($coll_id, $user_id, $asset_ids)) {
        mediamosa_sb::watchdog_error('Unable to remove assets from collection.');
        drupal_goto(mediamosa_sb::get_collection_detail_url($coll_id));
      }
    }
  }
  while (!empty($asset_ids));

  // No more assets in collection, now remove collection.
  if (!MediaMosaSbConnectorWrapper::delete_collection($coll_id, $user_id)) {
    mediamosa_sb::watchdog_error('Unable to delete collection.');
    drupal_goto(mediamosa_sb::get_collection_detail_url($coll_id));
  }

  // All ok.
  drupal_set_message(t('Collection has been deleted.'));
  drupal_goto('collections');
}
