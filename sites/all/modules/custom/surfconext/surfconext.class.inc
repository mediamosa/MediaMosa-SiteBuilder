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
 * The main class for surfconext module.
 */
class surfconext {
  /**
   * @var SimpleSAML_Auth_Simple
   *   The SimpleSAML_Auth_Simple object.
   */
  protected $simplesaml_auth_simple = NULL;

  /**
   * @var surfconext
   *   The SURFconext instance.
   */
  static protected $surfconext = NULL;

  // -------------------------------------------------------------- Constructor.
  function __construct() {
    // Will throw exceptions when failure.
    $this->init();
  }

  // ------------------------------------------------------- Functions (static).
  /**
   * Setup the surfconext object. Will initialize for usage and loads possible
   * session.
   *
   * @staticvar $surfconext
   *   The surfconext object.
   *
   * @return surfconext
   *   Returns object or FALSE.
   */
  static public function get() {
    // Enabled?
    if (!self::is_enabled()) {
      return FALSE;
    }

    // Create when needed.
    if (empty(self::$surfconext)) {
      try {
        self::$surfconext = new surfconext();
      }
      catch (Exception $e) {
        // Ignore.
      }
    }

    // Return the object.
    return self::$surfconext;
  }

  /**
   * Initialize the simplesaml library by activating its autoloader.
   */
  static public function autoload() {
    // Get the simplesaml library location.
    $basedir = self::get_simplesaml_basedir();

    // Check if file exists.
    if (file_exists($basedir . '/lib/_autoload.php')) {
      // Autoload class.
      require_once($basedir . '/lib/_autoload.php');
      return TRUE;
    }

    return FALSE;
  }
  /**
   * For debug message logging.
   *
   * @param $message
   *   The message to store in the log. Keep $message translatable
   *   by not concatenating dynamic values into it! Variables in the
   *   message should be added by using placeholder strings alongside
   *   the variables argument to declare the value of the placeholders.
   *   See t() for documentation on how $message and $variables interact.
   * @param $variables
   *   Array of variables to replace in the message on display or
   *   NULL if message is already translated or not possible to
   *   translate.
   */
  static public function debug($message, $variables = array()) {
    watchdog('surfconext', $message, $variables, WATCHDOG_DEBUG);
  }

  /**
   * For normal (watchdog) logging.
   *
   * @param $message
   *   The message to store in the log. Keep $message translatable
   *   by not concatenating dynamic values into it! Variables in the
   *   message should be added by using placeholder strings alongside
   *   the variables argument to declare the value of the placeholders.
   *   See t() for documentation on how $message and $variables interact.
   * @param $variables
   *   Array of variables to replace in the message on display or
   *   NULL if message is already translated or not possible to
   *   translate.
   */
  static public function log($message, $variables = array(), $severity = WATCHDOG_NOTICE) {
    watchdog('surfconext', $message, $variables, $severity);
  }

  /**
   * Return the URL of the metadata IDP provider.
   *
   * @return
   *   URL of the metadata IDP provider.
   */
  static public function get_surfconext_metadata_idp_url() {
    return variable_get('surfconext_metadata_idp_url', 'https://engine.surfconext.nl/authentication/idp/metadata');
  }

  /**
   * Return the location of the metadata IDP provider file.
   *
   * @return
   *   The location of the processed file metadata IDP provider.
   */
  static public function get_surfconext_metadata_idp_filename() {
    return variable_get('surfconext_metadata_idp_filename', 'private://saml20-idp-remote.php');
  }

  /**
   * Return the simpleSAML PHP library location.
   *
   * @return
   *   Location of the simpleSAML PHP library.
   */
  static public function get_simplesaml_basedir() {
    return variable_get('surfconext_simplesaml_basedir', '/var/simplesamlphp');
  }

  /**
   * Return the Auth soure type needed for simpleSAML.
   *
   * @return
   *   The simpleSAML source.
   */
  static public function get_authsource() {
    return variable_get('surfconext_authsource', 'default-sp');
  }

  /**
   * Return with the attribute name for the unique name.
   *
   * @return
   *   The name of the unique name.
   */
  static public function get_attribute_name_unique_id() {
    return variable_get('surfconext_attribute_name_unique_id', 'urn:mace:dir:attribute-def:eduPersonPrincipalName');
  }

  /**
   * Return with the attribute name for the unique name.
   *
   * @return
   *   The name of the unique name.
   */
  static public function get_attribute_name_mail() {
    return variable_get('surfconext_attribute_name_mail', 'urn:mace:dir:attribute-def:eduPersonPrincipalName');
  }

  /**
   * Return is the user is allowed to use Drupal login.
   *
   * @return
   *   TRUE when Drupal login is allowed.
   */
  static public function allow_drupal_login() {
    return variable_get('surfconext_allow_drupal_login', TRUE);
  }

  /**
   * Return is the users that are allowed to use Drupal login.
   *
   * @return
   *   TRUE when Drupal login is allowed.
   */
  static public function allow_drupal_login_users() {
    return variable_get('surfconext_allow_drupal_login_users', '');
  }

