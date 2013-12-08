<?php
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
      'total' => 3,
      'subtitle' => t('Upload'),
      'subtitle_next' => t('Enter metadata'),
    ),
  );

  // Get the transcode profile(s).
  $default_profile = MediaMosaSbConnectorWrapper::get_default_transcode_profile();
  $mediamosa_sb_transcodes = variable_get('mediamosa_ck_transcodes_autostart');
  if (!isset($mediamosa_sb_transcodes)) {
    $mediamosa_sb_transcodes = array(MediaMosaSbConnectorWrapper::get_default_transcode_profile());
  }
  // Remove not choosen transcodes.
  $transcodes = array();
  foreach ($mediamosa_sb_transcodes as $key => $value) {
    if ($value > 0) {
      $transcodes[] = $value;
    }
  }
  // Try to create upload ticket.
  $result = MediaMosaSbConnectorWrapper::create_upload_ticket(array('create_still' => TRUE, 'isprivate' => TRUE, 'transcode' => $transcodes ? $transcodes : array()));
  if (!$result) {
    $form['upload'] = array(
      '#markup' => t('Unable to upload to MediaMosa; @reason', array('@reason' => mediamosa_ck::get_connector_last_error_text())),
    );
    return $form;
  }

  // Get upload URL.
  $upload_url = $result['action'];

  // Because we override.
  $form_state['has_file_element'] = TRUE;

  // FIXME: Hack to make it work with single array file upload to mediamosa.
  // To make it work with MediaMosa single array upload result. MediaMosa
  // can not work with files[file].
  $form['file'] = array(
    '#type' => 'item',
    '#markup' => '<input type="file" id="edit-file-upload" name="file" size="40" class="form-file" />',
    '#title' => t('Upload your file'),
    '#required' => TRUE,
    '#description' => variable_get('mediamosa_sb_upload_description', 'Maximum size of 2.0GB. <br />Allowed file types: avi,mov,flv,mp4,mpeg.'),
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

  if (variable_get('mediamosa_sb_show_quota')) {
    $form['user_quota'] = array(
      '#title' => t('Your Quota status'),
      '#theme' => 'mediamosa_sb_upload_quota',
      '#options' => $user_quota,
    );
  }

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

  $form['#validate'][] = array('mediamosa_sb_asset_upload_form_validate');

  $form['#action'] = $upload_url;

  // Merge with other options in for upload (turned off for now).
  $form = array_merge(module_invoke_all('media_mediamosa_upload_collect'), $form);

  return $form;
}

function mediamosa_sb_asset_test_form_callback($form, &$fstate) {
  //  return "<div id='test-ajax'>Wrapper Div</div>";
}

function mediamosa_sb_asset_test_form_validate($form, &$fstate) {
  //form_set_error("item", "Some error to display.");
}

/**
 * Validation for upload form.
 */
function mediamosa_sb_asset_upload_form_validate($form, &$form_state) {
  //die('1');
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
        'subtitle_next' => t('Access Control'),
      ),
      2 => array(
        'form' => 'mediamosa_sb_asset_upload_step_access_form',
        'subtitle' => t('Access Control'),
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
      'total' => 3,
      'subtitle' => $step_information['subtitle'],
      'subtitle_next' => $step_information['subtitle_next'],
    ),
  );

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form['data'] = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step.
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

function mediamosa_sb_asset_upload_steps_form_validate($form, &$form_state) {

  switch($form_state['step']) {
    case 1:
      // Basic information validation checks.
      break;

    case 2:
      // Access control validation checks.
      mediamosa_sb_asset_forms::access_form_validate($form, $form_state);
    break;
  }
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
 *
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param array $form
 *   regular form array.
 * @param array $form_state
 *   form_state array.
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

    // Force rebuild with next step.
    $form_state['rebuild'] = TRUE;
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
 * Access form fields.
 *
 * Returns form elements for the 'other info' page of the steps. This is the
 * third and last step of the example steps.
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
 * Media fields form.
 *
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

  form_set_error('still_start_time', t('Time for still generation must be in format MM:SS.'));


  // Run function for validation transcode jobs / stills to MediaMosa.
  mediamosa_sb::validate_media($form_state['step_information'][3]['stored_values'], $form_state['asset_id']);
}

/**
 * Step 4 submition function.
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
  // mediamosa_sb::submit_media($form_state['step_information'][3]['stored_values'], $form_state['asset_id'], TRUE);

  // Go to view page.
  drupal_goto(mediamosa_sb::get_asset_detail_url($form_state['asset_id']));
}

/**
 * Build the metadata form.
 *
 * @param string $asset_id
 *   asset id of form.
 *
 * @return array
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
  if (_mediamosa_sb_access_asset_delete($asset_id)) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }

  // Transfer ownership.
  if (variable_get('mediamosa_sb_allow_transfer', FALSE)) {
    if (_mediamosa_sb_access_asset_delete($asset_id)) {
      $form['transfer'] = array(
        '#type' => 'submit',
        '#value' => t('Transfer'),
      );
    }
  }
  return $form;
}

/**
 * Validation for asset info page.
 */
