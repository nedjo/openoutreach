<?php
// $Id: calendar.views_default.inc,v 1.14 2011/01/18 00:37:21 karens Exp $

/**
 * @file
 * Default views for the Calendar module.
 */

/**
 * Set up so it can be used as an API to create default calendars for
 * specific date fields.
 * 
 * Use variable_set() to establish criteria for default calendars.
 * Set the variable in custom modules or in settings. 
 * 
 * Example: Add a new default calendar to custom
 * calendars that are already configured:
 *  
 * $options = variable_get('calendar_default_view_options', array());
 * $option = array(
 *   'name' => 'example_event',
 *   'description' => 'An example event calendar for the date field.',
 *   'path' => 'example_event',
 *   'types' => array('example_content_type'),
 *   'date_fields' => array('field_example_date'),
 *   );
 * $options[] = $option;
 * variable_set('calendar_default_view_options', $options);
 * 
*/
function calendar_views_default_views() {
  $views = array();

  // Construct the default view with default options.
  $view = calendar_views_construct();
  $views[$view->name] = $view;

  // Then see if there are any custom calendars to be created 
  // using variable_get().
  $calendar_options = variable_get('calendar_default_view_options', array());
  foreach ((array) $calendar_options as $calendar_option) {
    $view = calendar_views_construct($calendar_option);
    $views[$view->name] = $view;
  }
  return $views;
}

/**
 * 
 * Construct a default calendar to match specified options.
 * Views calls it without options, so the basic 
 * default view will use the default values.
 * 
 * @param $options: an optional array of options to 
 * create default calendars.
 * 
 * Possible options include:
 * @param string $name:           
 *   The view name, if empty, defaults to 'calendar'.
 * @param string $description:           
 *   The view description, if empty, defaults to generic description.
 * @param string $path:           
 *   The view url, if empty, defaults to 'calendar'.
 * @param array  $types:          
 *   Array of content types to limit the calendar to those types.  
 *   If empty, defaults to no type filter.
 * @param array  $date_fields:    
 *   Date fields used to filter the calendar.
 *   If empty, defaults to array('changed') for node.changed.
 * @param array  $display_fields: 
 *   Fields to display in the calendar.
 *   If empty, defaults to title and date fields.
 * 
 * @return the default calendar array.
 */
function calendar_views_construct($options = NULL) {
$name = NULL;
$description = NULL;
$path = NULL;
$types = NULL;
$date_fields = NULL;
$display_fields = NULL;

if (empty($options)) {
  $disabled = TRUE;
}
else {
  $disabled = FALSE;
  extract($options);
}
if (empty($name)) {
  $name = 'calendar';
}
if (empty($description)) {
  $description = 'A multi-dimensional calendar view with back/next navigation.';
}
if (empty($path)) {
  $path = 'calendar';
}
if (empty($types)) {
  $types = array();
}
if (empty($date_fields)) {
  $date_fields = array('changed');
}
$colors = array();
$date_link_type = '';
foreach ($types as $type => $label) {
  $colors[0][$type] = '#ffffff';
  $date_link_type = $type;
}

// Can handle core node timestamp fields or Field date fields.

$fields = array();
$upcoming_fields = array();

foreach ($date_fields as $key => $field_name) {
  if (substr($field_name, 0, 6) == 'field_') {
    $table = 'field_data_' . $field_name;
    $alias = $table . '.' . $field_name . '_value';
    $cck_field = TRUE;
  }
  else {
    $table = 'node';
    $alias = $table . '.' . $field_name;
    $cck_field = FALSE;
  }
  $fields[$alias] = $alias;
}

// Set up fields section with some of the basic options.
// Won't handle all possible options, but should cover
// the main ones needed for Drupal core and CCK fields.

if (empty($display_fields)) {
  $display_fields = array('title' => array());
  foreach ($date_fields as $field) {
    $display_fields[$field] = array();
  }
}

foreach ($display_fields as $key => $value) {
  $cck_field = substr($key, 0, 6) == 'field_' ? TRUE : FALSE;
  $date_field = $cck_field && in_array($key, $date_fields) ? TRUE : FALSE;
  $index = $cck_field ? 'entity_id' : $key;
  $display_fields[$index]['label'] = '';
  $display_fields[$index]['link_to_node'] = $key == 'title' ? 1 : 0;
  $display_fields[$index]['id'] = $cck_field ? 'entity_id' : $key;
  $display_fields[$index]['field'] = $cck_field ? 'entity_id' : $key;
  $display_fields[$index]['table'] = $cck_field ? 'field_data_' . $key : 'node';
  $display_fields[$index]['relationship'] = 'none';
  $display_fields[$index]['alter']['alter_text'] = 0;
  $display_fields[$index]['alter']['make_link'] = 0;
  $display_fields[$index]['alter']['absolute'] = 0;
  $display_fields[$index]['alter']['trim'] = 0;
  $display_fields[$index]['alter']['word_boundary'] = 0;
  $display_fields[$index]['alter']['ellipsis'] = 0;
  $display_fields[$index]['alter']['strip_tags'] = 0;
  $display_fields[$index]['alter']['html'] = 0;
  if (in_array($key, array('changed'))) {
    $display_fields[$index]['date_format'] = 'small';
  }
  elseif ($cck_field) {
    $display_fields[$index]['settings'] = array(
      'format_type' => 'short',
      'fromto' => 'both',
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_to' => '',
      'show_repeat_rule' => 'show',
      );
    unset($display_fields[$key]);  
  }
  // Upcoming and iCal fields should display the whole date, not just time.
  $upcoming_fields[$index] = $display_fields[$index];
  $upcoming_fields[$index]['settings']['format_type'] = 'long';
}

$view = new view;
$view->name = $name;
$view->description = $description;
$view->tag = 'Calendar';
$view->base_table = 'node';
$view->api_version = '3.0-alpha1';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Calendar';
$handler->display->display_options['items_per_page'] = 0;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'calendar_nav';

/* Field: Node: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['link_to_node'] = 1;

$handler->display->display_options['fields'] = $display_fields;

/* Argument: Date: Date (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['style_plugin'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'month';
$handler->display->display_options['arguments']['date_argument']['wildcard'] = 'All';
$handler->display->display_options['arguments']['date_argument']['date_fields'] =  $fields;
/* Filter: Node: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Filter: Node: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = drupal_map_assoc($types);

/* Display: Calendar page */
$handler = $view->new_display('calendar', 'Calendar page', 'calendar_1');
$handler->display->display_options['items_per_page'] = 0;
$handler->display->display_options['style_plugin'] = 'calendar_nav';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['path'] = $path;
$handler->display->display_options['calendar_colors'] = $colors;
$handler->display->display_options['calendar_colors_vocabulary'] = array();
$handler->display->display_options['calendar_colors_group'] = array();

// DODO This got lost in D7 version.
$handler->display->display_options['calendar_date_link'] = $date_link_type;

/* Display: Calendar block */
$handler = $view->new_display('calendar_block', 'Calendar block', 'calendar_block_1');
$handler->display->display_options['items_per_page'] = 0;
$handler->display->display_options['style_plugin'] = 'calendar_nav';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['block_description'] = 'Calendar';

/* Display: Year view */
$handler = $view->new_display('calendar_period', 'Year view', 'calendar_period_1');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['attachment_position'] = 'after';
$handler->display->display_options['inherit_exposed_filters'] = TRUE;
$handler->display->display_options['calendar_type'] = 'year';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
);

