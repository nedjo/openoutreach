<?php
/**
 * @file
 * debut_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_event_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_event_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function debut_event_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('An event has a start date and time as well as an optional end date and time.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Give your event a title and an optional description.'),
    ),
  );
  return $items;
}
