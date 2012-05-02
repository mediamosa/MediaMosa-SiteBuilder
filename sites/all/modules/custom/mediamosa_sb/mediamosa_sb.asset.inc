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
 * @file
 * Asset related functions.
 */

/**
 * Step 1: Upload file to MediaMosa.
 */
function mediamosa_sb_asset_upload_form($form, &$form_state) {

  // Set title.
  drupal_set_title('Upload');

  // Empty.
  $form = array();

  // Set the title.
  $form['title'] = array(
    '#title' => t('Upload a new video'),
    '#theme' => 'mediamosa_sb_title_header',
    '#options' => array(
      'current' => 1,
      'total' => 4,
      'subtitle' => t('Upload'),
      'subtitle_next' => t('Enter metadata'),
    ),
  );

  // Get the default profile.
  $default_profile = MediaMosaSbConnectorWrapper::get_default_transcode_profile();

  // Try to create upload ticket.
  $result = MediaMosaSbConnectorWrapper::create_upload_ticket(array('create_still' => TRUE, 'transcode' => $default_profile ? array($default_profile) : array()));
  if (!$result) {
    $form['upload'] = array(
      '#markup' => t('Unable to upload to MediaMosa; @reason', array('@reason' => mediamosa_ck::get_connector_last_error_text())),
    );

    return $form;
  }

  // Get upload URL.
  $upload_url = $result['action'];

/*
  drupal 6;
  <input type="file" name="file"  class="form-file required" id="edit-file" size="60" />

  drupal 7
  <input type="file" id="edit-file" name="files[file]" size="60" class="form-file" />
*/

  // Because we override.
  $form_state['has_file_element'] = TRUE;

  // FIXME: Hack to make it work with single array file upload to mediamosa.
  // To make it work with MediaMosa single array upload result. MediaMosa
  // can not work with files[file].
  $form['file'] = array(
    '#type' => 'item',
    '#markup' => '<input type="file" id="edit-file-upload" name="file" size="40" class="form-file" />',
    '#title' => t('Upload your file'),
    // @todo: make setting.
    '#description' => t('Maximum size of 2,0 GB, MOV, AVI'),
  );

  // Get the current user.
  $user = MediaMosaSbConnectorWrapper::get_user(mediamosa_ck::session_user_id());

  $user_quota = array(
    'user_over_quota' => TRUE,
    'user_total' => 0,
    'user_used' => 0,
  );

  if (!empty($user->header->item_count)) {
    $user_quota['user_over_quota'] = MediaMosaSbConnectorWrapper::string2bool($user->items->item->user_over_quota);
    $user_quota['user_total'] = (int) $user->items->item->app_quota_mb;
    $user_quota['user_used'] = $user_quota['user_total'] - (int) $user->items->item->quota_available_mb;
  }

  $form['user_quota'] = array(
    '#title' => t('Your Quota status'),
    '#theme' => 'mediamosa_sb_upload_quota',
    '#options' => $user_quota,
  );

  // Redirect value, we need to redirect back after upload so we can add it to
  // Drupal.
  $form['redirect_uri'] = array(
    '#type' => 'hidden',
    '#value' => url('asset/upload/edit/' . rawurlencode($result['asset_id']) . '/' . rawurlencode($result['mediafile_id']), array('absolute' => TRUE)),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#description' => t('Upload your file'),
    '#value' => t('Upload'),
  );

  $form['#action'] = $upload_url;

  // Merge with other options in for upload (turned off for now).
  $form = array_merge(module_invoke_all('media_mediamosa_upload_collect'), $form);

  return $form;
}

/**
 * The step 2/3/4 form.
 */
