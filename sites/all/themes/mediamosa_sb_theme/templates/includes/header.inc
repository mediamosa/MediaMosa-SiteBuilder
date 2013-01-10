<div id="header">
  <div class="header_content">
    <div class="site_logo">
      <?php print l(theme('image', array('path' => $logo, 'title' => $site_name, 'alt' => $site_name)), '<front>', array('html' => TRUE)); ?>
    </div>

    <?php if (user_is_logged_in()): ?>
    <div class="user-custom-navigation">
      <?php print l(t('My Videos'), 'myassets'); ?>&nbsp;|&nbsp;<?php print l(t('My Collections'), 'mycollections'); ?>&nbsp;|&nbsp;<?php print l(t('My account'), 'user'); ?>
    </div>
    <?php
    if (mediamosa_sb::access_may_upload()) {
      print l(t('Upload'), 'asset/upload', array('attributes' => array('class' => array('user-login-button'))));
    }
    ?>
    <?php else:
      $user_url = 'user';
      drupal_alter('mediamosa_sb_theme_user_url', $user_url);
      print l(t('Sign in'), $user_url, array('attributes' => array('class' => array('user-login-button'))));

    endif;
    ?>
    <select id="language-picker">
      <option selected>EN</option>
      <option>NL</option>
    </select>
    <?php print render($page['header']); ?>
  </div>
</div>
