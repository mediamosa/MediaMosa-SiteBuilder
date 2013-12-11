<?php
/**
 * @file
 * Admin functions.
 */

/**
 * The main configuration form for MediaMosa Sitebuilder.
 *
 * @return array
 *   An array representing the form definition.
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
    '#default_value' => variable_get('mediamosa_sb_upload_description', t('Maximum size of 2.0GB. <br \>Allowed file types: 3gp,avi,dv,flv,mov,mp3,mp4,mpeg,wav,wma,wmv.')),
    '#description' => 'default: <br \>' . t('Maximum size of 2.0GB. <br \>Allowed file types: 3gp,avi,dv,flv,mov,mp3,mp4,mpeg,wav,wma,wmv.'),
  );

  $form['upload']['mediamosa_sb_show_quota'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show available quota.'),
    '#default_value' => variable_get('mediamosa_sb_show_quota', TRUE),
  );

  $form['upload']['mediamosa_sb_is_visible'] = array(
    '#type' => 'checkbox',
    '#title' => t('Default visible in lists (step 3).'),
    '#description' => 'If checked, the media item will by default be visible on the frontpage (new/popular).',
    '#default_value' => variable_get('mediamosa_sb_is_visible', TRUE),
  );

  $form['upload']['mediamosa_sb_user_start_transcode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Let the uploader choose transcodes.'),
    '#description' => 'If checked, a user can choose transcodes in the last step of the upload process, otherwise transcodes defined below are used.',
    '#default_value' => variable_get('mediamosa_sb_user_start_transcode', TRUE),
  );

  $form['edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form settings for Edit Asset options.'),
  );
  $form['edit']['mediamosa_sb_allow_transfer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow user Transfer.'),
    '#description' => 'Allow users to transfer assets to other users.',
    '#default_value' => variable_get('mediamosa_sb_allow_transfer', FALSE),
  );

  $form['view_asset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form settings for View Asset page.'),
  );
  $form['view_asset']['mediamosa_sb_view_asset_formats'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show additional formats.'),
    '#description' => 'Shows a list of additional formats on the asset view page. By default, sitebuilder tries to present a playable media in the player area, this option gives the user more choice.',
    '#default_value' => variable_get('mediamosa_sb_view_asset_formats', TRUE),
  );

  return system_settings_form($form);
}
