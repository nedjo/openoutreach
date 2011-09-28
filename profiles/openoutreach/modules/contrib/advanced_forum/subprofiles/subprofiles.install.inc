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
  $tasks = array(
    'subprofiles_install_profile_features' => array(
      'display_name' => st('Install !profile features', array('!profile' => $profile)),
      'type' => 'batch',
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
 * Implements hook_form_FORM_ID_alter().
 *
 * Alter the site configuration form to enable selecting of a subprofile and
 * specific subprofile features to be enabled.
 */
function subprofiles_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  if ($subprofiles = subprofiles_get_subprofiles()) {
    $info = install_profile_info(drupal_get_profile());
    
    $form['subprofile'] = array(
      '#type' => 'fieldset',
      '#title' => st('!profile flavours', array('!profile' => $info['name'])),
      '#description' => st('Select the flavour of !profile you wish to install.', array('!profile' => $info['name'])),
      '#weight' => -1,
    );
    // Extract features checkboxes from the features admin form.
    module_load_include('inc', 'features', 'features.admin');
    $features_admin_form = features_admin_form(array(), array());
    $features = $features_admin_form['features']['status'];
    foreach ($subprofiles as $subprofile_name => $subprofile) {
      $title = $subprofile['name'];
      $form['subprofile'][$title] = array(
        '#type' => 'radio',
        '#default_value' => 'standard',
        '#return_value' => $subprofile_name,
        '#title' => $title,
        '#description' => isset($subprofile['description']) ? $subprofile['description'] : NULL,
        '#parents' => array('subprofile'),
      );
      $subprofile_features = $features;
      // Reduce selectable features to those specified in the selected subprofile
      // and set their default enabled status to that in the .info file.
      foreach (array_keys($subprofile_features) as $name) {
        if (!isset($subprofile['features'][$name])) {
          unset($subprofile_features[$name]);
        }
        else {
          $subprofile_features[$name]['#default_value'] = $subprofile['features'][$name];
        }
      }
      $form[$subprofile_name . '_features'] = array(
        '#type' => 'fieldset',
        '#title' => st('Customize !title features', array('!title' => $title)),
        '#description' => st('Select the features you wish to enable. You will also have a chance to enable or disable features after installing.'),
        '#weight' => -1,
        // Show the fieldset only when the corresponding subprofile is selected.
        '#states' => array(
          'visible' => array(
            ':input[name=subprofile]' => array('value' => $subprofile_name),
          ),
        ),
        '#tree' => TRUE,
      ) + $subprofile_features;
    }

    $form['#submit'][] = 'subprofiles_install_configure_form_submit';
  }
}

/**
 * Submit handler for install_configure_form. Set a variable specifying the
 * features to be installed.
 */
function subprofiles_install_configure_form_submit($form, &$form_state) {
  $subprofile = $form_state['values']['subprofile'];
  $features = array_keys(array_filter($form_state['values'][$subprofile . '_features']));
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
