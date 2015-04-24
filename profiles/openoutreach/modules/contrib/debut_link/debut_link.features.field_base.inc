<?php
/**
 * @file
 * debut_link.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function debut_link_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_link_term'
  $field_bases['field_link_term'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_term',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'parent' => 0,
          'vocabulary' => 'link_terms',
        ),
      ),
    ),
    'translatable' => 1,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
