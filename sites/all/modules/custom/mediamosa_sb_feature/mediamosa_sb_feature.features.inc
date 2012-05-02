<?php
/**
 * @file
 * mediamosa_sb_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function mediamosa_sb_feature_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function mediamosa_sb_feature_image_default_styles() {
  $styles = array();

  // Exported image style: mediamosa_sb_large
  $styles['mediamosa_sb_large'] = array(
    'name' => 'mediamosa_sb_large',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '300',
          'height' => '169',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: mediamosa_sb_normal
  $styles['mediamosa_sb_normal'] = array(
    'name' => 'mediamosa_sb_normal',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '220',
          'height' => '124',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: mediamosa_sb_small
  $styles['mediamosa_sb_small'] = array(
    'name' => 'mediamosa_sb_small',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '156',
          'height' => '110',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
