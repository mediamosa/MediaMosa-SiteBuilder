<?php
/**
 * @file
 * mediamosa_site_builder_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mediamosa_site_builder_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
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
    'link_title' => 'Media',
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
  // Translatables
  // Included for use with string extractors like potx.
  t('Collections');
  t('Home');
  t('Media');

  return $menu_links;
}
