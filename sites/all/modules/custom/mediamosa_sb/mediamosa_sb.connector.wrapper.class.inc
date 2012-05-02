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
 * Our connector class.
 */
class MediaMosaSbConnectorWrapper extends MediaMosaCkConnectorWrapper {

  /**
   * Get the asset.
   *
   * @see parent::get_asset()
   */
  static public function get_asset($asset_id, array $options = array(), $cached = TRUE, $reset = FALSE) {
    try {
      return parent::get_asset($asset_id, $options, $cached, $reset);
    }
    catch(Exception $e) {
      return FALSE;
    }
  }

  /**
   * Return with array of the users collection.
   *
   * @param $user_id
   *   The ID of the user from which to get the collections.
   *
   * @todo:
   *   Limit is 200.
   */
  static public function get_my_collections_for_options($user_id = '') {

    // No user_id provided, use session.
    if (empty($user_id)) {
      // Get the user ID.
      $user_id = mediamosa_ck::session_user_id();
    }

    $options = array(
      'offset' => 0,
      'limit' => 200, // Get max allowed per rest call.
      'cql' => strtr('owner_id == "^!user_id^"', array('!user_id' => $user_id)),
    );

    // Get it.
    $collections = array();
    $xml = parent::search_collection($options);
    if ($xml) {
      foreach ($xml->xpath('items/item') as $collection) {
        $collections[(string) $collection->coll_id] = (string) $collection->title;
      }
    }

    return $collections;
  }

  /**
   * Get the collections in which provided asset is present of current user.
   *
   * @todo:
   *   Limit is 200.
   */
  static public function get_my_asset_collections($asset_id, $user_id = '') {
    // No user_id provided, use session.
    if (empty($user_id)) {
      // Get the user ID.
      $user_id = mediamosa_ck::session_user_id();
    }

    $options = array(
      'offset' => 0,
      'limit' => 200, // Get max allowed per rest call.
      'asset_id' => $asset_id,
      'cql' => strtr('owner_id == "^!user_id^"', array('!user_id' => $user_id)),
    );

    // Get it.
    $collections = array();
    $xml = parent::search_collection($options);
    if ($xml) {
      foreach ($xml->xpath('items/item') as $collection) {
        $collections[(string) $collection->coll_id] = (string) $collection->title;
      }
    }

    return $collections;
  }

  /**
   * Get the access of a mediafile.
   *
   * @param $mediafile_id
   *   The ID of the mediafile.
   * @param $user_id
   *   The ID of the user / owner of the mediafile.
   *
   * @see parent::get_access_control()
   */
  static public function get_access_control($mediafile_id, $user_id = '') {

    // No user_id provided, use session.
    if (empty($user_id)) {
      // Get the user ID.
      $user_id = mediamosa_ck::session_user_id();
    }

    // Access array.
    $access = array(
      'acl_domain' => array(),
      'acl_realm' => array(),
      'acl_user' => array(),
    );

    // Get access.
    $xml = parent::get_access_control($mediafile_id, $user_id);

    if ($xml) {
      foreach ($xml->xpath('items/item/acl_domain') as $item) {
        $access['acl_domain'][] = (string) $item;
      }
      foreach ($xml->xpath('items/item/acl_realm') as $item) {
        $access['acl_realm'][] = (string) $item;
      }
      foreach ($xml->xpath('items/item/acl_user') as $item) {
        $access['acl_user'][] = (string) $item;
      }
    }

    return $access;
  }

  // ---------------------------------------------- Overrides for Drupal rights.
  /**
   * Update the metadata for given asset ID.
   *
   * @param $asset_id
   *   The ID of the asset.
   * @param $options
   *   The options for the REST call.
   */
  static public function update_metadata($asset_id, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $options += array('user_id' => mediamosa_sb::get_owner_asset($asset_id));
    }

