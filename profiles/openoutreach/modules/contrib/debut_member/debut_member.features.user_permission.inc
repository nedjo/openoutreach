<?php
/**
 * @file
 * debut_member.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_member_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create member_page content'.
  $permissions['create member_page content'] = array(
    'name' => 'create member_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any member_page content'.
  $permissions['delete any member_page content'] = array(
    'name' => 'delete any member_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'membership administrator' => 'membership administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own member_page content'.
  $permissions['delete own member_page content'] = array(
    'name' => 'delete own member_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any member_page content'.
  $permissions['edit any member_page content'] = array(
    'name' => 'edit any member_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'membership administrator' => 'membership administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own member_page content'.
  $permissions['edit own member_page content'] = array(
    'name' => 'edit own member_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
