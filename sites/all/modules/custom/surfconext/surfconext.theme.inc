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
 * Contains all theme related functions.
 */

/**
 * Generates the text for the log in block.
 */
function theme_surfconext_login_link() {
  global $user;

  if (!surfconext::is_enabled()) {
    // Exit without executing.
    return;
  }

  // Check if valid local session exists..
  if (surfconext::isAuthenticated()) {
    return '<p>Logged in as: ' . $user->name . '<br />' . l('Log Out', 'user/logout') . '</a></p>';
  }

  return '<p>' . l(t('SURFconext Log In'), 'user/login/surfconext') . '</p>';
}

/**
 * Show any authentication information on current user.
 */
function theme_surfconext_info() {
  global $user;

  // Get the instance.
  $surfconext = surfconext::get();
  if (!$surfconext) {
    return;
  }

  // Get the saml attributes.
  $attributes = $surfconext->getAttributes();

  // Init header.
  $header = array(t('Name'), t('Value'));

  $rows = array();
  foreach ($attributes as $key => $value) {
    $rows[] = array($key, implode(',', $value));
  }

  $form = array();
  $form['surfconext'] = array(
    '#title' => 'SURFConext authentication attributes',
    '#type' => 'fieldset',
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#attributes' => array('class' => array('collapsible collapsed')),
    '#attached' => array('library' => array(array('system', 'drupal.collapse'))),
  );

  $form['surfconext']['contents'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No SURFconext attributes found.'))),
  );

  // Add info about Drupal user.
  // Init header.
  $header = array(t('Name'), t('Value'));
  $rows = array();
  if (user_is_logged_in()) {
    $rows = array(
      array('UID', $user->uid),
      array('User', $user->name),
      array('Mail', $user->mail),
    );
  }

  $form['surfconext']['drupal'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('Drupal user is not logged in.'))),
  );

  return drupal_render($form);
}
