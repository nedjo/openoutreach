<?php
/**
 * @file
 * debut_blog.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_blog_user_default_permissions() {
  $permissions = array();

  // Exported permission: create blog content
  $permissions['create blog content'] = array(
    'name' => 'create blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'blogger',
      2 => 'contributor',
      3 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any blog content
  $permissions['delete any blog content'] = array(
    'name' => 'delete any blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own blog content
  $permissions['delete own blog content'] = array(
    'name' => 'delete own blog content',
    'roles' => array(
      0 => 'blogger',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any blog content
  $permissions['edit any blog content'] = array(
    'name' => 'edit any blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own blog content
  $permissions['edit own blog content'] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      0 => 'blogger',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
