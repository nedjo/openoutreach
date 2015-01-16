<?php

/**
 * @file
 * Provides methods for loading and creating standard apps components.
 */

/**
 * Ensure the components specified by a set of modules are created.
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
 * Make sure a given vocabulary exists.
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
 * Make sure a given role exists.
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
 * Provide a set of standard vocabulary components for use in multiple apps.
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
 * Provide a set of standard role components for use in multiple apps.
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

