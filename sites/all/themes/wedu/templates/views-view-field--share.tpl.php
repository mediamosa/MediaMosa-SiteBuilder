<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

?>
<div><p style="margin-bottom:3px;">
<input type=text
  style="width: 100%; min-width:50%; height:1em; cursor:pointer; font-size: 0.9em;"
  value="[site:url]asset/player/<?php print $row->asset_id; ?>" title="Click and press CTRL+C to copy..." onclick="this.style.borderColor = 'lightred'; this.select();" >
</p>
Object code:
  <p style="margin-top:2px;">
<textarea
  title="Click and press CTRL+C to copy..."
  onclick="this.style.borderColor = 'lightred'; this.select();"
  style="font-family:inherit;width: 100%; border: 1px solid #eaeaf3; min-width:50%; height:4.9em; cursor:pointer; font-size: 0.9em;"
  height="1">
&lt;iframe width="640" height="360" src="[site:url]asset/player/<?php print $row->asset_id; ?>" frameborder="0" allowfullscreen&gt;&lt;/iframe&gt;
</textarea>
</p>
</div>
