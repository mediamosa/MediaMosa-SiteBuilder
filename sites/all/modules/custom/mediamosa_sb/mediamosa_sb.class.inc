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
 * Simple static class for main functions of MediaMosa Site Builder.
 */
class mediamosa_sb {

  // ------------------------------------------------------------------- Consts
  // Permissions.
  const MEDIAMOSA_SB_PERMISSION_EDIT_ASSETS = 'mediamosa-sb edit assets';
  const MEDIAMOSA_SB_PERMISSION_DELETE_ASSETS = 'mediamosa-sb delete assets';
  const MEDIAMOSA_SB_PERMISSION_EDIT_COLLECTIONS = 'mediamosa-sb edit collections';
  const MEDIAMOSA_SB_PERMISSION_DELETE_COLLECTIONS = 'mediamosa-sb delete collections';
  const MEDIAMOSA_SB_PERMISSION_ALTER_FEATURED = 'mediamosa-sb alter featured';

  // ---------------------------------------------------------------- Functions.
  /**
   * Return the URL for detail page of asset.
   *
   * @param type $asset_id
   * @return type
   */
  static public function get_asset_detail_url($asset_id) {
    return 'asset/detail/' . $asset_id;
  }

  /**
   * Return the URL for detail page of collection.
   *
   * @param type $asset_id
   * @return type
   */
  static public function get_collection_detail_url($coll_id) {
    return 'collection/detail/' . $coll_id;
  }

  /**
   * Checks if current user is owner of the asset.
   *
   * @param $mixed
   *   Object or asset ID.
   *
   * @return
   *   Returns TRUE when current user is owner of asset, or FALSE.
   */
  static public function is_owner_asset($mixed) {
    // Get the owner.
    $user_id = self::get_owner_asset($mixed);

    // Is owner?
    return (!empty($user_id) && $user_id == mediamosa_ck::session_user_id());
  }

  /**
   * Gets the owner of the asset.
   *
   * @param $mixed
   *   Object or asset ID.
   *
   * @return
   *   Returns user_id, or FALSE.
   */
  static public function get_owner_asset($mixed) {

    if (is_object($mixed)) {
      $asset = $mixed;
    }
    else {
      // Get the asset cached.
      $asset = MediaMosaSbConnectorWrapper::get_asset((string) $mixed, array('show_stills' => FALSE, 'show_collections' => FALSE));
    }

    // Check if we are owner of the asset.
    if (!empty($asset)) {
      if (!empty($asset->items->item->owner_id)) {
        return (string) $asset->items->item->owner_id;
      }
      if (!empty($asset->owner_id)) {
        return (string) $asset->owner_id;
      }
    }

    return FALSE;
  }

  /**
   * Gets the owner of the asset.
   *
   * @param $mixed
   *   Object or mediafile ID.
   *
   * @return
   *   Returns user_id, or FALSE.
   */
  static public function get_owner_mediafile($mixed) {

    if (is_object($mixed)) {
      $mediafile = $mixed;
    }
    else {
      // Get the asset cached.
      $mediafile = MediaMosaSbConnectorWrapper::get_mediafile((string) $mixed, array('show_stills' => FALSE));
    }

    // Check if we are owner of the asset.
    if (!empty($mediafile)) {
      if (!empty($mediafile->items->item->owner_id)) {
        return (string) $mediafile->items->item->owner_id;
      }
      if (!empty($mediafile->owner_id)) {
        return (string) $mediafile->owner_id;
      }
    }

    return FALSE;
  }

  /**
   * Checks if current user is owner of the collection.
   *
   * @param $mixed
   *   Object or collection ID.
   *
   * @return
   *   Returns TRUE when current user is owner of collection, or FALSE.
   */
  static public function is_owner_collection($mixed) {
    // Get the owner.
    $user_id = self::get_owner_collection($mixed);

    // Is owner?
    return (!empty($user_id) && $user_id == mediamosa_ck::session_user_id());
  }

