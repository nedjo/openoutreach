<?php
/**
 * @file
 * debut_forum.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_forum_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer advanced forum.
  $permissions['administer advanced forum'] = array(
    'name' => 'administer advanced forum',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'advanced_forum',
  );

  // Exported permission: administer forums.
  $permissions['administer forums'] = array(
    'name' => 'administer forums',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'forum',
  );

  // Exported permission: create forum content.
  $permissions['create forum content'] = array(
    'name' => 'create forum content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any forum content.
  $permissions['delete any forum content'] = array(
    'name' => 'delete any forum content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own forum content.
  $permissions['delete own forum content'] = array(
    'name' => 'delete own forum content',
    'roles' => array(
      0 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any forum content.
  $permissions['edit any forum content'] = array(
    'name' => 'edit any forum content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own forum content.
  $permissions['edit own forum content'] = array(
    'name' => 'edit own forum content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: view forum statistics.
  $permissions['view forum statistics'] = array(
    'name' => 'view forum statistics',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'advanced_forum',
  );

  // Exported permission: view last edited notice.
  $permissions['view last edited notice'] = array(
    'name' => 'view last edited notice',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'advanced_forum',
  );

  return $permissions;
}