  /**
   * Returns if SURFconext is activated.
   *
   * In most cases its better to use get(), unless you don't need to use the
   * SURFconext. The get() function will return FALSE when not enabled (or
   * something is wrong).
   *
   * @return
   *   Returns TRUE when enabled, FALSE when not.
   */
  static public function is_enabled() {
    return variable_get('surfconext_enabled') ? TRUE : FALSE;
  }

  /**
   * Logout the Drupal session. Code copied from user_logout() in
   * user.pages.inc.
   *
   * @deadend
   *   Will never return from this function.
   */
  static public function user_logout() {
    global $user;

    watchdog('user', 'Session closed for %name.', array('%name' => $user->name));

    module_invoke_all('user_logout', $user);

    // Destroy the current session, and reset $user to the anonymous user.
    session_destroy();

    drupal_goto();
  }

  /**
   * Initialize SURFconext by loading the XML from the IDP url.
   */
  static public function cron_surfconext() {
    // Check if we need to update.
    $last_update = variable_get('surfconext_metadata_ipd_last_update');

    // Check if we need to update.
    if ($last_update + (24 * 60 * 60) > REQUEST_TIME) {
      return; // No time yet.
    }

    // Get the location of the metadata file.
    $idp_filename = self::get_surfconext_metadata_idp_filename();

    // Check if we filename is set and writable. The requirements hook will
    // tell problems if the filename is not working.
    if (empty($idp_filename) || !is_writable(dirname(drupal_realpath($idp_filename)))) {
      return;
    }

    // Already running?
    if (!lock_acquire('surfconext_metadata_idp_get')) {
      return;
    }

    // Autoload lib.
    if (!self::autoload()) {
      throw new surfconext_exception('Unable to autoload simpleSAML library.');
    }

    // Get url of the metadata.
    $url = self::get_surfconext_metadata_idp_url();

    // Make sure what we get is valid, so admin can't hack it to get some file
    // from the system.
    if (valid_url($url, TRUE)) {
      try {
        // Get the metadata.
        $xmldata = file_get_contents($url);
        if (empty($xmldata)) {
          throw new surfconext_exception('Unable to retrieve idp XML from SURFconext, check settings');
        }

        SimpleSAML_Utilities::validateXMLDocument($xmldata, 'saml-meta');
        $entities = SimpleSAML_Metadata_SAMLParser::parseDescriptorsString($xmldata);

        // Get all metadata for the entities.
        foreach($entities as &$entity) {
          $entity = array(
            'saml20-idp-remote' => $entity->getMetadata20IdP(),
          );
        }

        // Convert to array.
        $output = SimpleSAML_Utilities::transposeArray($entities);

        // Get the metadata.
        $entityMetadata = reset($output['saml20-idp-remote']);

        // Remove the entityDescriptor element because it is unused, and
        // only makes the output harder to read.
        unset($entityMetadata['entityDescriptor']);

        $text = '<?php
/**
 * SAML 2.0 remote IdP metadata for simpleSAMLphp.
 *
 * See: https://rnd.feide.no/content/idp-remote-metadata-reference
 */

$metadata[\'' . $url . '\'] = ' . var_export($entityMetadata, TRUE) . ";\n";

        // Save to file.
        if (file_put_contents($idp_filename, $text) == FALSE) {
          self::log('Unable to write to metadata IdP file');
        }
        else {
          // Store when we did the last update.
          variable_set('surfconext_metadata_ipd_last_update', REQUEST_TIME);
        }
      }
      catch (Exception $e) {
        // Log it, but ignore.
        self::log('Unable to retrieve or process the metadata from SURFconext idp; @message', array('@message' => $e->getMessage()));
      }
    }
    else {
      self::log('Invalid URL detected for SURFconext metadat idp URL');
    }

    // Release lock.
    lock_release('surfconext_metadata_idp_get');
  }

  /**
   * Is user authenticated in SURFconext?
   *
   * @return
   *   Returns TRUE when authenticated, or FALSE when not.
   */
  static public function isAuthenticated() {
    // Get instance.
    $surfconext = surfconext::get();

    // Check surfconext.
    return $surfconext && $surfconext->saml_isAuthenticated() ? TRUE : FALSE;
  }

  // ---------------------------------------------------------------- Functions.
  /**
   * Goto the login page of SURFconext.
   */
  public function login() {

    // Make sure we are enabled.
    if (!surfconext::is_enabled()) {
      drupal_set_message(t('SURFconext login is not enabled.'));
      drupal_goto();
    }

    if (!$this->simplesaml_auth_simple) {
      surfconext::log('A user attempted to login using this module but the environment of SURFconext is missing, please check settings.', array(), WATCHDOG_CRITICAL);
      drupal_set_message(t('There was a unexpected problem. The issue has been logged for the administrator.'));
      drupal_goto();
    }

    // Trigger the SURFconext login.
    if (!user_is_logged_in()) {
      // Require the user to be authenticated.
      $this->simplesaml_auth_simple->requireAuth();
    }

    // If we are logged in already, then ignore.

    // If use destination in GET, then we will be redirected back.
    drupal_goto();
  }

  /**
   * Get the SAML attributes.
   *
   * @return
   *   The attributes array or FALSE.
   */
  public function getAttributes() {
    return empty($this->simplesaml_auth_simple) ? FALSE : $this->simplesaml_auth_simple->getAttributes();
  }

  /**
   * Return with the attribute name for the unique name.
   *
   * @return
   *   The value
   */
  public function getAttribute($name) {
    $attributes = $this->getAttributes();

    if (!empty($attributes) && isset($attributes[$name])) {
      return is_array($attributes[$name]) ? reset($attributes[$name]) : $attributes[$name];
    }

    return FALSE;
  }

  /**
   * Gets the authname attribute from the SAML attributes.
   *
   * @return
   *   The authname attribute or FALSE.
   */
  protected function getAttribute_authname() {
    // Get authname.
    return $this->getAttribute(self::get_attribute_name_unique_id());
  }

  /**
   * Gets value we use for ACL realm. For now we can use the
   * getAttribute_authname().
   *
   * @return
   *   The authname attribute or FALSE.
   */
  public function getAttibute_used_for_realm() {
    return drupal_strtolower($this->getAttribute_authname());
  }

  /**
   * Gets the authname attribute from the SAML attributes.
   *
   * @return
   *   The authname attribute or FALSE.
   */
  protected function getAttribute_mail() {
    // Get authname.
    return $this->getAttribute(self::get_attribute_name_mail());
  }

  /**
   * Initialize the SURFconext by getting and initializing the session for
   * SimpleSAML.
   *
   * @throws surfconext_exception
   */
  public function init() {
    // Must be enabled.
    if (!surfconext::is_enabled()) {
      throw new surfconext_exception('SURFconext is not enabled.');
    }

    // Autoload lib.
    if (!self::autoload()) {
      throw new surfconext_exception('Unable to autoload simpleSAML library.');
    }

    // Create the SimpleSAML_Auth_Simple object.
    $this->simplesaml_auth_simple = new SimpleSAML_Auth_Simple(self::get_authsource());

    // Init based on login status on Drupal.
    user_is_logged_in() ? $this->init_drupal_loggedin() : $this->init_drupal_loggedoff();
  }

  /**
   * Is user authenticated in SURFconext?
   *
   * @return
   *   Returns TRUE when authenticated, or FALSE when not.
   */
  protected function saml_isAuthenticated() {
    return $this->simplesaml_auth_simple->isAuthenticated() ? TRUE : FALSE;
  }

  /**
   * Initialize while user is logged into Drupal.
   */
  private function init_drupal_loggedin() {
    global $user;

    // If we are authenticated on SURFconext, then we accept.
    if ($this->saml_isAuthenticated()) {
      return;
    }

    // Not authenticated on SURFconext.

    // Super user is always allowed as Drupal user without SURFconext.
    if ($user->uid == 1) {
      return;
    }

    // All other logged in Drupal users require SURFconext login.

    // user_logout() will not return.
    self::user_logout();
  }

  /**
   * Initialize while user is not logged into Drupal.
   */
  private function init_drupal_loggedoff() {

    // Ignore if we are not authenticated for SURFconext.
    if (!$this->saml_isAuthenticated()) {
      return;
    }

    // User is logged into SURFconext, but not in Drupal.
    $authname = $this->getAttribute_authname();
    self::debug("Authname is '%authname', not logged into Drupal.", array('%authname' => $authname));

    // No authname, then log and leave.
    if (empty($authname)) {
      self::debug("Can't continue init, authname not found in SAML attributes. Make sure ", array('%authname' => $authname));
      return;
    }

    // Get unique identifier from saml attributes.
    $authname = $this->getAttribute_authname();
    if (empty($authname)) {
      return;
    }

    // Retrieve user mapping and attempt to log the user in.
    $ext_user = user_external_load($authname);

    // Create user?
    if (!$ext_user) {
      // Register in log.
      surfconext::debug("Registering user '%authname'", array('%authname' => $authname));

      // Create user.
      user_external_login_register($authname, 'surfconext');

      // Get created account.
      $account = user_external_load($authname);
      if (!empty($account) && $account->uid) {

        // Get mail address user.
        $mail = $this->getAttribute_authname();

        // Extend user account.
        $userinfo = array(
          'mail' => drupal_strtolower($mail),
        );
        user_save($account, $userinfo);
      }
    }
    else {
      global $user;
      $user = $ext_user;
    }

    // Finalizing the login, calls hook_user op login.
    $edit = array();
    user_login_finalize($edit);
  }

  /**
   * Called when user logs out of Drupal.
   *
   * @param $account
   *   The account which is logging off (unused).
   */
  public function drupal_logoff($account) {

    // Ignore if we are not authenticated for SURFconext.
    if (!$this->saml_isAuthenticated()) {
      return;
    }

    // Destroy the current session, and reset $user to the anonymous user.
    session_destroy();

    // Logout of SURFconext.
    $this->simplesaml_auth_simple->logout(url('', array('absolute' => TRUE)));
  }
}
