<?php

/**
 * Enable social links for content types provided by a set of modules.
 *
 * To activate service links for its node type, a feature should include the
 * following in its .info file:
 * debut[social][node_types][my_content_type] = my_content_type
 * where my_content_type is the name of a feature-provided content type.
 *
 * The social links status of a feature's content type can be altered by using
 * hook_system_info_alter(). Example:
 * %code
 * function example_system_info_alter(&$info, $module, $type) {
 *   if ($type == $module && $module->name == 'debut_article') {
 *     unset($info['debut']['social']['article']);
 *   }
 * }
 * %endcode
 */
function debut_social_add_node_types($modules) {
  $social_types = array();

  // Load info of feature modules.
  $features = array_intersect_key(features_get_features(), drupal_map_assoc($modules));

  foreach ($features as $feature) {
    $info = $feature->info;

    if (isset($info['features']['node'])) {
      foreach ($info['features']['node'] as $type) {
        if (isset($info['debut']) && isset($info['debut']['social']) && isset($info['debut']['social']['node_types']) && in_array($type, $info['debut']['social']['node_types'])) {
          $social_types[$type] = $type;
        }
        // Unset follow display only for Debut features.
        elseif (strpos($feature->name, 'debut') === 0) {
          // Follow defaults to TRUE. If this is not a social node type,
          // explicitly exclude it from follow display.
          variable_set('forward_display_' . $type, FALSE);
        }
      }
    }
  }
  if (!empty($social_types)) {
    // Merge into the existing value so as not to overwrite existing settings.
    $service_links_node_types = array_merge(variable_get('service_links_node_types', array()), $social_types);
    variable_set('service_links_node_types', $service_links_node_types);
  }
}
