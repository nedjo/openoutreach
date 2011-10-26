<?php
/**
 * @file
 * Implements Skinr hooks for comment.module.
 */

/**
 * Implements hook_skinr_config_info().
 */
function comment_skinr_config_info() {
  return array('comment');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function comment_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'comment') {
    $theme_hooks = array(
      'comment_wrapper__' . $element,
      'comment_wrapper',
    );
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function comment_skinr_elements($variables, $hook) {
  $elements = array();
  if ($hook == 'comment_wrapper') {
    $elements['comment'] = array($variables['node']->type);
  }
  return $elements;
}
