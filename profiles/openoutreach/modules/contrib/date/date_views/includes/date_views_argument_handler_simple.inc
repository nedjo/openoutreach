<?php
/**
 * @file
 * Date API views argument handler.
 */

/**
 * Date API argument handler.
 */
class date_views_argument_handler_simple extends views_handler_argument_date {

  /**
   * Get granularity and use it to create the formula and a format
   * for the results.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Identify the type of display we're using.
    $this->display_handler = $view->display_handler->definition['handler'];

    // Add a date handler.
    module_load_include('inc', 'date_api', 'date_api_sql');
    $this->date_handler = new date_sql_handler(DATE_UNIX);
    if (!empty($this->definition['field_name'])) {
      $field = field_info_field($this->definition['field_name']);
      if (!empty($field) && !empty($field['type'])) {
        $this->date_handler->date_type = $field['type'];
      }
    }
    $this->date_handler->granularity = $this->options['granularity'];

    $this->format = $this->date_handler->views_formats($this->date_handler->granularity, 'display');
    $this->sql_format = $this->date_handler->views_formats($this->date_handler->granularity, 'sql');
    // $this->arg_format is the format the parent date handler will use to create a default argument.
    $this->arg_format = $this->format();
 }

  /**
   * Add a callback for the formula to wrap the field in the right SQL.
   */
  function formula() {
    $formula =  $this->date_handler->sql_format($this->sql_format, $this->date_handler->sql_field("***table***.$this->real_field"));
    return $formula;
  }

  /**
   * Override the parent get_formula() to use the date_handler formula.
   */
  function get_formula() {
    return str_replace('***table***', $this->table_alias, $this->formula());
  }

  function format() {
    if (!empty($this->options['granularity'])) {
      return $this->date_handler->views_formats($this->options['granularity']);
    }
    else {
      return !empty($this->options[$this->option_name]) ? $this->options[$this->option_name] : 'Y-m';
    }
  }

  /**
   * Set the empty argument value to the current date,
   * formatted appropriately for this argument.
   */
  function get_default_argument($raw = FALSE) {
    if (!$raw && $this->options['default_argument_type'] == 'date') {
      $granularity = $this->options['granularity'];
      if ($granularity == 'week') {
        $now = date_now();
        $week = date_week($now);
        return date_format($now, 'Y') .'-W'. $week;
      } 
      else {
        return date($this->arg_format, REQUEST_TIME);
      }
    }
    // Let the parent argument handle options like node created date.
    return parent::get_default_argument($raw);
  }

