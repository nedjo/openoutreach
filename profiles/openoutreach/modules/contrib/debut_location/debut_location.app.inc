<?php

/**
 * @file
 * Apps integration and admin page callbacks for the debut_location module.
 */

/**
 * Implements hook_apps_app_info().
 */
function debut_location_apps_app_info() {
  return array(
    'configure form' => 'debut_location_map_settings',
  );
}

/**
 * Form to set default center and bounds for location map.
 *
 * @ingroup forms
 * @see debut_location_map_settings_submit()
 */
function debut_location_map_settings($form, &$form_state) {
  // Reuse the form elements provided by openlayers_ui.
  // The map will load with altered values, so there is no need here to
  // explicitly feed in the values that will be saved.
  $map = openlayers_map_load('location_map');
  module_load_include('inc', 'ctools', 'includes/export-ui');
  $openlayers_form = ctools_export_ui_switcher_page('openlayers_maps', 'edit', $map);
  // Need to maintain the same key, 'center', so that Javascript will work.
  $form['center'] = $openlayers_form['center'];
  $form = system_settings_form($form);
  // Override the default submit handler as we need to rename the variable.
  unset($form['#submit']);
  return $form;
}

/**
 * Submit handler for debut_location_map_settings form.
 */
function debut_location_map_settings_submit($form, &$form_state) {
  // Todo: Why does $form_state['values'] contain the original, not the
  // submitted values?
  $value = $form_state['input']['center'];
  // The restrictextent checkbox is not sent as a value if unchecked.
  if (!isset($value['restrict']['restrictextent'])) {
    $value['restrict']['restrictextent'] = '';
  }
  variable_set('debut_location_map_settings', $value);
  drupal_set_message(t('The configuration options have been saved.'));
}
