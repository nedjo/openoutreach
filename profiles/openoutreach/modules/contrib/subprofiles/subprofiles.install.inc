<?php

/**
 * @file
 * Provides functionality to be used at install time.
 */

/**
 * Generate an install task to install subprofile features.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return
 *   The install task definition.
 */
function _subprofiles_install_tasks($install_state) {
  if (isset($install_state['parameters']['profile']) && $info = install_profile_info($install_state['parameters']['profile'])) {
    $profile = $info['name'];
  }
  else {
    $profile = st('profile');
  }

  $args = array('!profile' => $profile);
  $tasks = array(
    // Enable the selected features.
    'subprofiles_install_profile_features' => array(
      'display_name' => st('Install !profile features', $args),
      'type' => 'batch',
    ),
    // Subprofiles is no longer needed when it's done its work, so disable.
    'subprofiles_disable_self' => array(
      'display' => FALSE,
    ),
  );
  return $tasks;
}

/**
 * Installation task; install profile features via a batch process.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return
 *   The batch definition.
 */
function subprofiles_install_profile_features(&$install_state) {
  // If the installer was run interactively, specific features may have been selected.
  $modules = variable_get('subprofiles_install_profile_features', array());
  variable_del('subprofiles_install_profile_features');

  // If the install wasn't interactive, use the default features of the
  // subprofile.
  if (!count($modules)) {
    // Determine whether a subprofile was specified via a parameter.
    if (isset($install_state['parameters']['subprofile']) && !empty($install_state['parameters']['subprofile'])) {
      $subprofile_name = $install_state['parameters']['subprofile'];
    }
    // If not, look for a Drush option.
    elseif (function_exists('drush_get_option')) {
      $subprofile_name = drush_get_option('subprofile', 'standard');
    }
    // Finally, allow a variable, and if that's not set then use 'standard'.
    else {
      $subprofile_name = variable_get('subprofile', 'standard');
    }
    $subprofile = subprofiles_get_subprofile($install_state['parameters']['profile'], $subprofile_name);
    // Filter so that we have only the features set to be enabled by default.
    $modules = array_keys(array_filter($subprofile['features']));
  }
  module_load_include('inc', 'subprofiles', 'subprofiles.module_batch');
  return subprofiles_get_module_batch($modules);
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form.
 *
 * Alter the site configuration form to enable selecting of a subprofile and
 * specific subprofile features to be enabled.
 */
function subprofiles_form_install_configure_form_alter(&$form, $form_state) {
  if ($subprofiles = subprofiles_get_subprofiles()) {
    $info = install_profile_info(drupal_get_profile());
    $form['subprofiles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Select the type of !profile site you wish to install.', array('!profile' => $info['name'])),
      '#tree' => FALSE,
      '#weight' => -30,
    );
    // Add a custom suprofile that will show as options all available features
    // that were included in at least one subprofile.
    $subprofiles['custom'] = array(
      'name' => t('Custom'),
      'description' => t('Customize your own install.'),
      'features' => array(),
    );

    // Extract features checkboxes from the features admin form.
    module_load_include('inc', 'features', 'features.admin');
    $features_admin_form = features_admin_form(array(), array());
    $features = array();
    foreach (element_children($features_admin_form) as $child) {
      if (isset($features_admin_form[$child]['#type']) && $features_admin_form[$child]['#type'] == 'fieldset') {
        unset($features_admin_form[$child]['status']['#tree']);
        $features = array_merge($features, $features_admin_form[$child]['status']);
      }
    }
    ksort($features);
    $form['subprofiles']['subprofile'] = array(
      '#type' => 'select',
      '#default_value' => isset ($subprofiles['standard']) ? 'standard' : 'custom',
      // Hide by default for non-js usage.
      '#attributes' => array('class' => array('element-hidden')),
    );
    $options = array();
    foreach ($subprofiles as $subprofile_name => $subprofile) {
      $options[$subprofile_name] = $subprofile['name'];
      if (isset($subprofile['description'])) {
        $form['subprofiles']['subprofile_' . $subprofile_name] = array(
          '#type' => 'item',
          '#markup' => $subprofile['description'],
          '#states' => array(
            'visible' => array('select[name=subprofile]' => array('value' => $subprofile_name)),
          ),
        );
      }
      // Reduce selectable features to those specified in the selected subprofile
      // and set their default enabled status to that in the .info file.
      foreach ($subprofile['features'] as $name => $enable) {
        if (isset($features[$name])) {
          $features[$name]['#use'] = TRUE;
          $features[$name]['#states']['visible']['select[name=subprofile]'][] = array('value' => $subprofile_name);
          if ($enable) {
            $features[$name]['#states']['checked']['select[name=subprofile]'][] = array('value' => $subprofile_name);
          }
        }
      }
    }
    $form['subprofiles']['subprofile']['#options'] = $options;
    foreach ($features as $key => $info) {
      // Remove unused features and features whose element is disabled because
      // they are missing or already enabled.
      if (!isset($info['#use']) || isset($info['#disabled']) && $info['#disabled']) {
        unset($features[$key]);
      }
      // If it's offered in any of the subprofiles, process it.
      else {
        // Show it for the 'custom' option.
        $features[$key]['#states']['visible']['select[name=subprofile]'][] = array('value' => 'custom');
        // Add a logo.
        $info = system_get_info('module', $key);
        // Like theme screenshots, support a custom path specified in the
        // feature's .info file. If no path is specified, default to
        // 'logo.png'.
        $logo_path = drupal_get_path('module', $key) . '/' . (isset($info['logo']) ? $info['logo'] : 'logo.png');
        if (file_exists($logo_path)) {
          $logo = theme('image', array('path' => $logo_path, 'width' => '80px', 'height' => '80px'));
        }
        else {
          $logo = '';
        }
        $features[$key]['#title'] = '<strong>' . strip_tags($features[$key]['#title']) . '</strong><p><div>' . $logo . $features[$key]['#description'] . '</div></p>';
        unset($features[$key]['#description']);
      }
    }
    $form['subprofiles']['features'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    ) + $features;
    $path = drupal_get_path('module', 'subprofiles');
    $form['#attached']['js'][] = $path . '/subprofiles.js';
    $form['#attached']['css'][] = $path . '/subprofiles.css';
    $form['#submit'][] = 'subprofiles_install_configure_form_submit';
  }
}

