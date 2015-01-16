<?php
/**
 * @file
 * debut_social.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_social_user_default_permissions() {
  $permissions = array();

  // Exported permission: access forward.
  $permissions['access forward'] = array(
    'name' => 'access forward',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'forward',
  );

  // Exported permission: access service links.
  $permissions['access service links'] = array(
    'name' => 'access service links',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'service_links',
  );

  // Exported permission: administer follow.
  $permissions['administer follow'] = array(
    'name' => 'administer follow',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'follow',
  );

  // Exported permission: administer forward.
  $permissions['administer forward'] = array(
    'name' => 'administer forward',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'forward',
  );

  // Exported permission: change follow link titles.
  $permissions['change follow link titles'] = array(
    'name' => 'change follow link titles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'follow',
  );

  // Exported permission: edit any user follow links.
  $permissions['edit any user follow links'] = array(
    'name' => 'edit any user follow links',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'follow',
  );

  // Exported permission: edit own follow links.
  $permissions['edit own follow links'] = array(
    'name' => 'edit own follow links',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'follow',
  );

  // Exported permission: edit site follow links.
  $permissions['edit site follow links'] = array(
    'name' => 'edit site follow links',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'follow',
  );

  // Exported permission: override email address.
  $permissions['override email address'] = array(
    'name' => 'override email address',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'forward',
  );

  // Exported permission: override flood control.
  $permissions['override flood control'] = array(
    'name' => 'override flood control',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'forward',
  );

  return $permissions;
}
