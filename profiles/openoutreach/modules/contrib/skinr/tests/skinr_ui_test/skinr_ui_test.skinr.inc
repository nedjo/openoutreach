<?php

/**
 * Implements hook_skinr_api_VERSION().
 */
function skinr_ui_test_skinr_api_2() {
  return array(
    'directory' => 'skins',
  );
}

/**
 * Implements hook_skinr_skin_info().
 */
function skinr_ui_test_skinr_skin_info() {
  $skins['skinr_ui_test_bgcolor'] = array(
    'title' => t('Background color'),
    'type' => 'select',
    'group' => 'general',
    'default status' => 1,
    'options' => array(
      'bgcolor_red' => array(
        'title' => 'Red',
        'class' => array('bgcolor-red'),
      ),
    ),
  );
  $skins['skinr_ui_test_border'] = array(
    'title' => t('Border'),
    // Use an invalid type name.
    'type' => 'invalid',
    // Use a different group than the skin before to test for output of an empty group.
    'group' => 'box',
    'default status' => 1,
    'options' => array(
      'border_1' => array(
        'title' => 'Thin border',
        'class' => array('border-1'),
      ),
    ),
  );
  $skins['skinr_ui_test_color'] = array(
    'title' => t('Color'),
    'type' => 'checkboxes',
    'group' => 'general',
    'theme hooks' => array('block__system', 'comment_wrapper__page', 'node__page'),
    'default status' => 1,
    'options' => array(
      'color_white' => array(
        'title' => 'White',
        'class' => array('color-white'),
      ),
    ),
  );
  $skins['skinr_ui_test_custom'] = array(
    'title' => t('Custom'),
    'form callback' => 'skinr_ui_test_skinr_skinr_ui_test_custom_form',
    'group' => 'general',
    'theme hooks' => array('block__system', 'comment_wrapper__page', 'node__page'),
    'default status' => 1,
    'options' => array(
      'custom' => array(
        'class' => array('custom'),
      ),
    ),
  );
  return $skins;
}

function skinr_ui_test_skinr_skinr_ui_test_custom_form($form, $form_state, $context) {
  $form = array(
    '#type' => 'checkboxes',
    '#title' => t('Custom'),
    '#options' => array(
      'custom' => t('Custom'),
    ),
  );
  return $form;
}
