<?php
/**
 * @file
 * Date API views argument handler.
 * This argument combines multiple date arguments into a single argument 
 * where all fields are controlled by the same date and can be combined with either AND or OR.
 */

/**
 * Date API argument handler.
 */
class date_views_argument_handler extends date_views_argument_handler_simple {

  /**
   * Get granularity and use it to create the formula and a format
   * for the results.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    if (empty($this->view->date_info)) {
      $this->view->date_info = new stdClass();
    }
    if (empty($this->view->date_info->date_fields)) {
      $this->view->date_info->date_fields = array();
    }
    $this->view->date_info->date_fields = array_merge($this->view->date_info->date_fields, $this->options['date_fields']);
  }

  /**
   * Default value for the date_fields option.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['date_fields'] = array('default' => array());
    $options['date_method'] = array('default' => 'OR', 'export' => 'export_plugin');
    $options['date_group'] = array('default' => 'date', 'export' => 'export_plugin');
    return $options;
  }

  /**
   * Make sure our custom options get exported.
   * Handle the options we know about, pass the rest to the parent plugin.
   */
  function export_plugin($indent, $prefix, $storage, $option, $definition, $parents) {
    $output = '';
    if (in_array($option, array('date_method', 'date_group'))) {
      $name = $this->options[$option];
      $output .= $indent . $prefix . "['$option'] = '$name';\n";
      return $output;
    }
    return parent::export_plugin($indent, $prefix, $storage, $option, $definition, $parents);
  }

  /**
   * Add a form element to select date_fields for this argument.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $fields = date_views_fields($this->view->base_table);
    $options = array();
    foreach ($fields['name'] as $name => $field) {
      $options[$name] = $field['label'];
    }

    $form['date_fields'] = array(
      '#title' => t('Date field(s)'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $this->options['date_fields'],
      '#multiple' => TRUE,
      '#description' => t("Select one or more date fields to filter with this argument. Do not select both the 'From date' and 'To date' for date fields, only one of them is needed."),
    );
    $form['date_method'] = array(
      '#title' => t('Method'),
      '#type' => 'radios',
      '#options' => array('OR' => t('OR'), 'AND' => t('AND')),
      '#default_value' => $this->options['date_method'],
      '#description' => t('Method of handling multiple date fields in the same query. Return items that have any matching date field (date = field_1 OR field_2), or only those with matches in all selected date fields (date = field_1 AND field_2). '),
      );
    $form['date_group'] = array(
      '#type' => 'hidden',
      '#value' => $this->options['date_group'],
    );

  }

  function options_validate(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_validate($form, $form_state);

    if ($form_state['values']['form_id'] == 'views_ui_config_item_form') {
      $check_fields = array_filter($form_state['values']['options']['date_fields']);
      if (empty($check_fields)) {
        form_error($form['date_fields'], t('You must select at least one date field for this argument.'));
      }
    }
  }

  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);
    if ($form_state['values']['form_id'] == 'views_ui_config_item_form') {
      $form_state['values']['options']['date_fields'] = array_filter($form_state['values']['options']['date_fields']);
    }
  }

  // Update the summary values to show selected granularity.
  function admin_summary() {
    $fields = date_views_fields($this->view->base_table);
    if (!empty($this->options['date_fields'])) {
      $output = array();
      foreach ($this->options['date_fields'] as $field) {
        $output[] = $fields['name'][$field]['label'];
      }
      return implode('<br />' . $this->options['date_method'] . ' ', $output);
    }
    else {
      return parent::admin_summary();
    }
  }

  /**
   * Provide a list of default behaviors for this argument if the argument
   * is not present.
   *
   * Override this method to provide additional (or fewer) default behaviors.
   */
  function default_actions($which = NULL) {
    $defaults = parent::default_actions();
  
    // There is no easy way to do summary queries on multiple fields, so remove that option.
    unset($defaults['summary']);

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }

  function get_query_fields() {
    $fields = date_views_fields($this->view->base_table);
    $fields = $fields['name'];
    $this->query_fields = array();
    foreach ($this->options['date_fields'] as $delta => $name) {
      if (array_key_exists($name, $fields) && $field = $fields[$name]) {
        $date_handler = new date_sql_handler($field['sql_type'], date_default_timezone());
        $date_handler->granularity = $this->options['granularity'];
        date_views_set_timezone($date_handler, $this, $field);
        $this->query_fields[] = array('field' => $field, 'date_handler' => $date_handler);
      }
    }
  }

  /**
   * Set up the query for this argument.
   *
   * The argument sent may be found at $this->argument.
   */
  function query($group_by = FALSE) {
    if ($this->date_forbid()) {
      return;
    }

    $this->get_query_fields();
    $block_identifier = date_block_identifier($this->view);
    if (!empty($this->view->block_identifier) || isset($_GET[$block_identifier])) {
      // Retrieve the block arguments in a way that will work for
      // urls like user/%/calendar/2009-04.
      if (!empty($_GET[$block_identifier])) {
        $path_args = explode('/', $this->view->get_path());
        $mini_args = explode('/', $_GET[$block_identifier]);
        foreach ($path_args as $pos => $key) {
          if ($path_args[$pos] != '%') {
            unset($mini_args[$pos]);
          }
        }
        // Get rid of gaps in the array caused by embedded args.
        $mini_args = array_values($mini_args);
        $this->view->args = $mini_args;
      }
      $i = 0;
      foreach ($this->view->argument as $argument) {
        if ($argument->field == 'date_argument') {
          $this->argument = $this->view->args[$argument->position];
          break;
        }
        $i++;
      }
    }
    $this->query->set_where_group($this->options['date_method'], $this->options['date_group']);
    $this->granularity = $this->date_handler->arg_granularity($this->argument);
    $format = $this->date_handler->views_formats($this->granularity, 'sql');
    if (!empty($this->query_fields)) {
      // Use set_where_group() with the selected date_method 
      // of 'AND' or 'OR' to create the where clause.
      foreach ($this->query_fields as $count => $query_field) {
        $field = $query_field['field'];
        $this->date_handler = $query_field['date_handler'];
        $this->real_field = $field['field_name'];
        $this->table = $field['table_name'];
        if ($field['table_name'] != $this->table || !empty($this->relationship)) {
          $this->table = $this->query->queue_table($field['table_name'], $this->relationship);
        }
        // $this->table_alias gets set when the first field is processed if otherwise empty.
        // For subsequent fields, we need to be sure it is emptied again.
        elseif (empty($this->relationship)) {
          $this->table_alias = NULL;
        }
        $this->formula = $this->formula();
        parent::query($group_by);
      }
    }
  }
}
