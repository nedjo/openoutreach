<?php

/**
 * @file
 * Views navigation style plugin for the Calendar module.
 */

/**
 * Style plugin to create the calendar navigation and links.
 * 
 * Used by the main calendar page and calendar block displays.
 */
class calendar_plugin_style extends views_plugin_style {
  /**
   * Init will be called after construct, when the plugin is attached to a
   * view and a display. 
   */
   function init(&$view, &$display, $options = NULL) {
     parent::init($view, $display, $options);
     if (!isset($view->date_info)) {
       $view->date_info = new StdClass();
     }
     $view->date_info->display_types = $this->display_types();
   }

  function display_types($granularity = NULL, $option_type = 'names') {
    $ids = array();
    $names = array();
    foreach (calendar_display_types() as $name => $type) {
      foreach ($this->view->display as $id => $display) {
        if ($display->display_plugin == 'calendar_period') {
          if (!empty($display->display_options['calendar_type']) && $display->display_options['calendar_type'] == $name) {
            $attachments = array_filter($display->display_options['displays']);
            if (isset($attachments['calendar_1'])) {
              $ids[$name] = $id;
              $names[$name] = $display->display_title;
            }
          }
        }
      }
    }
    if ($granularity) {
      return $$option_type[$granularity];
    }
    return $$option_type;
  }

  /**
   * Calendar argument date fields used in this view.
   */
  function date_fields() {
    $date_fields = array();
    $calendar_fields = date_views_fields();
    $arguments = $this->display->handler->get_option('arguments');
    foreach ($arguments as $name => $argument) {
      if (isset($argument['date_fields'])) {
        foreach ($argument['date_fields'] as $date_field) {
          $field = $calendar_fields['name'][$date_field];
          $handler = views_get_handler($field['table_name'], $field['field_name'], 'field');
          if ($handler) {
            $date_fields[$date_field] = $field;
            $date_fields[$date_field]['name'] = $handler->ui_name();
          }
        }
      }
    }
    return ($date_fields);
  }

  /**
   * Style validation.
   */
  function validate() {
    $errors = parent::validate();

    if (empty($this->display->display_options['style_plugin'])) {
      return $errors;
    }
    $style = $this->display->display_options['style_plugin'];

    $arguments = $this->display->handler->get_option('arguments');
    if (!in_array('date_argument', array_keys($arguments))) {
      if (empty($this->view->date_info->arg_missing)) {
        $errors[$style] = t("The @style style requires a Date argument.", array('@style' => $style));      
      }
      $this->view->date_info->arg_missing = TRUE;
    }
    elseif ($arguments['date_argument']['default_action'] != 'default' || $arguments['date_argument']['default_argument_type'] != 'date') {
      if (empty($this->view->date_info->arg_missing_default)) {
        $errors[] = calendar_errors('missing_argument_default');      
      }
      $this->view->date_info->arg_missing_default = TRUE;
    }

    // Make sure date fields are not set up to 'Group multiple values' 
    // in the calendar style.
    if ($style == 'calendar_style') {
      $view_fields = date_views_fields('node');
      $view_fields = $view_fields['name'];
      $fields = $this->display->handler->get_option('fields');
      foreach ($fields as $column => $field) {
        $field_name = $field['table'] . "." . $field['field'];
        if (!empty($field['multiple']) && array_key_exists($field_name, $view_fields)) {
          $cck_fields = field_info_fields();
          $real_name = $view_fields[$field_name]['real_field_name'];
          if ($cck_fields[$real_name]['multiple'] && !empty($field['multiple']['group'])) {
            $errors[] = t("The date field '@field' used by the display '@display_title' cannot be set to 'Group multiple values'.", array('@field' => $view_fields[$field_name]['label'], '@display_title' => $this->display->display_title));
          }
        }
      }
    }
    return $errors;
  }

