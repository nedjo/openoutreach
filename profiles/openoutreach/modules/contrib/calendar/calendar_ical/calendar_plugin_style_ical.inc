<?php

/**
 * @file
 * Views style plugin for the Calendar iCal module.
 */

/**
 * Default style plugin to render an iCal feed.
 */
class calendar_plugin_style_ical extends views_plugin_style_rss {
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $fields = $display->handler->default_display->options['fields'];
    $this->options['fields'] = $fields;
  }

  function query() {
    // We need these values for the iCal feed.
    $this->view->query->add_field('node', 'title');
    $this->view->query->add_field('node', 'type');
    parent::query();
  }

  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }

    // TODO adjust this to pick up default values when no arg is set?
    $url = url($this->view->get_url(NULL, $path), $url_options);
    if (empty($this->view->feed_icon)) {
      $this->view->feed_icon = '';
    }
    $this->view->feed_icon .= theme('calendar_ical_icon', array('url' => $url));

    drupal_add_html_head_link(array(
      'rel' => 'alternate',
      'type' => 'application/calendar',
      'title' => $title,
      'href' => $url
    ));
  }

  /**
   * Set default options
   */
  function options(&$options) {
    parent::options($options);
    $options['summary_field'] = 'title';
    $options['description_field'] = '';
    $options['location_field'] = '';
    $options['fields'] = array();
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['summary_field'] = array('default' => '', 'translatable' => TRUE);
    $options['description_field'] = array('default' => '', 'translatable' => TRUE);
    $options['location_field'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $options = array('' => '');
    foreach ($this->options['fields'] as $field) {
      $handler = views_get_handler($field['table'], $field['field'], 'field');
      $options[$field['field']] = $handler->ui_name();
    }
    $form['#prefix'] = '<div class="form-item">' . t("Map the View fields to the values they should represent in the iCal feed. Only fields that have been added to the view are available to use in this way. You can add additional fields to the view and mark them 'Exclude from display' if you only want them in the iCal feed.") . '</div>';

    $form['summary_field'] = array(
      '#type' => 'select',
      '#title' => t('Title'),
      '#default_value' => !empty($this->options['summary_field']) ? $this->options['summary_field'] : 'title',
      '#options' => $options,
      '#required' => TRUE,
      );
    $form['description_field'] = array(
      '#type' => 'select',
      '#title' => t('Description'),
      '#default_value' => $this->options['description_field'],
      '#options' => $options,
      );
    $form['location_field'] = array(
      '#type' => 'select',
      '#title' => t('Location'),
      '#default_value' => $this->options['location_field'],
      '#options' => $options,
      );

  }

  /**
   * Style validation.
   */
  function validate() {
    $errors = parent::validate();

    $style = $this->display->display_options['style_plugin'];

    $arguments = $this->display->handler->get_option('arguments');
    $filters = $this->display->handler->get_option('filters');

    if (!array_key_exists('date_argument', $arguments) && !array_key_exists('date_filter', $filters)) {
      if (empty($this->view->date_info->arg_missing)) {
        $errors[$style] = t("The @style style requires a Date argument or a Date filter.", array('@style' => $style));
      }
      $this->view->date_info->arg_missing = TRUE;
    }
    if (array_key_exists('date_argument', $arguments) &&
    ($arguments['date_argument']['default_action'] != 'default' || $arguments['date_argument']['default_argument_type'] != 'date')) {
      if (empty($this->view->date_info->arg_missing_default)) {
        $errors[] = calendar_errors('missing_argument_default');
      }
      $this->view->date_info->arg_missing_default = TRUE;
    }

    if (empty($this->options['summary_field'])) {
      $errors[] = $errors[$style] = t("The @style style requires a Title field for the iCal export.", array('@style' => $style));
    }
    // Make sure date fields are not set up to 'Group multiple values'
    // in the calendar style.
    if ($style == 'calendar_style') {
      $view_fields = date_views_fields($this->view->base_table);
      $view_fields = $view_fields['name'];
      $fields = $this->display->handler->get_option('fields');
      foreach ($fields as $column => $field) {
        $field_name = $field['table'] . "." . $field['field'];
        if (!empty($field['multiple'])) {
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

  function render() {
    module_load_include('inc', 'calendar', 'includes/calendar');

    // Transfer the style options to the view object so they
    // can be easily accessed in the theme.
    $style_options = $this->options;
    $this->view->date_info->summary_field = $style_options['summary_field'];
    $this->view->date_info->description_field = $style_options['description_field'];
    $this->view->date_info->location_field = $style_options['location_field'];

    // Evaluate our argument values and figure out which values to use.
    $date_filter = NULL;
    foreach ($this->view->filter as $id => $handler) {
      if (date_views_handler_is_date($handler, 'filter')) {
        $date_filter = $handler;
        $key = 'filter';
        $name = $id;
      }
    }
    $i = 0;
    foreach ($this->view->argument as $id => $handler) {
      if (date_views_handler_is_date($handler, 'argument')) {
        $date_filter = $handler;
        $key = 'argument';
        $name = $id;
        $pos = $i;
        $i++;
      }
    }
    if (!empty($date_filter)) {
      
      if ($key == 'argument') {
        $this->view->date_info->date_arg = !empty($this->view->args) ? $this->view->args[$date_filter->position] : '';
        $this->view->date_info->date_arg_pos = $pos;

        // TODO Decide if we want to provide a date here or not.
        // Adding this now is to prevent fatal errors later if the
        // view is used in unexpected ways without a date being set.
        if (empty($date_filter->min_date)) {
          $value = $date_filter->get_default_argument();
          $range = $date_filter->date_handler->arg_range($value);
          $date_filter->min_date = $range[0];
          $date_filter->max_date = $range[1];
        }
      }

      elseif ($key == 'filter') {
        // TODO Decide if we want to provide a date here or not.
        // Adding this now is to prevent fatal errors later if the
        // view is used in unexpected ways without a date being set.
        if (empty($date_filter->min_date)) {
          $value = $date_filter->date_default_value('value');
          $range = $date_filter->date_handler->arg_range($value);
          $date_filter->min_date = $range[0];
          $date_filter->max_date = $range[1];
        }
      }
      $this->view->date_info->granularity = !empty($date_filter->granularity) ? $date_filter->granularity : $date_filter->options['granularity'];
      $this->view->date_info->min_date = $date_filter->min_date;
      $this->view->date_info->max_date = $date_filter->max_date;
      if (empty($this->view->date_info->date_fields)) {
        $this->view->date_info->date_fields = array();
      }
      $this->view->date_info->date_fields = array_merge($this->view->date_info->date_fields, array_keys($date_filter->options['date_fields']));

    }

    // Render each field into an output array.
    $result   = (array) $this->view->result;
    $this->view->style_plugin->render_fields($result);
    $rendered_items = !empty($view->style_plugin->rendered_fields) ? $view->style_plugin->rendered_fields : array();
    $items = array();
  
    $calendar_fields = date_views_fields($this->view->base_table);
    $calendar_fields = array_keys($calendar_fields['alias']);
  
    // Try to figure out the 'id' for this collection of items.
    // The id field is often not a field but instead an 'additional field',
    // so this is cludgy.
    foreach ($result as $num => $row) {
      $keys = array_keys((array) $row);
      foreach ($keys as $key) {
        if (strlen($key) == 3 && substr($key, -2) == 'id' && !empty($row->$key)) {
          $id = $key;
        }
      }
    }
    foreach ($result as $num => $row) {
      $copy = clone($row);
      $items[$num]->id = !empty($row->$id) ? $row->$id : NULL;
      $items[$num]->rendered = !empty($rendered_items[$num]) ? $rendered_items[$num] : '';
      $items[$num]->raw = $copy;
  
      $items[$num]->calendar_fields = new stdClass();
      foreach ($row as $key => $value) {
        if (in_array($key, $calendar_fields)) {
          $items[$num]->calendar_fields->$key = $value;
        }
      }
    }

    // Massage the resulting items into formatted calendar items.
    $items = calendar_build_nodes($this->view, $items);

    // Merge in items from other sources.
    foreach (module_implements('calendar_add_items') as $module) {
      $function = $module . '_calendar_add_items';
      if (function_exists($function)) {
        if ($feeds = $function($this->view)) {
          foreach ($feeds as $feed) {
            $items = $feed;
          }
        }
      }
    }
      
    return theme($this->theme_functions(),
      array(
        'view' => $this->view,
        'options' => $this->options,
        'items' => $items)
      );    
  }
}
