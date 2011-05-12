<?php
/**
 * @file
 * A standard Views filter for a single date field, using Date API form selectors and sql handling.
 */

class date_views_filter_handler_simple extends views_handler_filter_date {
  var $date_handler = NULL;

  function init(&$view, &$options) {
    parent::init($view, $options);
    module_load_include('inc', 'date_api', 'date_api_sql');
    $this->date_handler = new date_sql_handler(DATE_UNIX);
    if (!empty($this->definition['field_name'])) {
      $field = field_info_field($this->definition['field_name']);
      if (!empty($field) && !empty($field['type'])) {
        $this->date_handler->date_type = $field['type'];
      }
    }
    $this->form_submitted = FALSE;
    $this->date_handler->granularity = isset($options['granularity']) ? $options['granularity'] : 'day';
    $this->format = $this->date_handler->views_formats($this->options['granularity'], 'sql');
  }

  // Set default values for the date filter.
  function option_definition() {
    $options = parent::option_definition();
    $options['granularity'] = array('default' => 'day', 'export' => 'export_plugin');
    $options['form_type'] = array('default' => 'date_select', 'export' => 'export_plugin');
    $options['default_date'] = array('default' => '', 'export' => 'export_plugin');
    $options['default_to_date'] = array('default' => '', 'export' => 'export_plugin');
    $options['year_range'] = array('default' => '-3:+3', 'export' => 'export_plugin');  
    return $options;
  }

  /**
   * Make sure our custom options get exported.
   * Handle the options we know about, pass the rest to the parent plugin.
   */
  function export_plugin($indent, $prefix, $storage, $option, $definition, $parents) {
    $output = '';
    if (in_array($option, array('granularity', 'form_type', 'default_date', 'default_to_date', 'year_range'))) {
      $name = $this->options[$option];
      $output .= $indent . $prefix . "['$option'] = '$name';\n";
      return $output;
    }
    return parent::export_plugin($indent, $prefix, $storage, $option, $definition, $parents);
  }

  /**
   * Helper function to find a default value.
   */
  function date_default_value($prefix, $options = NULL) {
    $default_date = '';
    if (empty($options)) {
      $options = $this->options;
    }

    // If this is a remembered value, use the value from the SESSION.
    if (!empty($this->options['expose']['remember'])) {
      $display_id = ($this->view->display_handler->is_defaulted('filters')) ? 'default' : $this->view->current_display;
      return $_SESSION['views'][$this->view->name][$display_id]['date_filter'][$prefix];
    }

    // This is a date that needs to be constructed from options like 'now' .
    $default_option = $prefix == 'max' ? $options['default_to_date'] : $options['default_date'];
    if (!empty($default_option)) {
      str_replace('now', 'today', $default_option);
      $date = date_create($default_option, date_default_timezone_object());
      $default_date = !empty($date) ? $date->format($this->format) : '';

      // The format for our filter is in ISO format, but the widget will need it in datetime format.
      $default_date = str_replace('T', ' ', $default_date);
    }
    // This a fixed date.
    else {
      $default_date = $options['value'][$prefix];
    }
    return $default_date;
  }

  /**
   * Helper function to see if we need to swap in the default value.
   *
   * Views exposed filters treat everything as submitted, so if it's an empty value we have to
   * see if anything actually was submitted. If nothing has really been submitted, we need
   * to swap in our default value logic.
   */
  function get_filter_value($prefix, $input) {
    if (empty($input)) {
      if (empty($this->options['exposed'])) {
        return $this->date_default_value($prefix);
      }
      elseif (isset($this->options['expose']['identifier']) && !isset($_GET[$this->options['expose']['identifier']])) {
        return $this->date_default_value($prefix);
      }
    }
    // All our date widgets provide datetime values but we use ISO in our SQL
    // for consistency between the way filters and arguments work (arguments
    // cannot contain spaces).
    return str_replace(' ', 'T', $input);
  }

  function accept_exposed_input($input) {
    $element_input = $input[$this->options['expose']['identifier']];
    $element_input['value'] = $this->get_filter_value('value', !empty($element_input['value']) ? $element_input['value'] : '');
    $element_input['min'] = $this->get_filter_value('min', !empty($element_input['min']) ? $element_input['min'] : '');
    $element_input['max'] = $this->get_filter_value('max', !empty($element_input['max']) ? $element_input['max'] : '');
    unset($element_input['default_date']);
    unset($element_input['default_to_date']);

    $input[$this->options['expose']['identifier']] = $element_input;
    return parent::accept_exposed_input($input);

  }

  function op_between($field) {
    $min_value = $this->get_filter_value('min', $this->value['min']);
    $max_value = $this->get_filter_value('max', $this->value['max']);
    $field = $this->date_handler->sql_field($field);
    $field = $this->date_handler->sql_format($this->format, $field);
    $placeholder_min = $this->placeholder();
    $placeholder_max = $this->placeholder();
    $group = !empty($this->options['date_group']) ? $this->options['date_group'] : $this->options['group'];
    if ($this->operator == 'between') {
      $this->query->add_where_expression($group, "$field >= $placeholder_min", array($placeholder_min => $min_value));
      $this->query->add_where_expression($group, "$field <= $placeholder_max", array($placeholder_max => $max_value));
    }
    else {
      $this->query->add_where_expression($group, "$field <= $placeholder_min OR $field >= $placeholder_max", array($placeholder_min => $min_value, $placeholder_max => $max_value));
    }
  }

