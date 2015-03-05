<?php
/**
 * @file
 * debut_bio.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_bio_ctools_plugin_api($module = NULL, $api = NULL) {
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
function debut_bio_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_profile2_type().
 */
function debut_bio_default_profile2_type() {
  $items = array();
  $items['bio'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "bio",
    "label" : "Author bio",
    "weight" : "0",
    "data" : { "registration" : 0 },
    "rdf_mapping" : []
  }');
  return $items;
}
