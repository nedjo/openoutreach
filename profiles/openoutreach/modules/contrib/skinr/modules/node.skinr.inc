<?php
/**
 * @file
 * Implements Skinr hooks for node.module.
 */

/**
 * Implements hook_skinr_config_info().
 */
function node_skinr_config_info() {
  return array('node');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function node_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'node') {
    $theme_hooks = array(
      'node__' . $element,
      'node',
    );
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function node_skinr_elements($variables, $hook) {
  $elements = array();
  if ($hook == 'node') {
    $elements['node'] = array($variables['node']->type);
  }
  return $elements;
}