  /**
   * Get the owner of the collection.
   *
   * @param $mixed
   *   Object or collection ID.
   *
   * @return
   *   Returns the owner of collection, or FALSE.
   */
  static public function get_owner_collection($mixed) {

    if (is_object($mixed)) {
      $collection = $mixed;
    }
    else {
     // Get the collection cached.
      $collection = MediaMosaSbConnectorWrapper::get_collection((string) $mixed);
    }

    // Check if we are owner of the collection.
    if (!empty($collection)) {
      if (!empty($collection->items->item->owner_id)) {
        return (string) $collection->items->item->owner_id;
      }
      if (!empty($collection->owner_id)) {
        return (string) $collection->owner_id;
      }
    }

    return FALSE;
  }

  /**
   * Access function for editing asset.
   *
   * @param $mixed
   *   Object or asset ID.
   *
   * @return
   *   Returns TRUE when current user can edit asset, or FALSE.
   */
  static public function access_asset_edit($mixed) {

    // Check Drupal access.
    if (user_access(mediamosa_sb::MEDIAMOSA_SB_PERMISSION_EDIT_ASSETS)) {
      return TRUE;
    }

    return mediamosa_sb::is_owner_asset($mixed);
  }

  /**
   * Access function for deleting asset.
   *
   * @param $mixed
   *   Object or asset ID.
   *
   * @return
   *   Returns TRUE when current user can delete asset, or FALSE.
   */
  static public function access_asset_delete($mixed) {

    // Check Drupal access.
    if (user_access(mediamosa_sb::MEDIAMOSA_SB_PERMISSION_DELETE_ASSETS)) {
      return TRUE;
    }

    return mediamosa_sb::is_owner_asset($mixed);
  }

  /**
   * Access function for editing collection.
   *
   * @param $mixed
   *   Object or collection ID.
   *
   * @return
   *   Returns TRUE when current user can edit collection, or FALSE.
   */
  static public function access_collection_edit($mixed) {
    // Check Drupal access.
    if (user_access(mediamosa_sb::MEDIAMOSA_SB_PERMISSION_EDIT_COLLECTIONS)) {
      return TRUE;
    }

    return mediamosa_sb::is_owner_collection($mixed);
  }

  /**
   * Access function for deleting collection.
   *
   * @param $mixed
   *   Object or collection ID.
   *
   * @return
   *   Returns TRUE when current user is owner of collection, or FALSE.
   */
  static public function access_collection_delete($mixed) {
    // Check Drupal access.
    if (user_access(mediamosa_sb::MEDIAMOSA_SB_PERMISSION_DELETE_COLLECTIONS)) {
      return TRUE;
    }

    return mediamosa_sb::is_owner_collection($mixed);
  }

  /**
   * Returns the title of the asset using the metadata.
   *
   * @param SimpleXMLElement $asset
   *   The asset in SimpleXMLElement.
   *
   * @return
   *   The title or default.
   *
   * @see mediamosa_ck::get_asset_title()
   */
  static public function get_asset_title($asset) {
    return mediamosa_ck::get_asset_title($asset);
  }

  /**
   * This wrapper is indended when in the future if we want to tell the user
   * that something went wrong and log the problem. We might want to make
   * options for the admin in which we log the error, but will not bore the user
   * with the error.
   */
  static public function watchdog_error($message, array $variables = array()) {
    // Call our CK version.
    mediamosa_ck::watchdog_error($message, $variables);
  }

