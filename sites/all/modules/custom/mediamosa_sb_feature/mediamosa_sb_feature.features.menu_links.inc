<?php
/**
 * @file
 * mediamosa_sb_feature.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mediamosa_sb_feature_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: main-menu:assets
  $menu_links['main-menu:assets'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'assets',
    'router_path' => 'assets',
    'link_title' => 'Videos',
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
  // Exported menu link: main-menu:collections
  $menu_links['main-menu:collections'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'collections',
    'router_path' => 'collections',
    'link_title' => 'Collections',
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
  // Exported menu link: menu-footer:node/2
  $menu_links['menu-footer:node/2'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
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
    'weight' => '0',
  );
  // Exported menu link: menu-footer:node/3
  $menu_links['menu-footer:node/3'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
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
    'weight' => '0',
  );
  // Exported menu link: menu-footer:node/4
  $menu_links['menu-footer:node/4'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
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
    'weight' => '0',
  );
  // Exported menu link: menu-footer:node/5
  $menu_links['menu-footer:node/5'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
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
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Collections');
  t('Colofon');
  t('Contact');
  t('Copyrights');
  t('Disclaimer');
  t('Home');
  t('Videos');


  return $menu_links;
}
