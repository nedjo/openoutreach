<?php

/**
 * @file
 * View templates for the Calendar module.
 *
 * Create calendar templates for every date field in the system.
 */

/**
 * Implements hook_views_templates().
 *
*/
function calendar_views_templates() {

  $views = array();

  // Map the base tables to entity types.
  $entity_info = entity_get_info();
  $base_tables = date_views_base_tables();

  // Find all the date fields we know about.

  $processed = array();

  foreach ($entity_info as $entity_type => $info) {
    if (!$info['fieldable']) {
      continue;
    }
    $items = field_info_instances($entity_type);
    $views_fields = date_views_fields($info['base table']);
    foreach ($views_fields['name'] as $name => $data) {
  
      // For each of the Field date fields, we need to find the bundle and entities this field is used on.
      if ($data['is_field']) {
        foreach ($items as $bundle => $widgets) {
          foreach ($widgets as $field_name => $widget) {
            $field = field_info_field($field_name);

            // See if this is a date field. Since fields might be shared
            // across bundles, make sure we haven't already processed this field.
            $alias = 'field_data_' . $field_name . '.' . $field_name . '_value';
            if ($alias == $name && !in_array($alias, $processed)) {
              $base_table = $base_tables[$entity_type];
              $calendar_option = array(
                'name' => 'calendar_' . $field_name,
                'description' => t("A calendar view of the '@field_name' field in the '@base_table' base table.", array('@base_table' => $base_table, '@field_name' => $field_name)),
                'path' => 'calendar-' . str_replace('_', '-', $field_name),
                'base_table' => $base_table,
                'field_name' => $field_name,
              );
              $view = calendar_views_template_construct($calendar_option);
              $views[$view->name] = $view;        
              $processed[] = $alias;
            }
          }
        }
      }

      // For other date fields, we infer the entity type from the base table.
      else {
        $parts = explode('.', $name);
        $base_table = $parts[0];
        $field_name = $parts[1];
        $calendar_option = array(
          'name' => 'calendar_' . $entity_type . '_' . $field_name,
          'description' => t("A calendar view of the '@field_name' field in the '@base_table' base table.", array('@base_table' => $base_table, '@field_name' => $field_name)),
          'path' => 'calendar-' . str_replace('_', '-', $field_name),
          'base_table' => $base_table,
          'field_name' => $field_name,
        );
        $view = calendar_views_template_construct($calendar_option);
        $views[$view->name] = $view;        
      }
    }
  }
 return $views;
}

/**
 * Helper function to construct a calendar template from an array of values.
 *
 * @param $options: 
 *   An array of options to create calendar templates.
 *
 * Possible options include:
 * @param string $base_table:
 *   The base table for the view.
 * @param string $name:
 *   The view name.
 * @param string $description:
 *   The view description.
 * @param string $path:
 *   The view url, if empty, defaults to 'calendar'.
 * @param string  $bundle:
 *   The bundle for this calendar.
 * @param string  $field_name:
 *   Date field used to filter the calendar.
 *
 * @return the default template array.
 */
