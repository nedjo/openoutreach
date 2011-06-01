<?php

/**
 * Enable social links for content types provided by a set of modules.
 */
function debut_social_add_node_types($modules) {
  $node_types = array();
  foreach ($modules as $module) {
    $info = drupal_parse_info_file(drupal_get_path('module', $module) . '/' . $module . '.info');
    if (isset($info['debut']) && isset($info['debut']['social']) && isset($info['debut']['social']['node_types'])) {
      // Key the array by node type to match the format of the 'service_links_node_types' variable.
      $node_types = array_merge($node_types, array_combine($info['debut']['social']['node_types'], $info['debut']['social']['node_types']));
    }
  }
  if (!empty($node_types)) {
    $service_links_node_types = array_merge(variable_get('service_links_node_types', array()), $node_types);
    variable_set('service_links_node_types', $service_links_node_types);
  }
}
