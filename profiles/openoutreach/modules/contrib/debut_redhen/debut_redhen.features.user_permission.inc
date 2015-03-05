<?php
/**
 * @file
 * debut_redhen.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_redhen_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access redhen'.
  $permissions['access redhen'] = array(
    'name' => 'access redhen',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen',
  );

  // Exported permission: 'access redhen contacts'.
  $permissions['access redhen contacts'] = array(
    'name' => 'access redhen contacts',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_contact',
  );

  // Exported permission: 'access redhen notes'.
  $permissions['access redhen notes'] = array(
    'name' => 'access redhen notes',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_note',
  );

  // Exported permission: 'access redhen orgs'.
  $permissions['access redhen orgs'] = array(
    'name' => 'access redhen orgs',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_org',
  );

  // Exported permission: 'administer redhen'.
  $permissions['administer redhen'] = array(
    'name' => 'administer redhen',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen',
  );

  // Exported permission: 'administer redhen contacts'.
  $permissions['administer redhen contacts'] = array(
    'name' => 'administer redhen contacts',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_contact',
  );

  // Exported permission: 'administer redhen engagements'.
  $permissions['administer redhen engagements'] = array(
    'name' => 'administer redhen engagements',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_engagement',
  );

  // Exported permission: 'administer redhen membership types'.
  $permissions['administer redhen membership types'] = array(
    'name' => 'administer redhen membership types',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_membership',
  );

  // Exported permission: 'administer redhen notes'.
  $permissions['administer redhen notes'] = array(
    'name' => 'administer redhen notes',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_note',
  );

  // Exported permission: 'administer redhen orgs'.
  $permissions['administer redhen orgs'] = array(
    'name' => 'administer redhen orgs',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_org',
  );

  // Exported permission: 'administer redhen_contact types'.
  $permissions['administer redhen_contact types'] = array(
    'name' => 'administer redhen_contact types',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_contact',
  );

  // Exported permission: 'administer redhen_org types'.
  $permissions['administer redhen_org types'] = array(
    'name' => 'administer redhen_org types',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_org',
  );

  // Exported permission: 'edit redhen contact connections'.
  $permissions['edit redhen contact connections'] = array(
    'name' => 'edit redhen contact connections',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_relation',
  );

  // Exported permission: 'edit redhen contact memberships'.
  $permissions['edit redhen contact memberships'] = array(
    'name' => 'edit redhen contact memberships',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_membership',
  );

  // Exported permission: 'edit redhen org connections'.
  $permissions['edit redhen org connections'] = array(
    'name' => 'edit redhen org connections',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_relation',
  );

  // Exported permission: 'edit redhen org memberships'.
  $permissions['edit redhen org memberships'] = array(
    'name' => 'edit redhen org memberships',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_membership',
  );

  // Exported permission: 'list redhen memberships'.
  $permissions['list redhen memberships'] = array(
    'name' => 'list redhen memberships',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_membership',
  );

  // Exported permission: 'manage redhen contacts'.
  $permissions['manage redhen contacts'] = array(
    'name' => 'manage redhen contacts',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_contact',
  );

  // Exported permission: 'manage redhen notes'.
  $permissions['manage redhen notes'] = array(
    'name' => 'manage redhen notes',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_note',
  );

  // Exported permission: 'manage redhen orgs'.
  $permissions['manage redhen orgs'] = array(
    'name' => 'manage redhen orgs',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
    ),
    'module' => 'redhen_org',
  );

  // Exported permission: 'view redhen contact connections'.
  $permissions['view redhen contact connections'] = array(
    'name' => 'view redhen contact connections',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_relation',
  );

  // Exported permission: 'view redhen contact memberships'.
  $permissions['view redhen contact memberships'] = array(
    'name' => 'view redhen contact memberships',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_membership',
  );

  // Exported permission: 'view redhen org connections'.
  $permissions['view redhen org connections'] = array(
    'name' => 'view redhen org connections',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_relation',
  );

  // Exported permission: 'view redhen org memberships'.
  $permissions['view redhen org memberships'] = array(
    'name' => 'view redhen org memberships',
    'roles' => array(
      'administrator' => 'administrator',
      'crm manager' => 'crm manager',
      'crm viewer' => 'crm viewer',
    ),
    'module' => 'redhen_membership',
  );

  return $permissions;
}
