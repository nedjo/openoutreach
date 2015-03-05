<?php

/**
 * @file
 * Specify common apps components to be created by apps_compatible.
 */

/**
 * Implements hook_apps_compatible_info().
 */
function debut_redhen_apps_compatible_info() {
  return array(
    // Ensure a set of roles is created.
    'role' => array(
      'administrator' => array(
        'machine name' => 'administrator',
      ),
      'member' => array(
        'machine name' => 'member',
      ),
    ),
    // Ensure a set of field bases is created.
    'field_base' => array(
      'field_address' => array(
        'machine name' => 'field_address',
      ),
    ),
  );
}

