<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function debut_media_user_default_permissions() {
  $permissions = array();

  // Exported permission: add media from remote sources
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'contributor',
      '2' => 'editor',
    ),
  );

  // Exported permission: administer media
  $permissions['administer media'] = array(
    'name' => 'administer media',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit media
  $permissions['edit media'] = array(
    'name' => 'edit media',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: import media
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view media
  $permissions['view media'] = array(
    'name' => 'view media',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'contributor',
      '4' => 'editor',
    ),
  );

  return $permissions;
}