  function op_simple($field) {
    $value = $this->get_filter_value('value', $this->value['value']);
    $field = $this->date_handler->sql_field($field);
    $field = $this->date_handler->sql_format($this->format, $field);
    $placeholder = $this->placeholder();
    $group = !empty($this->options['date_group']) ? $this->options['date_group'] : $this->options['group'];
    $this->query->add_where_expression($group, "$field $this->operator $placeholder", array($placeholder => $value));
  }

  /**
   * Set the granularity of the date parts to use in the filter.
    */
  function has_extra_options() { return TRUE; }

  /**
   * Date selection options.
   */
  function widget_options() {
    $options = array(
      'date_select' => t('Select'), 
      'date_text' => t('Text'), 
      'date_popup' => t('Popup'),
      );
    if (!module_exists('date_popup')) {
      unset($options['date_popup']);
    }  
    return $options;
  }

  function year_range() {
    $year_range = explode(':', $this->options['year_range']);
    if (substr($this->options['year_range'], 0, 1) == '-' || $year_range[0] < 0) {
      $this_year = date_format(date_now(), 'Y');
      $year_range[0] = $this_year + $year_range[0];
      $year_range[1] = $this_year + $year_range[1];
    }
    return $year_range;
  }

  function extra_options_form(&$form, &$form_state) {
    parent::extra_options_form($form, $form_state);
    $form['form_type'] = array(
      '#type' => 'radios',
      '#title' => t('Date form type'),
      '#default_value' => $this->options['form_type'],
      '#options' => $this->widget_options(),
      '#description' => t('Choose the form element to use for date selection.'),
      );

    $form['granularity'] = $this->date_handler->granularity_form($this->options['granularity']);
    $form['granularity']['#description'] = '<p>' . t("Select a granularity for the date filter. For instance, selecting 'day' will create a filter where users can select the year, month, and day.") . '</p>';

    $form['year_range'] = array(
      '#title' => t('Date year range'),
      '#type' => 'textfield',
      '#default_value' => $this->options['year_range'],
      '#description' => t("Set the allowable minimum and maximum year range for this argument, either a -X:+X offset from the current year, like '-3:+3' or an absolute minimum and maximum year, like '2005:2010' . When the argument is set to a date outside the range, the page will be returned as 'Page not found (404)' ."),
    );
  }

  function extra_options_validate($form, &$form_state) {
    if (!preg_match('/^(?:\-[0-9]{1,4}|[0-9]{4}):(?:[\+|\-][0-9]{1,4}|[0-9]{4})$/', $form_state['values']['options']['year_range'])) {
      form_error($form['year_range'], t('Date year range must be in the format -9:+9, 2005:2010, -9:2010, or 2005:+9'));
    }
  }

