<?php

/**
 * @file
 * Default pages.
 */

/**
 * Implementation of hook_default_page_manager_pages().
 */
function skinr_panels_test_default_page_manager_pages() {
  static $pages;

  if (isset($pages)) {
    return $pages;
  }

  $files = file_scan_directory(drupal_get_path('module', 'skinr_panels_test') . '/pages_default', '/\.inc$/');
  foreach ($files as $filepath => $file) {
    include $filepath;
    if (isset($page)) {
      $pages[$page->name] = $page;
    }
  }
  return $pages;
}
