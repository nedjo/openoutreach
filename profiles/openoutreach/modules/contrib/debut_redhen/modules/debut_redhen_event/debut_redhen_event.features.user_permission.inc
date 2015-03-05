<?php
/**
 * @file
 * debut_redhen_event.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_redhen_event_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer registration'.
  $permissions['administer registration'] = array(
    'name' => 'administer registration',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'administer standard registration'.
  $permissions['administer standard registration'] = array(
    'name' => 'administer standard registration',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create standard registration'.
  $permissions['create standard registration'] = array(
    'name' => 'create standard registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create standard registration other anonymous'.
  $permissions['create standard registration other anonymous'] = array(
    'name' => 'create standard registration other anonymous',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create standard registration other users'.
  $permissions['create standard registration other users'] = array(
    'name' => 'create standard registration other users',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'delete any standard registration'.
  $permissions['delete any standard registration'] = array(
    'name' => 'delete any standard registration',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'update any standard registration'.
  $permissions['update any standard registration'] = array(
    'name' => 'update any standard registration',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'view standard registration'.
  $permissions['view standard registration'] = array(
    'name' => 'view standard registration',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'registration',
  );

  return $permissions;
}