/* Display: Month view */
$handler = $view->new_display('calendar_period', 'Month view', 'calendar_period_2');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['attachment_position'] = 'after';

if (module_exists('calendar_multiday')) {
  $handler->display->display_options['style_options']['theme_style'] = 1;  
}

$handler->display->display_options['inherit_exposed_filters'] = TRUE;
$handler->display->display_options['calendar_type'] = 'month';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
);

/* Display: Day view */
$handler = $view->new_display('calendar_period', 'Day view', 'calendar_period_3');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['attachment_position'] = 'after';

if (module_exists('calendar_multiday')) {
  $handler->display->display_options['style_options']['theme_style'] = 1;  
}

$handler->display->display_options['inherit_exposed_filters'] = TRUE;
$handler->display->display_options['calendar_type'] = 'day';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
);

/* Display: Week view */
$handler = $view->new_display('calendar_period', 'Week view', 'calendar_period_4');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['defaults']['style_options'] = FALSE;

if (module_exists('calendar_multiday')) {
  $handler->display->display_options['style_options']['theme_style'] = 1;  
}

$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['attachment_position'] = 'after';
$handler->display->display_options['inherit_exposed_filters'] = TRUE;
$handler->display->display_options['calendar_type'] = 'week';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
);

/* Display: Block view */
$handler = $view->new_display('calendar_period', 'Block view', 'calendar_period_5');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'calendar_style';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['attachment_position'] = 'after';
$handler->display->display_options['inherit_exposed_filters'] = TRUE;
$handler->display->display_options['calendar_type'] = 'month';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 0,
  'default' => 0,
  'calendar_block_1' => 'calendar_block_1',
);

/* Display: Upcoming */
$handler = $view->new_display('block', 'Upcoming', 'block_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Upcoming';
$handler->display->display_options['defaults']['items_per_page'] = FALSE;
$handler->display->display_options['defaults']['use_more'] = FALSE;
$handler->display->display_options['use_more'] = TRUE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '5';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;

/* Field: Node: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['link_to_node'] = 1;

$handler->display->display_options['fields'] = $upcoming_fields;

$handler->display->display_options['defaults']['arguments'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;

/* Filter: Node: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter: Date: Date (node) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'node';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['operator'] = '>=';
$handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
$handler->display->display_options['filters']['date_filter']['date_fields'] = $fields;
$handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
$handler->display->display_options['block_description'] = 'Upcoming';

// iCal feed.
if (module_exists('calendar_ical')) {
/* Display: iCal feed */
$handler = $view->new_display('calendar_ical', 'iCal feed', 'calendar_ical_1');
$handler->display->display_options['style_plugin'] = 'ical';
$handler->display->display_options['style_options']['mission_description'] = FALSE;
$handler->display->display_options['style_options']['summary_field'] = 'title';
$handler->display->display_options['defaults']['arguments'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter: Node: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter: Node: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = $types;
/* Filter: Date: Date (node) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'node';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['operator'] = '>=';
$handler->display->display_options['filters']['date_filter']['date_fields'] = $fields;
$handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
$handler->display->display_options['path'] = $path . '/ical';
$handler->display->display_options['displays'] = array(
  'calendar_1' => 'calendar_1',
  'calendar_block_1' => 'calendar_block_1',
  'default' => 0,
  'block_1' => 0,
);

}

return $view;

}