function mediamosa_sb_asset_upload_steps_form($form, &$form_state, $asset_id, $mediafile_id) {
  // Initialize a description of the steps for the steps.
  if (empty($form_state['step'])) {
    // Store them. Even if the user tries something with url, he can only handle
    // own assets.
    $form_state['asset_id'] = $asset_id;
    $form_state['mediafile_id'] = $mediafile_id;

    $form_state['step'] = 1;
    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = array(
      1 => array(
        'form' => 'mediamosa_sb_asset_upload_step_metadata_form',
        'subtitle' => t('Metadata'),
        'subtitle_next' => t('Define Access & Visibility'),
      ),
      2 => array(
        'form' => 'mediamosa_sb_asset_upload_step_access_form',
        'subtitle' => t('Access & Visibility'),
        'subtitle_next' => t('Define transcoding formats'),
      ),
      3 => array(
        'form' => 'mediamosa_sb_asset_upload_step_media_form',
        'subtitle' => t('Transcoding formats'),
        'subtitle_next' => '',
      ),
    );
  }

  $step = $form_state['step'];
  $step_information = $form_state['step_information'][$step];

  // Set title.
  drupal_set_title('Upload');

  // Set the title.
  $form['title'] = array(
    '#title' => t('Upload a new video'),
    '#theme' => 'mediamosa_sb_title_header',
    '#options' => array(
      'current' => $step + 1,
      'total' => 4,
      'subtitle' => $step_information['subtitle'],
      'subtitle_next' => $step_information['subtitle_next'],
    ),
  );

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form['data'] = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('_mediamosa_sb_asset_upload_steps_next_submit'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#name' => 'prev',
      '#submit' => array('_mediamosa_sb_asset_upload_steps_cancel_submit'),
      '#limit_validation_errors' => array(),
    );

    // Include each validation function defined for the different steps.
    if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
      $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
    }
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form steps.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
      '#submit' => array('_mediamosa_sb_asset_upload_steps_finish_submit'),
    );
  }

  return $form;
}

/**
 * Submit handler for the "cancel" button.
 */
function _mediamosa_sb_asset_upload_steps_cancel_submit($form, &$form_state) {
  // Go back to start.
  drupal_goto('mediamosa/upload');
}

/**
 * Submit handler for the 'next' button.
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param $form
 * @param $form_state
 */
