<?php
/**
 * @file
 * debut_redhen_event.features.inc
 */

/**
 * Implements hook_views_api().
 */
function debut_redhen_event_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_registration_type().
 */
function debut_redhen_event_default_registration_type() {
  $items = array();
  $items['standard'] = entity_import('registration_type', '{
    "name" : "standard",
    "label" : "Standard registration",
    "locked" : "0",
    "weight" : "0",
    "data" : null,
    "rdf_mapping" : []
  }');
  return $items;
}
