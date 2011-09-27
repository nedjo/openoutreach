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
    return _subprofiles_install_tasks($install_state);
  }
}

