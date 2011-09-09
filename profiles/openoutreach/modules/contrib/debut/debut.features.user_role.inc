<?php
/**
 * @file
 * debut.features.user_role.inc
 */

/**
 * Implementation of hook_user_default_roles().
 */
function debut_user_default_roles() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '2',
  );

  // Exported role: contributor
  $roles['contributor'] = array(
    'name' => 'contributor',
    'weight' => '3',
  );

  // Exported role: editor
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => '4',
  );

  return $roles;
}
