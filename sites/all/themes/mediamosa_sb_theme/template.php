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

/**
 * Create themed owner field.
 */
function mediamosa_sb_theme_mediamosa_ck_views_theme_owner($variables) {
  if (module_exists('surfconext')) {
    $u = user_load($variables['uid']);
    if (isset($u->display_name) && isset($u->display_name['und'][0]['value'])) {
      return $u->display_name['und'][0]['value'];
    }
    else {
      return '-';
    }
  }
  theme_mediamosa_ck_views_theme_owner($variables);
}

/**
 * We override the normal theme_select function that takes care of
 * theming the select element.
 */
function mediamosa_sb_theme_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  // Now we implement our own custom function for theming the options.
  return '<select' . drupal_attributes($element['#attributes']) . '>'
    . mediamosa_sb_theme_form_select_options($element) . '</select>';
}

/**
 * This is a copy of normal form select options,
 * with option attribute support.
 */
function mediamosa_sb_theme_form_select_options($element, $choices = NULL) {
  if (!isset($choices)) {
    $choices = $element['#options'];
  }
  // array_key_exists() accommodates the rare event
  // where $element['#value'] is NULL.
  // isset() fails in this situation.
  $value_valid = isset($element['#value'])
    || array_key_exists('#value', $element);
  $value_is_array = $value_valid && is_array($element['#value']);
  $options = '';
  foreach ($choices as $key => $choice) {
    if (is_array($choice)) {
      $options .= '<optgroup label="' . $key . '">';
      $options .= form_select_options($element, $choice);
      $options .= '</optgroup>';
    }
    elseif (is_object($choice)) {
      $options .= form_select_options($element, $choice->option);
    }
    else {
      $key = (string) $key;

      // Get option attributes if set.
      // The attributes are added to the parent select element,
      // which we can access here ($element)
      // The #option_attributes have the same keys as the #option
      // elements, and can be added here to the current option by key
      $attributes = "";
      if (isset($element['#option_attributes'][$key])) {
        $attributes = drupal_attributes($element['#option_attributes'][$key]);
      }

      // check if this element is selected
      if ($value_valid
        && (!$value_is_array && (string) $element['#value'] === $key
        || ($value_is_array && in_array($key, $element['#value'])))) {
        $selected = ' selected="selected"';
      } else {
        $selected = '';
      }

      // Here we add the attributes to the option
      $options .= '<option ' . $attributes
        . ' value="' . check_plain($key) . '"' . $selected . '>'
        . check_plain($choice) . '</option>';
    }
  }
  return $options;
}

/**
 * Shows listing of asset metadata.
 *
 * The theme used to generate a listing of metadata in the views using
 * mediamosa_ck_views_field_text_metadata. Slightly modified from the original:
 * no showing of empty rows.
 *
 * @param array $variables
 *   Data used for the theme.
 */
function mediamosa_sb_theme_mediamosa_ck_views_theme_asset_metadata($variables) {
  $rows = array();

  ksort($variables['metadata']);

  foreach ($variables['metadata'] as $name => $value) {
    $name = drupal_ucfirst(str_replace('_', ' ', $name));

    if (is_array($value)) {
      $value = implode("\n", $value);
    }
    if (($name == 'created') and (isset($value)) and (substr($value, -9) == ' 00:00:00')) {
      $value = substr($value, 0, -9);
    }

    if (empty($value)) {
      $rows[] = array(
        'class' => array('empty'), 'data' => array('name' => $name, 'value' => ''),
      );
    }
    else {
      $rows[] = array('name' => $name, 'value' => (empty($value) ? ' ' : nl2br(check_plain($value))));
    }
  }
  if (empty($rows)) {
    $rows[] = array('-', '');
  }

  return theme('table', array('rows' => $rows));
}