  /**
   * Add the selectors to the value form using the date handler.
   */
  function value_form(&$form, &$form_state) {
    // We use different values than the parent form, so we must
    // construct our own form element.
    $form['value'] = array();
    $form['value']['#tree'] = TRUE;

    // Below section copied from views_handler_filter_numeric.inc.
    $which = 'all';
    $source = '';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator_id'])) {
        // exposed and locked.
        $which = in_array($this->operator, $this->operator_values(2)) ? 'minmax' : 'value';
      }
      else {
        $source = 'edit-' . drupal_html_id($this->options['expose']['operator_id']);
      }
    }

    if ($which == 'all' || $which == 'value') {
      $form['value'] += $this->date_parts_form($form_state, 'value', $source, $which, $this->operator_values(1), $identifier);
    }

    if ($which == 'all' || $which == 'minmax') {
      $form['value'] += $this->date_parts_form($form_state, 'min', $source, $which, $this->operator_values(2), $identifier);
      $form['value'] += $this->date_parts_form($form_state, 'max', $source, $which, $this->operator_values(2), $identifier);
    }

    // Add some text to make it clear when additional options are available.
    $extra = t("You can use any values PHP's date_create() can understand, like between '12AM today' and '12AM tomorrow.");
    $form['value']['default_date'] = array(
      '#type' => 'textfield',
      '#title' => t('Date default'),
      '#default_value' => $this->options['default_date'],
      '#prefix' => '<div class="form-item"><label>' . t('Relative value') . '</label><p>' . t("Relative values will be used if no date is set above. Use 'now' to default to the current date at runtime or add modifiers like 'now +1 day' . The To date default value is used when the operator is set to 'between' or 'not between'.") . ' ' . $extra . '</p><p>' . t('If the filter is exposed, these values will be used to set the inital value of the exposed filter. Leave both date and default values blank to start with no value in the exposed filter.') . '</p></div>',
      );
    $form['value']['default_to_date'] = array(
      '#type' => 'textfield',
      '#title' => t('To date default'),
      '#default_value' => $this->options['default_to_date'],
      );

    // Test if this value is in the UI or exposed, only show these elements in the UI.
    // We'll save it as an option rather than a value to store it for use
    // in the exposed filter.
    if (!empty($form_state['exposed'])) {
      $form['value']['default_date']['#type'] = 'value';
      $form['value']['default_date']['#value'] = $form['value']['default_date']['#default_value'];
      $form['value']['default_to_date']['#type'] = 'value';
      $form['value']['default_to_date']['#value'] = $form['value']['default_to_date']['#default_value'];
      unset($form['value']['default_date']['#prefix']);
    }
  }

  /**
   * A form element to select date part values.
   *
   * @param string $prefix
   *   A prefix for the date values, 'value', 'min', or 'max' .
   * @param string $source
   *   The operator for this element.
   * @param string $which
   *   Which element to provide, 'all', 'value', or 'minmax' .
   * @param array $operator_values
   *   An array of the allowed operators for this element.
   * @param array $limit
   *   An array of date parts to limit this element to.
   *
   * @return
   *   The form date part element for this instance.
   */
  function date_parts_form($form_state, $prefix, $source, $which, $operator_values, $identifier) {
    module_load_include('inc', 'date_api', 'date_api_elements');
    switch($prefix) {
      case 'min':
        $name = t('From date');
        break;
      case 'max':
        $name = t('To date');
        break;
      default:
        $name = '';
        break;
    }

    $type = $this->options['form_type'];
    if ($type == 'date_popup' && !module_exists('date_popup')) {
      $type = 'date_text';
    }

    $format = $this->date_handler->views_formats($this->options['granularity'], 'sql');
    $granularity = array_keys($this->date_handler->date_parts($this->options['granularity']));

    // Don't set a default date in the UI, only in the exposed form.
    $default_date = '';
    if (!empty($form_state['exposed'])) {
      $default_date = $this->date_default_value($prefix);
    }
    $id = !empty($form_state['exposed']) ? 'edit-' . str_replace('_', '-', $this->field) . '-' . $prefix : 'edit-options-value-' . $prefix;
    $form[$prefix] = array(
      '#title' => $name,
      '#type' => $type,
      '#size' => 20,
      '#default_value' => !empty($this->value[$prefix]) ? $this->value[$prefix] : $default_date,
      '#date_format' => date_limit_format($format, $granularity),
      '#date_label_position' => 'within',
      '#date_year_range' => $this->options['year_range'],
      '#process' => array($type . '_element_process'),
      '#prefix' => '<div id="' . $id . '-wrapper"><div id="' . $id . '">',
      '#suffix' => '</div></div>',
    );
    if ($which == 'all') {
      $form[$prefix]['#pre_render'][] = 'ctools_dependent_pre_render';
      $form[$prefix]['#dependency'] = array($source => $operator_values);
    }
    if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier][$prefix])) {
      $form_state['input'][$identifier][$prefix] = $this->value[$prefix];
    } 
    return $form;
  }

  /**
   * Value validation.
   * 
   * TODO add in more validation.
   * 
   * We are setting an extra option using a value form
   * because it makes more sense to set it there. 
   * That's not the normal method, so we have to manually
   * transfer the selected value back to the option.
   */
  function value_validate($form, &$form_state) {

    if (($form_state['values']['options']['operator'] == 'between' || $form_state['values']['options']['operator'] == 'not between') && 
    !empty($form_state['values']['options']['value']['default_date']) && empty($form_state['values']['options']['value']['default_to_date'])) {
      form_error($form['value']['default_to_date'], t('Please set a default value for the To date as well as the From date when using default values with the Between or Not between operators.'));
    }
    if (isset($form_state['values']['options']['value']['default_date'])) {
      $this->options['default_date'] = $form_state['values']['options']['value']['default_date'];
      $this->options['default_to_date'] = $form_state['values']['options']['value']['default_to_date'];
    }

  }

  /**
   * Validate that the time values convert to something usable.
   */
  function validate_valid_time(&$form, $operator, $value) {
    // Override the core date filter validation.
    // Our date widgets do their own validation.
  }

  // Update the summary values to provide
  // meaningful information for each option.
  function admin_summary() {
    $parts = $this->date_handler->date_parts();
    $widget_options = $this->widget_options();
    // If the filter is exposed, display the granularity.
    if ($this->options['exposed']) {
      return t('<strong>Exposed</strong> @widget @format', array('@format' => $parts[$this->date_handler->granularity], '@widget' => $widget_options[$this->options['form_type']]));
    }
    // If not exposed, display the value.
    $output = '';
    if (in_array($this->operator, $this->operator_values(2))) {
      $min = check_plain(!empty($this->options['default_date']) ? $this->options['default_date'] : $this->options['value']['min']);
      $max = check_plain(!empty($this->options['default_to_date']) ? $this->options['default_to_date'] : $this->options['value']['max']);
      $output .= t('@min and @max', array('@min' => $min, '@max' => $max));
    }
    else {
      $output .= check_plain(!empty($this->options['default_date']) ? $this->options['default_date'] : $this->options['value']['value']);
    }
    return $output;
  }

}