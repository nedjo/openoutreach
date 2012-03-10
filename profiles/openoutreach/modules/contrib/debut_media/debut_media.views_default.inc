<?php
/**
 * @file
 * debut_media.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function debut_media_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'media';
  $view->description = 'Displays of media including a page and a carousel of promoted items.';
  $view->tag = '';
  $view->base_table = 'file_managed';
  $view->human_name = 'Media';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_text'] = '';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: File: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['fid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['fid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['fid']['link_to_file'] = 0;
  /* Field: File: File */
  $handler->display->display_options['fields']['rendered']['id'] = 'rendered';
  $handler->display->display_options['fields']['rendered']['table'] = 'file_managed';
  $handler->display->display_options['fields']['rendered']['field'] = 'rendered';
  $handler->display->display_options['fields']['rendered']['label'] = '';
  $handler->display->display_options['fields']['rendered']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['path'] = 'file/[fid]';
  $handler->display->display_options['fields']['rendered']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rendered']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rendered']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rendered']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rendered']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['rendered']['link_to_file'] = 0;
  $handler->display->display_options['fields']['rendered']['file_view_mode'] = 'media_preview';
  /* Field: File: Title */
  $handler->display->display_options['fields']['media_title']['id'] = 'media_title';
  $handler->display->display_options['fields']['media_title']['table'] = 'field_data_media_title';
  $handler->display->display_options['fields']['media_title']['field'] = 'media_title';
  $handler->display->display_options['fields']['media_title']['label'] = '';
  $handler->display->display_options['fields']['media_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['path'] = 'file/[fid] ';
  $handler->display->display_options['fields']['media_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['media_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['media_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['media_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['media_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['media_title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['media_title']['field_api_classes'] = 0;
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = '';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_tags']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_tags']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_tags']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tags']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_tags']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_tags']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_tags']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_tags']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_tags']['field_api_classes'] = 0;
  /* Sort criterion: File: Upload date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: File: Mime type */
  $handler->display->display_options['filters']['filemime']['id'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['table'] = 'file_managed';
  $handler->display->display_options['filters']['filemime']['field'] = 'filemime';

  /* Display: Page: Media */
  $handler = $view->new_display('page', 'Page: Media', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Multimedia';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: File: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'file_managed';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'audio' => 'audio',
    'image' => 'image',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['path'] = 'file';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Multimedia';
  $handler->display->display_options['menu']['description'] = 'View media files.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Page: Images */
  $handler = $view->new_display('page', 'Page: Images', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Images';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: File: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'file_managed';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'image' => 'image',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['path'] = 'file/image';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Page: Video */
  $handler = $view->new_display('page', 'Page: Video', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Videos';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: File: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'file_managed';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'video' => 'video',
  );
  $handler->display->display_options['path'] = 'file/video';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Block: Carousel */
  $handler = $view->new_display('block', 'Block: Carousel', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent multimedia';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'jcarousel';
  $handler->display->display_options['style_options']['wrap'] = '0';
  $handler->display->display_options['style_options']['visible'] = '';
  $handler->display->display_options['style_options']['auto'] = '0';
  $handler->display->display_options['style_options']['autoPause'] = 1;
  $handler->display->display_options['style_options']['easing'] = '';
  $handler->display->display_options['style_options']['vertical'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: File: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['fid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['fid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['fid']['link_to_file'] = 0;
  /* Field: File: File */
  $handler->display->display_options['fields']['rendered']['id'] = 'rendered';
  $handler->display->display_options['fields']['rendered']['table'] = 'file_managed';
  $handler->display->display_options['fields']['rendered']['field'] = 'rendered';
  $handler->display->display_options['fields']['rendered']['label'] = '';
  $handler->display->display_options['fields']['rendered']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['path'] = 'file/[fid]';
  $handler->display->display_options['fields']['rendered']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rendered']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rendered']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rendered']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rendered']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rendered']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rendered']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['rendered']['link_to_file'] = 0;
  $handler->display->display_options['fields']['rendered']['file_view_mode'] = 'media_preview';
  /* Field: File: Title */
  $handler->display->display_options['fields']['media_title']['id'] = 'media_title';
  $handler->display->display_options['fields']['media_title']['table'] = 'field_data_media_title';
  $handler->display->display_options['fields']['media_title']['field'] = 'media_title';
  $handler->display->display_options['fields']['media_title']['label'] = '';
  $handler->display->display_options['fields']['media_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['path'] = 'file/[fid] ';
  $handler->display->display_options['fields']['media_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['media_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['media_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['media_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['media_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['media_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['media_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['media_title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['media_title']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: File: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'file_managed';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'image' => 'image',
    'video' => 'video',
  );
  /* Filter criterion: File: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'file_managed';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';
  $export['media'] = $view;

  return $export;
}
