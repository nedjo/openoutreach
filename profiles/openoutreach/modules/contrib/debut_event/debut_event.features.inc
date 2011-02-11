<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function debut_event_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
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

/**
 * Implementation of hook_views_api().
 */
function debut_event_views_api() {
  return array(
    'api' => '3.0-alpha1',
  );
}
