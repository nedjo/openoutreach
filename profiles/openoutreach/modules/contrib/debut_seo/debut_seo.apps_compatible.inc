<?php

/**
 * @file
 * Specify common apps components to be created by apps_compatible.
 */

/**
 * Implements hook_apps_compatible_info().
 */
function debut_seo_apps_compatible_info() {
  return array(
    // Ensure a set of roles is created.
    'role' => array(
      'administrator' => array(
        'machine name' => 'administrator',
      ),
      'editor' => array(
        'machine name' => 'editor',
      ),
    ),
  );
}

