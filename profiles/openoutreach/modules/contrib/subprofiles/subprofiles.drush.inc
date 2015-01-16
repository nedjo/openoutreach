<?php

/**
 * @file
 * Provides Subprofiles drush integration.
 *
 * Because it is designed to be used before a site has been installed, and
 * therefore before any module drush files are available, this file should be
 * copied to a location accessible to Drush, e.g., a .drush subdirectory in the
 * user's home directory.
 */

/**
 * Prevent a fatal error in the case that subprofiles.drush.inc is left in the
 * subprofiles module and also copied to e.g. the .drush directory.
 */
if (!function_exists('subprofiles_drush_command')) {

/**
 * Implementation of hook_drush_command().
 *
 * This is identical to the core Drush site-install command except that it
 * installs only the subprofiles profile and accepts as an argument a
 * subprofile as well as a profile name.
 */
function subprofiles_drush_command() {
  $items = array();

  $items['site-install-subprofile'] = array(
    'description' => 'Install Drupal along with modules/themes/configuration using the specified install profile and subprofile.',
    'arguments' => array(
      'profile' => "The install profile you wish to run. Defaults to 'standard'.",
      'subprofile' => "The install subprofile you wish to run. Defaults to 'standard'.",
    ),
    'options' => array(
      'features' => 'A list of features from the specified subprofile to be installed.',
      'db-url' => 'A Drupal 5/6 style database URL. Only required for initial install - not re-install.',
      'db-prefix' => 'An optional table prefix to use for initial install.',
      'account-name' => 'uid1 name. defaults to admin',
      'account-pass' => 'uid1 pass. defaults to admin',
      'account-mail' => 'uid1 email. defaults to admin@example.com',
      'locale' => 'A short language code. Sets the default site language. Language files must already be present. You may use download command to get them.',
      'clean-url'=> 'Defaults to 1',
      'site-name' => 'Defaults to Site-Install',
      'site-mail' => 'From: for system mailings. Defaults to admin@example.com',
      'sites-subdir' => "Name of directory under 'sites' which should be created. Only needed when the subdirectory does not already exist. Defaults to 'default'",
    ),
    'examples' => array(
      'drush subprofiles-site-install openoutreach minimal --locale=uk' => '(Re)install using the minimal subprofile. Set default language to Ukranian.',
      'drush subprofiles-site-install openoutreach minimal --features="debut,debut_article"' => "(Re)install using the openoutreach profile's minimal subprofile. Enable only the debut and debut_article features.",
      'drush subprofiles-site-install openoutreach --db-url=mysql://root:pass@localhost:port/dbname' => 'Install using the openoutreach profile and the default "standard" subprofile with specified DB params.',
      'drush subprofiles-site-install standard --db-url=sqlite:/full/path/to/database.sqlite' => 'Install using the standard profile (provided by Drupal core) and SQLite.',
      'drush subprofiles-site-install --account-name=joe --account-pass=mom' => 'Re-install with specified uid1 credentials.',
    ),
    'core' => array(7),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('sis'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function subprofiles_drush_help($section) {
  switch ($section) {
    case 'drush:subprofiles-site-install':
      return dt('Install Drupal with a specified subprofile.');
  }
}

/**
 * Command callback.
 *
 * Based on drush_core_site_install_version().
 *
 * @see drush_core_site_install_version().
 */
function drush_subprofiles_site_install_subprofile($profile = NULL, $subprofile = NULL) {
  if (is_null($profile)) {
    drush_print(dt('Usage: supbrofiles-site-install profilename subprofilename'));
    return;
  }

  if (is_null($subprofile)) {
    $subprofile = 'standard';
  }

  define('MAINTENANCE_MODE', 'install');
  require_once DRUPAL_ROOT . '/includes/install.core.inc';

  // Function was renamed to _drush_sql_get_db_spec. Support older versions.
  $db_spec = function_exists('_drush_sql_get_db_spec') ? _drush_sql_get_db_spec() : drush_core_site_install_db_spec();

  $account_pass = drush_get_option('account-pass', 'admin');
  $settings = array(
    'parameters' => array(
      'profile' => $profile,
      // Passing the subprofile here may be superfluous, as the form values
      // in install_configure_form override the subprofile's features.
      'subprofile' => $subprofile,
      'locale' => drush_get_option('locale', 'en'),
    ),
    'forms' => array(
      'install_settings_form' => array(
        'driver' => $db_spec['driver'],
        $db_spec['driver'] => $db_spec,
        'op' => dt('Save and continue'),
      ),
      'install_configure_form' => array(
        'subprofile' => $subprofile,
        'site_name' => drush_get_option('site-name', 'Site-Install'),
        'site_mail' => drush_get_option('site-mail', 'admin@example.com'),
        'account' => array(
          'name' => drush_get_option('account-name', 'admin'),
          'mail' => drush_get_option('account-mail', 'admin@example.com'),
          'pass' => array(
            'pass1' => $account_pass,
            'pass2' => $account_pass,
          ),
        ),
        'update_status_module' => array(
          1 => TRUE,
          2 => TRUE,
        ),
        'clean_url' => drush_get_option('clean-url', TRUE),
        'op' => dt('Save and continue'),
      ),
    ),
  );
  // Only specify values for features if they were explicitly passed in.
  $features = drush_get_option('features', array());
  if (count($features)) {
    $settings['forms']['install_configure_form'][$subprofile . '_features'] = $features;
  }
  drush_log(dt('Starting Drupal installation. This takes a few seconds ...'), 'ok');
  install_drupal($settings);
}

/**
 * Command validate.
 */
function drush_subprofiles_site_install_subprofile_validate() {
  drush_core_site_install_validate();
}

/**
 * Perform setup tasks for installation.
 */
function drush_subprofiles_pre_site_install_subprofile() {
  drush_core_pre_site_install();
}

}
