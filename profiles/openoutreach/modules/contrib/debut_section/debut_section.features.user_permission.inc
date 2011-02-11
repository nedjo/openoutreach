<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function debut_section_user_default_permissions() {
  $permissions = array();

  // Exported permission: access printer-friendly version
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'contributor',
      '2' => 'editor',
    ),
  );

  // Exported permission: add content to books
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'contributor',
      '2' => 'editor',
    ),
  );

  // Exported permission: administer book outlines
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create new books
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create section content
  $permissions['create section content'] = array(
    'name' => 'create section content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'contributor',
      '2' => 'editor',
    ),
  );

  // Exported permission: delete any section content
  $permissions['delete any section content'] = array(
    'name' => 'delete any section content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own section content
  $permissions['delete own section content'] = array(
    'name' => 'delete own section content',
    'roles' => array(
      '0' => 'contributor',
    ),
  );

  // Exported permission: edit any section content
  $permissions['edit any section content'] = array(
    'name' => 'edit any section content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own section content
  $permissions['edit own section content'] = array(
    'name' => 'edit own section content',
    'roles' => array(
      '0' => 'contributor',
    ),
  );

  return $permissions;
}