function _mediamosa_sb_asset_upload_steps_next_submit($form, &$form_state) {
  $form_state['step_information'][$form_state['step']]['stored_values'] = $form_state['input'];

  if ($form_state['step'] < count($form_state['step_information'])) {
    $form_state['step']++;

    if (!empty($form_state['step_information'][$form_state['step']]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$form_state['step']]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }

    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

/**
 * The info (metadata) step form.
 */
function mediamosa_sb_asset_upload_step_metadata_form($form, $form_state) {
  // Set default.
  $form_state += array(
    'values' => array(),
  );

  // Set asset_id in case we need it.
  $values = array_merge(array('asset_id' => $form_state['asset_id']), $form_state['values']);

  return mediamosa_sb_asset_forms::info_form($values, $form_state['asset_id']);
}

/**
 * Validation for metadata form.
 */
function mediamosa_sb_asset_upload_step_metadata_form_validate($form, $form_state) {
}

/**
 * Returns form elements for the 'other info' page of the steps. This is the
 * thid and last step of the example steps.
 *
 * @ingroup upload_form
 */
function mediamosa_sb_asset_upload_step_access_form($form, $form_state) {
  // Set default.
  $form_state += array(
    'values' => array(),
  );

  // Set asset_id in case we need it.
  $values = array_merge(array('asset_id' => $form_state['asset_id']), $form_state['values']);

  return mediamosa_sb_asset_forms::access_form($values);
}

/**
 * Returns form elements for the 'other info' page of the steps. This is the
 * thid and last step of the example steps.
 *
 * @ingroup upload_form
 */
function mediamosa_sb_asset_upload_step_media_form($form, &$form_state) {
  // Set default.
  $form_state += array(
    'values' => array(),
  );

  // Set asset_id in case we need it.
  $values = array_merge(array('asset_id' => $form_state['asset_id']), $form_state['values']);

  return mediamosa_sb_asset_forms::media_form($values, TRUE);
}

/**
 * Validation for metadata form.
 */
function _mediamosa_sb_asset_upload_steps_finish_validation($form, &$form_state) {
  // Run function for validation transcode jobs / stills to MediaMosa.
  mediamosa_sb::validate_media($form_state['step_information'][3]['stored_values'], $form_state['asset_id']);
}

/**
 * Step 4 submition function.
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup upload_form
 */
function _mediamosa_sb_asset_upload_steps_finish_submit($form, &$form_state) {
  // Store the last step.
  $form_state['step_information'][$form_state['step']]['stored_values'] = $form_state['input'];

  // Run function for posting metadata to MediaMosa.
  mediamosa_sb::submit_info($form_state['step_information'][1]['stored_values'], $form_state['asset_id']);

  // Run function for posting access rules to MediaMosa.
  mediamosa_sb::submit_access($form_state['step_information'][2]['stored_values'], $form_state['asset_id']);

  // Run function for posting transcode jobs / stills to MediaMosa.
  mediamosa_sb::submit_media($form_state['step_information'][3]['stored_values'], $form_state['asset_id'], TRUE);

  // Go to view page.
  drupal_goto(mediamosa_sb::get_asset_detail_url($form_state['asset_id']));
}

/**
 * Build the metadata form.
 *
 * @param $form
 * @param $form_state
 * @param $asset_id
 * @return
 *   The metadata form.
 */
function mediamosa_sb_asset_edit_metadata_form($form, &$form_state, $asset_id) {

  $values = array();

  // Get the asset.
  $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id, array('show_collections' => TRUE));
  if (!$asset) {
    drupal_set_message('Media not found');
    return;
  }

  // Get title.
  $title = mediamosa_ck::get_asset_title($asset);

  // Set the title.
  drupal_set_title($title);

  // Get the metadata setup.
  $metadata_fields = mediamosa_ck::get_metadata_fields();

  // Fill values with metadata.
  foreach ($metadata_fields as $prefix => $metadata_field) {

    // Must exists.
    if (!isset($asset->items->item->{$metadata_field['xpath']})) {
      continue;
    }

    // Loop through fields.
    foreach ($asset->xpath('items/item/' . $metadata_field['xpath']) as $metadata) {
      foreach ($metadata as $name => $value) {
        $values[$prefix . '_' . (string) $name] = (string) $value;
      }
    }
  }

  // Get the collections of the asset.
  foreach ($asset->xpath('items/item/collections/collection') as $collection) {
    $values['mycollections'][] = (string) $collection->attributes()->id;
  }

  // Get the form.
  $form = mediamosa_sb_asset_forms::info_form($values, $asset_id);

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => $asset_id,
  );

    // Submit button.
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  // Has delete rights?
  if (_mediamosa_sb_access_collection_delete($asset_id)) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }

  return $form;
}

/**
 * Validation for asset info page.
 */
function mediamosa_sb_asset_edit_metadata_form_validation($form, &$form_state) {
}

/**
 * Submit for asset info page.
 */
function mediamosa_sb_asset_edit_metadata_form_submit($form, $form_state) {
  // What was pressed.
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // The collection ID.
  $asset_id = $form_state['values']['asset_id'];

  switch ($op) {
    case t('Save'):
      // Run function for posting metadata to MediaMosa.
      mediamosa_sb::submit_info($form_state['input'], $asset_id);
      break;

    case t('Delete'):
      drupal_goto('asset/delete/' . rawurlencode($asset_id));
  }

  // Redirect.
  drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
}

/**
 * Access form.
 */
function mediamosa_sb_asset_edit_access_form($form, $form_state, $asset_id) {
  $values = array();

  // Get the asset.
  $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id);
  if (!$asset) {
    drupal_set_message('Media not found');
    return;
  }

  // Set the title.
  drupal_set_title(mediamosa_sb::get_asset_title($asset));

  // Set values. Use the original mediafile.
  $mediafile_ids = MediaMosaSbConnectorWrapper::get_asset_mediafile_ids($asset_id, array('get_original_only' => TRUE));
  $mediafile_id = reset($mediafile_ids);

  if (!empty($mediafile_id)) {
    $user_id = mediamosa_ck::session_user_id();

    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      // Although the owner of the asset might be the user that is in the
      // session, having the edit right here grants you to be the owner for now.
      $user_id = mediamosa_sb::get_owner_asset($asset_id);
    }

    $access = MediaMosaSbConnectorWrapper::get_access_control($mediafile_id, $user_id);

    $values['acl_domain'] = implode(', ', $access['acl_domain']);
    $values['acl_realm'] = implode(', ', $access['acl_realm']);
    $values['acl_user'] = implode(', ', $access['acl_user']);
  }

  // isprivate = !is_visible.
  $values['is_visible'] = drupal_strtoupper((string) $asset->items->item->isprivate) == 'TRUE' ? FALSE : TRUE;

  // Get the form.
  $form = mediamosa_sb_asset_forms::access_form($values);

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => $asset_id,
  );

    // Submit button.
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validation for asset access page.
 */
