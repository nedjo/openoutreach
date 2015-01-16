<?php

/**
 * @file
 * Provides a batch operation for enabling modules and their dependencies.
 */

/**
 * Set a batch operation to enable a given set of modules and their
 * dependencies.
 *
 * @param $modules
 *   An array of names of modules to be enabled.
 */
function subprofiles_set_module_batch($modules) {
  // Ensure modules are not already enabled.
  $modules = array_filter($modules, 'subprofiles_module_disabled');
  if (!empty($modules)) {
    $batch = subprofiles_get_module_batch($modules);
    batch_set($batch);
  }
}

/**
 * Get a batch operation definition to enable a given set of modules and their
 * dependencies.
 *
 * @param $modules
 *   An array of names of modules to be enabled.
 *
 * $return
 *   A batch definition.
 */
function subprofiles_get_module_batch($modules) {
  $files = system_rebuild_module_data();

  // Always install required modules first. Respect the dependencies between
  // the modules.
  $required = array();
  $non_required = array();

  // Add modules that other modules depend on.
  foreach ($modules as $key => $module) {
    if ($files[$module]->requires) {
      $modules = array_merge($modules, array_keys($files[$module]->requires));
    }
  }
  $modules = array_unique($modules);
  foreach ($modules as $module) {
    if (!empty($files[$module]->info['required'])) {
      $required[$module] = $files[$module]->sort;
    }
    else {
      $non_required[$module] = $files[$module]->sort;
    }
  }
  arsort($required);
  arsort($non_required);

  $modules = $required + $non_required;
  // Ensure modules are not already enabled.
  $modules = array_filter(array_keys($modules), 'subprofiles_module_disabled');

  $operations = array();
  foreach ($modules as $module) {
    if (isset($files[$module])) {
      $operations[] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
  }
  $batch = array(
    'title' => t('Enable modules'),
    'init_message' => t('Enabling modules...'),
    'progress_message' => t('Enabling @current out of @total modules.'),
    'operations' => $operations,
    'error_message' => t('Module enabling encountered an error.'),
    'file' => 'includes/install.core.inc',
  );
  return $batch;
}

/**
 * Determine whether a given module is disabled. This function can be used as
 * a callback to array_filter().
 *
 * @param $module
 *   The name of a module.
 *
 * @return
 *   Boolean TRUE if the module is not enabled, FALSE if it is.
 */
function subprofiles_module_disabled($module) {
  return !module_exists($module);
}
