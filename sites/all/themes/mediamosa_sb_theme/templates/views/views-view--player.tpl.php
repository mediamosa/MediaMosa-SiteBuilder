<?php
/**
 * @file
 * Template for video player.
 *
 * A Very much tomed down version of views-view.tpl.php.
 *
 * @ingroup views_templates
 */
?>
<style type="text/css">
  html {
    overflow-y: hidden;
  }
  .video-js .vjs-tech {
    height: inherit !important;
  }
</style>
<?php if ($rows): ?>
<div class="view-content">
<?php print $rows; ?>
  </div>
<?php elseif ($empty): ?>
  <div class="view-empty">
<?php print $empty; ?>
  </div>
<?php endif; ?>
