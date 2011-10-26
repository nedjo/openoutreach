<?php

/**
 * @file
 * Implements Skinr hooks for views.module.
 */

/**
 * Implements hook_skinr_config_info().
 */
function views_skinr_config_info() {
  return array('views');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function views_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'views') {
    list($name, $display_id) = explode('__', $element, 2);
    if ($view = views_get_view($name)) {
      $view->execute_display($display_id);

      $display = $view->display[$view->current_display];

      // Create list of suggested templates.
      $theme_hooks = views_theme_functions('views_view', $view, $display);

      // @todo Determine whether below code is still relevant.
      /*
      // Fetch additional style based suggested templates.
      $additional_hooks = views_theme_functions($display->display_plugin, $view, $display);
      $theme_hooks = array_merge($additional_hooks, $theme_hooks);
      */
    }
    else {
      $theme_hooks[] = 'views_view';
    }
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function views_skinr_elements($variables, $hook, $op) {
  $elements = array();
  if ($op == 'preprocess' && $hook == 'views_view') {
    $elements['views'] = array($variables['view']->name . '__' . $variables['view']->current_display);
  }
  elseif ($op == 'contextual_links' && $hook == 'page' && isset($variables['page']['#views_contextual_links_info'])) {
    // Contextual links for views are on 'page' hook, not 'views_view'.
    $elements['views'] = array($variables['page']['#views_contextual_links_info']['views_ui']['view_name'] . '__' . $variables['page']['#views_contextual_links_info']['views_ui']['view_display_id']);
  }
  return $elements;
}