function mediamosa_sb_asset_edit_access_form_validation($form, &$form_state) {
}

/**
 * Submit for asset access page.
 */
function mediamosa_sb_asset_edit_access_form_submit($form, $form_state) {
  // What was pressed.
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // The collection ID.
  $asset_id = $form_state['values']['asset_id'];

  switch ($op) {
    case t('Save'):
      // Run function for posting access to MediaMosa.
      mediamosa_sb::submit_access($form_state['input'], $asset_id);
      break;
  }

  // Redirect.
  drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
}

/**
 * The Media form.
 */
function mediamosa_sb_asset_edit_media_form($form, $form_state, $asset_id) {
  $values = array('asset_id' => $asset_id);

  // Get the asset.
  $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id);
  if (!$asset) {
    drupal_set_message('Media not found');
    return;
  }

  // Set the title.
  drupal_set_title(mediamosa_sb::get_asset_title($asset));

  // Get the media form.
  $form = mediamosa_sb_asset_forms::media_form($values);

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => $asset_id,
  );

  // Submit button.
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validation for asset media page.
 */
function mediamosa_sb_asset_edit_media_form_validate($form, &$form_state) {
  // What was pressed.
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // The collection ID.
  $asset_id = $form_state['values']['asset_id'];

  switch ($op) {
    case t('Save'):
      // Run function for validating media form post.
      mediamosa_sb::validate_media($form_state['input'], $asset_id);
      break;
  }
}

/**
 * Submit for asset media page.
 */
function mediamosa_sb_asset_edit_media_form_submit($form, $form_state) {
  // What was pressed.
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // The collection ID.
  $asset_id = $form_state['values']['asset_id'];

  switch ($op) {
    case t('Save'):
      // Submit the media form.
      mediamosa_sb::submit_media($form_state['input'], $asset_id);
      break;
  }

  // Redirect.
  drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
}

/**
 * Deletion confirm.
 *
 * @param $asset_id
 *   ID of the asset to delete.
 *
 * @see mediamosa_sb_asset_delete_confirm_form_submit()
 */
function mediamosa_sb_asset_delete_confirm_form($form, &$form_state, $asset_id) {

  // Get the collection.
  $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id);

  if (!$asset) {
    drupal_set_message(t('Unable to find media, already deleted?'), 'warning');

    // Failed.
    drupal_goto('assets');
  }

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => $asset_id,
  );

  return confirm_form($form,
                      t('Are you sure you want to delete this media file?'),
                      url('asset/' . rawurlencode($asset_id), array('absolute' => TRUE)),
                      t('This action cannot be undone.'),
                      t('Delete'), t('Cancel')
  );
}

/**
 * Submit handler for deletion collection.
 *
 * @see mediamosa_sb_asset_delete_confirm_form()
 */
function mediamosa_sb_asset_delete_confirm_form_submit($form, &$form_state) {

  // Remove all links
  $asset_id = $form_state['values']['asset_id'];

  // Get the current user.
  $user_id = mediamosa_ck::session_user_id();

  // No more assets in collection, now remove collection.
  if (!MediaMosaSbConnectorWrapper::delete_asset($asset_id, $user_id)) {
    mediamosa_sb::watchdog_error('Unable to delete media.');
    drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
  }

  // All ok.
  drupal_set_message(t('Media has been deleted.'));
  drupal_goto('myassets');
}
