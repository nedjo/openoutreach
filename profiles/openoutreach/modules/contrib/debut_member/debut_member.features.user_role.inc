<?php
/**
 * @file
 * debut_member.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function debut_member_user_default_roles() {
  $roles = array();

  // Exported role: member.
  $roles['member'] = array(
    'name' => 'member',
    'weight' => 3,
  );

  // Exported role: membership administrator.
  $roles['membership administrator'] = array(
    'name' => 'membership administrator',
    'weight' => 2,
  );

  return $roles;
}
