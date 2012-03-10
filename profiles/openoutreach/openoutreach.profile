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

/**
 * Implements hook_install_configure_form_alter().
 */
function openoutreach_form_install_configure_form_alter(&$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = 'Open Outreach';
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
}

/**
 * Implements hook_context_default_contexts_alter().
 *
 * If the debut_blogger module is enabled, display the shortcut block to users
 * with the blogger role.
 */
function openoutreach_context_default_contexts_alter(&$contexts) {
  if (isset($contexts['shortcut']) && module_exists('debut_blog') && !openoutreach_is_recreating('openoutreach')) {
    $contexts['shortcut']->conditions['user']['values']['blogger'] = 'blogger';
  }
}

/**
 * Determine whether a feature is being recreated.
 */
function openoutreach_is_recreating($feature = NULL) {
  // Test for Drush usage.
  if (function_exists('drush_get_command') && $command = drush_get_command()) {
    switch($command['command']) {
      case 'features-update-all':
        return TRUE;
      case 'features-update':
        // If a specific feature was requested, test for it. If not, return
        // true for any feature recreation.
        return is_null($feature) || in_array($feature, $command['arguments']);
    }
  }

  // Test for admin UI usage.
  $feature = is_null($feature) ? arg(3) : $feature;
  if ($_GET['q'] == "admin/structure/features/{$feature}/recreate") {
    return TRUE;
  }
  return FALSE;
}

