<?php
/**
 * @file
 * mediamosa_sb_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function mediamosa_sb_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'collections';
  $view->description = 'Show a listing of collections.';
  $view->tag = 'collections, listing, search';
  $view->base_table = 'mediamosa_collection_search';
  $view->human_name = 'MediaMosa Collections';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Collections';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'coll_id' => 'coll_id',
    'description' => 'description',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'coll_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'description' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: MediaMosa: Collection ID */
  $handler->display->display_options['fields']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['fields']['coll_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['fields']['coll_id']['label'] = '';
  $handler->display->display_options['fields']['coll_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['coll_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Collection';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'collection/detail/[coll_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  /* Field: MediaMosa: numofvideos */
  $handler->display->display_options['fields']['numofvideos']['id'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['numofvideos']['field'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['label'] = 'Items';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Filter criterion: MediaMosa: Owner */
  $handler->display->display_options['filters']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['filters']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['owner_id']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['owner_id']['expose']['label'] = 'Owner';
  $handler->display->display_options['filters']['owner_id']['expose']['operator'] = 'owner_id_op';
  $handler->display->display_options['filters']['owner_id']['expose']['identifier'] = 'owner_id';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'collections';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $export['collections'] = $view;

  $view = new view();
  $view->name = 'mediamosa_asset_detail';
  $view->description = 'Show a single asset. The first contextual filter is the asset_id.';
  $view->tag = 'asset, detail';
  $view->base_table = 'mediamosa_asset_get';
  $view->human_name = 'MediaMosa Asset Detail';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Video detail';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['mediamosa_ck_views_show_stills'] = 1;
  $handler->display->display_options['query']['options']['mediamosa_ck_views_show_collections'] = 1;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';

  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Access - Is owner */
  $handler->display->display_options['fields']['is_owner']['id'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['is_owner']['field'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['label'] = '';
  $handler->display->display_options['fields']['is_owner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_owner']['type'] = 'true-false';
  $handler->display->display_options['fields']['is_owner']['not'] = 0;
  /* Field: MediaMosa: Access - Edit */
  $handler->display->display_options['fields']['access_edit']['id'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['access_edit']['field'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['label'] = '';
  $handler->display->display_options['fields']['access_edit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_edit']['not'] = 0;
  /* Field: MediaMosa: Access - Delete */
  $handler->display->display_options['fields']['access_delete']['id'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['access_delete']['field'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['label'] = '';
  $handler->display->display_options['fields']['access_delete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_delete']['not'] = 0;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Mediafiles */
  $handler->display->display_options['fields']['mediafiles']['id'] = 'mediafiles';
  $handler->display->display_options['fields']['mediafiles']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['mediafiles']['field'] = 'mediafiles';
  $handler->display->display_options['fields']['mediafiles']['mediafile_path'] = '';
  /* Field: MediaMosa: Video player */
  $handler->display->display_options['fields']['player']['id'] = 'player';
  $handler->display->display_options['fields']['player']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['player']['field'] = 'player';
  $handler->display->display_options['fields']['player']['player_autostart'] = '1';
  /* Field: MediaMosa: Collections */
  $handler->display->display_options['fields']['collections']['id'] = 'collections';
  $handler->display->display_options['fields']['collections']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['collections']['field'] = 'collections';
  $handler->display->display_options['fields']['collections']['collection_theme'] = 'mediamosa_ck_views_theme_asset_collections';
  /* Field: MediaMosa: Metadata block for Dublin Core */
  $handler->display->display_options['fields']['metadata_dc']['id'] = 'metadata_dc';
  $handler->display->display_options['fields']['metadata_dc']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['metadata_dc']['field'] = 'metadata_dc';
  $handler->display->display_options['fields']['metadata_dc']['metadata_theme'] = 'mediamosa_ck_views_theme_asset_metadata';
  /* Field: MediaMosa: Metadata block for Qualified Dublin Core */
  $handler->display->display_options['fields']['metadata_qdc']['id'] = 'metadata_qdc';
  $handler->display->display_options['fields']['metadata_qdc']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['metadata_qdc']['field'] = 'metadata_qdc';
  $handler->display->display_options['fields']['metadata_qdc']['metadata_theme'] = 'mediamosa_ck_views_theme_asset_metadata';
  /* Field: MediaMosa: Technical metadata */
  $handler->display->display_options['fields']['technical_metadata']['id'] = 'technical_metadata';
  $handler->display->display_options['fields']['technical_metadata']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['technical_metadata']['field'] = 'technical_metadata';
  $handler->display->display_options['fields']['technical_metadata']['technical_metadata_theme'] = 'mediamosa_ck_views_theme_asset_technical_metadata';
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Download */
  $handler->display->display_options['fields']['download']['id'] = 'download';
  $handler->display->display_options['fields']['download']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['download']['field'] = 'download';
  $handler->display->display_options['fields']['download']['label'] = '';
  $handler->display->display_options['fields']['download']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['download']['download_path'] = '';

  /* Display: MediaMosa Asset Detail */
  $handler = $view->new_display('page', 'MediaMosa Asset Detail', 'page');
  $handler->display->display_options['display_description'] = 'Show a single asset. First contextual filter is the asset_id.';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Access - Is owner */
  $handler->display->display_options['fields']['is_owner']['id'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['is_owner']['field'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['label'] = '';
  $handler->display->display_options['fields']['is_owner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_owner']['type'] = 'true-false';
  $handler->display->display_options['fields']['is_owner']['not'] = 0;
  /* Field: MediaMosa: Access - Edit */
  $handler->display->display_options['fields']['access_edit']['id'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['access_edit']['field'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['label'] = '';
  $handler->display->display_options['fields']['access_edit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_edit']['not'] = 0;
  /* Field: MediaMosa: Access - Delete */
  $handler->display->display_options['fields']['access_delete']['id'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['access_delete']['field'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['label'] = '';
  $handler->display->display_options['fields']['access_delete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_delete']['not'] = 0;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Mediafiles */
  $handler->display->display_options['fields']['mediafiles']['id'] = 'mediafiles';
  $handler->display->display_options['fields']['mediafiles']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['mediafiles']['field'] = 'mediafiles';
  $handler->display->display_options['fields']['mediafiles']['mediafile_path'] = '';
  /* Field: MediaMosa: Video player */
  $handler->display->display_options['fields']['player']['id'] = 'player';
  $handler->display->display_options['fields']['player']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['player']['field'] = 'player';
  $handler->display->display_options['fields']['player']['player_autostart'] = '1';
  /* Field: MediaMosa: Collections */
  $handler->display->display_options['fields']['collections']['id'] = 'collections';
  $handler->display->display_options['fields']['collections']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['collections']['field'] = 'collections';
  $handler->display->display_options['fields']['collections']['collection_theme'] = 'mediamosa_ck_views_theme_asset_collections';
  /* Field: MediaMosa: Metadata block for Dublin Core */
  $handler->display->display_options['fields']['metadata_dc']['id'] = 'metadata_dc';
  $handler->display->display_options['fields']['metadata_dc']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['metadata_dc']['field'] = 'metadata_dc';
  $handler->display->display_options['fields']['metadata_dc']['metadata_theme'] = 'mediamosa_ck_views_theme_asset_metadata';
  /* Field: MediaMosa: Metadata block for Qualified Dublin Core */
  $handler->display->display_options['fields']['metadata_qdc']['id'] = 'metadata_qdc';
  $handler->display->display_options['fields']['metadata_qdc']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['metadata_qdc']['field'] = 'metadata_qdc';
  $handler->display->display_options['fields']['metadata_qdc']['metadata_theme'] = 'mediamosa_ck_views_theme_asset_metadata';
  /* Field: MediaMosa: Technical metadata */
  $handler->display->display_options['fields']['technical_metadata']['id'] = 'technical_metadata';
  $handler->display->display_options['fields']['technical_metadata']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['technical_metadata']['field'] = 'technical_metadata';
  $handler->display->display_options['fields']['technical_metadata']['technical_metadata_theme'] = 'mediamosa_ck_views_theme_asset_technical_metadata';
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Download */
  $handler->display->display_options['fields']['download']['id'] = 'download';
  $handler->display->display_options['fields']['download']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['download']['field'] = 'download';
  $handler->display->display_options['fields']['download']['label'] = '';
  $handler->display->display_options['fields']['download']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['download']['download_path'] = '';
  /* Field: share */
  $handler->display->display_options['fields']['share']['id'] = 'share';
  $handler->display->display_options['fields']['share']['table'] = 'views';
  $handler->display->display_options['fields']['share']['field'] = 'nothing';
  $handler->display->display_options['fields']['share']['ui_name'] = 'share';
  $handler->display->display_options['fields']['share']['label'] = 'Embed';
  $handler->display->display_options['fields']['share']['alter']['text'] = '<p><form>
<input type=text value="[site:url]/asset/player/[asset_id]"></p>
<p>object code:
<div class="embed_iframe">
<textarea title="Click and press CTRL+C to copy..." onclick="this.style.borderColor = \'lightred\'; this.select();" style="min-width:50%; height:4em; cursor:pointer;" height="1">
&lt;iframe width="640" height="360" src="[site:url]asset/player/[asset_id]" frameborder="0" allowfullscreen&gt;&lt;/iframe&gt;
</textarea>
</div></form>
</p>';
  $handler->display->display_options['fields']['share']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['share']['element_default_classes'] = FALSE;
  $handler->display->display_options['path'] = 'asset/detail';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $export['mediamosa_asset_detail'] = $view;

  $view = new view();
  $view->name = 'mediamosa_asset_featured';
  $view->description = 'Shows the (selected) featured assets.';
  $view->tag = 'asset, listing, featured';
  $view->base_table = 'mediamosa_asset_featured';
  $view->human_name = 'MediaMosa Asset Featured';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Featured videos';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_large';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['empty'] = 'No title available';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Sort criterion: MediaMosa: Created */
  $handler->display->display_options['sorts']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['sorts']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'asset/featured';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $export['mediamosa_asset_featured'] = $view;

  $view = new view();
  $view->name = 'mediamosa_asset_new';
  $view->description = 'Shows a listing of the latest assets.';
  $view->tag = 'asset, listing, new';
  $view->base_table = 'mediamosa_asset_new';
  $view->human_name = 'MediaMosa Asset New';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'MediaMosa Asset New';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  /* Sort criterion: MediaMosa: Created */
  $handler->display->display_options['sorts']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['table'] = 'mediamosa_asset_new';
  $handler->display->display_options['sorts']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'assets/new';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'New';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $export['mediamosa_asset_new'] = $view;

  $view = new view();
  $view->name = 'mediamosa_asset_popular';
  $view->description = 'Shows a listing of the most popular assets.';
  $view->tag = 'asset, listing, popular';
  $view->base_table = 'mediamosa_asset_popular';
  $view->human_name = 'MediaMosa Asset Popular';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'MediaMosa Asset Popular';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  /* Sort criterion: MediaMosa: Played */
  $handler->display->display_options['sorts']['played']['id'] = 'played';
  $handler->display->display_options['sorts']['played']['table'] = 'mediamosa_asset_popular';
  $handler->display->display_options['sorts']['played']['field'] = 'played';
  $handler->display->display_options['sorts']['played']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'assets/popular';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Popular';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $export['mediamosa_asset_popular'] = $view;

  $view = new view();
  $view->name = 'mediamosa_asset_search_page';
  $view->description = 'Show a listing assets for searching results.';
  $view->tag = 'asset, listing, search';
  $view->base_table = 'mediamosa_asset_search';
  $view->human_name = 'MediaMosa Asset Search page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'MediaMosa Asset Search page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Your search yielded no results';
  $handler->display->display_options['empty']['area']['content'] = '<h2>Your search yielded no results</h2>
Check if your spelling is correct.
Remove quotes around phrases to search for each word individually. bike shed will often show more results than "bike shed".
Consider loosening your query with OR. bike OR shed will often show more results than bike shed.
';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['alter']['max_length'] = '400';
  $handler->display->display_options['fields']['description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Filter criterion: MediaMosa: The search box */
  $handler->display->display_options['filters']['keywords']['id'] = 'keywords';
  $handler->display->display_options['filters']['keywords']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['filters']['keywords']['field'] = 'keywords';
  $handler->display->display_options['filters']['keywords']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keywords']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['keywords']['expose']['operator'] = 'keywords_op';
  $handler->display->display_options['filters']['keywords']['expose']['identifier'] = 'keywords';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'assets/search';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'mediamosa_asset_search_block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $export['mediamosa_asset_search_page'] = $view;

  $view = new view();
  $view->name = 'mediamosa_assets';
  $view->description = 'Show a listing of assets.';
  $view->tag = 'default';
  $view->base_table = 'mediamosa_asset_search';
  $view->human_name = 'MediaMosa Assets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Videos';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['alter']['path'] = 'asset/[asset_id]';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['videotimestamp']['alter']['text'] = '<span class="stamp">[videotimestamp]</span> by <span class="owner">[owner_id]</span>';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  /* Sort criterion: MediaMosa: Created */
  $handler->display->display_options['sorts']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['sorts']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: MediaMosa: Collection ID */
  $handler->display->display_options['filters']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['filters']['coll_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['filters']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['filters']['coll_id']['group'] = 0;
  $handler->display->display_options['filters']['coll_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['coll_id']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['coll_id']['expose']['label'] = 'Collection';
  $handler->display->display_options['filters']['coll_id']['expose']['operator'] = 'coll_id_op';
  $handler->display->display_options['filters']['coll_id']['expose']['identifier'] = 'coll_id';
  /* Filter criterion: MediaMosa: Owner */
  $handler->display->display_options['filters']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['filters']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['group'] = 0;
  $handler->display->display_options['filters']['owner_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['owner_id']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['owner_id']['expose']['label'] = 'User';
  $handler->display->display_options['filters']['owner_id']['expose']['operator'] = 'owner_id_op';
  $handler->display->display_options['filters']['owner_id']['expose']['identifier'] = 'owner_id';
  $handler->display->display_options['path'] = 'assets';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $export['mediamosa_assets'] = $view;

  $view = new view();
  $view->name = 'mediamosa_assets_in_collection';
  $view->description = 'Show a listing of assets in a collection';
  $view->tag = 'default';
  $view->base_table = 'mediamosa_assets_in_collection';
  $view->human_name = 'MediaMosa Assets in Collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_large';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['videotimestamp']['alter']['text'] = '<span class="stamp">[videotimestamp]</span> by <span class="owner">[owner_id]</span>';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'short';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'custom';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  /* Contextual filter: MediaMosa: Collection ID */
  $handler->display->display_options['arguments']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['arguments']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['coll_id']['exception']['value'] = '';
  $handler->display->display_options['arguments']['coll_id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['coll_id']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['coll_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['coll_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['coll_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['coll_id']['limit'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_large';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['videotimestamp']['alter']['text'] = '<span class="stamp">[videotimestamp]</span> by <span class="owner">[owner_id]</span>';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'short';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'custom';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  $handler->display->display_options['path'] = 'collection/assets';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['alter']['link_class'] = 'views-field-still-url';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_large';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['videotimestamp']['alter']['text'] = '<span class="stamp">[videotimestamp]</span> by <span class="owner">[owner_id]</span>';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['label'] = '';
  $handler->display->display_options['fields']['mediafile_duration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 's:i';
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_assets_in_collection';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  $export['mediamosa_assets_in_collection'] = $view;

  $view = new view();
  $view->name = 'mediamosa_collection_detail';
  $view->description = 'Show a single collection detail (no assets).';
  $view->tag = 'collection, detail';
  $view->base_table = 'mediamosa_collection_get';
  $view->human_name = 'MediaMosa Collection Detail';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'MediaMosa Collection Detail';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Collection ID */
  $handler->display->display_options['fields']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['fields']['coll_id']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['coll_id']['field'] = 'coll_id';
  /* Field: MediaMosa: Access - Is owner */
  $handler->display->display_options['fields']['is_owner']['id'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['is_owner']['field'] = 'is_owner';
  $handler->display->display_options['fields']['is_owner']['label'] = '';
  $handler->display->display_options['fields']['is_owner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_owner']['type'] = 'true-false';
  $handler->display->display_options['fields']['is_owner']['not'] = 0;
  /* Field: MediaMosa: Access - Edit */
  $handler->display->display_options['fields']['access_edit']['id'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['access_edit']['field'] = 'access_edit';
  $handler->display->display_options['fields']['access_edit']['label'] = '';
  $handler->display->display_options['fields']['access_edit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_edit']['not'] = 0;
  /* Field: MediaMosa: Access - Delete */
  $handler->display->display_options['fields']['access_delete']['id'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['access_delete']['field'] = 'access_delete';
  $handler->display->display_options['fields']['access_delete']['label'] = '';
  $handler->display->display_options['fields']['access_delete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['access_delete']['not'] = 0;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = '';
  $handler->display->display_options['fields']['owner_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: MediaMosa: numofvideos */
  $handler->display->display_options['fields']['numofvideos']['id'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['fields']['numofvideos']['field'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['label'] = '';
  $handler->display->display_options['fields']['numofvideos']['element_label_colon'] = FALSE;
  /* Contextual filter: MediaMosa: Collection ID */
  $handler->display->display_options['arguments']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['arguments']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['coll_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['coll_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['coll_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['coll_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['coll_id']['limit'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'collection/detail';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'MediaMosa Collection Detail Block';
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: MediaMosa: Collection ID */
  $handler->display->display_options['arguments']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['table'] = 'mediamosa_collection_get';
  $handler->display->display_options['arguments']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['arguments']['coll_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['coll_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['coll_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['coll_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['coll_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['coll_id']['limit'] = '0';
  $handler->display->display_options['block_description'] = 'Mediamosa Collection Detail Block';
  $export['mediamosa_collection_detail'] = $view;

  $view = new view();
  $view->name = 'mediamosa_my_assets';
  $view->description = 'Show a listing of the users assets.';
  $view->tag = 'assets, my, listing';
  $view->base_table = 'mediamosa_asset_search';
  $view->human_name = 'MediaMosa My Assets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My videos';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['exclude'] = TRUE;
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] <span>views</span>';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 'H:i';
  /* Sort criterion: MediaMosa: Created */
  $handler->display->display_options['sorts']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['sorts']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['sorts']['videotimestamp']['order'] = 'DESC';
  /* Filter criterion: MediaMosa: Owner */
  $handler->display->display_options['filters']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['filters']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['value'] = '[user:mail]';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['label'] = '';
  $handler->display->display_options['fields']['granted']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['still_url']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'mediamosa_sb_normal';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'asset/detail/[asset_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['label'] = '';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['played']['alter']['text'] = '[played] views';
  $handler->display->display_options['fields']['played']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['label'] = '';
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Mediafile duration */
  $handler->display->display_options['fields']['mediafile_duration']['id'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['table'] = 'mediamosa_asset_search';
  $handler->display->display_options['fields']['mediafile_duration']['field'] = 'mediafile_duration';
  $handler->display->display_options['fields']['mediafile_duration']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mediafile_duration']['date_format'] = 'mediamosa_ck_mf_duration';
  $handler->display->display_options['fields']['mediafile_duration']['custom_date_format'] = 'H:i';
  $handler->display->display_options['path'] = 'myassets';
  $export['mediamosa_my_assets'] = $view;

  $view = new view();
  $view->name = 'mediamosa_player_block';
  $view->description = 'Can be used to include player using IFRAME on an external page. Can only play videos that are publc.';
  $view->tag = 'player';
  $view->base_table = 'mediamosa_asset_get';
  $view->human_name = 'Mediamosa Player Page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Mediamosa Player';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['label'] = '';
  $handler->display->display_options['fields']['asset_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Video player */
  $handler->display->display_options['fields']['player']['id'] = 'player';
  $handler->display->display_options['fields']['player']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['player']['field'] = 'player';
  $handler->display->display_options['fields']['player']['label'] = '';
  $handler->display->display_options['fields']['player']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['player']['player_width'] = '942';
  $handler->display->display_options['fields']['player']['player_height'] = '942';
  $handler->display->display_options['fields']['player']['player_autostart'] = '0';
  /* Field: MediaMosa: Playback range */
  $handler->display->display_options['fields']['playback_range']['id'] = 'playback_range';
  $handler->display->display_options['fields']['playback_range']['table'] = 'mediamosa_asset_get';
  $handler->display->display_options['fields']['playback_range']['field'] = 'playback_range';
  $handler->display->display_options['fields']['playback_range']['label'] = '';
  $handler->display->display_options['fields']['playback_range']['exclude'] = TRUE;
  $handler->display->display_options['fields']['playback_range']['element_label_colon'] = FALSE;

  /* Display: Asset Page */
  $handler = $view->new_display('page', 'Asset Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'asset/player';
  $export['mediamosa_player_block'] = $view;

  $view = new view();
  $view->name = 'my_collections';
  $view->description = 'Show a listing of the users collections.';
  $view->tag = 'collection, my, listing';
  $view->base_table = 'mediamosa_collection_search';
  $view->human_name = 'Mediamosa My Collections';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Collections';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'coll_id' => 'coll_id',
    'description' => 'description',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'coll_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'description' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: MediaMosa: Collection ID */
  $handler->display->display_options['fields']['coll_id']['id'] = 'coll_id';
  $handler->display->display_options['fields']['coll_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['coll_id']['field'] = 'coll_id';
  $handler->display->display_options['fields']['coll_id']['exclude'] = TRUE;
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'collection/detail/[coll_id]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: MediaMosa: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  /* Field: MediaMosa: numofvideos */
  $handler->display->display_options['fields']['numofvideos']['id'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['numofvideos']['field'] = 'numofvideos';
  $handler->display->display_options['fields']['numofvideos']['label'] = 'Items';
  /* Field: MediaMosa: Owner */
  $handler->display->display_options['fields']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['fields']['owner_id']['label'] = 'User';
  /* Field: MediaMosa: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'mediamosa_ck_normal';
  /* Field: MediaMosa: Actions */
  $handler->display->display_options['fields']['actions']['id'] = 'actions';
  $handler->display->display_options['fields']['actions']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['fields']['actions']['field'] = 'actions';
  /* Filter criterion: MediaMosa: Owner */
  $handler->display->display_options['filters']['owner_id']['id'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['table'] = 'mediamosa_collection_search';
  $handler->display->display_options['filters']['owner_id']['field'] = 'owner_id';
  $handler->display->display_options['filters']['owner_id']['value'] = '[user:mail]';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'mycollections';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $export['my_collections'] = $view;

  return $export;
}
