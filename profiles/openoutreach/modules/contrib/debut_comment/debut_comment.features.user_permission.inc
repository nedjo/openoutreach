<?php
/**
 * @file
 * debut_comment.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_comment_user_default_permissions() {
  $permissions = array();

  // Exported permission: access comments.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: administer CAPTCHA settings.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'captcha',
  );

  // Exported permission: administer comment notify.
  $permissions['administer comment notify'] = array(
    'name' => 'administer comment notify',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'comment_notify',
  );

  // Exported permission: administer comments.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: edit own comments.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: post comments.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: skip CAPTCHA.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'captcha',
  );

  // Exported permission: skip comment approval.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: subscribe to comments.
  $permissions['subscribe to comments'] = array(
    'name' => 'subscribe to comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'comment_notify',
  );

  return $permissions;
}
