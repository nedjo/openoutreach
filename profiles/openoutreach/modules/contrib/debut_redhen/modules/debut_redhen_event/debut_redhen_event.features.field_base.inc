<?php
/**
 * @file
 * debut_redhen_event.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function debut_redhen_event_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_registration'
  $field_bases['field_registration'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_registration',
    'indexes' => array(
      'registration_type' => array(
        0 => 'registration_type',
      ),
    ),
    'locked' => 0,
    'module' => 'registration',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'registration',
  );

  return $field_bases;
}
