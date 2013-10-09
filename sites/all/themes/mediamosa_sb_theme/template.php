<?php
/**
 * @file
 * Template file containing alternative rendering for Drupal's default methods.
 *
 * @author Thijs @ One Shoe
 */

/**
 * Implements hook_theme().
 */
function bootstrap_theme() {
  return array(
    'pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
      'file' => 'includes/pager.inc',
    ),
    'pager_placeholder' => array(
      'variables' => array('text' => NULL),
      'file' => 'includes/pager.inc',
    ),
  );
}

/**
 * Override or insert variables into the page template for HTML output.
 */
function mediamosa_sb_theme_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Implements hook_preprocess_page().
 */
function mediamosa_sb_theme_preprocess_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Theme override for theme_breadcrumb().
 */
function mediamosa_sb_theme_breadcrumb($variables) {
  $breadcrumb = array_values($variables['breadcrumb']);
  $l = count($breadcrumb);
  $items = array();
  for ($i = 0; $i < $l; $i++) {
    $items[] = '<li>' . $breadcrumb[$i] . '</li>';
  }
  // @todo Check if drupal_get_title() needs a check_plain().
  $current_title = drupal_get_title();
  if (!$current_title && empty($variables['breadcrumb']) && drupal_is_front_page()) {
    $current_title = t('Home');
  }
  $items[] = '<li class="active">' . ($current_title)  . '</li>';

  return '<ul class="breadcrumb">' . implode($items) . '</ul>';
}

/**
 * Implements hook_page_alter().
 */
function mediamosa_sb_theme_page_alter(&$page) {

  // Hide the admin menu on our iframe asset/player page.
  if (arg(0) == 'asset' && arg(1) == 'player') {
    if (!empty($page['page_bottom']['admin_toolbar'])) {
      hide($page['page_bottom']['admin_toolbar']);
    }
  }
}

/**
 * Overrides theme_mediamosa_ck_views_theme_asset_mediafiles().
 */
function mediamosa_sb_theme_mediamosa_ck_views_theme_asset_mediafiles($variables) {

  if (!variable_get('mediamosa_sb_view_asset_formats', TRUE)) {
    return;
  }
  else {
    return theme_mediamosa_ck_views_theme_asset_mediafiles($variables);
  }
}
