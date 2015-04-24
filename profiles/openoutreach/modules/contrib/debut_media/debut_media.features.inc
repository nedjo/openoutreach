<?php
/**
 * @file
 * debut_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_media_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function debut_media_image_default_styles() {
  $styles = array();

  // Exported image style: medium_large.
  $styles['medium_large'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 360,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'Medium large',
  );

  // Exported image style: small_square_thumbnail.
  $styles['small_square_thumbnail'] = array(
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 100,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'Small square thumbnail',
  );

  return $styles;
}
