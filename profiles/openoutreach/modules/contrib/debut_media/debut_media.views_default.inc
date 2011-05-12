<?php
/**
 * @file
 * debut_media.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function debut_media_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'media';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'file_managed';
  $view->human_name = 'Media';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_text'] = '';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
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
  $handler->display->display_options['fields']['fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['fid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['fid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['fid']['link_to_file'] = 0;
  /* Field: Media: File */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_file';
  $handler->display->display_options['fields']['entity_id']['field'] = 'file';
  $handler->display->display_options['fields']['entity_id']['label'] = '';
  $handler->display->display_options['fields']['entity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['path'] = 'media/[fid]';
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['entity_id']['type'] = 'styles_file_square_thumbnail';
  /* Sort criterion: File: Upload date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    0 => 'OR',
  );

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
  $handler->display->display_options['path'] = 'media';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';

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
  /* Filter criterion: File: Mime type */
  $handler->display->display_options['filters']['filemime']['id'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['table'] = 'file_managed';
  $handler->display->display_options['filters']['filemime']['field'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['operator'] = 'contains';
  $handler->display->display_options['filters']['filemime']['value'] = 'image';
  $handler->display->display_options['path'] = 'media/image';
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
  /* Filter criterion: File: Mime type */
  $handler->display->display_options['filters']['filemime']['id'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['table'] = 'file_managed';
  $handler->display->display_options['filters']['filemime']['field'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['operator'] = 'contains';
  $handler->display->display_options['filters']['filemime']['value'] = 'video';
  $handler->display->display_options['path'] = 'media/video';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Page: Single item */
  $handler = $view->new_display('page', 'Page: Single item', 'page_4');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Media: File */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_file';
  $handler->display->display_options['fields']['entity_id']['field'] = 'file';
  $handler->display->display_options['fields']['entity_id']['label'] = '';
  $handler->display->display_options['fields']['entity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['entity_id']['type'] = 'styles_file_large';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Fields: File (file) - fid */
  $handler->display->display_options['arguments']['file_fid']['id'] = 'file_fid';
  $handler->display->display_options['arguments']['file_fid']['table'] = 'field_data_file';
  $handler->display->display_options['arguments']['file_fid']['field'] = 'file_fid';
  $handler->display->display_options['arguments']['file_fid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['file_fid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['file_fid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['file_fid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['file_fid']['not'] = 0;
  $handler->display->display_options['path'] = 'media/%';
  $translatables['media'] = array(
    t('Defaults'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('File ID'),
    t('media/[fid]'),
    t('Page: Media'),
    t('Multimedia'),
    t('more'),
    t('Page: Images'),
    t('Images'),
    t('Page: Video'),
    t('Videos'),
    t('Page: Single item'),
    t('All'),
  );
  $export['media'] = $view;

  return $export;
}
