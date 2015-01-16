<?php

/**
 * Implements hook_views_default_views().
 */
function forward_views_default_views() {

  $view = new view();
  $view->name = 'forward_forwards';
  $view->description = 'Display nodes that have been forwarded the most times.';
  $view->tag = 'forward';
  $view->base_table = 'node';
  $view->human_name = 'Most forwarded';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Most forwarded';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  /* Field: Forward: Forward count */
  $handler->display->display_options['fields']['forward_count']['id'] = 'forward_count';
  $handler->display->display_options['fields']['forward_count']['table'] = 'forward_statistics';
  $handler->display->display_options['fields']['forward_count']['field'] = 'forward_count';
  $handler->display->display_options['fields']['forward_count']['label'] = 'Forwards';
  /* Sort criterion: Forward: Forward count */
  $handler->display->display_options['sorts']['forward_count']['id'] = 'forward_count';
  $handler->display->display_options['sorts']['forward_count']['table'] = 'forward_statistics';
  $handler->display->display_options['sorts']['forward_count']['field'] = 'forward_count';
  $handler->display->display_options['sorts']['forward_count']['order'] = 'DESC';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Forward: Forward count */
  $handler->display->display_options['filters']['forward_count']['id'] = 'forward_count';
  $handler->display->display_options['filters']['forward_count']['table'] = 'forward_statistics';
  $handler->display->display_options['filters']['forward_count']['field'] = 'forward_count';
  $handler->display->display_options['filters']['forward_count']['operator'] = '>=';
  $handler->display->display_options['filters']['forward_count']['value']['value'] = '1';
  $handler->display->display_options['filters']['forward_count']['group'] = '0';
  $handler->display->display_options['filters']['forward_count']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'forward_clickthroughs';
  $view->description = 'Display forwarded nodes with the most clickthroughs.';
  $view->tag = 'forward';
  $view->base_table = 'node';
  $view->human_name = 'Most clickthroughs';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Most clickthroughs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = 5;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  /* Field: Forward: Clickthrough count */
  $handler->display->display_options['fields']['clickthrough_count']['id'] = 'clickthrough_count';
  $handler->display->display_options['fields']['clickthrough_count']['table'] = 'forward_statistics';
  $handler->display->display_options['fields']['clickthrough_count']['field'] = 'clickthrough_count';
  $handler->display->display_options['fields']['clickthrough_count']['label'] = 'Clickthrough count';
  /* Sort criterion: Forward: Clickthrough count */
  $handler->display->display_options['sorts']['clickthrough_count']['id'] = 'clickthrough_count';
  $handler->display->display_options['sorts']['clickthrough_count']['table'] = 'forward_statistics';
  $handler->display->display_options['sorts']['clickthrough_count']['field'] = 'clickthrough_count';
  $handler->display->display_options['sorts']['clickthrough_count']['order'] = 'DESC';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Forward: Clickthrough count */
  $handler->display->display_options['filters']['clickthrough_count']['id'] = 'clickthrough_count';
  $handler->display->display_options['filters']['clickthrough_count']['table'] = 'forward_statistics';
  $handler->display->display_options['filters']['clickthrough_count']['field'] = 'clickthrough_count';
  $handler->display->display_options['filters']['clickthrough_count']['operator'] = '>=';
  $handler->display->display_options['filters']['clickthrough_count']['value']['value'] = '1';
  $handler->display->display_options['filters']['clickthrough_count']['group'] = '0';
  $handler->display->display_options['filters']['clickthrough_count']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'forward_recent';
  $view->description = 'Display the most recently forwarded nodes.';
  $view->tag = 'forward';
  $view->base_table = 'node';
  $view->human_name = 'Most recently forwarded';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Recent forwards';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = 5;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  /* Field: Forward: Most recent forward */
  $handler->display->display_options['fields']['last_forward_timestamp']['id'] = 'last_forward_timestamp';
  $handler->display->display_options['fields']['last_forward_timestamp']['table'] = 'forward_statistics';
  $handler->display->display_options['fields']['last_forward_timestamp']['field'] = 'last_forward_timestamp';
  $handler->display->display_options['fields']['last_forward_timestamp']['date_format'] = 'long';
  /* Sort criterion: Forward: Most recent forward */
  $handler->display->display_options['sorts']['last_forward_timestamp']['id'] = 'last_forward_timestamp';
  $handler->display->display_options['sorts']['last_forward_timestamp']['table'] = 'forward_statistics';
  $handler->display->display_options['sorts']['last_forward_timestamp']['field'] = 'last_forward_timestamp';
  $handler->display->display_options['sorts']['last_forward_timestamp']['order'] = 'DESC';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Forward: Forward count */
  $handler->display->display_options['filters']['forward_count']['id'] = 'forward_count';
  $handler->display->display_options['filters']['forward_count']['table'] = 'forward_statistics';
  $handler->display->display_options['filters']['forward_count']['field'] = 'forward_count';
  $handler->display->display_options['filters']['forward_count']['operator'] = '>=';
  $handler->display->display_options['filters']['forward_count']['value']['value'] = '1';
  $handler->display->display_options['filters']['forward_count']['group'] = '0';
  $handler->display->display_options['filters']['forward_count']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $views[$view->name] = $view;
  return $views;
}
