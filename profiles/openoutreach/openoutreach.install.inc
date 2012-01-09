<?php

/**
 * @file
 * Provides functionality to be used at install time.
 */

/**
 * Generate an install task to install subprofile features.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return
 *   The install task definition.
 */
function openoutreach_install_tasks($install_state) {
  if (module_exists('subprofiles')) {
    $tasks = _subprofiles_install_tasks($install_state);
  }
  else {
    $tasks = array();
  }
  $tasks['openoutreach_wrapup'] = array();
  return $tasks;
}

/**
 * Installation task; install permissions and revert the openoutreach feature's
 * user_permission components.
 *
 * Permissions for optional modules need to be assigned after the modules
 * have been installed.
 *
 * Reverting the openoutreach user_permission component seems to be needed
 * because the permissions are not correctly registered when the feature is
 * enabled.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 */
function openoutreach_wrapup(&$install_state) {
  openoutreach_install_permissions();
  features_revert(array('openoutreach' => array('user_permission')));
}

/**
 * Pseudo implementation of hook_user_default_permissions().
 *
 * @see openoutreach_install_permissions().
 */
function openoutreach_install_user_default_permissions() {
  $permissions = array();

  // Exported permission: access contextual links
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'contextual',
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: view advanced help index
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help popup
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help topic
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  return $permissions;
}

/**
 * Install permissions for optional modules.
 *
 * Optional modules - identified by the "recommends" array in
 * openoutreach.info - cannot have their permissions in features; recommended
 * modules are enabled after features permissions are implemented, and in any
 * case such features would break if the optional module was disabled.
 *
 * Take advantage of existing support in the Features module for processing
 * default user permissions. Use a pseudo module name, 'openoutreach_install'.
 */
function openoutreach_install_permissions() {
  features_include();
  module_load_include('inc', 'features', 'features.export');
  user_permission_features_rebuild('openoutreach_install');
}
