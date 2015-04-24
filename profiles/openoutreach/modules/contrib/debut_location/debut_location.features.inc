<?php
/**
 * @file
 * debut_location.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_location_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "openlayers" && $api == "openlayers_maps") {
    return array("version" => "1");
  }
  if ($module == "openlayers" && $api == "openlayers_styles") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_location_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function debut_location_image_default_styles() {
  $styles = array();

  // Exported image style: icon_small.
  $styles['icon_small'] = array(
    'effects' => array(
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 25,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'Icon small',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function debut_location_node_info() {
  $items = array(
    'location' => array(
      'name' => t('Location'),
      'base' => 'node_content',
      'description' => t('A physical location.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
