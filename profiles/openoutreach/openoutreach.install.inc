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
  $tasks['openoutreach_cleanup'] = array();
  return $tasks;
}

/**
 * Installation task; revert the openoutreach feature's user_permissions.
 *
 * This seems to be needed because the permissions are not correctly
 * registered when the feature is enabled.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 */
function openoutreach_cleanup(&$install_state) {
  features_revert(array('openoutreach' => array('user_permission')));
}
