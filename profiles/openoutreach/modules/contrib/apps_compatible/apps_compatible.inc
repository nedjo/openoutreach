<?php

/**
 * @file
 * Provides methods for loading and creating standard apps components.
 */

/**
 * Ensures the components specified by a set of modules are created.
 *
 * @param $modules
 *   An array of module names to ensure components for.
 */
function apps_compatible_ensure_components($modules) {
  $info = apps_compatible_info(NULL, $modules);
  foreach ($info as $type => $components) {
    $function = 'apps_compatible_ensure_' . $type;
    $function($components);
  }
}

/**
 * Ensures a given vocabulary exists.
 *
 * @param $items
 *   An array of items to be fetched and created.
 */
function apps_compatible_ensure_vocabulary($items) {
  $vocabularies = apps_compatible_vocabularies();
  foreach ($items as $item) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($item['machine name']);
    // If there isn't an existing vocabulary with this machine name, create
    // one.
    if (!$vocabulary && isset($vocabularies[$item['machine name']])) {
      taxonomy_vocabulary_save((object) $vocabularies[$item['machine name']]);
    }
  }
}

/**
 * Ensures a given role exists.
 *
 * @param $items
 *   An array of items to be fetched and created.
 */
function apps_compatible_ensure_role($items) {
  $roles = apps_compatible_roles();
  foreach ($items as $item) {
    $role = user_role_load_by_name($item['machine name']);
    // If there isn't an existing role by this name, create one.
    if (!$role && isset($roles[$item['machine name']])) {
      $role = (object) $roles[$item['machine name']];
      user_role_save($role);
    }
  }
}

/**
 * Ensures a given field base exists.
 *
 * @param $items
 *   An array of items to be fetched and created.
 */
function apps_compatible_ensure_field_base($items) {
  $fields = apps_compatible_field_bases();

  field_info_cache_clear();

  // Load all the existing field bases up-front so that we don't
  // have to rebuild the cache all the time.
  $existing_fields = field_info_fields();

  foreach ($items as $item) {
    $field = $fields[$item['machine name']];
    // Create or update field.
    if (isset($existing_fields[$field['field_name']])) {
      $existing_field = $existing_fields[$field['field_name']];
      if ($field + $existing_field !== $existing_field) {
        field_update_field($field);
      }
    }
    else {
      field_create_field($field);
      $existing_fields[$field['field_name']] = $field;
    }
    variable_set('menu_rebuild_needed', TRUE);
  }
}

/**
 * Provides a set of standard vocabulary components for use in multiple apps.
 *
 * @return
 *   An array of items to be created.
 */
function apps_compatible_vocabularies() {
  // Use the same format used by the Features module.
  return array(
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => 'Use tags to group content on similar topics into categories.',
      'help' => 'Enter a comma-separated list of words to describe your content.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}

/**
 * Provides a set of standard role components for use in multiple apps.
 *
 * @return
 *   An array of items to be created.
 */
function apps_compatible_roles() {
  // Use the same format used by the Features module.
  // @todo: should we be assigning weights?
  $roles = array();

  $roles['administrator'] = array(
    'name' => 'administrator',
  );

  $roles['contributor'] = array(
    'name' => 'contributor',
  );

  $roles['editor'] = array(
    'name' => 'editor',
  );

  $roles['manager'] = array(
    'name' => 'manager',
  );

  $roles['member'] = array(
    'name' => 'member',
  );

  return $roles;
}

/**
 * Provides a set of standard field bases for use in multiple apps.
 *
 * @return
 *   An array of items to be created.
 */
function apps_compatible_field_bases() {
  // Use the same format used by the Features module.
  $field_bases = array();

  // Exported field_base: 'body'
  $field_bases['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
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
    'translatable' => 1,
    'type' => 'text_with_summary',
  );

  // Exported field_base: 'field_address'
  $field_bases['field_address'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_address',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'addressfield',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'addressfield',
  );

  // Exported field_base: 'field_content_image'
  $field_bases['field_content_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_content_image',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'public',
    ),
    'translatable' => 1,
    'type' => 'image',
  );

  // Exported field_base: 'field_link'
  $field_bases['field_link'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'profile2_private' => FALSE,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 1,
    'type' => 'link_field',
  );

  // Exported field_base: 'field_media'
  $field_bases['field_media'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_media',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'file',
    'settings' => array(
      'display_default' => 0,
      'display_field' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'file',
  );

  // Exported field_base: 'field_tags'
  $field_bases['field_tags'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_tags',
    'foreign keys' => array(
      'tid' => array(
        'columns' => array(
          'tid' => 'tid',
        ),
        'table' => 'taxonomy_term_data',
      ),
    ),
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
          'vocabulary' => 'tags',
          'parent' => 0,
        ),
      ),
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
