<?php
/**
 * @file
 * Implements Skinr hooks for panels.module.
 */

/**
 * Implements hook_skinr_config_info().
 */
function skinr_panels_skinr_config_info() {
  return array('panels');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function skinr_panels_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'panels') {
    if (strpos($element, 'region') === 0) {
      $theme_hooks[] = 'panels_region';
    }
    elseif (strpos($element, 'pane') === 0) {
      $theme_hooks[] = 'panels_pane';
    }
    else {
      $theme_hooks[] = 'panels_display';
    }
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function skinr_panels_skinr_elements($variables, $hook) {
  $elements = array();
  if ($hook == 'panels_pane') {
    $elements['panels'] = array('pane__' . $variables['pane']->did . '__' . $variables['pane']->pid);
  }
  return $elements;
}
