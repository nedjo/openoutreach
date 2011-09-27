<?php
/**
 * @file
 * Provide skinr handling for node.module
 */

/**
 * @defgroup skinr_node_module node.module handlers
 *
 * @{
 */

/**
 * Implements hook_skinr_config_info().
 */
function node_skinr_config_info() {
  $data['node']['form']['skinr_ui_form'] = array(
    'preprocess_hook_callback' => 'node_skinr_preprocess_hook_callback',
    'title' => t('node settings'),
    'collapsed' => FALSE,
  );
  $data['node']['preprocess']['node'] = array(
    'index_handler' => 'node_skinr_preprocess_index_handler',
  );
  $data['node']['contextual_links']['node'] = array(
    'contextual_links_handler' => 'node_skinr_contextual_links',
  );

  return $data;
}

/**
 * Skinr form index handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - 'form': the form elements for Skinr are being inserted in a form.
 *   - 'submit': the form has been submitted.
 * @param &$form
 *   - For 'form', passes in the $form parameter from hook_form_alter().
 *   - For 'submit', passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   - For 'form', passes in the $form_state parameter from hook_form_alter().
 *   - For 'submit', passes in the $form_state parameter from hook_form_submit().
 *
 * @return
 *   The index where we can find our values in Skinr's data structure.
 */
function node_skinr_form_index_handler($op, &$form, $form_state) {
  switch ($op) {
    case 'form':
      return $form['#node_type']->type;

    case 'submit':
      // Clear old variable before we set a new one if the node type has changed.
      if ($form_state['values']['old_type'] != $form_state['values']['type']) {
        foreach ($form_state['values']['skinr_settings']['node_group'] as $theme_name => $theme_data) {
          $skinr = new stdClass();
          $skinr->theme = $theme_name;
          $skinr->module = 'node';
          $skinr->element = $form_state['values']['old_type'];
          $skinr->skins = array();

          skinr_skin_save($skinr);
        }
      }
    return $form_state['values']['type'];
  }
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
function node_skinr_preprocess_hook_callback(&$form, $form_state) {
  $preprocess_hooks = array();

  if (!isset($form['#node_type']->type) && !empty($form['skinr']['element']['#value'])) {
    $preprocess_hooks[] = 'node__' . $form['skinr']['element']['#value'];
  }
  else {
    $preprocess_hooks[] = 'node__' . $form['#node_type']->type;
  }
  $preprocess_hooks[] = 'node';

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
function node_skinr_preprocess_index_handler(&$variables) {
  return array($variables['node']->type);
}

/**
 * Skinr contextual links handler.
 *
 * @param &$variables
 *   Passes in the $variables parameter from skinr_preprocess().
 * @return
 *   An array. Each value is an array that forms the function arguments for
 *   menu_contextual_links(). For example:
 *   @code
 *     array(
 *       'admin/appearance/skinr/edit', array('system', 'navigation')),
 *     )
 *   @endcode
 */
function node_skinr_contextual_links(&$variables) {
  $links = array();
  $links['skinr-node'] = array(
    'admin/appearance/skinr/edit/nojs', array('node', $variables['node']->type),
  );
  return $links;
}

/**
 * @}
 */
