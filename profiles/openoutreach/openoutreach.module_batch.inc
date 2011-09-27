<?php

/**
 * @file
 * Provide a batch operation for enabling modules and their dependencies.
 */

/**
 * Set a batch operation to enable recommended enhancing modules of a given set of modules.
 *
 * Recommendations are identified in a module's .info file as follows:
 * <code>
 * recommends[] = comment
 * recommends[] = views_ui
 * </code>
 *
 * @param $modules
 *   An array of names of modules whose recommended modules should be enabled.
 */
function openoutreach_module_batch($modules) {
  module_load_include('inc', 'subprofiles', 'subprofiles.module_batch');

  $recommended = array();
  foreach ($modules as $module) {
    $info = drupal_parse_info_file(drupal_get_path('module', $module) . "/$module.info");
    if ($info && isset($info['recommends'])) {
      $recommended = array_unique(array_merge($recommended, $info['recommends']));
    }
  }
  subprofiles_set_module_batch($recommended);
}

