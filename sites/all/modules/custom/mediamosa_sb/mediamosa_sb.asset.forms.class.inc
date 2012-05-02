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
 * Simple static class to hold form functions, so we keep our inc files cleaner
 * and this is autoloaded.
 */
class mediamosa_sb_asset_forms {
  // ------------------------------------------------------------------- Consts.
  const DEFAULT_START_TIME_STILL_FORM = '00:00';

  // ---------------------------------------------------------------- Functions.
  /**
   * Return the default value.
   */
  static protected function default_value($values, $name, $default = '') {
    return !isset($values[$name]) ? $default : $values[$name];
  }

  /**
   * The info form.
   *
   * @param $values
   *   The values of the form.
   * @param $asset_id
   *   The ID of the asset.
   *
   * @return
   *   Returns the form array.
   */
  static public function info_form($values, $asset_id) {
    $form = array();

    // Add basic information form.
    $form['bacicinfo'] = self::info_basicinfo_form($values, $asset_id);

    // Add collections form.
    $form['collections'] = self::info_collections_form($values, $asset_id);

    // Add metadata form.
    $form['metadata'] = self::info_metadata_form($values, $asset_id);

    return $form;
  }

  /**
   * The metadata form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function info_basicinfo_form($values, $asset_id) {
    $form = array();

    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => t('Basic Information'),
    );

    // dc.title is translated by Drupal to dc_title in form_state['input'],
    // so better use _ instead from the start.
    $form['basic']['dc_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#required' => TRUE,
      '#default_value' => self::default_value($values, 'dc_title'),
    );

    $form['basic']['dc_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'dc_description'),
    );

    if (user_access('mediamosa_sb::MEDIAMOSA_SB_PERMISSION_ALTER_FEATURED')) {
      $asset_ids_featured = mediamosa_ck_views_rest_asset_featured::get_featured_ids();

      $form['basic']['asset_featured'] = array(
        '#type' => 'checkbox',
        '#title' => t('Is featured'),
        '#description' => t('When checked, this asset will show up in the featured listing.'),
        '#required' => FALSE,
        '#default_value' => isset($asset_ids_featured[$asset_id]),
      );
    }

    return $form;
  }

  /**
   * The metadata form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function info_collections_form($values, $asset_id) {
    $form = array();

    $user_id = '';
    if (!empty($asset_id)) {
      $user_id = MediaMosaSbConnectorWrapper::get_asset_owner($asset_id);
    }

    // Get the collections.
    $options_collections = MediaMosaSbConnectorWrapper::get_my_collections_for_options($user_id);

    $form['collections'] = array(
      '#type' => 'fieldset',
      '#title' => t('Collections'),
    );

    if (count($options_collections)) {
      $form['collections']['mycollections'] = array(
        '#type' => 'select',
        '#title' => t('My collections'),
        '#required' => FALSE,
        '#multiple' => TRUE,
        '#size'=> 5,
        '#options' => $options_collections,
        '#default_value' => self::default_value($values, 'mycollections'),
      );
    }
    else {
      $form['collections']['mycollections'] = array(
        '#markup' => '<p><br />' . t('No Collections yet, you can add them at the <a href=@mycollections>My Collections</a> page.', array('@mycollections' => url('mycollections')))
        . '<br /><br /></p>',
      );
    }

    return $form;
  }

  /**
   * The metadata form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function info_metadata_form($values) {
    $form = array();

    $form['additional'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional metadata <span>(According Dublin Metadata Initiative)</span>'),
    );

    $form['additional']['dc'] = array(
      '#type' => 'fieldset',
      '#title' => t('Dublin core'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['additional']['dc']['dc_type'] = array(
      '#type' => 'textfield',
      '#title' => t('Type'),
      '#required' => FALSE,
      '#description' => t('The nature or genre of the resource e.g. Image, MovingImage'),
      '#default_value' => self::default_value($values, 'dc_type'),
    );

    $form['additional']['dc']['dc_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Format'),
      '#required' => FALSE,
      '#description' => t('The file format, physical medium e.g. video, image'),
      '#default_value' => self::default_value($values, 'dc_format'),
    );

    $form['additional']['dc']['dc_language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#required' => FALSE,
      '#description' => t('The language of the resource'),
      '#options'  => mediamosa_sb::get_metdata_languages_options(),
      '#default_value' => self::default_value($values, 'dc_language'),
    );

    $form['additional']['dc']['dc_creator'] = array(
      '#type' => 'textfield',
      '#title' => t('Creator'),
      '#required' => FALSE,
      '#description' => t('Responsible for making the resource'),
      '#default_value' => self::default_value($values, 'dc_creator'),
    );

    $form['additional']['dc']['dc_publisher'] = array(
      '#type' => 'textfield',
      '#title' => t('Publisher'),
      '#required' => FALSE,
      '#description' => t('Responsible for making the resource available'),
      '#default_value' => self::default_value($values, 'dc_publisher'),
    );

    $form['additional']['dc']['dc_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#required' => FALSE,
      '#description' => t('The topic of the resource'),
      '#default_value' => self::default_value($values, 'dc_subject'),
    );

    // Provide a default date in the format YYYY-MM-DD HH:MM:SS.
    $date = '';

    // Provide a format using regular PHP format parts (see documentation on php.net).
    // If you're using a date_select, the format will control the order of the date parts in the selector,
    // rearrange them any way you like. Parts left out of the format will not be displayed to the user.
    $format = 'Y-m-d';

    $form['additional']['dc']['dc_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Date'),
      '#description' => t('Date of the resource'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
      '#default_value' => self::default_value($values, 'dc_date'),
    );

    $form['additional']['dc']['dc_identifier'] = array(
      '#type' => 'textfield',
      '#title' => t('Indentifier'),
      '#required' => FALSE,
      '#description' => t('An unambiguous reference to the resource within a given context'),
      '#default_value' => self::default_value($values, 'dc_identifier'),
    );

    $form['additional']['dc']['dc_source'] = array(
      '#type' => 'textfield',
      '#title' => t('Source'),
      '#required' => FALSE,
      '#description' => t('A related resource from which the described resource is derived'),
      '#default_value' => self::default_value($values, 'dc_source'),
    );

    $form['additional']['dc']['dc_relation'] = array(
      '#type' => 'textfield',
      '#title' => t('Relation'),
      '#required' => FALSE,
      '#description' => t('A related resource from which the described resource is derived'),
      '#default_value' => self::default_value($values, 'dc_relation'),
    );

    $form['additional']['dc']['dc_coverage_temporal'] = array(
      '#type' => 'textfield',
      '#title' => t('Temporal coverage'),
      '#required' => FALSE,
      '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
      '#default_value' => self::default_value($values, 'dc_coverage_temporal'),
    );

    $form['additional']['dc']['dc_coverage_spatial'] = array(
      '#type' => 'textfield',
      '#title' => t('Spatial coverage'),
      '#required' => FALSE,
      '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
      '#default_value' => self::default_value($values, 'dc_coverage_spatial'),
    );

    $form['additional']['dc']['dc_rights'] = array(
      '#type' => 'textfield',
      '#title' => t('Rights'),
      '#required' => FALSE,
      '#description' => t('Information about rights held in and over the resource.'),
      '#default_value' => self::default_value($values, 'dc_rights'),
    );

    $form['additional']['qdc'] = array(
      '#type' => 'fieldset',
      '#title' => t('Qualified Dublin core'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['additional']['qdc']['qdc_title_alternative'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternative title'),
      '#required' => FALSE,
      '#description' => t('Alternative title of the resource'),
      '#default_value' => self::default_value($values, 'qdc_title_alternative'),
    );

    $form['additional']['qdc']['qdc_description_abstract'] = array(
      '#type' => 'textarea',
      '#title' => t('Abstract description'),
      '#required' => FALSE,
      '#rows' => 5,
      '#description' => t('An abstract description of the resource'),
      '#default_value' => self::default_value($values, 'qdc_description_abstract'),
    );

    $form['additional']['qdc']['qdc_created'] = array(
      '#type' => 'date_popup',
      '#title' => t('Created'),
      '#description' => t('Date of creation of the resource.'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within',
      '#default_value' => self::default_value($values, 'qdc_created'),
    );

    $form['additional']['qdc']['qdc_issued'] = array(
      '#type' => 'date_popup',
      '#title' => t('Issued'),
      '#description' => t('Date of formal issuance (e.g., publication) of the resource'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within',
      '#default_value' => self::default_value($values, 'qdc_issued'),
    );

    $form['additional']['qdc']['qdc_hasformat'] = array(
      '#type' => 'textfield',
      '#title' => t('Has format'),
      '#required' => FALSE,
      '#description' => t('The described resource pre-existed the referenced resource'),
      '#default_value' => self::default_value($values, 'qdc_hasformat'),
    );

    $form['additional']['qdc']['qdc_isformat'] = array(
      '#type' => 'textfield',
      '#title' => t('Is format of'),
      '#required' => FALSE,
      '#description' => t('The described resource is the same intellectual content of the referenced resource, but presented in another format'),
      '#default_value' => self::default_value($values, 'qdc_isformat'),
    );

    $form['additional']['qdc']['qdc_format_medium'] = array(
      '#type' => 'textfield',
      '#title' => t('Medium'),
      '#required' => FALSE,
      '#description' => t('The material or physical carrier of the resource'),
      '#default_value' => self::default_value($values, 'qdc_format_medium'),
    );

    $form['additional']['qdc']['qdc_format_extent'] = array(
      '#type' => 'textfield',
      '#title' => t('Extent'),
      '#required' => FALSE,
      '#description' => t('The size or duration of the resource'),
      '#default_value' => self::default_value($values, 'qdc_format_extent'),
    );

    $form['additional']['qdc']['qdc_license'] = array(
      '#type' => 'textfield',
      '#title' => t('License'),
      '#required' => FALSE,
      '#description' => t('License of the resource'),
      '#default_value' => self::default_value($values, 'qdc_license'),
    );

    $form['additional']['qdc']['qdc_rightsholder'] = array(
      '#type' => 'textfield',
      '#title' => t('Rights'),
      '#required' => FALSE,
      '#description' => t('Rights holder of the resource'),
      '#default_value' => self::default_value($values, 'qdc_rightsholder'),
    );

    $form['additional']['qdc']['qdc_isreferencedby'] = array(
      '#type' => 'textfield',
      '#title' => t('Is referenced by'),
      '#required' => FALSE,
      '#description' => t('The described resource is referenced, cited, or otherwise pointed to by the referenced resource.'),
      '#default_value' => self::default_value($values, 'qdc_isreferencedby'),
    );

    return $form;
  }

  /**
   * The access form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static public function access_form($values) {
    $form = array();

    // Add visibility form.
    $form['visibility'] = self::access_visibility_form($values);

    // Add acl form.
    $form['acl'] = self::access_acl_form($values);

    return $form;
  }

  /**
   * The access form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function access_visibility_form($values) {
    $form = array();

    $form['visibility'] = array(
      '#type' => 'fieldset',
      '#title' => t('Visibility'),
    );

    // is_visible = !isprivate
    $form['visibility']['is_visible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Visible in lists'),
      '#description' => t('If checked, the video will be visible on the frontpage (new/popular).'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'is_visible', TRUE),
    );

    return $form;
  }

  /**
   * The access form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function access_acl_form($values) {
    $form = array();

    $form['control'] = array(
      '#type' => 'fieldset',
      '#title' => t('Access control'),
    );

    $form['control']['acl_domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Domain'),
      '#required' => FALSE,
      '#description' => t('Define which domains can view this video. Example; mediamosa.org, example.com'),
      '#default_value' => self::default_value($values, 'acl_domain'),
    );

    $form['control']['acl_realm'] = array(
      '#type' => 'textfield',
      '#title' => t('By realm'),
      '#required' => FALSE,
      '#description' => t('Select wich registered users based on their e-mail domain have access to this video. Example; @mediamosa.org, @example.com'),
      '#default_value' => self::default_value($values, 'acl_realm'),
    );

    $form['control']['acl_user'] = array(
      '#type' => 'textfield',
      '#title' => t('By email'),
      '#required' => FALSE,
      '#description' => t('Select which registered users based on their e-mail adress have access to this video. Example; info@mediamosa.org, name@example.com'),
      '#default_value' => self::default_value($values, 'acl_user'),
    );

    return $form;
  }

  /**
   * The access form.
   *
   * @param $values
   *   The values of the form.
   * @param $is_upload
   *   Form is used during upload.
   *
   * @return
   *   Returns the form array.
   */
  static public function media_form($values, $is_upload = FALSE) {
    $form = array();

    // Add transcoding form.
    $form['transcoding'] = self::media_transcoding_form($values, $is_upload);

    // Add still form.
    $form['still'] = self::media_still_form($values);

    return $form;
  }

