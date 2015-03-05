<?php
/**
 * @file
 * debut_wysiwyg.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_wysiwyg_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format wysiwyg_contributor'.
  $permissions['use text format wysiwyg_contributor'] = array(
    'name' => 'use text format wysiwyg_contributor',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format wysiwyg_editor'.
  $permissions['use text format wysiwyg_editor'] = array(
    'name' => 'use text format wysiwyg_editor',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format wysiwyg_public'.
  $permissions['use text format wysiwyg_public'] = array(
    'name' => 'use text format wysiwyg_public',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
