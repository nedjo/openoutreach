<?php

/**
 * @file
 * Implements page and region level rules, and adds default groups.
 */

/**
 * Implements hook_skinr_api_VERSION().
 */
function skinr_skinr_api_2() {
}

/**
 * Implements hook_skinr_group_info().
 */
function skinr_skinr_group_info() {
  $groups['general'] = array(
    'title' => t('General'),
    'description' => t('Styles for content such as lists, buttons, margins, padding, etc.'),
    'weight' => -10,
  );
  $groups['box'] = array(
    'title' => t('Box styles'),
    'description' => t('Presentational styles for the container.'),
  );
  $groups['typography'] = array(
    'title' => t('Typography'),
    'description' => t('Fonts, styles, sizes and other typography related skins.'),
  );
  $groups['layout'] = array(
    'title' => t('Layout'),
    'description' => t('Grid, layout and other structural related skins.'),
  );
  return $groups;
}

/**
 * Implementation of hook_skinr_config_info().
 */
function skinr_skinr_config_info() {
  return array('rules');
}

/**
 * Implements hook_skinr_theme_hooks().
 */
function skinr_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'rules') {
    $rule = skinr_rule_load($element);
    $hooks = explode('__', $rule->rule_type);
    while (count($hooks)) {
      $theme_hooks[] = implode('__', $hooks);
      array_pop($hooks);
    }
  }

  return $theme_hooks;
}

/**
 * Implements hook_skinr_elements().
 */
function skinr_skinr_elements($variables, $hook) {
  $elements = array();
  if ($hook == 'html' || $hook == 'region') {
    $elements['rules'] = array();

    $rule_type = 'page';
    if ($hook == 'region') {
      $rule_type = 'region__' . $variables['region'];
    }

    $rules = skinr_rule_load_multiple(array(), array('rule_type' => $rule_type));
    foreach ($rules as $rule) {
      if (skinr_rule_is_visible($rule->rid)) {
        $elements['rules'][] = $rule->rid;
      }
    }
  }
  return $elements;
}
