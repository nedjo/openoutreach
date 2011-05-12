<?php
/**
 * @file
 * debut_media.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function debut_media_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}

/**
 * Implementation of hook_views_api().
 */
function debut_media_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => 3.0);
  }
}