  /**
   * Return the metadata languages.
   *
   * @return
   *   Return an array with languages.
   */
  static public function get_metdata_languages_options() {
    return array(
      '' => t('<none>'),
      'ab' => t('Abkhaz'),
      'aa' => t('Afar'),
      'af' => t('Afrikaans'),
      'ak' => t('Akan'),
      'sq' => t('Albanian'),
      'am' => t('Amharic'),
      'ar' => t('Arabic'),
      'an' => t('Aragonese'),
      'hy' => t('Armenian'),
      'as' => t('Assamese'),
      'av' => t('Avaric'),
      'ae' => t('Avestan'),
      'ay' => t('Aymara'),
      'az' => t('Azerbaijani'),
      'bm' => t('Bambara'),
      'ba' => t('Bashkir'),
      'eu' => t('Basque'),
      'be' => t('Belarusian'),
      'bn' => t('Bengali'),
      'bh' => t('Bihari'),
      'bi' => t('Bislama'),
      'bs' => t('Bosnian'),
      'br' => t('Breton'),
      'bg' => t('Bulgarian'),
      'my' => t('Burmese'),
      'ca' => t('Catalan'),
      'ch' => t('Chamorro'),
      'ce' => t('Chechen'),
      'ny' => t('Chichewa'),
      'zh' => t('Chinese'),
      'cv' => t('Chuvash'),
      'kw' => t('Cornish'),
      'co' => t('Corsican'),
      'cr' => t('Cree'),
      'hr' => t('Croatian'),
      'cs' => t('Czech'),
      'da' => t('Danish'),
      'dv' => t('Divehi'),
      'nl' => t('Dutch'),
      'dz' => t('Dzongkha'),
      'en' => t('English'),
      'eo' => t('Esperanto'),
      'et' => t('Estonian'),
      'ee' => t('Ewe'),
      'fo' => t('Faroese'),
      'fj' => t('Fijian'),
      'fi' => t('Finnish'),
      'fr' => t('French'),
      'ff' => t('Fula'),
      'gl' => t('Galician'),
      'ka' => t('Georgian'),
      'de' => t('German'),
      'el' => t('Greek'),
      'gn' => t('Guaraní'),
      'gu' => t('Gujarati'),
      'ht' => t('Haitian'),
      'ha' => t('Hausa'),
      'he' => t('Hebrew'),
      'hz' => t('Herero'),
      'hi' => t('Hindi'),
      'ho' => t('Hiri Motu'),
      'hu' => t('Hungarian'),
      'ia' => t('Interlingua'),
      'id' => t('Indonesian'),
      'ie' => t('Interlingue'),
      'ga' => t('Irish'),
      'ig' => t('Igbo'),
      'ik' => t('Inupiaq'),
      'io' => t('Ido'),
      'is' => t('Icelandic'),
      'it' => t('Italian'),
      'iu' => t('Inuktitut'),
      'ja' => t('Japanese'),
      'jv' => t('Javanese'),
      'kl' => t('Kalaallisut'),
      'kn' => t('Kannada'),
      'kr' => t('Kanuri'),
      'ks' => t('Kashmiri'),
      'kk' => t('Kazakh'),
      'km' => t('Khmer'),
      'ki' => t('Kikuyu'),
      'rw' => t('Kinyarwanda'),
      'ky' => t('Kirghiz'),
      'kv' => t('Komi'),
      'kg' => t('Kongo'),
      'ko' => t('Korean'),
      'ku' => t('Kurdish'),
      'kj' => t('Kwanyama'),
      'la' => t('Latin'),
      'lb' => t('Luxembourgish'),
      'lg' => t('Luganda'),
      'li' => t('Limburgish'),
      'ln' => t('Lingala'),
      'lo' => t('Lao'),
      'lt' => t('Lithuanian'),
      'lu' => t('Luba-Katanga'),
      'lv' => t('Latvian'),
      'gv' => t('Manx'),
      'mk' => t('Macedonian'),
      'mg' => t('Malagasy'),
      'ms' => t('Malay'),
      'ml' => t('Malayalam'),
      'mt' => t('Maltese'),
      'mr' => t('Marathi'),
      'mh' => t('Marshallese'),
      'mn' => t('Mongolian'),
      'na' => t('Nauru'),
      'nv' => t('Navajo'),
      'nb' => t('Norwegian Bokmål'),
      'nd' => t('North Ndebele'),
      'ne' => t('Nepali'),
      'ng' => t('Ndonga'),
      'nn' => t('Norwegian Nynorsk'),
      'no' => t('Norwegian'),
      'ii' => t('Nuosu'),
      'nr' => t('South Ndebele'),
      'oc' => t('Occitan'),
      'oj' => t('Ojibwe'),
      'om' => t('Oromo'),
      'or' => t('Oriya'),
      'os' => t('Ossetian'),
      'pa' => t('Panjabi'),
      'fa' => t('Persian'),
      'pl' => t('Polish'),
      'ps' => t('Pashto'),
      'pt' => t('Portuguese'),
      'qu' => t('Quechua'),
      'rm' => t('Romansh'),
      'rn' => t('Kirundi'),
      'ro' => t('Romanian'),
      'ru' => t('Russian'),
      'sa' => t('Sanskrit'),
      'sc' => t('Sardinian'),
      'sd' => t('Sindhi'),
      'se' => t('Northern Sami'),
      'sm' => t('Samoan'),
      'sg' => t('Sango'),
      'sr' => t('Serbian'),
      'gd' => t('Gaelic'),
      'sn' => t('Shona'),
      'si' => t('Sinhala'),
      'sk' => t('Slovak'),
      'sl' => t('Slovene'),
      'so' => t('Somali'),
      'st' => t('Southern Sotho'),
      'es' => t('Spanish'),
      'su' => t('Sundanese'),
      'sw' => t('Swahili'),
      'ss' => t('Swati'),
      'sv' => t('Swedish'),
      'ta' => t('Tamil'),
      'te' => t('Telugu'),
      'tg' => t('Tajik'),
      'th' => t('Thai'),
      'ti' => t('Tigrinya'),
      'bo' => t('Tibetan'),
      'tk' => t('Turkmen'),
      'tl' => t('Tagalog'),
      'tn' => t('Tswana'),
      'to' => t('Tonga'),
      'tr' => t('Turkish'),
      'ts' => t('Tsonga'),
      'tt' => t('Tatar'),
      'tw' => t('Twi'),
      'ty' => t('Tahitian'),
      'ug' => t('Uighur'),
      'uk' => t('Ukrainian'),
      'ur' => t('Urdu'),
      'uz' => t('Uzbek'),
      've' => t('Venda'),
      'vi' => t('Vietnamese'),
      'vo' => t('Volapük'),
      'wa' => t('Walloon'),
      'cy' => t('Welsh'),
      'wo' => t('Wolof'),
      'fy' => t('Western Frisian'),
      'xh' => t('Xhosa'),
      'yi' => t('Yiddish'),
      'yo' => t('Yoruba'),
      'za' => t('Zhuang, Chuang'),
      'zu' => t('Zulu')
     );
  }

