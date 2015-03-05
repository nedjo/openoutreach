<?php

/**
 * @file
 * Provides functionality to be used at install time.
 */

/**
 * Generate install tasks.
 */
function openoutreach_install_tasks($install_state) {
  $tasks = array();

  // Add Subprofiles tasks.
  require_once(drupal_get_path('module', 'subprofiles') . '/subprofiles.install.inc');
  $tasks = $tasks + _subprofiles_install_tasks($install_state);

  // Set up the theme selection task.
  $tasks['openoutreach_theme_form'] = array(
    'display_name' => st('Choose a theme'),
    'type' => 'form',
  );

  // Set up the wrapup task.
  $tasks['openoutreach_wrapup'] = array(
    'display_name' => st('Final details'),
  );

  return $tasks;
}

/**
 * Implements hook_install_configure_form_alter().
 */
function openoutreach_form_install_configure_form_alter(&$form, &$form_state) {
  global $install_state;

  $form['site_elements'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site elements'),
    '#weight' => -20,
  );
  $form['site_elements']['migrate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Install sample content'),
    '#default_value' => TRUE,
    '#description' => t('Select this box to get some initial content created on your site. Without sample content, the site may look empty before you start adding to it. Sample content also provides cues as to how to use and structure your site. You can later modify or delete the sample content.'),
  );
  $form['site_elements']['contact'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable a contact form and accompanying menu item'),
    '#default_value' => TRUE,
  );

  // Set some reasonable defaults for site configuration form.
  if (isset($install_state['profile_info']['distribution_name'])) {
    $form['site_information']['site_name']['#default_value'] = $install_state['profile_info']['distribution_name'];
  }
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  // Don't set the email address to "admin@localhost" as that will fail D7's
  // email address validation.
  if ($_SERVER['HTTP_HOST'] != 'localhost') {
    $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  }
  // Hide update notifications.
  $form['update_notifications']['#access'] = FALSE;
  $form['#submit'][] = 'openoutreach_install_configure_form_submit';
}

/**
 * Submit handler for install_configure_form. Conditionally enable sample
 * content module.
 */
function openoutreach_install_configure_form_submit($form, &$form_state) {

  // Set a flag that we'll later test to enable the migration module.
  if (!empty($form_state['values']['migrate'])) {
    variable_set('openoutreach_migrate', TRUE);
  }
  if (!empty($form_state['values']['contact'])) {
    // We don't want contact without captcha.
    module_enable(array('contact', 'captcha'));
  }
}

/**
 * Pseudo implementation of hook_user_default_permissions().
 *
 * @see openoutreach_install_permissions().
 */
function openoutreach_install_user_default_permissions() {
  $permissions = array();

  // Exported permission: access contextual links
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'contextual',
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: view advanced help index
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help popup
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: view advanced help topic
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  return $permissions;
}

/**
 * Install permissions for optional modules.
 *
 * Optional modules - identified by the "recommends" array in
 * openoutreach.info - cannot have their permissions in features; recommended
 * modules are enabled after features permissions are implemented, and in any
 * case such features would break if the optional module was disabled.
 *
 * Take advantage of existing support in the Features module for processing
 * default user permissions. Use a pseudo module name, 'openoutreach_install'.
 */
function openoutreach_install_permissions() {
  features_include();
  module_load_include('inc', 'features', 'features.export');
  user_permission_features_rebuild('openoutreach_install');

  if (module_exists('contact') && module_exists('captcha')) {
    // Assign permisions to access contact form.
    foreach (array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID) as $role_id) {
      user_role_grant_permissions($role_id, array('access site-wide contact form'));
    }

    // Set Captcha on the contact form.
    module_load_include('inc', 'captcha');
    captcha_set_form_id_setting('contact_site_form', 'default');

    // Conditionally create a Contact link in the main menu.
    // Do so here rather than immediately after enabling the contact module to
    // ensure the menu item is valid.
    // Create a Contact link in the main menu.
    $item = array(
      'link_title' => st('Contact'),
      'link_path' => 'contact',
      'menu_name' => 'main-menu',
      'options' => array(
        'attributes' => array(
          'title' => st('Send us an email.'),
        ),
      ),
      'weight' => '20',
    );
    menu_link_save($item);

    // Update the menu router information.
    menu_rebuild();
  }
}

/**
 * Form to choose the starting theme from list of available options.
 */
