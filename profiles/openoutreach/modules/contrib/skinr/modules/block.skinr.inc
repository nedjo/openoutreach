<?php
/**
 * @file
 * Provide skinr handling for block.module
 */

/**
 * @defgroup skinr_block_module block.module handlers
 *
 * @{
 */

/**
 * Implements hook_skinr_config_info().
 */
function block_skinr_config_info() {
  $data['block']['form']['skinr_ui_form'] = array(
    'preprocess_hook_callback' => 'block_skinr_preprocess_hook_callback',
    'title' => t('block settings'),
    'collapsed' => FALSE,
  );
  $data['block']['preprocess']['block'] = array(
    'index_handler' => 'block_skinr_preprocess_index_handler',
  );
  $data['block']['contextual_links']['block'] = array(
    'contextual_links_handler' => 'block_skinr_contextual_links',
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
function block_skinr_preprocess_hook_callback(&$form, $form_state) {
  $preprocess_hooks = array();

  if (empty($form['module']['#value']) && !empty($form['skinr']['element']['#value'])) {
    list($module, $delta) = explode('__', $form['skinr']['element']['#value'], 2);

    $result = db_select('block', 'b')
      ->fields('b')
      ->distinct()
      ->condition('b.module', $module)
      ->condition('b.delta', $delta)
      ->range(0, 1)
      ->execute();
    foreach ($result as $block) {
      $preprocess_hooks[] = 'block__'. $block->module;
    }
  }
  else {
    $preprocess_hooks[] = 'block__'. $form['module']['#value'];
  }
  $preprocess_hooks[] = 'block';

  return $preprocess_hooks;
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
function block_skinr_preprocess_index_handler(&$variables) {
  return array($variables['block']->module . '__' . $variables['block']->delta);
}

/**
 * Skinr contextual links handler.
 *
 * @param &$variables
 *   Passes in the $variables parameter from skinr_preprocess().
 *
 * @return
 *   An array. Each value is an array that forms the function arguments for
 *   menu_contextual_links(). For example:
 *   @code
 *     array(
 *       'admin/appearance/skinr/edit', array('system', 'navigation')),
 *     )
 *   @endcode
 */
function block_skinr_contextual_links(&$variables) {
  $links = array();
  $links['skinr-block'] = array(
    'admin/appearance/skinr/edit/nojs', array('block', $variables['block']->module . '__' . $variables['block']->delta),
  );
  return $links;
}

/**
 * @}
 */
