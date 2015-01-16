<?php

/**
 * @file
 * Provides features-related hook implementations.
 */

/**
 * Implements hook_features_export_alter().
 *
 * Remove the apps_compatible controlled vocabularies.
 */
function apps_compatible_features_export_alter(&$export, $module_name) {
  if (isset($export['features']['taxonomy']) && isset($export['features']['taxonomy']['tags'])) {
    unset($export['features']['taxonomy']['tags']);
  }
}