function calendar_views_template_construct($options = NULL) {

$name        = $options['name'];
$description = $options['description'];
$path        = $options['path'];
$base_table  = $options['base_table'];
$field_name  = $options['field_name'];

$colors      = array();

if (substr($field_name, 0, 6) == 'field_') {
  $table = 'field_data_' . $field_name;
  $alias = $table . '.' . $field_name . '_value';
  $is_field = TRUE;
}
else {
  $table = $base_table;
  $alias = $table . '.' . $field_name;
  $is_field = FALSE;
}
$aliases     = array($alias => $alias);

$view = new view;
$view->name = $name;
$view->description = $description;
$view->tag = 'Calendar';
$view->base_table = $base_table;
$view->human_name = t("Calendar");
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */

$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = '';
$handler->display->display_options['link_display'] = 'page_1';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'month';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['row_plugin'] = 'calendar_entity';

/* Field: Title */

switch ($base_table) {

  case 'node':
  case 'node_revision':
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = $base_table;
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['title']['alter']['external'] = 0;
    $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 1;
    break;

  case 'users':
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = '';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['link_to_user'] = 1;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  break;
  
}

/* Date Field */

$handler->display->display_options['fields'][$field_name]['id'] = $field_name;
$handler->display->display_options['fields'][$field_name]['table'] = $table;
$handler->display->display_options['fields'][$field_name]['field'] = $field_name;
$handler->display->display_options['fields'][$field_name]['label'] = '';
$handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
$handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
$handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
$handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
$handler->display->display_options['fields'][$field_name]['element_label_colon'] = FALSE;
$handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
$handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
$handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
$handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;

if ($is_field) {
  $handler->display->display_options['fields'][$field_name]['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields'][$field_name]['group_rows'] = 0;
  $handler->display->display_options['fields'][$field_name]['delta_offset'] = '0';
  $handler->display->display_options['fields'][$field_name]['delta_reversed'] = 0;
  $handler->display->display_options['fields'][$field_name]['field_api_classes'] = 0;

  /* Sort criterion */
  $handler->display->display_options['sorts'][$field_name . '_value']['id'] = $field_name . '_value';
  $handler->display->display_options['sorts'][$field_name . '_value']['table'] = $table;
  $handler->display->display_options['sorts'][$field_name . '_value']['field'] = $field_name . '_value';

}
else {

  /* Sort criterion */
  $handler->display->display_options['sorts'][$field_name]['id'] = $field_name;
  $handler->display->display_options['sorts'][$field_name]['table'] = $table;
  $handler->display->display_options['sorts'][$field_name]['field'] = $field_name;

}

/* Filter criterion: Content: Published */

switch ($base_table) {

  case 'node':

    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = $base_table;
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    break;
}

/* Display: Month */

$handler = $view->new_display('page', 'Month', 'page_1');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'month';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['calendar_type'] = 'month';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'calendar_entity';
$handler->display->display_options['row_options']['calendar_date_link'] = '';
$handler->display->display_options['row_options']['colors']['legend'] = 'type';
$handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array();
$handler->display->display_options['row_options']['colors']['calendar_colors_vocabulary'] = array();
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;

/* Contextual filter: Date */

$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = $base_table;
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['year_range'] = '-3:+3';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'month';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = $aliases;
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'OR';
$handler->display->display_options['arguments']['date_argument']['date_group'] = 'date';
$handler->display->display_options['path'] = $path . '/month';
$handler->display->display_options['menu']['title'] = 'Month';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['tab_options']['type'] = 'normal';
$handler->display->display_options['tab_options']['title'] = 'Month';
$handler->display->display_options['tab_options']['weight'] = '0';

/* Display: Week */

$handler = $view->new_display('page', 'Week', 'page_2');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'week';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['calendar_type'] = 'week';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['groupby_times'] = 'hour';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'calendar_entity';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;

/* Contextual filter: Date */

$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = $base_table;
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['year_range'] = '-3:+3';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = $aliases;
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'OR';
$handler->display->display_options['arguments']['date_argument']['date_group'] = 'date';
$handler->display->display_options['path'] = $path . '/week';
$handler->display->display_options['menu']['title'] = 'Week';
$handler->display->display_options['menu']['weight'] = '2';

/* Display: Day */

$handler = $view->new_display('page', 'Day', 'page_3');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'day';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['calendar_type'] = 'day';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['style_options']['groupby_times'] = 'hour';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'calendar_entity';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;

/* Contextual filter: Date */

$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = $base_table;
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['year_range'] = '-3:+3';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = '';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = $aliases;
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'OR';
$handler->display->display_options['arguments']['date_argument']['date_group'] = 'date';
$handler->display->display_options['path'] = $path . '/day';
$handler->display->display_options['menu']['title'] = 'Day';
$handler->display->display_options['menu']['weight'] = '3';

/* Display: Year */

$handler = $view->new_display('page', 'Year', 'page');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'year';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['calendar_type'] = 'year';
$handler->display->display_options['style_options']['name_size'] = '1';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'calendar_entity';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;

/* Contextual filter: Date */

$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = $base_table;
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['year_range'] = '-3:+3';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = $aliases;
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'OR';
$handler->display->display_options['arguments']['date_argument']['date_group'] = 'date';
$handler->display->display_options['path'] = $path . '/year';
$handler->display->display_options['menu']['title'] = 'Year';
$handler->display->display_options['menu']['weight'] = '4';

/* Display: Block */

$handler = $view->new_display('block', 'Block', 'block_1');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'mini';
$handler->display->display_options['pager']['options']['pager_position'] = 'top';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['style_options']['calendar_type'] = 'month';
$handler->display->display_options['style_options']['name_size'] = '1';
$handler->display->display_options['style_options']['mini'] = '1';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'calendar_entity';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;

/* Contextual filter: Date */

$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = $base_table;
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['year_range'] = '-3:+3';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'month';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = $aliases;
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'OR';
$handler->display->display_options['arguments']['date_argument']['date_group'] = 'date';

if (module_exists('date_ical')) {

/* Display: iCal */

$handler = $view->new_display('feed', 'iCal', 'feed_1');
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['style_plugin'] = 'date_ical';
$handler->display->display_options['row_plugin'] = 'date_ical';
$handler->display->display_options['row_options']['date_field'] = $alias;
$handler->display->display_options['defaults']['filters'] = FALSE;

/* Filter criterion: Content: Published */

switch ($base_table) {

  case 'node':
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = $base_table;
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    break;
}

/* Filter criterion: Date */

$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = $base_table;
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['operator'] = '>=';
$handler->display->display_options['filters']['date_filter']['granularity'] = 'day';
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_select';
$handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
$handler->display->display_options['filters']['date_filter']['default_to_date'] = '';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-3:+3';
$handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
$handler->display->display_options['filters']['date_filter']['date_fields'] = $aliases;
$handler->display->display_options['filters']['date_filter']['date_method'] = 'OR';
$handler->display->display_options['filters']['date_filter']['date_group'] = 'date';
$handler->display->display_options['path'] = $path . '/ical/%/calendar.ics';
$handler->display->display_options['displays'] = array(
  'page' => 'page',
  'page_1' => 'page_1',
  'page_2' => 'page_2',
  'page_3' => 'page_3',
  'block_1' => 'block_1',
  'default' => 0,
);

} // End if module_exists()

/* Display: Upcoming */

$handler = $view->new_display('block', 'Upcoming', 'block_2');
$handler->display->display_options['display_description'] = 'Upcoming events block';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '5';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['links'] = 1;
$handler->display->display_options['row_options']['comments'] = 0;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;

/* Filter criterion: Content: Published */

switch ($base_table) {

  case 'node':

    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = $base_table;
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    break;
}

/* Filter criterion: Date */

$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = $base_table;
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['operator'] = '>=';
$handler->display->display_options['filters']['date_filter']['granularity'] = 'day';
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_select';
$handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
$handler->display->display_options['filters']['date_filter']['default_to_date'] = '';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-3:+3';
$handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
$handler->display->display_options['filters']['date_filter']['date_fields'] = $aliases;
$handler->display->display_options['filters']['date_filter']['date_method'] = 'OR';
$handler->display->display_options['filters']['date_filter']['date_group'] = 'date';

$translatables[$name] = array(
  t('Master'),
  t($name),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Year'),
  t('All'),
  t('Month'),
  t('Week'),
  t('Day'),
  t('Block'),
  t('iCal'),
  t('Upcoming'),
  t('Upcoming events block'),
);


return $view;

}
