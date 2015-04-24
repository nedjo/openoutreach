<?php
/**
 * @file
 * debut_highlighted.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function debut_highlighted_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_kicker'
  $field_bases['field_kicker'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_kicker',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