function openoutreach_theme_form($form, &$form_state) {
  drupal_set_title(t('Choose a theme'));

  // Declare a white list of themes offered for selection along with data used
  // to determine what modules should be enabled and what blocks configured.
  $form_state['theme dependencies'] = array(
    'outreach' => array('superfish'),
    'sky' => array('superfish'),
    'mix_and_match' => array('superfish'),
    'at_commerce' => array('superfish'),
  );

  // Create list of theme options.
  $theme_data = array_intersect_key(system_rebuild_theme_data(), $form_state['theme dependencies']);
  $themes = array();
  foreach($theme_data as $theme) {
    $themes[$theme->name] = theme('image', array('path' => $theme->info['screenshot'])) . '<strong>' . $theme->info['name'] . '</strong><br><p><em>' . strip_tags($theme->info['description']) . '</em></p><p class="clearfix"></p>';
  }

  // Move Outreach to first.
  $outreach = $themes['outreach'];
  unset($themes['outreach']);
  $themes = array('outreach' => $outreach) + $themes;

  $form['theme'] = array(
    '#title' => t('Starting Theme'),
    '#type' => 'radios',
    '#options' => $themes,
    '#default_value' => 'outreach',
  );

  $distribution_name = isset($install_state['profile_info']['distribution_name']) ? $install_state['profile_info']['distribution_name'] : t('Open Outreach');

  $form['openingtext'] = array(
    '#markup' => '<h3>' . t('!distribution_name now needs to do a bit more to get everything set up.', array('!distribution_name' => $distribution_name)) . '</h3><p>' . t('This step may take a few minutes.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Choose theme and set up site'),
  );

  $form['#attached']['css'] = array(
    drupal_get_path('profile', 'openoutreach') . '/openoutreach.install.css',
  );

  return $form;
}

/**
 * Form submit handler to select the theme.
 */
function openoutreach_theme_form_submit($form, &$form_state) {
  // Enable and set the theme of choice.
  $theme = $form_state['values']['theme'];
  theme_enable(array($theme));
  variable_set('theme_default', $theme);
  // Enable and set the theme of choice.
  $dependencies = $form_state['theme dependencies'];

  if (!empty($dependencies[$theme])) {
    module_enable($dependencies[$theme]);
  }

  // Copy over the 'outreach' settings if the selected theme is a different
  // adaptivetheme subtheme.
  if ($theme != 'outreach') {
    global $conf;
    cache_clear_all('variables', 'cache_bootstrap');
    $conf['theme_' . $theme . '_settings'] = $conf['theme_outreach_settings'];
  }

  // AdaptiveTheme requires that the system theme settings form
  // be submitted in order for its themes' settings to be properly set
  // and the resulting css files generated.
  // For more background, see http://drupal.org/node/1776730.
  module_load_include('inc', 'system', 'system.admin');
  $form_state = form_state_defaults();
  $form_state['build_info']['args'][0] = $theme;
  $form_state['values'] = array();
  drupal_form_submit('system_theme_settings', $form_state);

  // Assign regions for the theme.
  $regions = system_region_list($theme);
  $blocks = array();

  $assignments = array();
  $assignments['system'] = array(
    'main' => 'content',
    'help' => 'help',
  );

  if (module_exists('superfish')) {
    $assignments['superfish'] = array(
      // 'menu_bar' is the region used by adaptivetheme subthemes.
      'superfish_1' => 'menu_bar',
    );
  }

  foreach ($assignments as $module => $module_blocks) {
    foreach ($module_blocks as $delta => $region) {
      if (isset($regions[$region])) {
        $blocks[] = array(
          'module' => $module,
          'delta' => $delta,
          'theme' => $theme,
          'status' => 1,
          'weight' => 0,
          'region' => $region,
          'pages' => '',
          'cache' => -1,
        );
      }
    }
  }
  if ($blocks) {
    foreach ($blocks as $record) {
      $query = db_merge('block')
        ->key(array('theme' => $record['theme'], 'module' => $record['module'], 'delta' => $record['delta']))
        ->fields($record)
        ->execute();
    }
  }

  // Flush theme caches so things are right.
  system_rebuild_theme_data();
  drupal_theme_rebuild();
}

/**
 * Complete the install.
 */
function openoutreach_wrapup(&$install_state) {
  if (variable_get('openoutreach_migrate', FALSE)) {
    module_enable(array('openoutreach_migrate'));
    variable_del('openoutreach_migrate');
  }

  // Set error messages to an appropriate setting for production sites.
  // Don't do this in Features as sites may wish to turn on error reporting.
  // Set here as features rebuilding may trigger distracting error messages.
  variable_set('error_level', 0);

  openoutreach_install_permissions();

}
