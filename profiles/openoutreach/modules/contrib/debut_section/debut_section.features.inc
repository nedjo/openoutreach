<?php
/**
 * @file
 * debut_section.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function debut_section_ctools_plugin_api() {
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
function debut_section_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function debut_section_node_info() {
  $items = array(
    'section' => array(
      'name' => t('Section'),
      'base' => 'node_content',
      'description' => t('A <em>section</em> is a page of content, organized into a collection of related entries collectively known as a <em>book</em>. A <em>section</em> automatically displays links to sub-section pages, providing a simple navigation system for organizing nested sections of a site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