    return parent::update_metadata($asset_id, $options);
  }

  /**
   * Update a asset.
   *
   * @param $options
   *   The options for the asset.
   *
   * @return type
   */
  static public function update_asset($asset_id, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $options += array('user_id' => mediamosa_sb::get_owner_asset($asset_id));
    }

    return parent::update_asset($asset_id, $options);
  }

  /**
   * Update a mediafile.
   *
   * @param $options
   *   The options for the mediafile.
   *
   * @return type
   */
  static public function update_mediafile_asset($asset_id, $mediafile_id, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $options += array('user_id' => mediamosa_sb::get_owner_mediafile($mediafile_id));
    }

    return parent::update_mediafile($mediafile_id, $options);
  }

  /**
   * Update a collection.
   *
   * @param $options
   *   The options for the collection.
   *   - title
   *     The title of the collection.
   *   - description
   *     The description of the collection.
   *
   * @return type
   */
  static public function update_collection($coll_id, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_collection_edit($coll_id)) {
      $options += array('user_id' => mediamosa_sb::get_owner_collection($coll_id));
    }

    return parent::update_collection($coll_id, $options);
  }

  /**
   * Apply access limitations to mediafile.
   *
   * @param $asset_id
   *   The asset ID.
   * @param $mediafile_id
   *   The ID of the mediafile.
   * @param $user_id
   *   The owner of the mediafile.
   * @param $acl_domain_realm
   *   A string with domains and realms. Function is responsible to determine
   *   correct type for each element.
   * @param $acl_user_id
   *   A string with users. This can be anything as MediaMosa does not care
   *   about the content of a user_id.
   */
  static public function set_access_control_asset($asset_id, $mediafile_id, $user_id, $acl_domain_realm, $acl_user_id = '') {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $user_id = mediamosa_sb::get_owner_mediafile($mediafile_id);
    }

    return parent::set_access_control($mediafile_id, $user_id, $acl_domain_realm, $acl_user_id);
  }

  /**
   * Delete still(s) from a asset.
   *
   * @param $asset_id
   *   The asset ID.
   * @param $user_id
   *   The user ID.
   * @param $options
   *   The REST call options.
   */
  static public function delete_asset_still($asset_id, $user_id, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $user_id = mediamosa_sb::get_owner_asset($asset_id);
    }

    return parent::delete_asset_still($asset_id, $user_id, $options);
  }

  /**
   * Mediafile delete.
   *
    * @param $asset_id
   *   The asset ID.
   * @param $mediafile_id
   *   The ID of the mediafile.
   * @param $user_id
   *   The ID of the user, must be owner.
   *
   * @return
   *   Returns TRUE when delete was successful.
   */
  static public function delete_mediafile_asset($asset_id, $mediafile_id, $user_id) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $user_id = mediamosa_sb::get_owner_asset($asset_id);
    }

    return parent::delete_mediafile($mediafile_id, $user_id);
  }

  /**
   * Delete a collection.
   *
   * @param $coll_id
   *   The ID of the collection.
   * @param $user_id
   *   The ID of the user, must be owner.
   * @param $options
   *   Array of options.
   *
   * @return
   *   Returns TRUE when delete was successful.
   */
  static public function delete_collection($coll_id, $user_id, $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($coll_id)) {
      $user_id = mediamosa_sb::get_owner_collection($coll_id);
    }

    return parent::delete_collection($coll_id, $user_id, $options);
  }

  /**
   * Remove the relation between collection and assets.
   *
   * @param $coll_id
   *   The collection ID.
   * @param $user_id
   *   The user ID.
   * @param $asset_ids
   *   Array with asset_ids to remove from collection.
   */
  static public function delete_collection_asset_relations($coll_id, $user_id, array $asset_ids, array $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($coll_id)) {
      $user_id = mediamosa_sb::get_owner_collection($coll_id);
    }

    return parent::delete_collection_asset_relations($coll_id, $user_id, $asset_ids, $options);
  }

  /**
   * Create a still for specific mediafile.
   *
   * @param $asset_id
   *   The asset ID.
   * @param $mediafile_id
   *   The mediafile ID.
   * @param $user_id
   *   The owner of the mediafile.
   * @param $data
   *   Array with all the still parameters.
   *
   * @return mediamosa_connector_response
   *   Returns FALSE when failure or mediamosa_connector_response.
   */
  static public function create_mediafile_still_asset($asset_id, $mediafile_id, $user_id, $data = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $user_id = mediamosa_sb::get_owner_mediafile($mediafile_id);
    }

    return parent::create_mediafile_still($mediafile_id, $user_id, $data);
  }

  /**
   * Create transcoded mediafile.
   *
   * @param $mediafile_id
   *   The mediafile ID of the original.
   * @param $user_id
   *   The owner of the asset.
   * @param $options
   *   The options for the REST call.
   *
   * @return
   *   Returns FALSE for failure.
   */
  static public function create_transcode_asset($asset_id, $mediafile_id, $options = array()) {
    // Need edit right.
    if (mediamosa_sb::access_asset_edit($asset_id)) {
      $options['user_id'] = mediamosa_sb::get_owner_mediafile($mediafile_id);
    }

    return parent::create_transcode($mediafile_id, $options);
  }
}
