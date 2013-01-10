<?php
$path = drupal_get_path('theme', 'mediamosa_sb_theme');
include $path . '/templates/includes/header.inc';
?>
<div id="container">
  <?php if ($site_slogan): ?>
    <div class="slogan">
      <h1><?php print $site_slogan; ?></h1>
    </div>
  <?php endif; ?>
  <div id="content">
    <div id="spotlight">
      <div class="region">
        <?php print render($page['highlighted']); ?>
      </div>
    </div>
    <div id="page_content">
      <div class="region region-content">
        <?php print $messages; ?>

        <?php hide($page['content']['system_main']); ?>
        <?php print render($page['content']); ?>
      </div>
    </div>
  </div>
  <div id="footer">
    <div class="site_logo">
      <?php
        if (substr($logo, -27) !=  'mediamosa_sb_theme/logo.png') {
          print theme('image', array('path' => $logo));
        }
      ?>
    </div>
    <?php print render($page['footer']); ?>
  </div>
</div>