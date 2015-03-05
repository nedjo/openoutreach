<?php
/**
 * @file
 * debut_redhen.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function debut_redhen_user_default_roles() {
  $roles = array();

  // Exported role: crm manager.
  $roles['crm manager'] = array(
    'name' => 'crm manager',
    'weight' => 6,
  );

  // Exported role: crm viewer.
  $roles['crm viewer'] = array(
    'name' => 'crm viewer',
    'weight' => 7,
  );

  return $roles;
}
