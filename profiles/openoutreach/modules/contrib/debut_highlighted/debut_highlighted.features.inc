<?php
/**
 * @file
 * debut_highlighted.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_highlighted_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_highlighted_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function debut_highlighted_image_default_styles() {
  $styles = array();

  // Exported image style: highlighted.
  $styles['highlighted'] = array(
    'label' => 'Highlighted',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 830,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      4 => array(
        'name' => 'image_crop',
        'data' => array(
          'width' => 830,
          'height' => 360,
          'anchor' => 'center-center',
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlighted_full.
  $styles['highlighted_full'] = array(
    'label' => 'Highlighted full',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1140,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      2 => array(
        'name' => 'image_crop',
        'data' => array(
          'width' => 1140,
          'height' => 300,
          'anchor' => 'center-center',
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function debut_highlighted_node_info() {
  $items = array(
    'highlighted' => array(
      'name' => t('Highlighted'),
      'base' => 'node_content',
      'description' => t('For displaying images and brief text that will be displayed on the home page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
