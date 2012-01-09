<?php
/**
 * @file
 * debut_highlighted.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function debut_highlighted_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'highlighted';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Highlighted';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'slideshow';
  $handler->display->display_options['style_options']['slideshow_type'] = 'views_slideshow_cycle';
  $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
  $handler->display->display_options['style_options']['skin_info'] = array(
    'class' => 'default',
    'name' => 'Default',
    'module' => 'views_slideshow',
    'path' => '',
    'stylesheets' => array(),
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['enable'] = 1;
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'counter' => 'counter',
    'field_link' => 0,
    'field_content_image' => 0,
    'title' => 0,
    'field_kicker' => 0,
    'nothing' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_link' => 0,
    'field_content_image' => 0,
    'title' => 0,
    'field_kicker' => 0,
    'nothing' => 0,
    'counter' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['hide_on_single_slide'] = 1;
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['transition_advanced'] = 1;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['timeout'] = '6000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['speed'] = '700';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['delay'] = '1000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['start_paused'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['remember_slide_days'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['wait_for_image_load_timeout'] = '3000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartype'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartypenobg'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_link']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_link']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_link']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_link']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_link']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_link']['type'] = 'link_plain';
  $handler->display->display_options['fields']['field_link']['field_api_classes'] = 0;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_content_image']['id'] = 'field_content_image';
  $handler->display->display_options['fields']['field_content_image']['table'] = 'field_data_field_content_image';
  $handler->display->display_options['fields']['field_content_image']['field'] = 'field_content_image';
  $handler->display->display_options['fields']['field_content_image']['label'] = '';
  $handler->display->display_options['fields']['field_content_image']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['text'] = '<a href="[field_link]">[field_content_image]</a>';
  $handler->display->display_options['fields']['field_content_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_content_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_content_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_content_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_content_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_content_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_content_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_content_image']['settings'] = array(
    'image_style' => 'highlighted_full',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_content_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Kicker */
  $handler->display->display_options['fields']['field_kicker']['id'] = 'field_kicker';
  $handler->display->display_options['fields']['field_kicker']['table'] = 'field_data_field_kicker';
  $handler->display->display_options['fields']['field_kicker']['field'] = 'field_kicker';
  $handler->display->display_options['fields']['field_kicker']['label'] = '';
  $handler->display->display_options['fields']['field_kicker']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_kicker']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['path'] = '[field_link]';
  $handler->display->display_options['fields']['field_kicker']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_kicker']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_kicker']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_kicker']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_kicker']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kicker']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_kicker']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_kicker']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_kicker']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_kicker']['field_api_classes'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="views-slideshow-overlay">
<h2><a href="[field_link]">[title]</a></h2>
<h4>[field_kicker]</h4>
<a href="[field_link]" class="views-slideshow-button">Read more</a>
</div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 1;
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['exclude'] = TRUE;
  $handler->display->display_options['fields']['counter']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['text'] = '<a href="#">[counter]</a>';
  $handler->display->display_options['fields']['counter']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['path'] = '#';
  $handler->display->display_options['fields']['counter']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['external'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['html'] = 0;
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['counter']['hide_empty'] = 0;
  $handler->display->display_options['fields']['counter']['empty_zero'] = 0;
  $handler->display->display_options['fields']['counter']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'highlighted' => 'highlighted',
  );

  /* Display: Block: Content width slideshow */
  $handler = $view->new_display('block', 'Block: Content width slideshow', 'block_content');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_link']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_link']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_link']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_link']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_link']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_link']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_link']['type'] = 'link_plain';
  $handler->display->display_options['fields']['field_link']['field_api_classes'] = 0;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_content_image']['id'] = 'field_content_image';
  $handler->display->display_options['fields']['field_content_image']['table'] = 'field_data_field_content_image';
  $handler->display->display_options['fields']['field_content_image']['field'] = 'field_content_image';
  $handler->display->display_options['fields']['field_content_image']['label'] = '';
  $handler->display->display_options['fields']['field_content_image']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['text'] = '<a href="[field_link]">[field_content_image]</a>';
  $handler->display->display_options['fields']['field_content_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_content_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_content_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_content_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_content_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_content_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_content_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_content_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_content_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_content_image']['settings'] = array(
    'image_style' => 'highlighted',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_content_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Kicker */
  $handler->display->display_options['fields']['field_kicker']['id'] = 'field_kicker';
  $handler->display->display_options['fields']['field_kicker']['table'] = 'field_data_field_kicker';
  $handler->display->display_options['fields']['field_kicker']['field'] = 'field_kicker';
  $handler->display->display_options['fields']['field_kicker']['label'] = '';
  $handler->display->display_options['fields']['field_kicker']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_kicker']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['path'] = '[field_link]';
  $handler->display->display_options['fields']['field_kicker']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_kicker']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_kicker']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_kicker']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_kicker']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_kicker']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kicker']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_kicker']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_kicker']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_kicker']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_kicker']['field_api_classes'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="views-slideshow-overlay">
<h2><a href="[field_link]">[title]</a></h2>
<h4>[field_kicker]</h4>
<a href="[field_link]" class="views-slideshow-button">Read more</a>
</div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 1;
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['exclude'] = TRUE;
  $handler->display->display_options['fields']['counter']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['text'] = '<a href="#">[counter]</a>';
  $handler->display->display_options['fields']['counter']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['path'] = '#';
  $handler->display->display_options['fields']['counter']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['external'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['counter']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['counter']['alter']['html'] = 0;
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['counter']['hide_empty'] = 0;
  $handler->display->display_options['fields']['counter']['empty_zero'] = 0;
  $handler->display->display_options['fields']['counter']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  $handler->display->display_options['block_description'] = 'Highlighted content width';

  /* Display: Block: Full width slideshow */
  $handler = $view->new_display('block', 'Block: Full width slideshow', 'block_full');
  $handler->display->display_options['block_description'] = 'Highlighted full width';
  $export['highlighted'] = $view;

  return $export;
}
