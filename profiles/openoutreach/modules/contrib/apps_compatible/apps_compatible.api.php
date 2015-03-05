<?php

/**
 * @file
 * Hooks provided by the Apps compatible module. Implementations of these hooks
 * should be placed in a $modulename.apps_compatible.inc file, which will be
 * loaded when needed.
 */

/**
 * Define app components to be programmatically handled.
 *
 * This hook allows a module to define one or more of each of several component
 * types to be programmatically created by the app_compatible module.
 *
 * @return
 *   An array of information defining components of distinct types that are to
 *   be created. The array contains a sub-array of items of each type to be
 *   created, with the type name as key. Components to be created are keyed by
 *   machine-readable name and each item itself being a sub_array. Valid types:
 *   - "role": an array keyed by role name with the following attribute:
 *      - "machine name": the machine-readable name of the field.
 *   - "field": an array of field bases defined by app_compatible for which
 *     fieldbases should be created, keyed by field machine-readable name and
 *     with the following attribute:
 *      - "machine name": the machine-readable name of the field base.
 *   - "vocabulary": an array of vocabularies defined by app_compatible to be
 *     created, keyed by vocabulary machine name, with the following
 *     attribute:
 *      - "machine name": the machine-readable name of the field.
 */
function hook_apps_compatible_info() {
  return array(
    // Ensure a set of roles is created.
    'role' => array(
      'administrator' => array(
        'machine name' => 'administrator',
      ),
    ),
    // Ensure the 'tags' vocabulary, as defined in apps_compatible, is created.
    'vocabulary' => array(
      'tags' => array(
        'machine name' => 'tags',
      ),
    ),
    // Ensure a set of field bases, as defined in apps_compatible, is created.
    'field_base' => array(
      'body' => array(
        'machine name' => 'body',
      ),
      'field_content_image' => array(
        'machine name' => 'field_content_image',
      ),
      'field_media' => array(
        'machine name' => 'field_media',
      ),
      'field_tags' => array(
        'machine name' => 'field_tags',
      ),
    ),
  );
}

/**
 * Alter apps_compatible information.
 */
function hook_apps_compatible_info_alter(&$info) {
  // Prevent the "editor" role from being created.
  unset($info['role']['editor']);
}

