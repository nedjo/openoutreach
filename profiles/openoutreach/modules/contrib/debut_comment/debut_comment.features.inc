<?php
/**
 * @file
 * debut_comment.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function debut_comment_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "captcha" && $api == "captcha") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
