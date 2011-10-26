<?php

/**
 * Implements hook_skinr_api_VERSION().
 */
function skinr_test_skinr_api_2() {
  return array(
    'directory' => 'skins',
  );
}

/**
 * Implements hook_skinr_group_info().
 */
function skinr_test_skinr_group_info() {
  $groups['skinr_test'] = array(
    'title' => t('skinr_test'),
  );
}

/**
 * Implements hook_skinr_skin_info().
 */
function skinr_test_skinr_skin_info() {
  $skins['skinr_test_font'] = array(
    'title' => t('Font family'),
    'type' => 'select',
    'group' => 'typography',
    'theme hooks' => array('block', 'region'),
    'default status' => 1,
    'attached' => array(
      'css' => array('skinr_test.css'),
      'js' => array('skinr_test.js'),
    ),
    'options' => array(
      'font_1' => array(
        'title' => 'Arial, Helvetica, Nimbus Sans L, Liberation Sans, FreeSans',
        'class' => array('font-1'),
      ),
      'font_2' => array(
        'title' => 'Lucida Grande, Lucida Sans Unicode, DejaVu Sans, Tahoma',
        'class' => array('font-2'),
      ),
    ),
  );
  return $skins;
}
