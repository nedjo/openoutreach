<?php

/**
 * @file
 *
 */

/**
 * Wrapper for system_admin_menu_block_page().
 */
function redhen_landing_page() {
  $items = array(
    'contact' => array(
      'module' => 'redhen_contact',
      'path' => 'redhen/contact',
      'title' => t('Contacts'),
      'description' => t('View, manage, and search contacts.'),
      'permission' => 'access redhen contacts',
    ),
    'org' => array(
      'module' => 'redhen_org',
      'path' => 'redhen/org',
      'title' => t('Organizations'),
      'description' => t('View, manage, and search organizations.'),
      'permission' => 'access redhen orgs',
    ),
    'membership' => array(
      'module' => 'redhen_membership',
      'path' => 'redhen/memberships',
      'title' => t('Memberships'),
      'description' => t('View, manage, and search memberships.'),
      'permission' => 'list redhen memberships',
    ),
    'activity' => array(
      'module' => 'redhen_activity',
      'path' => 'redhen/activity',
      'title' => t('Activity'),
      'description' => t('RedHen activity stream.'),
      'permission' => 'access redhen activity',
    ),
    'structure' => array(
      'path' => 'admin/structure/redhen',
      'title' => t('Structure'),
      'description' => t('Define bundles and manage fields for RedHen entities.'),
      'permission' => 'administer redhen',
    ),
    'settings' => array(
      'path' => 'admin/config/redhen',
      'title' => t('Settings'),
      'description' => t('RedHen configuration and settings.'),
      'permission' => 'administer redhen',
    ),
  );

  foreach ($items as $key => $item) {
    if ((isset($item['module']) && !module_exists($item['module'])) || !user_access($item['permission'])) {
      unset($items[$key]);
    }
  }

  return theme('redhen_home', array('items' => $items));
}

/**
 * Settings form for Redhen CRM.
 *
 * @return array
 *   System settings form array.
 */
function redhen_settings() {
  $form['intro'] = array(
    '#type' => 'item',
    '#markup' => t('RedHen CRM settings.'),
  );
  $form['redhen_admin_path'] = array(
    '#title' => t('Treat RedHen paths as administrative'),
    '#type' => 'checkbox',
    '#description' => t('This is used by other modules to, for example, use the admin theme on RedHen paths.'),
    '#default_value' => variable_get('redhen_admin_path', FALSE),
  );
  $items_page_options = array(
    5 => 5,
    10 => 10,
    15 => 15,
    20 => 20,
    30 => 30,
    40 => 40,
    50 => 50,
    100 => 100,
  );
  $form[REDHEN_ITEMS_PAGE] = array(
    '#title' => t('Number of items per page'),
    '#type' => 'select',
    '#options' => $items_page_options,
    '#description' => t('The number of records per page to show on all RedHen list pages.'),
    '#default_value' => variable_get(REDHEN_ITEMS_PAGE, 10),
  );

  // Allow other modules to inject their own settings.
  $form += module_invoke_all('redhen_settings');
  return system_settings_form($form);
}
