<?php

/**
 * @file
 * Implementation of a Skinr plugin.
 */

/**
 * Implements hook_skinr_group_PLUGIN_info().
 */
function mix_and_match_skinr_group_info() {
  $groups['skinr_styles_colors'] = array(
    'title' => t('Colors'),
    'description' => t('Colors for backgrounds, headers, and links'),
    'weight' => -14,
  );
  return $groups;
}

/**
 * Implements hook_skinr_skin_PLUGIN_info().
 *
 *
 */
function mix_and_match_skinr_skin_info() {
  $skins = array();
  $skins['skinr_background_color'] = array(
    'title' => t('Background Color'),
    'type' => 'select',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'white_bg' => array(
        'title' => t('White'),
        'class' => array('white-background'),
      ),
      'black_bg' => array(
        'title' => t('Black'),
        'class' => array('black-background'),
      ),
      'ltgray_bg' => array(
        'title' => t('Light Gray'),
        'class' => array('gray-background'),
      ),
        'medgray_bg' => array(
        'title' => t('Medium Gray'),
        'class' => array('med-gray-background'),
      ),
      'dkgray_bg' => array(
        'title' => t('Dark Gray'),
        'class' => array('dk-gray-background'),
      ),
      'red_bg' => array(
        'title' => t('Red'),
        'class' => array('red-background'),
      ),
      'blue_bg' => array(
        'title' => t('Dark Blue'),
        'class' => array('blue-background'),
      ),
      'ltblue_bg' => array(
        'title' => t('Light Blue'),
        'class' => array('lt-blue-background'),
      ),
      'dkgreen_bg' => array(
        'title' => t('Dark Green'),
        'class' => array('green-background'),
      ),
        'ltgreen_bg' => array(
        'title' => t('Light Green'),
        'class' => array('lt-green-background'),
      ),
        'orange_bg' => array(
        'title' => t('Dark Orange'),
        'class' => array('orange-background'),
      ),
        'ltorange_bg' => array(
        'title' => t('Light Orange'),
        'class' => array('lt-orange-background'),
      ),
    ),
  );

  $skins['skinr_header_background_color'] = array(
    'title' => t('Header Background Color'),
    'type' => 'select',
    'description' => 'Select a color if you would like a header background different from the body background.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'black_header_bg' => array(
        'title' => t('Black'),
        'class' => array('black-header'),
      ),
      'gray_header_bg' => array(
        'title' => t('Gray'),
        'class' => array('gray-header'),
      ),
      'red_header_bg' => array(
        'title' => t('Red'),
        'class' => array('red-header'),
      ),
      'blue_header_bg' => array(
        'title' => t('Blue'),
        'class' => array('blue-header'),
      ),
      'green_header_bg' => array(
        'title' => t('Green'),
        'class' => array('green-header'),
      ),
      'orange_header_bg' => array(
        'title' => t('Orange'),
        'class' => array('orange-header'),
      ),
    ),
  );

  $skins['skinr_header_text_color'] = array(
    'title' => t('Header Text Color'),
    'type' => 'select',
    'description' => 'Select a color for the block or node title text.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'white_header_text' => array(
        'title' => t('White'),
        'class' => array('white-title'),
      ),
      'black_header_text' => array(
        'title' => t('Black'),
        'class' => array('black-title'),
      ),
      'gray_header_text' => array(
        'title' => t('Gray'),
        'class' => array('gray-title'),
      ),
      'red_header_text' => array(
        'title' => t('Red'),
        'class' => array('red-title'),
      ),
      'blue_header_text' => array(
        'title' => t('Blue'),
        'class' => array('blue-title'),
      ),
      'green_header_text' => array(
        'title' => t('Green'),
        'class' => array('green-title'),
      ),
     'orange_header_text' => array(
        'title' => t('Orange'),
        'class' => array('orange-title'),
      ),
    ),
  );

  $skins['skinr_link_text_color'] = array(
    'title' => t('Link Text Color'),
    'type' => 'select',
    'description' => 'Select a color for the link text.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'white_link_text' => array(
        'title' => t('White'),
        'class' => array('block-white-links'),
      ),
      'black_link_text' => array(
        'title' => t('Black'),
        'class' => array('block-black-links'),
      ),
      'gray_link_text' => array(
        'title' => t('Gray'),
        'class' => array('block-gray-links'),
      ),
      'ltgray_link_text' => array(
        'title' => t('Light Gray'),
        'class' => array('block-lt-gray-links'),
      ),
      'red_link_text' => array(
        'title' => t('Red'),
        'class' => array('block-red-links'),
      ),
      'blue_link_text' => array(
        'title' => t('Blue'),
        'class' => array('block-blue-links'),
      ),
      'green_link_text' => array(
        'title' => t('Green'),
        'class' => array('block-green-links'),
      ),
     'orange_link_text' => array(
        'title' => t('Orange'),
        'class' => array('block-orange-links'),
      ),
    ),
  );

  return $skins;
}