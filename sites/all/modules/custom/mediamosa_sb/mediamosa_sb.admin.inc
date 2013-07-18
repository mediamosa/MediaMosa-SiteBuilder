<?php
/**
 * @file
 * Admin functions.
 */

/**
 * The main configuration form for MediaMosa Sitebuilder
 *
 * @return array
 *   An array representing the form definition.
 *
 */
function mediamosa_sb_configuration_form() {

  $form = array();

  $form['upload'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form settings for Upload process.'),
  );

  $form['upload']['mediamosa_sb_upload_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description shown with the file upload button.'),
    '#default_value' => variable_get('mediamosa_sb_upload_description', t('Maximum size of 2.0GB. <br>Allowed file types: 3gp,avi,dv,flv,mov,mp3,mp4,mpeg,wav,wma,wmv.')),
    '#description' => 'default: <br>' . t('Maximum size of 2.0GB. <br>Allowed file types: 3gp,avi,dv,flv,mov,mp3,mp4,mpeg,wav,wma,wmv.'),
  );

  $form['upload']['mediamosa_sb_show_quota'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show available quota.'),
    '#default_value' => variable_get('mediamosa_sb_show_quota', TRUE),
  );

  $form['upload']['mediamosa_sb_is_visible'] = array(
    '#type' => 'checkbox',
    '#title' => t('Default visible in lists (step 3).'),
    '#description' => 'If checked, the video will by default be visible on the frontpage (new/popular).',
    '#default_value' => variable_get('mediamosa_sb_is_visible', TRUE),
  );

  $default_transcode_profile = variable_get('media_mediamosa_transcode_profile_default');
  if (!isset($default_transcode_profile)) {
    $default_transcode_profile = MediaMosaCkConnectorWrapper::get_default_transcode_profile();
  }
  $available_transcode_profiles = variable_get('media_mediamosa_transcode_profiles_allowed');

  $mediamosa_sb_transcodes = variable_get('mediamosa_sb_transcodes');
  if (!isset($mediamosa_sb_transcodes)) {
    $mediamosa_sb_transcodes = array($default_transcode_profile);
  }

  $form['upload']['mediamosa_sb_user_start_transcode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Let the uploader choose transcodes.'),
    '#description' => 'If checked, a user can choose transcodes in the last step of the upload process, otherwise transcodes defined below are used.',
    '#default_value' => variable_get('mediamosa_sb_user_start_transcode', TRUE),
  );

  $form['upload']['mediamosa_sb_transcodes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Automatically start transcodes:'),
    '#options' => $available_transcode_profiles,
    '#default_value' => $mediamosa_sb_transcodes,
    '#description' => 'Profiles from allowed profiles: ' . l(t('MediaMosa ck configuration'), "admin/config/media/mediamosa_ck/config"),
    '#states' => array(
      'enabled' => array(
        ':input[name="mediamosa_sb_user_start_transcode"]' => array('checked' => FALSE),
      ),
    ),
  );

  return system_settings_form($form);
}


/**
 * Implements hook_form_validate().
 */
//function mediamosa_sb_configuration_form_validate($form, &$form_state) {
//}

/**
 * Implements hook_form_submit().
 */
//function mediamosa_sb_configuration_form_submit($form, &$form_state) {
//}
