<?php
/**
 * @file
 * debut_member.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_member_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function debut_member_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function debut_member_node_info() {
  $items = array(
    'member_page' => array(
      'name' => t('Member page'),
      'base' => 'node_content',
      'description' => t('Use <em>Member pages</em> to post content that can be viewed only by members.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