  function query() {
    module_load_include('inc', 'date_api', 'date_api_sql');

    //$this->view->date_info->display_types = $this->display_types();
    $style_options = $this->view->style_plugin->options;

    // Evaluate our argument values and figure out which 
    // calendar display we need to create.
    $i = 0;   
    foreach ($this->view->argument as $id => $argument) {
      // The instanceof function makes this work for any handler that was derived 
      // from date_views_argument_handler_simple, including date_views_argument_handler.
      if ($argument instanceof date_views_argument_handler_simple) {
        $this->view->date_info->granularity = $argument->granularity;
        $this->view->date_info->date_arg = $argument->argument;
        $this->view->date_info->date_arg_pos = $i;
        $this->view->date_info->year = date_format($argument->min_date, 'Y');
        $this->view->date_info->month = date_format($argument->min_date, 'n');;
        $this->view->date_info->day = date_format($argument->min_date, 'j');
        $this->view->date_info->week = date_week(date_format($argument->min_date, DATE_FORMAT_DATE));
        $this->view->date_info->date_range = $argument->date_range;
        $this->view->date_info->min_date = $argument->min_date;
        $this->view->date_info->max_date = $argument->max_date;
        $this->view->date_info->limit = $argument->limit;
        $this->view->date_info->url = $this->view->get_url();
        $this->view->date_info->min_date_date = date_format($this->view->date_info->min_date, DATE_FORMAT_DATE);
        $this->view->date_info->max_date_date = date_format($this->view->date_info->max_date, DATE_FORMAT_DATE);
        $this->view->date_info->forbid = isset($argument->forbid) ? $argument->forbid : FALSE;
      }
      $i++;
    }
    $this->view->date_info->display_types = $this->display_types();
    $keys = drupal_map_assoc(array_keys(calendar_display_types()));
    $this->view->date_info->calendar_display = $keys[$this->view->date_info->granularity];

    parent::query();

    // We need the right date fields joined into our query if they are not already.
    // If we are dealing with a from/to date range, we need to know the whole range.
    // We may also need the delta for multiple value fields, because from that can get 
    // timezone or rrule. This extra work is necessary because otherwise we have the 
    // whole node with potentially dozens of fields and we would have to iterate over 
    // it and test each date on it to figure out which one(s) fall into the range for 
    // this view, and then which ones should fall into each day in the calendar. 
    // It's far easier to add the fields to the query, knowing that we will
    // have results that include only the specific values that meet our criteria. 
    // This also makes the results of field date queries consistent with non-field date 
    // queries, so the results for a calendar of node changed dates (which will always
    // have all the right tables and fields joined in) will be structured the same as 
    // the results for a calendar of date fields.

    $date_fields = array();
    $all_date_fields = date_views_fields($this->view->base_table);
    foreach ($this->view->argument as $name => $handler) {
      if (date_views_handler_is_date($handler, 'argument')) {
        foreach ($handler->options['date_fields'] as $alias) {
          // Make sure the tables we need are joined in.
          $info = $all_date_fields['name'][$alias];
          $table = $info['table_name'];
          if ($handler->table != $table && !empty($handler->relationship)) {
            $table = $this->view->query->queue_table($table, $handler->relationship);
          }
          // Make sure both from and to date values and the delta are identified in our results.
          $base_field = str_replace(array('_value2', '_value'), '', $info['field_name']);
          if ($base_field != $info['field_name']) {
            if (!array_key_exists($table . '_' . $base_field . '_value', $this->view->query->fields)) {
              $this->view->query->add_field($table, $base_field . '_value');
            }
            if ($info['fromto'][0] != $info['fromto'][1] && !array_key_exists($table . '_' . $base_field . '_value2', $this->view->query->fields)) {
              $this->view->query->add_field($table, $base_field . '_value2');
            } 
            if (!empty($info['delta_field']) && !array_key_exists($table . '_' . $info['delta_field'], $this->view->query->fields)) {
              $this->view->query->add_field($table, $delta_field);
            } 
          }   
        }
      }
    }
  }

  /**
   * Render the calendar navigation style.
   */
  function render() {
    return theme($this->theme_functions(), array('view' => $this->view, 'options' => $this->options, 'items' => array()));
  }
}
