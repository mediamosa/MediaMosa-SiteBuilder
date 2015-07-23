<?php
/**
 * @file
 * Simple static class to hold form functions, so we keep our inc files cleaner
 * and this is autoloaded.
 */

class mediamosa_sb_asset_forms {

  const DEFAULT_START_TIME_STILL_FORM = '00:00';

  /**
   * Return the default value.
   */
  static protected function default_value($values, $name, $default = '') {
    return !isset($values[$name]) ? $default : $values[$name];
  }

  /**
   * The info form.
   *
   * @param array $values
   *   The values of the form.
   * @param string $asset_id
   *   The ID of the asset.
   *
   * @return array
   *   Returns the form array.
   */
  static public function info_form($values, &$form_state, $asset_id) {
    $form = array();

    // Add basic information form.
    $form['bacicinfo'] = self::info_basicinfo_form($values, $asset_id);

    // Add collections form.
    $form['collections'] = self::info_collections_form($values, $asset_id);

    // Add metadata form.
    $form['metadata'] = self::info_metadata_form($values, $form_state);

    return $form;
  }

  /**
   * The metadata form.
   *
   * @param array $values
   *   The values of the form.
   *
   * @return array
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
        '#size' => 5,
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
   * @param array $values
   *   The values of the form.
   *
   * @return array
   *   Returns the form array.
   */
  static protected function info_metadata_form($values, &$form_state) {
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

    $form['additional']['dc'] += static::create_multivalue_field('dc_type', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_format', $values, $form_state);

    // Language can only have a single value
    $form['additional']['dc']['dc_language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#required' => FALSE,
      '#description' => t('The language of the resource'),
      '#options'  => mediamosa_sb::get_metdata_languages_options(),
      '#default_value' => self::default_value($values, 'dc_language'),
    );

    $form['additional']['dc'] += static::create_multivalue_field('dc_creator', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_publisher', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_subject', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_date', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_identifier', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_source', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_relation', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_coverage_temporal', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_coverage_spatial', $values, $form_state);

    $form['additional']['dc'] += static::create_multivalue_field('dc_rights', $values, $form_state);

    $form['additional']['qdc'] = array(
      '#type' => 'fieldset',
      '#title' => t('Qualified Dublin core'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_title_alternative', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_description_abstract', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_created', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_issued', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_hasformat', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_isformatof', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_format_medium', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_format_extent', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_license', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_rightsholder', $values, $form_state);

    $form['additional']['qdc'] += static::create_multivalue_field('qdc_isreferencedby', $values, $form_state);

    if (variable_get('mediamosa_sb_asset_czp', FALSE)) {
      $form['additional']['czp'] = array(
        '#type' => 'fieldset',
        '#title' => t('Leerobject'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['additional']['czp']['czp_beschrijving'] = array(
        '#type' => 'textarea',
        '#title' => t('Beschrijving'),
        '#required' => FALSE,
        '#default_value' => self::default_value($values, 'czp_beschrijving'),
      );

      $form['additional']['czp'] += static::create_multivalue_field('czp_sleutelwoord', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_taal', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_soort_leermateriaal', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_context', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_beoogde_leeftijdsgroep', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_beoogde_eindgebruiker', $values, $form_state);
      $form['additional']['czp'] += static::create_multivalue_field('czp_classificatie', $values, $form_state);
    }

    return $form;
  }

  public static function create_multivalue_field($name, $values, &$form_state) {
    $default_values = array();
    if (isset($values[$name])) {
      if (is_array($values[$name])) {
        $default_values = $values[$name];
      } else {
        $default_values[] = $values[$name];
      }
    }

    $field = array();
    $field[$name] = array(
      '#prefix' => '<div id="form-multivalue-'.$name.'-wrapper" class="form-multivalue-wrapper">',
      '#suffix' => '</div>',
      '#tree' => TRUE,
    );

    if (empty($form_state[$name.'_num'])) {
      $form_state[$name.'_num'] = count($default_values) ?: 1;
    }

    for ($i = 0; $i < $form_state[$name.'_num']; $i++) {
      $field[$name][$i] = array();
      $field[$name][$i] += static::multivalue_field_properties($name);
      // only the first field must have the title
      if ($i != 0) {
        unset($field[$name][$i]['#title']);
        $field[$name][$i]['#title'] = '&nbsp;';
      }
      if ($i != $form_state[$name.'_num']-1) {
        unset($field[$name][$i]['#description']);
      }
      if (isset($default_values[$i])) {
        $field[$name][$i]['#default_value'] = $default_values[$i];
      }
    }

    $field[$name.'_add'] = array(
      '#type' => 'submit',
      '#value' => '+',
      '#submit' => array('mediamosa_sb_asset_edit_form_add_field'),
      '#limit_validation_errors' => array(),
      '#name' => $name,
      '#ajax' => array(
        'callback' => 'mediamosa_sb_asset_edit_form_add_field_callback',
        'wrapper' => 'form-multivalue-'.$name.'-wrapper',
      ),
    );

    return $field;
  }

  protected static function multivalue_field_properties($name) {
    $properties = array(
      '#type' => 'textfield',
      '#required' => FALSE,
    );
    switch ($name) {
      case 'dc_type':
        $properties['#title'] = t('Type');
        $properties['#description'] = t('The nature or genre of the resource e.g. Image, MovingImage');
        break;

      case 'dc_format':
        $properties['#title'] = t('Format');
        $properties['#description'] = t('The file format, physical medium e.g. video, image');
        break;

      case 'dc_creator':
        $properties['#title'] = t('Creator');
        $properties['#description'] = t('Responsible for making the resource');
        break;

      case 'dc_publisher':
        $properties['#title'] = t('Publisher');
        $properties['#description'] = t('Responsible for making the resource available');
        break;

      case 'dc_subject':
        $properties['#title'] = t('Subject');
        $properties['#description'] = t('The topic of the resource');
        break;

      case 'dc_date':
        $properties['#title'] = t('Date');
        $properties['#description'] = t('Date of the resource');
        $properties['#type'] = 'date_popup';
        $properties['#date_format'] = 'Y-m-d';
        $properties['#size'] = 40;
        $properties['#date_label_position'] = 'within';
        break;

      case 'dc_identifier':
        $properties['#title'] = t('Identifier');
        $properties['#description'] = t('An unambiguous reference to the resource within a given context');
        break;

      case 'dc_source':
        $properties['#title'] = t('Source');
        $properties['#description'] = t('A related resource from which the described resource is derived');
        break;

      case 'dc_relation':
        $properties['#title'] = t('Relation');
        $properties['#description'] = t('A related resource from which the described resource is derived');
        break;

      case 'dc_coverage_temporal':
        $properties['#title'] = t('Temporal coverage');
        $properties['#description'] = t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant');
        break;

      case 'dc_coverage_spatial':
        $properties['#title'] = t('Spatial coverage');
        $properties['#description'] = t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant');
        break;

      case 'dc_rights':
        $properties['#title'] = t('Rights');
        $properties['#description'] = t('Information about rights held in and over the resource.');
        break;

      case 'qdc_title_alternative':
        $properties['#title'] = t('Alternative title');
        $properties['#description'] = t('Alternative title of the resource');
        break;

      case 'qdc_description_abstract':
        $properties['#title'] = t('Abstract description');
        $properties['#description'] = t('An abstract description of the resource');
        break;

      case 'qdc_hasformat':
        $properties['#title'] = t('Has format');
        $properties['#description'] = t('The described resource pre-existed the referenced resource');
        break;

      case 'qdc_isformatof':
        $properties['#title'] = t('Is format of');
        $properties['#description'] = t('The described resource is the same intellectual content of the referenced resource, but presented in another format');
        break;

      case 'qdc_format_medium':
        $properties['#title'] = t('Medium');
        $properties['#description'] = t('The material or physical carrier of the resource');
        break;

      case 'qdc_format_extent':
        $properties['#title'] = t('Extent');
        $properties['#description'] = t('The size or duration of the resource');
        break;

      case 'qdc_license':
        $properties['#title'] = t('License');
        $properties['#description'] = t('License of the resource');
        break;

      case 'qdc_rightsholder':
        $properties['#title'] = t('Rights');
        $properties['#description'] = t('Rights holder of the resource');
        break;

      case 'qdc_isreferencedby':
        $properties['#title'] = t('Is referenced by');
        $properties['#description'] = t('The described resource is referenced, cited, or otherwise pointed to by the referenced resource.');
        break;

      case 'qdc_created':
        $properties['#title'] = t('Created');
        $properties['#description'] = t('Date of creation of the resource.');
        $properties['#type'] = 'date_popup';
        $properties['#date_format'] = 'Y-m-d';
        $properties['#size'] = 40;
        $properties['#date_label_position'] = 'within';
        break;

      case 'qdc_issued':
        $properties['#title'] = t('Issued');
        $properties['#description'] = t('Date of formal issuance (e.g., publication) of the resource');
        $properties['#type'] = 'date_popup';
        $properties['#date_format'] = 'Y-m-d';
        $properties['#size'] = 40;
        $properties['#date_label_position'] = 'within';
        break;
    }
    return $properties;
  }

  /**
   * The access form.
   *
   * @param array $values
   *   The values of the form.
   *
   * @return array
   *   Returns the form array.
   */
  static public function access_form($values) {
    global $base_url;

    $form = array();

    // Add css.
    $form['#attached'] = array(
      'css' => array(
        'type' => 'file',
        'data' => drupal_get_path('module', 'mediamosa_sb') . '/mediamosa_sb.css',
      ),
    );

    // Protected.
    $protected = 'Open';
    if (!empty($values['acl_domain']) || !empty($values['acl_realm']) || !empty($values['acl_user'])) {
      $protected = 'Protected';
    }
    $form['protected'] = array(
      '#type' => 'fieldset',
      '#title' => t('Protection'),
    );
    $form['protected']['choose'] = array(
      '#type' => 'radios',
      '#options' => array(
        'Open' => 'Open, No protection.',
        'Protected' => 'Protected, you will need to provide access control information.',
      ),
      '#default_value' => $protected,
    );

    // Access Control.
    $form['control'] = array(
      '#type' => 'fieldset',
      '#title' => t('Access control'),
      '#states' => array(
        'visible' => array(
          ':input[name="choose"]' => array('value' => 'Protected'),
        ),
      ),
    );
    $form['control']['acl_domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Domain'),
      '#required' => FALSE,
      '#description' => t('Define which domains can view this asset. Enter more domains seperated by a comma. Example: "mediamosa.org, example.com"'),
      '#default_value' => self::default_value($values, 'acl_domain'),
    );
    $form['control']['acl_realm'] = array(
      '#type' => 'textfield',
      '#title' => t('By realm'),
      '#required' => FALSE,
      '#description' => t('Select wich registered users based on their e-mail realm have access to this asset. Every domain must start with an "@". Example: "@mediamosa.org, @example.com"'),
      '#default_value' => self::default_value($values, 'acl_realm'),
    );
    $form['control']['acl_user'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#title' => t('By email'),
      '#required' => FALSE,
      '#description' => t('Select which registered users based on their e-mail address have access to this asset. Example; info@mediamosa.org, name@example.com'),
      '#default_value' => self::default_value($values, 'acl_user'),
    );

    // License.
    $form['license'] = array(
      '#type' => 'fieldset',
      '#title' => t('License'),
      '#states' => array(
        'visible' => array(
          ':input[name="choose"]' => array('value' => 'Open'),
        ),
      ),
    );
    $img_path = $base_url . '/' . drupal_get_path('module', 'mediamosa_sb') . '/img/';
    $images = array(
      'CC BY (Attribution)' => '<img src="' . $img_path . 'cc-by.png" />',
      'CC BY-SA (Attribution-ShareAlike)' => '<img src="' . $img_path . 'cc-by-sa.png" />',
      'CC BY-ND (Attribution-NoDerivs)' => '<img src="' . $img_path . 'cc-by-nd.png" />',
      'CC BY-NC (Attribution-NonCommercial)' => '<img src="' . $img_path . 'cc-by-nc.png" />',
      'CC BY-NC-SA (Attribution-NonCommercial-ShareAlike)' => '<img src="' . $img_path . 'cc-by-nc-sa.png" />',
      'CC BY-NC-ND (Attribution-NonCommercial-NoDerivs)' => '<img src="' . $img_path . 'cc-by-nc-nd.png" />',
      '' => 'No license.',
    );
    $form['license']['license'] = array(
      '#type' => 'radios',
      '#description' => l(t('<img src="') . $img_path .  'cc-terms.png" />', 'http://creativecommons.nl/uitleg/', array('html' => TRUE, 'attributes' => array('target' => '_blank'))) .
      l(t('<img src="') . $base_url . '/misc/message-24-info.png" />', 'http://creativecommons.nl/uitleg/', array('html' => TRUE, 'attributes' => array('target' => '_blank'))),
      '#options' => $images,
      '#default_value' => self::default_value($values, 'license', ''),
    );

    // Visibility.
    $form['visibility'] = array(
      '#type' => 'fieldset',
      '#title' => t('Visibility'),
    );
    // is_visible = !isprivate.
    $form['visibility']['is_visible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Visible in lists'),
      '#description' => t('If checked, the media item will be visible on the frontpage (new/popular).'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'is_visible', TRUE),
    );

    $form['downloads'] = array(
      '#type' => 'fieldset',
      '#title' => t('Downloadable'),
      '#collapsible' => FALSE,
      '#collapsed' => TRUE,
      '#states' => array(
        'visible' => array(
          ':input[name="choose"]' => array('value' => 'Open'),
        ),
      ),
    );
    $form['downloads']['is_downloadable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Downloadable'),
      '#description' => t('If checked, the asset will be downloadable'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'is_downloadable', TRUE),
    );

    return $form;
  }

  /**
   * Implements hook_form_validate().
   */
  static public function access_form_validate($form, $form_state) {

    if ($form_state['values']['choose'] == 'Protected') {
      if (($form_state['values']['acl_domain'] == '') &&
        ($form_state['values']['acl_realm'] == '') &&
        ($form_state['values']['acl_user'] == '')) {
        form_set_error('acl_domain', 'When choosing protected, at least one access control must be given.');
      }
    }
  }

  /**
   * The Transcode form.
   *
   * @param array $values
   *   The values of the form.
   * @param bool $is_upload
   *   Form is used during upload.
   *
   * @return array
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
   * @param array $values
   *   The values of the form.
   *
   * @return array
   *   Returns the form array.
   */
  static protected function media_transcoding_form($values, $is_upload) {
    $form = array();

    // The asset ID.
    $asset_id = $values['asset_id'];

    $form['transcode'] = array(
      '#type' => 'fieldset',
      '#title' => t('Currently active media profiles'),
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

        // Is allowed as profile?
        // If a mediafile exists, we ignore the allowed profile.
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
   * @param array $values
   *   The values of the form.
   *
   * @return array
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
