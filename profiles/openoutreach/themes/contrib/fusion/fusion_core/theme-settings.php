<?php

/**
 * Allow themes to alter the theme-specific settings form.
 *
 * With this hook, themes can alter the theme-specific settings form in any way
 * allowable by Drupal's Forms API, such as adding form elements, changing
 * default values and removing form elements. See the Forms API documentation on
 * api.drupal.org for detailed information.
 *
 * Note that the base theme's form alterations will be run before any sub-theme
 * alterations.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function fusion_core_form_system_theme_settings_alter(&$form, $form_state) {
  global $base_url;

  // Get theme name from url (admin/.../theme_name)
  $theme_name = arg(count(arg()) - 1);

  // Get default theme settings from .info file
  $theme_data = list_themes();   // get data for all themes
  $defaults = ($theme_name && isset($theme_data[$theme_name]->info['settings'])) ? $theme_data[$theme_name]->info['settings'] : array();

  // Create theme settings form widgets using Forms API

  // TNT Fieldset
  $form['tnt_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fusion theme settings'),
    '#description' => t('Use these settings to enhance the appearance and functionality of your Fusion theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // General Settings
  $form['tnt_container']['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Grid settings
  $form['tnt_container']['general_settings']['theme_grid_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Grid type
  // Generate grid type options
  $grid_options = array();
  if (isset($defaults['theme_grid_options'])) {
    foreach ($defaults['theme_grid_options'] as $grid_option) {
      $grid_type = (substr($grid_option, 7) == 'fluid') ? t('fluid grid') : t('fixed grid') . ' [' . substr($grid_option, 7) . 'px]';
      $grid_options[$grid_option] = (int)substr($grid_option, 4, 2) . t(' column ') . $grid_type;
    }
  }
  $form['tnt_container']['general_settings']['theme_grid_config']['theme_grid'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select a grid layout for your theme'),
    '#default_value' => theme_get_setting('theme_grid'),
    '#options'       => $grid_options,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['theme_grid']['#options'][$defaults['theme_grid']] .= t(' - Theme Default');
  // Fluid grid width
  $form['tnt_container']['general_settings']['theme_grid_config']['fluid_grid_width'] = array(
    '#type'          => 'select',
    '#title'         => t('Select a width for your fluid grid layout'),
    '#default_value' => theme_get_setting('fluid_grid_width'),
    '#options'       => array(
      'fluid-100' => t('100%'),
      'fluid-95' => t('95%'),
      'fluid-90' => t('90%'),
      'fluid-85' => t('85%'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['fluid_grid_width']['#options'][$defaults['fluid_grid_width']] .= t(' - Theme Default');
  // Sidebar layout
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_layout'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select a sidebar layout for your theme'),
    '#default_value' => theme_get_setting('sidebar_layout'),
    '#options'       => array(
      'sidebars-split' => t('Split sidebars'),
      'sidebars-both-first' => t('Both sidebars first'),
      'sidebars-both-last' => t('Both sidebars last'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_layout']['#options'][$defaults['sidebar_layout']] .= t(' - Theme Default');
  // Calculate sidebar width options
  $grid_width = (int)substr(theme_get_setting('theme_grid'), 4, 2);
  $grid_type = substr(theme_get_setting('theme_grid'), 7);
  $width_options = array();
  for ($i = 1; $i <= floor($grid_width / 2); $i++) {
    $grid_units = $i . (($i == 1) ? t(' grid unit: ') : t(' grid units: '));
    $width_options[$i] = $grid_units . (($grid_type == 'fluid') ? (round($i * (100 / $grid_width), 2) . '%') : ($i * ((int)$grid_type / $grid_width)) . 'px');
  }
  // Sidebar first width
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_first_width'] = array(
    '#type'          => 'select',
    '#title'         => t('Select a different width for your first sidebar'),
    '#default_value' => theme_get_setting('sidebar_first_width'),
    '#options'       => $width_options,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_first_width']['#options'][$defaults['sidebar_first_width']] .= t(' - Theme Default');
  // Sidebar last width
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_second_width'] = array(
    '#type'          => 'select',
    '#title'         => t('Select a different width for your second sidebar'),
    '#default_value' => theme_get_setting('sidebar_second_width'),
    '#options'       => $width_options,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_second_width']['#options'][$defaults['sidebar_second_width']] .= t(' - Theme Default');

  // Theme fonts
  $form['tnt_container']['general_settings']['theme_font_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Typography'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font'] = array(
    '#type'          => 'select',
    '#title'         => t('Select a new font family'),
    '#default_value' => theme_get_setting('theme_font'),
    '#options'       => array(
      'none' => t('Theme default'),
      'font-family-sans-serif-sm' => t('Sans serif - smaller (Helvetica Neue, Arial, Helvetica, sans-serif)'),
      'font-family-sans-serif-lg' => t('Sans serif - larger (Verdana, Geneva, Arial, Helvetica, sans-serif)'),
      'font-family-serif-sm' => t('Serif - smaller (Garamond, Perpetua, Nimbus Roman No9 L, Times New Roman, serif)'),
      'font-family-serif-lg' => t('Serif - larger (Baskerville, Georgia, Palatino, Palatino Linotype, Book Antiqua, URW Palladio L, serif)'),
      'font-family-myriad' => t('Myriad (Myriad Pro, Myriad, Trebuchet MS, Arial, Helvetica, sans-serif)'),
      'font-family-lucida' => t('Lucida (Lucida Sans, Lucida Grande, Lucida Sans Unicode, Verdana, Geneva, sans-serif)'),
      'font-family-tahoma' => t('Tahoma (Tahoma, Arial, Verdana, sans-serif)'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font_size'] = array(
    '#type'          => 'select',
    '#title'         => t('Change the base font size'),
    '#description'   => t('Adjusts all text in proportion to your base font size.'),
    '#default_value' => theme_get_setting('theme_font_size'),
    '#options'       => array(
      'font-size-10' => t('10px'),
      'font-size-11' => t('11px'),
      'font-size-12' => t('12px'),
      'font-size-13' => t('13px'),
      'font-size-14' => t('14px'),
      'font-size-15' => t('15px'),
      'font-size-16' => t('16px'),
      'font-size-17' => t('17px'),
      'font-size-18' => t('18px'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font_size']['#options'][$defaults['theme_font_size']] .= t(' - Theme Default');

  // Navigation
  $form['tnt_container']['general_settings']['navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Breadcrumb
  $form['tnt_container']['general_settings']['navigation']['breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumb'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['tnt_container']['general_settings']['navigation']['breadcrumb']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display breadcrumb'),
    '#default_value' => theme_get_setting('breadcrumb_display'),
  );

  // Search Settings
  if (module_exists('search')) {
    $form['tnt_container']['general_settings']['search_container'] = array(
      '#type' => 'fieldset',
      '#title' => t('Search results'),
      '#description' => t('What additional information should be displayed on your search results page?'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_snippet'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display text snippet'),
      '#default_value' => theme_get_setting('search_snippet'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_type'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display content type'),
      '#default_value' => theme_get_setting('search_info_type'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_user'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display author name'),
      '#default_value' => theme_get_setting('search_info_user'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_date'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display posted date'),
      '#default_value' => theme_get_setting('search_info_date'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_comment'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display comment count'),
      '#default_value' => theme_get_setting('search_info_comment'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_upload'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display attachment count'),
      '#default_value' => theme_get_setting('search_info_upload'),
    );
  }

  // Admin & developer settings
  $form['tnt_container']['admin_dev_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Administrator & developer settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
 $form['tnt_container']['admin_dev_settings']['grid_mask'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable grid overlay mask for administrators.'),
    '#default_value' => theme_get_setting('grid_mask'),
    '#description' => t('This setting enables a "GRID" button in the upper left corner of each page to toggle a grid overlay and block outlines, which can help with visualizing page layout and block positioning.'),
  );

  // Return theme settings form
  return $form;
}