  /**
   * The transcode form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function media_transcoding_form($values, $is_upload) {
    $form = array();

    // The asset ID.
    $asset_id = $values['asset_id'];

    $form['transcode'] = array(
      '#type' => 'fieldset',
      '#title' => t('Currently active video profiles'),
    );

    $xml = MediaMosaSbConnectorWrapper::get_transcode_profiles();
    if ($xml == FALSE) {
      drupal_set_message(t('Unable to retrieve transcode profiles, check MediaMosa Connector.'), 'error');
    }

    $options = array();

    // Get the allowed profiles.
    $allowed_profiles = MediaMosaSbConnectorWrapper::get_allowed_transcode_profiles();

    // List of the profile IDs that are used.
    $existing_transcodes = array();
    $is_downloadable = array();

    // Get the default profiles, these can not be deleted or re-created.
    $default_profile = MediaMosaSbConnectorWrapper::get_default_transcode_profile();

    try {
      // Get existing mediafiles.
      $asset = MediaMosaSbConnectorWrapper::get_asset($asset_id);

      // Loop through the mediafiles.
      foreach ($asset->xpath('items/item/mediafiles/mediafile') as $mediafile) {
        // Skip original.
        if (MediaMosaSbConnectorWrapper::string2bool($mediafile->is_original_file)) {
          continue;
        }

        // Collect the transcodes.
        if (!empty($mediafile->transcode_profile_id)) {
          $existing_transcodes[(int) $mediafile->transcode_profile_id] = (int) $mediafile->transcode_profile_id;
        }

        // Collect the downloadables.
        if (MediaMosaSbConnectorWrapper::string2bool($mediafile->is_downloadable)) {
          $is_downloadable[(int) $mediafile->transcode_profile_id] = (int) $mediafile->transcode_profile_id;
        }
      }
    }
    catch (Exception $e) {
      mediamosa_ck::watchdog_error('Unable to find existing mediafiles, error message; @message', array('@message' => $e->getMessage()));
    }

    if (!empty($xml->items->item)) {
      foreach ($xml->items->item as $profile) {
        $profile_id = (int) $profile->profile_id;

        // Is allowed as profile? If a mediafile exists, we ignore the allowed profile.
        if (!isset($allowed_profiles[$profile_id]) && !isset($existing_transcodes[$profile_id])) {
          continue;
        }

        // Is default profile?
        $default = $profile_id == $default_profile;

        // Exists as transcode? Put checked on.
        // If we are during upload, then we expect the defaults to exist (job
        // is running).
        $checked_transcode = isset($existing_transcodes[$profile_id]) || ($is_upload && $default ? TRUE : FALSE);

        // Disable the checkbox only when default and transcode is available.
        $disabled = $default && $checked_transcode;

        // Is downloadable?
        $checked_downloadable = $checked_transcode && isset($is_downloadable[$profile_id]);

        // Is default profile?
        $options[$profile_id]['default'] = $default;
        $options[$profile_id]['disabled'] = $disabled;
        $options[$profile_id]['checked_transcode'] = $checked_transcode;
        $options[$profile_id]['checked_downloadable'] = $checked_downloadable;

        $options[$profile_id]['title'] = (string) $profile->profile;
        $options[$profile_id]['profile_id'] = (int) $profile->profile_id;
      }
    }

    $form['transcode']['table'] = array(
      '#theme' => 'mediamosa_sb_profile_select',
      '#options' => $options,
      '#default_value' => reset($options),
    );

    return $form;
  }

  /**
   * The still form.
   *
   * @param $values
   *   The values of the form.
   *
   * @return
   *   Returns the form array.
   */
  static protected function media_still_form($values) {
    $form = array();

    $form['still'] = array(
      '#type' => 'fieldset',
      '#title' => t('Still generation for this video'),
    );

    $form['still']['still_start_time'] = array(
      '#type' => 'textfield',
      '#title' => t('Time for still generation'),
      '#required' => FALSE,
      '#size' => 5,
      '#default_value' => isset($values['still_start_time']) ? $values['still_start_time'] : self::DEFAULT_START_TIME_STILL_FORM,
      '#description' => t('Enter the time in MM:SS (minutes:seconds) format for the frame on which the still wil be generated'),
    );

    return $form;
  }
}
