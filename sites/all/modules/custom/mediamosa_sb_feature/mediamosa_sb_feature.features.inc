<?php
/**
 * @file
 * mediamosa_sb_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mediamosa_sb_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function mediamosa_sb_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function mediamosa_sb_feature_image_default_styles() {
  $styles = array();

  // Exported image style: mediamosa_sb_large.
  $styles['mediamosa_sb_large'] = array(
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 169,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'mediamosa_sb_large',
  );

  // Exported image style: mediamosa_sb_normal.
  $styles['mediamosa_sb_normal'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 220,
          'height' => 124,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'mediamosa_sb_normal',
  );

  // Exported image style: mediamosa_sb_small.
  $styles['mediamosa_sb_small'] = array(
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 156,
          'height' => 110,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'mediamosa_sb_small',
  );

  return $styles;
}
