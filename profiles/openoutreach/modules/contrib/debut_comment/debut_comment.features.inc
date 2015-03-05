<?php
/**
 * @file
 * debut_comment.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_comment_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
