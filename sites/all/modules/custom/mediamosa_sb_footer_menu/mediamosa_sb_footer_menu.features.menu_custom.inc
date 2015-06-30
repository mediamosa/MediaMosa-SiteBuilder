<?php
/**
 * @file
 * mediamosa_sb_footer_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function mediamosa_sb_footer_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: footer-menu.
  $menus['footer-menu'] = array(
    'menu_name' => 'footer-menu',
    'title' => 'Footer menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer menu');


  return $menus;
}
