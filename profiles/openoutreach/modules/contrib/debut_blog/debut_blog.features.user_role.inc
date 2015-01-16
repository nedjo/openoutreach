<?php
/**
 * @file
 * debut_blog.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function debut_blog_user_default_roles() {
  $roles = array();

  // Exported role: blogger.
  $roles['blogger'] = array(
    'name' => 'blogger',
    'weight' => '5',
  );

  return $roles;
}
