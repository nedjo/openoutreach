<?php
/**
 * @file
 * debut_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_event_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_event_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
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
  drupal_alter('node_info', $items);
  return $items;
}
