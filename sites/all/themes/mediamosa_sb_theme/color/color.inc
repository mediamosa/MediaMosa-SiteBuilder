<?php

// Put the logo path into JavaScript for the live preview.
drupal_add_js(array('color' => array('logo' => theme_get_setting('logo', 'mediamosa_sb_theme'))), 'setting');

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'header_bg' => t('Header background color'),
    'link' => t('Links'),
    'primary_text' => t('Primary text'),
    'secondary_text' => t('Secondary text'),
    'tertiary_text' => t('Tertiary text'),
    'heading' => t('Heading color'),
    'sloganbar' => t('Slogan background'),
    'slogantext' => t('Slogan text'),
    'box' => t('Background UI Color'),
    'videohover' => t('Video Hover Color'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
        'header_bg' => '#f1f1f1',
        'link' => '#f1761e',
        'primary_text' => '#888888',
        'secondary_text' => '#cdcdcd',
        'tertiary_text' => '#000000',
        'heading' => '#595959',
        'sloganbar' => '#ffffff',
        'slogantext' => '#999999',
        'box' => '#eaeaf3',
        'videohover' => '#fdd5b3',
      ),
    ),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/colors.css',
  ),

  // Files to copy.
  'copy' => array(
    'images/logo.png',
  ),
  
  // Gradient definitions.
  'gradients' => array(
   array(
      // (x, y, width, height).
      'dimension' => array(0, 0, 0, 0),
      // Direction of gradient ('vertical' or 'horizontal').
      'direction' => 'vertical',
      // Keys of colors to use for the gradient.
      'colors' => array('top', 'bottom'),
    ),
  ),
  
  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_css' => 'color/preview.css',
  'preview_js' => 'color/preview.js',
  'preview_html' => 'color/preview.html',

  // Base file for image generation.
  'base_image' => 'color/base.png',

);