/**
 * Submit handler for subprofiles_install_configure_form_submit. Set a variable
 * specifying the features to be installed.
 */
function subprofiles_install_configure_form_submit($form, &$form_state) {
  $features = array_keys(array_filter($form_state['values']['features']));
  variable_set('subprofiles_install_profile_features', $features);
}

/**
 * Return an array of data about subprofiles of a profile.
 */
function subprofiles_get_subprofiles($profile = NULL) {
  $profile = _subprofiles_get_profile($profile);
  include_once DRUPAL_ROOT . '/includes/install.inc';
  $info = install_profile_info($profile);
  return isset($info['subprofiles']) ? $info['subprofiles'] : FALSE;
}

/**
 * Return an array of data about a specified subprofile of a profile.
 *
 * @param $profile
 *   The name of a profile.
 * @param $subprofile
 *   The name of a subprofile.
 *
 * @return
 *   Array of information about the specified subprofile, if available.
 */
function subprofiles_get_subprofile($profile = NULL, $subprofile = 'standard') {
  $profile = _subprofiles_get_profile($profile);
  $subprofiles = subprofiles_get_subprofiles($profile);
  return $subprofiles && isset($subprofiles[$subprofile]) ? $subprofiles[$subprofile] : FALSE;
}

/**
 * Helper function to determine the site's profile if none is specified.
 *
 * @param $profile
 *   The name of a profile.
 *
 * @return
 *   The name of the site's install_profile.
 */
function _subprofiles_get_profile($profile) {
  return empty($profile) ? drupal_get_profile() : $profile;
}

/**
 * Disable subprofiles when it's done its work.
 */
function subprofiles_disable_self() {
  module_disable(array('subprofiles'));
}
