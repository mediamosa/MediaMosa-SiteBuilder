<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<h1><?php print $fields['title']->content; ?></h1>
<ul class="item-navigation">
  <?php if ($fields['access_edit']->raw == TRUE): ?>
    <li><span><?php print l(t('Edit'), 'collection/edit/' . $fields['coll_id']->raw, array('attributes' => array('class' => 'edit'))); ?></span></li>
  <?php endif; ?>
</ul>

<div class="collection-detail-information">
  <div class="information-row">
    <p class="collection-view-count"><span class="count"><?php print $fields['numofvideos']->raw; ?></span> <?php print t('videos'); ?></p>

    <p class="collection-uploaded-info">
      <?php print t('Posted by');?>: <strong><?php print $fields['owner_id']->content; ?></strong> <?php print t('on'); ?> <strong><?php print $fields['created']->content; ?></strong>
    </p>
  </div>

  <div class="information-row collection-description">
    <h3><?php print t('About this collection'); ?></h3>
    <p><?php print $fields['description']->content; ?></p>
  </div>
</div>

<div class="collection-videos">
<?php print views_embed_view('mediamosa_assets_in_collection', 'block'); ?>
</div>
