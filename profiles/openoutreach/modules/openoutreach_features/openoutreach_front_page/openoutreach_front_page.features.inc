<?php
/**
 * @file
 * openoutreach_front_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function openoutreach_front_page_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function openoutreach_front_page_views_api() {
  return array("version" => "3.0");
}
