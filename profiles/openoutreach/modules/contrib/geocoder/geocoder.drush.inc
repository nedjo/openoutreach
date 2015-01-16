<?php

/**
 * Implementation of hook_drush_command().
 */
function geocoder_drush_command() {
  $items = array();
  
  // the key in the $items array is the name of the command.
  $items['geocoder-backfill'] = array(
    'callback' => 'geocoder_drush_backfill',
    'description' => "Geocodes all nodes that have a geocoder widget but no geodata.",
  );
  
  return $items;
}

function geocoder_drush_backfill() {
  $all_entity_info = entity_get_info();
  foreach ($all_entity_info as $entity_type => $entity_info) {
    if ($entity_type == 'node') { //TODO: FIX THE LOGIC BELOW and implement for all entities
      if ($entity_info['fieldable']) {
        foreach ($entity_info['bundles'] as $bundle_name => $bundle_info) {
          foreach (field_info_instances($entity_type, $bundle_name) as $field_name => $field_instance) {
            $field_info = field_info_field($field_name);
            if ($field_instance['widget']['type'] === 'geocoder') {
              $entity_load = $entity_info['load hook'];
              
              $query = db_select($entity_info['base table'])
                         ->fields($entity_info['base table'], array($entity_info['entity keys']['id']))
                         ->condition($entity_info['entity keys']['bundle'], $bundle_name);
              
              $results = $query->execute();
              while ($id = $results->fetchField()) {
                $entity = $entity_load($id);
                $langcode = field_language($entity_type, $entity, $field_name);
                $items = field_get_items($entity_type, $entity, $field_name, $langcode);
                
                // Check for values and if there are no values, reload the entity
                if ($field_info['type'] == 'geofield') {
                  if (empty($items['wkt'])) node_save($entity); //TODO: fix for all entities
                }
                if ($field_info['type'] == 'location') {
                  if (empty($items['latitude'])) node_save($entity); //TODO: fix for all entities
                }
                if ($field_info['type'] == 'geolocation') {
                  if (empty($items['lat'])) node_save($entity); //TODO: fix for all entities
                }
              }
            }
          }
        }
      }
    }
  }
}