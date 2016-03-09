<?php
/**
 * @file
 * mediamosa_sb_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mediamosa_sb_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'mediamosa_sb' => 'mediamosa_sb',
    'file_entity' => 0,
    'node' => 0,
    'user' => 0,
  );
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'mediamosa_sb';
  $export['search_default_module'] = $strongarm;

  return $export;
}
