<?php

/**
 * @file
 * skinr_panels_test.panels_default.inc
 */

/**
 * Implementation of hook_default_panels_mini().
 */
function skinr_panels_test_default_panels_mini() {
  static $minis;

  if (isset($minis)) {
    return $minis;
  }

  $files = file_scan_directory(drupal_get_path('module', 'skinr_panels_test') . '/panels_default', '/\.inc$/');
  foreach ($files as $filepath => $file) {
    include $filepath;
    if (isset($mini)) {
      $minis[$mini->name] = $mini;
    }
  }
  return $minis;
}
