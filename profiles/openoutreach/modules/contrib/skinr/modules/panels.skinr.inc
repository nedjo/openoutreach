<?php
/**
 * @file
 * Provide skinr handling for panels.module.
 */

/**
 * @defgroup skinr_panels_module panels.module handlers.
 *
 * @{
 */

/**
 * Implements hook_skinr_config_info().
 */
function panels_skinr_config_info() {
  $data['panels']['form']['skinr_ui_form'] = array(
    'preprocess_hook_callback' => 'panels_skinr_preprocess_hook_callback',
    'title' => t('panel pane settings'),
    'collapsed' => FALSE,
  );
  $data['panels']['preprocess']['panels_pane'] = array(
    'index_handler' => 'panels_skinr_preprocess_index_handler',
  );

  return $data;
}

/**
 * Skinr preprocess hook callback.
 *
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 *
 * @return
 *   An array of preprocess hooks we wish to use.
 */
function panels_skinr_preprocess_hook_callback(&$form, $form_state) {
  if (strpos($form['skinr']['element']['#value'], 'region') === 0) {
    return 'panels_region';
  }
  elseif (strpos($form['skinr']['element']['#value'], 'pane') === 0) {
    return 'panels_pane';
  }
  else {
    return 'panels_display';
  }
}

/**
 * Skinr preprocess index handler.
 *
 * @param &$variables
 *   Passes in the $variables parameter from module_preprocess().
 *
 * @return
 *   The index where we can find our values in Skinr's data structure. If an
 *   array is returned, it will loop through each index in Skinr's data
 *   structure and merge the returned classes.
 */
function panels_skinr_preprocess_index_handler(&$variables) {
  $index = array();
  $index[] = 'pane__' . $variables['pane']->did . '__' . $variables['pane']->pid;
  return $index;
}

/**
 * Implements hook_panels_pane_content_alter().
 *
 * Because of the way panels handles contextual links we can't use a
 * contextual links handler.
 */
function panels_panels_pane_content_alter(&$content, $pane, $display_args, $context) {
  if (user_access('edit skin settings')) {
    $element = 'pane__' . $pane->did . '__' . $pane->pid;
    $content->admin_links[] = array(
      'title' => t('Edit skin'),
      'href' => 'admin/appearance/skinr/edit/nojs/panels/' . $element . '/configure',
      'query' => drupal_get_destination(),
    );
  }
}

/**
 * @}
 */
