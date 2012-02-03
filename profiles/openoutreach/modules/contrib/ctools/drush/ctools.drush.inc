<?php

/**
 * @file
 * CTools Drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function ctools_drush_command() {
  $items = array();

  $items['ctools-export'] = array(
    'aliases' => array('ctex'),
    'description' => 'Export multiple CTools-handled data objects directly to code.',
    'arguments' => array(
      'module'    => 'Name of your module.',
    ),
    'options' => array(
      'subdir' => 'The name of the sub directory to create the module in. Defaults to ctools_export which will be placed into sites/all/modules.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'drupal dependencies' => array('bulk_export'),
    'examples' => array(
      'drush ctex export_module' => 'Export CTools exportables to a module called "export_module".',
    ),
  );

  return $items;
}

/**
 * Drush callback: export
 */
function drush_ctools_export($module = 'foo') {
  $error = FALSE;
  if (preg_match('@[^a-z_]+@', $module)) {
    $error = dt('The name of the module must contain only lowercase letters and underscores') . '.';
    drush_log($error, 'error');
    return;
  }

  // Subdirectory.
  $dest_exists = FALSE;
  $subdir = drush_get_option('subdir', 'ctools_export');
  $dest = 'sites/all/modules/' . $subdir . '/' . $module;

  // Check if module or folder exists.
  if (module_exists($module) || file_exists($dest)) {
    $dest_exists = TRUE;
    if (drush_confirm(dt('Are you sure to overwrite files in folder !module ? An extra confirmation will be asked for the module file.', array('!module' => $module)))) {
      drush_log(dt('Files will be overwritten'), 'success');
    }
    else {
      drush_log(dt('Export aborted.'), 'success');
      return;
    }
  }

  // Create new dir if needed.
  if (!$dest_exists) {
    if (!file_exists('sites/all/modules/' . $subdir)) {
      drush_mkdir('sites/all/modules/' . $subdir);
    }
  }

  // Create destination directory.
  drush_mkdir($dest);

  // Create options and call Bulk export function.
  // We create an array, because maybe in the future we can pass in more
  // options to the export function (pre-selected modules and/or exportables).
  $options = array(
    'name' => $module,
  );
  $files = bulk_export_export(TRUE, $options);

  // Start writing.
  if (is_array($files)) {
    foreach ($files as $base_file => $data) {
      $filename = $dest . '/' . $base_file;
      // Extra check for .module file.
      if ($base_file == $module . '.module' && file_exists($filename)) {
        if (!drush_confirm(dt('Do you want to overwrite !module_file', array('!module_file' => $base_file)))) {
          drush_log(dt('Writing of !filename skipped. This is the code that was supposed to be written.', array('!filename' => $filename)), 'success');
          drush_print('---------');
          drush_print($data);
          drush_print('---------');
          continue;
        }
      }
      if (file_put_contents($filename, $data)) {
        drush_log(dt('Succesfully written !filename', array('!filename' => $filename)), 'success');
      }
      else {
        drush_log(dt('Error writing !filename', array('!filename' => $filename)), 'error');
      }
    }
  }
  else {
    drush_log(dt('No files were found to be written.'), 'error');
  }
}