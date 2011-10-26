<?php
/**
 * @file
 * debut_wysiwyg.features.user_permission.inc
 */

/**
 * Implementation of hook_user_default_permissions().
 */
function debut_wysiwyg_user_default_permissions() {
  $permissions = array();

  // Exported permission: use text format wysiwyg_contributor
  $permissions['use text format wysiwyg_contributor'] = array(
    'name' => 'use text format wysiwyg_contributor',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format wysiwyg_editor
  $permissions['use text format wysiwyg_editor'] = array(
    'name' => 'use text format wysiwyg_editor',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format wysiwyg_public
  $permissions['use text format wysiwyg_public'] = array(
    'name' => 'use text format wysiwyg_public',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