  static public function submit_info($values, $asset_id) {
    // Submit the metadata.
    self::submit_info_metadata($values, $asset_id);

    // Submit the metadata.
    self::submit_info_collections($values, $asset_id);

    if (user_access('mediamosa_sb::MEDIAMOSA_SB_PERMISSION_ALTER_FEATURED')) {
      // Featured status.
      if (empty($values['asset_featured'])) {
        mediamosa_ck_views_rest_asset_featured::unset_featured_id($asset_id);
      }
      else {
        mediamosa_ck_views_rest_asset_featured::set_featured_id($asset_id);
      }
    }
  }

  /**
   * Submit the metadata from form submited fields.
   */
  static protected function submit_info_metadata($values, $asset_id) {
    // Options + metadata for write.
    $options = array('action' => 'replace');

    // Get the metadata def.
    $metadata_fields = mediamosa_ck::get_metadata_fields();

    foreach ($metadata_fields as $prefix => $metadata_field) {
      foreach ($metadata_field['fields'] as $name => $type) {
        // Build name.
        $prefixed_name = $prefix . '_' . $name;

        if (!isset($values[$prefixed_name]) || $values[$prefixed_name] === '') {
          continue;
        }

        // Set.
        $options[$name] = $values[$prefixed_name];
      }
    }

    // Do request.
    if (!MediaMosaSbConnectorWrapper::update_metadata($asset_id, $options)) {
      mediamosa_sb::watchdog_error('Unable to save metadata.');
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Submit the metadata from form submited fields.
   */
  static protected function submit_info_collections($values, $asset_id) {

    // Create array for easy lookup.
    $selected_collections = empty($values['mycollections']) ? array() : array_combine($values['mycollections'], $values['mycollections']);

    // Get the session user ID.
    $user_id = mediamosa_ck::session_user_id();

    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {

      // Although the owner of the asset might be the user that is in the
      // session, having the edit right here grants you to be the owner for now.
      $user_id = mediamosa_sb::get_owner_asset($asset_id);
    }

    // Get the collections in which now the asset is in.
    $my_asset_collections = MediaMosaSbConnectorWrapper::get_my_asset_collections($asset_id, $user_id);

    // Get my collections.
    $my_collections = MediaMosaSbConnectorWrapper::get_my_collections_for_options($user_id);

    // Loop through my collections
    foreach ($my_collections as $coll_id => $title) {
      // Is asset selected in this collection?
      if (isset($selected_collections[$coll_id])) {
        // If not already in collection, then create relation.
        if (!isset($my_asset_collections[$coll_id])) {
          MediaMosaSbConnectorWrapper::create_collection_asset_relations($coll_id, $user_id, array($asset_id));
        }
      }
      else {
        // Not selected, so has it got a collection relation?
        if (isset($my_asset_collections[$coll_id])) {
          // Remove from collection.
          MediaMosaSbConnectorWrapper::delete_collection_asset_relations($coll_id, $user_id, array($asset_id));
        }
      }
    }
  }

  /**
   * Set access on mediafile.
   *
   * @param $values
   *   The submited values.
   * @param $asset_id
   *   The asset ID.
   *
   * @return
   */
  static public function submit_access($values, $asset_id) {

    // Submit visiblilty.
    self::submit_access_visibility($values, $asset_id);

    // Submit ACL.
    self::submit_access_acl($values, $asset_id);
  }

  /**
   * Set access on mediafile.
   *
   * @param $values
   *   The submited values.
   * @param $asset_id
   *   The asset ID.
   *
   * @return
   */
  static protected function submit_access_visibility($values, $asset_id) {

    // Save state isprivate to asset.
    $options = array(
      'isprivate' => (isset($values['is_visible']) && !empty($values['is_visible']) ? FALSE : TRUE),
    );

    MediaMosaSbConnectorWrapper::update_asset($asset_id, $options);
  }

  /**
   * Set access on mediafile.
   *
   * @param $values
   *   The submited values.
   * @param $asset_id
   *   The asset ID.
   *
   * @return
   */
  static protected function submit_access_acl($values, $asset_id) {
    // Get the mediafiles.
    $mediafile_ids = MediaMosaSbConnectorWrapper::get_asset_mediafile_ids($asset_id);

    // Domains and realms.
    $acl_domain_realm = array();

    $acl_domain = trim($values['acl_domain']);
    $acl_realm = trim($values['acl_realm']);
    $acl_user = trim($values['acl_user']);

    if (!empty($acl_domain)) {
      $acl_domain_realm[] = $acl_domain;
    }
    if (!empty($acl_realm)) {
      $acl_domain_realm[] = $acl_realm;
    }
    $acl_domain_realm = implode(',', $acl_domain_realm);

    foreach ($mediafile_ids as $mediafile_id) {
      if (!MediaMosaSbConnectorWrapper::set_access_control_asset($asset_id, $mediafile_id, mediamosa_ck::session_user_id(), $acl_domain_realm, $acl_user)) {
        mediamosa_sb::watchdog_error('Unable to save access for mediafile with ID @mediafile_id.', array('@mediafile_id' => $mediafile_id));
      }
    }
  }

  /**
   * Validate form media.
   *
   * @param $values
   *   The post values.
   * @param $asset_id
   *   The asset ID.
   */
  static public function validate_media($values, $asset_id) {
    // Validate the still form.
    self::validate_media_still($values, $asset_id);
  }

  /**
   * Validate form still.
   *
   * @param $values
   *   The post values.
   * @param $asset_id
   *   The asset ID.
   */
  static protected function validate_media_still($values, $asset_id) {
    // Check if still time is correct format.
    if (!preg_match("/[0-9]{1,2}:[0-9]{1,2}/", $values['still_start_time'])) {
      form_set_error('still_start_time', t('Time for still generation must be in format MM:SS.'));
    }
  }


  /**
   * Submit the media form.
   *
   * @param $values
   *   The post values.
   * @param $asset_id
   *   The asset ID.
   */
  static public function submit_media($values, $asset_id, $is_upload = FALSE) {
    // Submit still.
    self::submit_media_still($values, $asset_id);

    // Submit media.
    self::submit_media_transcoding($values, $asset_id, $is_upload);
  }

  /**
   * Submit still.
   *
   * @param $values
   *   The post values.
   * @param $asset_id
   *   The asset ID.
   */
  static protected function submit_media_still($values, $asset_id) {
    // Get the original mediafile_id.
    $mediafile_id_original = MediaMosaSbConnectorWrapper::get_asset_mediafile_id_first_original($asset_id);

    // Check if we need to generate still.
    if ($values['still_start_time'] != mediamosa_sb_asset_forms::DEFAULT_START_TIME_STILL_FORM) {
      // Remove all stills first.
      MediaMosaSbConnectorWrapper::delete_asset_still($asset_id, mediamosa_ck::session_user_id());

      // Calc number of seconds.
      list($minutes, $seconds) = explode(':', $values['still_start_time'], 2);
      $data = array(
        'start_time' => ($minutes * 60) + $seconds,
      );

      // Create still.
      MediaMosaSbConnectorWrapper::create_mediafile_still_asset($asset_id, $mediafile_id_original, $data);
    }
  }

  /**
   * Submit transcodes.
   *
   * @param $values
   *   The post values.
   * @param $asset_id
   *   The asset ID.
   * @param $is_upload
   *   Is TRUE when called during the upload steps (need to ignore the default
   *   profile(s)).
   */
  static protected function submit_media_transcoding($values, $asset_id, $is_upload = FALSE) {
    // Get the original mediafile_id.
    $mediafile_id_original = MediaMosaSbConnectorWrapper::get_asset_mediafile_id_first_original($asset_id);

    // Get existing mediafiles transcodes.
    $current_used_transcode_profiles = MediaMosaSbConnectorWrapper::get_asset_current_used_transcode_profiles($asset_id);

    // Get the allowed profiles.
    $allowed_profiles = MediaMosaSbConnectorWrapper::get_allowed_transcode_profiles();

    // Get the default profiles, these can not be deleted or re-created.
    $default_profile = MediaMosaSbConnectorWrapper::get_default_transcode_profile();

    // List of the profile IDs now used.
    $active_profile_ids = array();

    if (!empty($mediafile_id_original)) {
      foreach ($values as $name => $on_status) {
        if (empty($on_status)) {
          continue;
        }

        if (drupal_substr($name, 0, strlen('active_')) == 'active_') {
          $profile_id = (int) drupal_substr($name, strlen('active_'));

          // When upload, do not create default profile transcodes. That is
          // already started in step 1.
          if ($is_upload && $default_profile == $profile_id) {
            continue;
          }

          // Add as checked.
          $active_profile_ids[$profile_id] = $profile_id;

          // If not in $current_used_transcode_profiles, then we can start it.
          if (empty($current_used_transcode_profiles[$profile_id])) {
            // Hmmm how to get this value into a not yet created transcode...
            $is_downloadable = !empty($values['downloadable_' . $profile_id]);

            // Start transcode job.
            $job_id = MediaMosaSbConnectorWrapper::create_transcode_asset($asset_id, $mediafile_id_original, array('profile_id' => $profile_id));
          }
        }
      }

      // Remove transcodes that are not checked (if they are found).
      foreach ($current_used_transcode_profiles as $profile_id => $profile) {
        if (isset($active_profile_ids[$profile_id])) {
          $is_downloadable = !empty($values['downloadable_' . $profile_id]);

          $options = array(
            'is_downloadable' => $is_downloadable,
            'transcode_inherits_acl' => TRUE,
          );

          // Is checked, so set download status.
          MediaMosaSbConnectorWrapper::update_mediafile_asset($asset_id, $profile['mediafile_id'], $options);
          continue;
        }

        // Not allowed, skip.
        if (!isset($allowed_profiles[$profile_id])) {
          continue;
        }

        // Can't delete the default profile.
        if ($default_profile == $profile_id) {
          continue;
        }

        // Remove transcode, for now we ignore the result.
        MediaMosaSbConnectorWrapper::delete_mediafile_asset($asset_id, $profile['mediafile_id'], mediamosa_ck::session_user_id());
      }
    }
  }
}