function mediamosa_sb_asset_edit_metadata_form_validate($form, &$form_state) {
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

    case t('Transfer'):
      drupal_goto('asset/transfer/' . rawurlencode($asset_id));
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
    $mf = MediaMosaSbConnectorWrapper::get_mediafile($mediafile_id);
    $values['is_downloadable'] = 0;
    if (((string) $mf->xml->items->item->is_downloadable) == 'TRUE') {
      $values['is_downloadable'] = 1;
    }
  }

  // MediaMosa field 'isprivate' -> 'is_visible'.
  $values['is_visible'] = drupal_strtoupper((string) $asset->items->item->isprivate) == 'TRUE' ? FALSE : TRUE;

  // License is on access page.
  $values['license'] = '';
  if (isset($asset->xml->items->item->qualified_dublin_core->license)) {
    $values['license'] = (string) $asset->xml->items->item->qualified_dublin_core->license;
  }

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
function mediamosa_sb_asset_edit_access_form_validate($form, &$form_state) {
  mediamosa_sb_asset_forms::access_form_validate($form, $form_state);
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
 * @param string $asset_id
 *   ID of the asset to delete.
 *
 * @see mediamosa_sb_asset_delete_confirm_form_submit()
 */
function mediamosa_sb_asset_delete_confirm_form($form, &$form_state, $asset_id) {

  // Get the asset.
  $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id);

  if (!$asset) {
    drupal_set_message(t('Unable to find media, already deleted?'), 'warning');
    drupal_goto('assets');
  }

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => rawurlencode($asset_id),
  );

  return confirm_form($form,
    t('Are you sure you want to delete this media file?'),
    url(mediamosa_sb::get_asset_detail_url($asset_id), array('absolute' => TRUE)),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for deletion collection.
 *
 * @see mediamosa_sb_asset_delete_confirm_form()
 */
function mediamosa_sb_asset_delete_confirm_form_submit($form, &$form_state) {

  $asset_id = $form_state['values']['asset_id'];

  // Get the current user.
  $user_id = mediamosa_ck::session_user_id();

  // Now remove asset.
  if (!MediaMosaSbConnectorWrapper::delete_asset($asset_id, $user_id)) {
    mediamosa_sb::watchdog_error('Unable to delete asset.');
    drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
  }

  // All ok.
  drupal_set_message(t('Asset has been deleted.'));
  drupal_goto('myassets');
}

/**
 * Transfer confirmation form.
 *
 * @param string $asset_id
 *   ID of the asset to delete.
 *
 * @see mediamosa_sb_asset_transfer_confirm_form_submit()
 */
function mediamosa_sb_asset_transfer_confirm_form($form, &$form_state, $asset_id) {

  if (!variable_get('mediamosa_sb_allow_transfer', FALSE)) {
    drupal_set_message(t('Transfer not allowed'), 'warning');
    drupal_goto('myassets');
  }

  // Get the asset.
  $asset = MediaMosaSbConnectorWrapper::get_asset(rawurlencode($asset_id));
  if (!$asset) {
    drupal_set_message(t('Unable to find media, already deleted?'), 'warning');
    drupal_goto('myassets');
  }

  // Owner check.
  $owner_id = mediamosa_sb::get_owner_asset($asset);
  $user_id = mediamosa_ck::session_user_id();
  if (($user_id != $owner_id) && (!user_access('administer site configuration'))) {
    drupal_set_message(t('You need ownership in order to transfer.'), 'warning');
    return FALSE;
  }

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => rawurlencode($asset_id),
  );

  $form['asset_id'] = array(
    '#type' => 'value',
    '#value' => rawurlencode($asset_id),
  );

  $form['introduction'] = array(
    '#markup' => t('You can transfer the ownership of this asset. You need to enter the e-mail
address of the person to transfer the asset to. The email address must be known
in this application and you will need permission of the new owner. This action
cannot be undone.'),
  );

  $form['new_owner_id'] = array(
    '#type' => 'textfield',
    '#title' => t('New Owner email'),
    '#default_value' => '',
    '#size' => 40,
    '#maxlength' => 128,
    '#required' => TRUE,
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
function mediamosa_sb_asset_transfer_confirm_form_validate($form, &$form_state) {
  // Check if user exists in this installation.
  $email = check_plain($form_state['values']['new_owner_id']);
  $result = db_query("SELECT count(*) FROM {users} WHERE mail = '$email'")->fetchField();
  if ($result < 1) {
    // User doesn't exist.
    form_set_error('new_owner_id', 'This user is not known.');
  }
}

/**
 * Define transfer_message mail.
 */
function mediamosa_sb_asset_mail($key, &$message, $params) {
  global $base_url;

  $options['language'] = $message['language'];
  switch ($key) {
    case 'transfer_message':
      $langcode = $message['language']->language;
      $message['subject'] = t('Transfer media');
      $url = $base_url . '/asset/detail/' . check_plain($params['asset_id']);
      $message['body'][] = t('You receive this email because there is a video- or audio file transferred to
you.

!asset_link

You are now the owner of this file. You have permission to edit the
file, to transfer it to another user or to delete the file.', array(
        '!asset_link' => l($url, $url, array('absolute' => TRUE))));
      break;
  }
}

/**
 * Submit handler for transfer asset.
 *
 * @see mediamosa_sb_asset_transfer_confirm_form()
 */
function mediamosa_sb_asset_transfer_confirm_form_submit($form, &$form_state) {

  $asset_id = $form_state['values']['asset_id'];

  // Get the current user.
  $user_id = mediamosa_ck::session_user_id();
  $new_owner_id = check_plain($form['new_owner_id']['#value']);

  // Now transfer ownership.
  if (!MediaMosaSbConnectorWrapper::change_asset_owner($asset_id, $user_id, $new_owner_id)) {
    mediamosa_sb::watchdog_error('Unable to transfer asset.');
    drupal_goto(mediamosa_sb::get_asset_detail_url($asset_id));
  }

  $module = 'mediamosa_sb_asset';
  $key = 'transfer_message';
  $from = variable_get('site_mail', 'admin@example.com');
  $language = language_default();
  $params = array('asset_id' => $asset_id);

  $result = drupal_mail($module, $key, $new_owner_id, $language, $params, $from, TRUE);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Asset ownership has been transferred, a mail to the new owner has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }

  drupal_goto('myassets');
}
