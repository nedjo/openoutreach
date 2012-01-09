<?php

/**
 * @file
 * Installation profile for the Open Outreach distribution.
 */

include_once('openoutreach.features.inc');
// Include only when in install mode. MAINTENANCE_MODE is defined in
// install.php and in drush_core_site_install().
if (defined('MAINTENANCE_MODE') && MAINTENANCE_MODE == 'install') {
  include_once('openoutreach.install.inc');
}

/**
 * Implements hook_modules_installed().
 *
 * When a module is installed, enable the modules it recommends if they are
 * present. For Open Outreach, also install permissions.
 */
function openoutreach_modules_installed($modules) {
  module_load_include('inc', 'openoutreach', 'openoutreach.module_batch');
  openoutreach_module_batch($modules);
}

/**
 * Check that other install profiles are not present to ensure we don't collide with a
 * similar form alter in their profile.
 *
 * Set Open Outreach as default install profile.
 */
if (!function_exists('system_form_install_select_profile_form_alter')) {
  function system_form_install_select_profile_form_alter(&$form, $form_state) {
    // Only set the value if Open Outreach is the only profile.
    if (count($form['profile']) == 1) {
      foreach($form['profile'] as $key => $element) {
        $form['profile'][$key]['#value'] = 'openoutreach';
      }
    }
  }
}
