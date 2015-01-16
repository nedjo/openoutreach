<?php
/**
 * @file
 * debut_seo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_seo_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer meta tags.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'metatag',
  );

  // Exported permission: administer pathauto.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: create url aliases.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'path',
  );

  // Exported permission: edit meta tags.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'metatag',
  );

  return $permissions;
}