  /**
   * Default value for the date_fields option.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['year_range'] = array('default' => '-3:+3', 'export' => 'export_plugin');
    $options['granularity'] = array('default' => 'month', 'export' => 'export_plugin');
    $options['default_argument_type'] = array('default' => 'date', 'export' => 'export_plugin');
    return $options;
  }

  /**
   * Make sure our custom options get exported.
   * Handle the options we know about, pass the rest to the parent plugin.
   */
  function export_plugin($indent, $prefix, $storage, $option, $definition, $parents) {
    $output = '';
    if (in_array($option, array('year_range', 'granularity', 'default_argument_type'))) {
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
    $options = $this->date_handler->date_parts();
    unset($options['second'], $options['minute']);
    $options += array('week' => t('Week', array(), array('context' => 'datetime')));
    $form['granularity'] = array(
      '#title' => t('Granularity'),
      '#type' => 'radios',
      '#options' => $options,
      '#default_value' => $this->options['granularity'],
      '#multiple' => TRUE,
      '#description' => t("Select the type of date value to be used in defaults, summaries, and navigation. For example, a granularity of 'month' will set the default date to the current month, summarize by month in summary views, and link to the next and previous month when using date navigation."),
    );

    $form['year_range'] = array(
      '#title' => t('Date year range'),
      '#type' => 'textfield',
      '#default_value' => $this->options['year_range'],
      '#description' => t("Set the allowable minimum and maximum year range for this argument, either a -X:+X offset from the current year, like '-3:+3' or an absolute minimum and maximum year, like '2005:2010' . When the argument is set to a date outside the range, the page will be returned as 'Page not found (404)' ."),
    );
  }

  function options_validate(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_validate($form, $form_state);
    if (!preg_match('/^(?:\-[0-9]{1,4}|[0-9]{4}):(?:[\+|\-][0-9]{1,4}|[0-9]{4})$/', $form_state['values']['options']['year_range'])) {
      form_error($form['year_range'], t('Date year range must be in the format -9:+9, 2005:2010, -9:2010, or 2005:+9'));
    }
  }

  /**
   * Provide a link to the next level of the view from the summary.
   */
  function summary_name($data) {
    $value = $data->{$this->name_alias};
    if (empty($value) && !empty($this->definition['empty field name'])) {
      return $this->definition['empty field name'];
    }
    elseif (empty($value)) {
      return $this->options['wildcard_substitution'];
    }
    $format = $this->date_handler->views_formats($this->options['granularity'], 'display');
    $range = $this->date_handler->arg_range($value);
    return date_format_date($range[0], 'custom', $format);
  }

  /**
   * Provide the argument to use to link from the summary to the next level;
   * this will be called once per row of a summary, and used as part of
   * $view->get_url().
   *
   * @param $data
   *   The query results for the row.
   */
  function summary_argument($data) {
    $format = $this->date_handler->views_formats($this->options['granularity'], 'sql');
    $value = $data->{$this->name_alias};
    if (empty($value)) {
      return $this->options['exception']['value'];
    }
    $range = $this->date_handler->arg_range($value);
    return date_format_date($range[0], 'custom', $format);
  }

  /**
   * Inject a test for valid date range before the summary query.
   */
  function summary_query() {
    if ($this->date_forbid()) {
      return;
    }
    $this->formula = $this->formula($this->real_field);
    parent::summary_query();
  }

  /**
   * Inject a test for valid date range before the regular query.
   * Override the parent query to be able to control the $group.
   */
  function query($group_by = FALSE) {
    if ($this->date_forbid()) {
      return;
    }
    
    $this->formula = $this->formula($this->real_field);
    $this->date_handler->granularity = $this->date_handler->arg_granularity($this->argument);
    $this->format = $this->date_handler->views_formats($this->date_handler->granularity, 'display');
    $this->sql_format = $this->date_handler->views_formats($this->date_handler->granularity, 'sql');

    $this->ensure_my_table();
    $group = !empty($this->options['date_group']) ? $this->options['date_group'] : 0;

    // Now that our table is secure, get our formula.
    if ($this->date_handler->granularity != 'week') {
      $placeholder = $this->placeholder();
      $formula = $this->get_formula() .' = ' . $placeholder;
      $placeholders = array(
        $placeholder => $this->argument,
      );
      $this->query->add_where($group, $formula, $placeholders, 'formula');
    }
    else {
      $min_value = date_format($this->min_date, DATE_FORMAT_DATETIME);
      $max_value = date_format($this->max_date, DATE_FORMAT_DATETIME);
      $field = $this->date_handler->sql_field($this->table . '.' . $this->real_field);
      $field = $this->date_handler->sql_format(DATE_FORMAT_DATETIME, $field);
      $placeholder_min = $this->placeholder();
      $placeholder_max = $this->placeholder();
      $this->query->add_where_expression($group, "$field >= $placeholder_min", array($placeholder_min => $min_value));
      $this->query->add_where_expression($group, "$field <= $placeholder_max", array($placeholder_max => $max_value));
    }

  }

  /**
   * Add a callback to determine if we have moved outside the valid date range for this argument.
   */
  function date_forbid() {
    if (empty($this->argument)) {
      return;
    }
    $this->date_range = $this->date_handler->arg_range($this->argument);
    $this->min_date = $this->date_range[0];
    $this->max_date = $this->date_range[1];
    $this->limit = date_range_years($this->options['year_range']); 
    $group = !empty($this->options['date_group']) ? $this->options['date_group'] : 0;

    // See if we're outside the allowed date range for our argument.
    if (date_format($this->min_date, 'Y') < $this->limit[0] || date_format($this->max_date, 'Y') > $this->limit[1]) {
      $this->forbid = TRUE;
      $this->query->add_where_expression($group, "0=1", array());
      return TRUE;
    }
    return FALSE;
  }
}
