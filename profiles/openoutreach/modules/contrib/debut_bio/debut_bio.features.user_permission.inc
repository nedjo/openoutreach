<?php
/**
 * @file
 * debut_bio.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_bio_user_default_permissions() {
  $permissions = array();

  // Exported permission: edit any bio profile
  $permissions['edit any bio profile'] = array(
    'name' => 'edit any bio profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit own bio profile
  $permissions['edit own bio profile'] = array(
    'name' => 'edit own bio profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view any bio profile
  $permissions['view any bio profile'] = array(
    'name' => 'view any bio profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own bio profile
  $permissions['view own bio profile'] = array(
    'name' => 'view own bio profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'profile2',
  );

  return $permissions;
}
