<?php

/**
 * @file
 * Provides methods for altering default components to be called from within
 * alter hooks.
 */

/**
 * Add coloring for any taxonomy terms added to a calendar view.
 *
 * Call this function from within a hook_views_default_views_alter()
 * implementation to have colors assigned to calendar listings by taxonomy
 * term. Example:
 * @code
 * function example_views_default_views_alter(&$views) {
 *   if (isset($views['event_calendar'])) {
       module_load_include('inc', 'apps_compatible', 'apps_compatible.alter');
 *     apps_compatible_calendar_view_colorize_by_term($views['event_calendar'], 'event_type', 'field_event_type');
 *   }
 * }
 * @endcode
 *
 * @param $view
 *   A view object.
 * @param $vocabulary_name
 *   The machine-readable name of a vocabulary to be used for coloring.
 * @param $field_name
 *   The name of a taxonomy term reference field to be used for coloring.
 * @param $colors
 *   An optional array of up to ten colors to be assigned to taxonomy terms.
 *   If omitted, a default color set will be used.
 */
function apps_compatible_calendar_view_colorize_by_term(&$view, $vocabulary_name, $field_name, $colors = array()) {
  if (empty($colors)) {
    $colors = array(
      // Red.
      '#FF0000',
      // Lime.
      '#00FF00',
      // Fuchsia.
      '#FF00FF',
      // Blue.
      '#0000FF',
      // Brown.
      '#A52A2A',
      // Aqua.
      '#00FFFF',
      // Purple.
      '#800080',
      // Green.
      '#008000',
      // Orange.
      '#FFA500',
      // Black.
      '#000000',
    );
  }
  if ($vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name)) {
    // Load all terms for the 'event_type' 
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'taxonomy_term')
      ->propertyCondition('vid', $vocabulary->vid, '=')
      ->propertyOrderBy('weight', 'ASC')
      ->propertyOrderBy('name', 'ASC')
      ->range(0, 10)
      ->execute();
    if ($result) {
      $tids = array_keys($result['taxonomy_term']);
      if (count($tids) < 10) {
        $colors = array_splice($colors, 0, count($tids));
      }
      $colors = array_combine($tids, $colors);
      foreach ($view->display as $display_id => $display) {
        if (isset($display->display_options['row_plugin']) && $display->display_options['row_plugin'] == 'calendar_entity') {
          // Set the field to be used for taxonomy coloring.
          $view->display[$display_id]->display_options['row_options']['colors']['taxonomy_field'] = $field_name;
          // Set the vocabulary to be used by vocabulary ID.
          $view->display[$display_id]->display_options['row_options']['colors']['calendar_colors_vocabulary'] = array($field_name => $vocabulary->vid);
          // Assign the array of term colors.
          $view->display[$display_id]->display_options['row_options']['colors']['calendar_colors_taxonomy'] = $colors;
        }
      }
    }
  }
}

