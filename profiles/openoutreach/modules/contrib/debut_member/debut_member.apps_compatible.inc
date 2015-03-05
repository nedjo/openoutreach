<?php

/**
 * @file
 * Specify common apps components to be created by apps_compatible.
 */

/**
 * Implements hook_apps_compatible_info().
 */
function debut_member_apps_compatible_info() {
  return array(
    // Ensure a set of roles is created.
    'role' => array(
      'administrator' => array(
        'machine name' => 'administrator',
      ),
      'editor' => array(
        'machine name' => 'editor',
      ),
      'contributor' => array(
        'machine name' => 'contributor',
      ),
    ),
    // Ensure the 'tags' vocabulary, as defined in apps_compatible, is created.
    'vocabulary' => array(
      'tags' => array(
        'machine name' => 'tags',
      ),
    ),
    // Ensure a set of field bases is created.
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

