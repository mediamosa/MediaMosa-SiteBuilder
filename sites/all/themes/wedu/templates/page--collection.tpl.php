<?php
$path = drupal_get_path('theme', 'wedu');
include $path . '/templates/includes/header.inc';
?>
<div id="container">
  <?php if ($site_slogan): ?>
    <div class="slogan">
      <p><?php print $site_slogan; ?></p>
    </div>
  <?php endif; ?>

  <?php if ($breadcrumb): ?>
    <div id="breadcrumbs"><?php print $breadcrumb; ?></div>
  <?php endif; ?>

  <div id="content">
    <div id="page_content">
      <?php print $messages; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
      <div class="collection-holder">
        <?php print render($page['content']); ?>
      </div>

      <?php if (!empty($page['sidebar_first'])): ?>
        <div class="collection-information">
          <?php print render($page['sidebar_first']); ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
  <div id="footer">
    <div class="site_logo">
      <?php
        if (substr($logo, -27) !=  'wedu/logo.png') {
          print theme('image', array('path' => $logo));
        }
      ?>
    </div>
    <?php print render($page['footer']); ?>
  </div>
</div>