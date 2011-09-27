<?php

/**
 * @file
 * Provide skinr handling for views.module
 */

/**
 * @defgroup skinr_views_module views.module handlers
 *
 * @{
 */

/**
 * Implements hook_skinr_config_info().
 */
function views_skinr_config_info() {
  $data['views']['form']['skinr_ui_form'] = array(
    'preprocess_hook_callback' => 'views_skinr_preprocess_hook_callback',
    'title' => t('views style settings'),
    'collapsed' => FALSE,
  );
  $data['views']['preprocess']['views_view'] = array(
    'index_handler' => 'views_skinr_preprocess_index_handler',
  );
  $data['views']['contextual_links']['page'] = array(
    'contextual_links_handler' => 'views_skinr_contextual_links',
  );

  return $data;
}

/**
 * Skinr form preprocess hook callback.
 *
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 *
 * @return
 *   An array of preprocess hooks we wish to use.
 */
function views_skinr_preprocess_hook_callback(&$form, $form_state) {
  $preprocess_hooks = array('views_view');

  if (!empty($form_state['view']) && !empty($form_state['view']->name)) {
    $view = $form_state['view'];
  }
  elseif(isset($form['skinr']['element']['#value'])) {
    list($element_info['view'], $element_info['display']) = explode('__', $form['skinr']['element']['#value'], 2);
    if ($view = views_get_view($element_info['view'])) {
      $view->execute_display($element_info['display']);
    }
  }

  if (!empty($view)) {
    $display = $view->display[$view->current_display];

    // Create list of suggested templates.
    $preprocess_hooks = views_theme_functions('views_view', $view, $display);
    // Fetch additional style based suggested templates.
    $additional_hooks = views_theme_functions($display->display_plugin, $view, $display);

    $preprocess_hooks = array_merge($additional_hooks, $preprocess_hooks);
  }

  return $preprocess_hooks;
}

/**
 * Skinr preprocess index handler.
 */
function views_skinr_preprocess_index_handler(&$variables) {
  return array($variables['view']->name .'__'. $variables['view']->current_display);
}

/**
 * Skinr contextual links handler.
 */
function views_skinr_contextual_links(&$variables) {
  $links = array();
  if (!empty($variables['page']['#views_contextual_links_info'])) {
    $links['skinr-views'] = array(
      'admin/appearance/skinr/edit/nojs', array('views', $variables['page']['#views_contextual_links_info']['views_ui']['view_name'] . '__' . $variables['page']['#views_contextual_links_info']['views_ui']['view_display_id']),
    );
  }
  return $links;
}

/**
 * @}
 */
