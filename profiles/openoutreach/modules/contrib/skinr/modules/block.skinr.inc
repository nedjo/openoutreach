<?php
/**
 * @file
 * Implements Skinr hooks for block.module.
 */

/**
 * Implements hook_skinr_config_info().
 */
function block_skinr_config_info() {
  return array('block');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function block_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'block') {
    list($module, $delta) = explode('__', $element, 2);
    $result = db_select('block', 'b')
      ->fields('b')
      ->distinct()
      ->condition('b.module', $module)
      ->condition('b.delta', $delta)
      ->range(0, 1)
      ->execute();
    foreach ($result as $block) {
      $theme_hooks[] = 'block__'. $block->module;
    }
    $theme_hooks[] = 'block';
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function block_skinr_elements($variables, $hook) {
  $elements = array();
  if ($hook == 'block') {
    $elements['block'] = array($variables['block']->module . '__' . $variables['block']->delta);
  }
  return $elements;
}
