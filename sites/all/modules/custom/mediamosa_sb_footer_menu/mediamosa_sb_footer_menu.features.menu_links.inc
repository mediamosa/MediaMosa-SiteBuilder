<?php
/**
 * @file
 * mediamosa_sb_footer_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mediamosa_sb_footer_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: footer-menu:contact
  $menu_links['footer-menu:contact'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: footer-menu:colofon
  $menu_links['footer-menu:colofon'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'colofon',
    'link_title' => 'Colofon',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: footer-menu:disclaimer
  $menu_links['footer-menu:disclaimer'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'disclaimer',
    'link_title' => 'Disclaimer',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: footer-menu:copyrights
  $menu_links['footer-menu:copyrights'] = array(
    'menu_name' => 'footer-menu',
    'link_path' => 'copyrights',
    'link_title' => 'Copyrights',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Colofon');
  t('Contact');
  t('Copyrights');
  t('Disclaimer');

  return $menu_links;
}
