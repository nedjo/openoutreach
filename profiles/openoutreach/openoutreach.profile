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
 * present.
 */
function openoutreach_modules_installed($modules) {
  module_load_include('inc', 'openoutreach', 'openoutreach.module_batch');
  openoutreach_module_batch($modules);
}
