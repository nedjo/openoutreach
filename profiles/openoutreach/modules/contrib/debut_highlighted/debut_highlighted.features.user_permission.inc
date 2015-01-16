<?php
/**
 * @file
 * debut_highlighted.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_highlighted_user_default_permissions() {
  $permissions = array();

  // Exported permission: create highlighted content.
  $permissions['create highlighted content'] = array(
    'name' => 'create highlighted content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any highlighted content.
  $permissions['delete any highlighted content'] = array(
    'name' => 'delete any highlighted content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any highlighted content.
  $permissions['edit any highlighted content'] = array(
    'name' => 'edit any highlighted content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
