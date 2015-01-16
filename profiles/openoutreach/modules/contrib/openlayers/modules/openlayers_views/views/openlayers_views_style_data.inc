<?php

/**
 * @file
 * This file holds style plugin for OpenLayers Views
 *
 * @ingroup openlayers
 */

/**
 * @class
 * Extension of the Views Plugin Style for OpenLayers
 *
 * This class extended the default views plugin class to provide
 * a style plugin for the Open Layers module.
 */
class openlayers_views_style_data extends views_plugin_style {

   /**
   * Render the map features.
   *
   * Overrides views_plugin_style->render
   */
  function render() {
    $grouped_results = $this->render_grouping($this->view->result, $this->options['grouping']);
    $data = $this->map_features($grouped_results);

    // If we are not in preview, just return the data
    if (empty($this->view->live_preview)) {
      return $data;
    }
    else {
      // If we are in preview mode, dump out some useful information about this data layer
      $output = "You can use the following parameters in your styles as dynamic values";
      $output .= "\n------------\n";
      if (!empty($data)) {
        $keys = array_keys($data);
        foreach ($data[$keys[0]]['attributes'] as $key => $value) {
          $output .= '${' . $key . "}\n";
        }
      }
      $output .= "\n------------\n";

      $output .= t('The following is a dump of the data that is rendered from this display. It is used for debugging purposes only.') . '
        ' . var_export($data, TRUE);

      return $output;
    }
  }

  /**
   * Set default options
   *
   * Overrides views_plugin_style->option_definition
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['data_source'] = array('default' => 'openlayers_wkt');
    return $options;
  }

  /**
   * Options form
   *
   * Overrides views_plugin_style->options_form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get list of fields in this view & flag available geodata fields
    $handlers = $this->display->handler->get_handlers('field');

    // Check for any fields, as the view needs them
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#value' => t('You need to enable at least one field before you can '
          . 'configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      return;
    }

    $fields = array();
    foreach ($handlers as $field_id => $handler) {
      $fields[$field_id] = $handler->ui_name() . ' (' . $field_id .')';
    }

    $form['data_source'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('Data Source'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['data_source']['value'] = array(
      '#type' => 'select',
      '#title' => t('Map Data Sources'),
      '#description' => t('Choose which sources of data that the map will '
      . 'provide features for.'),
      '#options' => array(
        'other_latlon' => t('Lat/Lon Pair'),
        'other_boundingbox' => t('Bounding Box'),
        'wkt' => t('WKT')
      ),
      '#default_value' => $this->options['data_source']['value'],
    );
    if (count($fields > 0)) {
      $form['data_source']['other_lat'] = array(
        '#type' => 'select',
        '#title' => t('Latitude Field'),
        '#description' => t('Choose a field for Latitude.  This should be a '
        . 'field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_lat'],
        '#states' => $this->datasource_dependent('other_latlon')
      );
      $form['data_source']['other_lon'] = array(
        '#type' => 'select',
        '#title' => t('Longitude Field'),
        '#description' => t('Choose a field for Longitude.  This should be a '
        . 'field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_lon'],
        '#states' => $this->datasource_dependent('other_latlon')
      );

      $form['data_source']['wkt'] = array(
        '#type' => 'select',
        '#title' => t('WKT Field'),
        '#description' => t('Choose the OpenLayers WKT field.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['wkt'],
        '#states' => $this->datasource_dependent('wkt')
      );

      $form['data_source']['other_top'] = array(
        '#type' => 'select',
        '#title' => t('Top Field'),
        '#description' => t('Choose a field for Top.  This should be a '
        . 'field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_top'],
        '#states' => $this->datasource_dependent('other_boundingbox')
      );
      $form['data_source']['other_right'] = array(
        '#type' => 'select',
        '#title' => t('Right Field'),
        '#description' => t('Choose a field for Right.  This should be a field '
        . 'that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_right'],
        '#states' => $this->datasource_dependent('other_boundingbox')
      );
      $form['data_source']['other_bottom'] = array(
        '#type' => 'select',
        '#title' => t('Bottom Field'),
        '#description' => t('Choose a field for Bottom.  This should be a '
        . 'field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_bottom'],
        '#states' => $this->datasource_dependent('other_boundingbox')
      );
      $form['data_source']['other_left'] = array(
        '#type' => 'select',
        '#title' => t('Left Field'),
        '#description' => t('Choose a field for Left.  This should be a field ' .
          'that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_left'],
        '#states' => $this->datasource_dependent('other_boundingbox')
      );
    }
    $form['data_source']['name_field'] = array(
      '#type' => 'select',
      '#title' => t('Title Field'),
      '#description' => t('Choose the field which will appear as a title on ' .
        'tooltips.'),
      '#options' => array_merge(array('' => ''), $fields),
      '#default_value' => $this->options['data_source']['name_field'],
    );

    // For node content type, we can render the node as with a specific
    // view mode.
    if ($this->view->base_table == 'node') {
      $desc_options = array_merge(array(
        '' => '',
        '#row' => '<' . t('entire row') . '>',
      ), $fields);
    }
    else {
      $desc_options = array_merge(array(
        '' => '',
        '#row' => '<' . t('entire row') . '>',
      ), $fields);
    }

    // Description field
    $form['data_source']['description_field'] = array(
      '#type' => 'select',
      '#title' => t('Description Content'),
      '#description' => t('Choose the field or rendering method which will
        appear as a description on tooltips or popups.'),
      '#required' => FALSE,
      '#options' => $desc_options,
      '#default_value' => $this->options['data_source']['description_field'],
    );

    $form['data_source']['style_field'] = array(
      '#type'          => 'select',
      '#title'         => t('Style Field'),
      '#description'   => t('Choose the field which will appear as a style on '
        . 'the layer.'),
      '#required'      => FALSE,
      '#options'       => array('' => '', ) + $fields,
      '#default_value' => $this->options['data_source']['style_field'],
    );

    // A simple way to display attributes and styling
    $form['attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Attributes and Styling'),
      '#description' => t('Attributes are field data attached to each '
      . 'feature.  This can be used with styling to create Variable styling.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $variable_fields = array();
    foreach ($this->view->display_handler->get_handlers('field') as
             $field => $handler) {
        $variable_fields[$field] = '${' . $field . '}';
    }
    if (!empty($this->options['data_source']['name_field'])) {
      $variable_fields['name'] = '${name}';
    }
    if (!empty($this->options['data_source']['description_field'])) {
      $variable_fields['description'] = '${description}';
    }

    $form['attributes']['display'] = array(
      '#title' => 'Select attributes to include in the features',
      '#type' => 'checkboxes',
      '#options' => $variable_fields,
      '#default_value' => !empty($this->options['attributes']['display']) ?
          $this->options['attributes']['display'] : array_combine(array_keys($variable_fields), array_keys($variable_fields)),
      '#description' => t('Any fields that you select will be attached to '
          . 'their respective feature (point, line, polygon) as attributes.  '
          . 'These attributes can then be used to add variable styling to your '
          . 'themes.  This is accomplished by using the %syntax syntax in the '
          . 'values for a style.  You can see a list of available variables in '
          . 'the view preview; these can be placed right in the style interface. '
          . 'The field has been processed by Views.'
          . 'By disabling some of them, you can reduce the size '
          . 'of the Javascript included in your pages.'
          . 'Please note that this does not apply to Grouped Displays.',
          array(
            '%syntax' => '${field_name}'
          ))
    );
  }


  /**
   * @param $records ...
   *
   * openlayers_views_style_data specific
   */
  function map_features($sets = array()) {
    $features = $excluded_fields = array();
    $handlers = $this->display->handler->get_handlers('field');

    foreach ($sets as $title => $records) {
      foreach ($records as $id => $record) {
        $this->view->row_index = $id;
        $attributes = array();
        $wkt = NULL;
        $field_exclude = array();

        // Save the 'exclude' options of fields as backup.
        foreach ($this->view->field as $fid => $field) {
          $field_exclude[$fid] = $field->options['exclude'];
        }
        // Loop through each fields and render it if there were only one
        // field in the row, so we have all the goodness of Views's field
        // wrapping, class customizations and label.
        foreach ($handlers as $hid => $handler) {
          $field_id = $handler->options['id'];
          // Exclude all the field from rendering
          foreach ($this->view->field as $field) {
            $field->options['exclude'] = TRUE;
          }
          // Enable only the field we want to render the row.
          $this->view->field[$field_id]->options['exclude'] = FALSE;
          // Render the row.
          $attributes[$hid] = trim($this->row_plugin->render($record));
        }
        // Restore the state of the exclude options in the fields.
        foreach ($this->view->field as $fid => $field) {
          $this->view->field[$fid]->options['exclude'] = $field_exclude[$fid];
        }

        // Add the 'name' attribute.
        if (isset($this->options['data_source']['name_field'])) {
          if (isset($attributes[$this->options['data_source']['name_field']])) {
            $attributes['name'] = $attributes[$this->options['data_source']['name_field']];
          }
        }

        // Add the 'description' attribute.
        if (isset($this->options['data_source']['description_field'])) {
          // Handle rendering the whole record.
          if ($this->options['data_source']['description_field'] === '#row') {
            $attributes['description'] = $this->row_plugin->render($record);
          } else {
            if (isset($attributes[$this->options['data_source']['description_field']])) {
              $attributes['description'] = $attributes[$this->options['data_source']['description_field']];
            }
          }
        }

        // We do not need the rendered value for these fields,
        // just the raw value.
        // This is why we use $this->rendered_fields.
        if (isset($this->options['data_source']['value'])) {
          switch ($this->options['data_source']['value']) {
            case 'wkt':
              $wkt = $this->rendered_fields[$id][$this->options['data_source']['wkt']];
              break;
            case 'other_latlon':
              $wkt = 'POINT(' . $this->rendered_fields[$id][$this->options['data_source']['other_lon']] . ' ' . $this->rendered_fields[$id][$this->options['data_source']['other_lat']] . ')';
              break;
          }
        }

        // Only render features that has been enabled in the configuration
        // of the display.
        if (isset($this->options['attributes']['display'])) {
          foreach($this->options['attributes']['display'] as $id => $value) {
            if ($this->options['attributes']['display'][$id] === 0) {
              unset($attributes[$id]);
            }
          }
        }

        // Create features array.
        $feature = array(
          'projection' => 'EPSG:4326',
          'attributes' => $attributes,
          'style' => $this->get_style($attributes, $handlers, $this->options['data_source'], $record),
          'wkt' => $wkt,
        );

        $features = $this->reduce_features($this->options['grouping'], $features, $feature, $title);
      }
    }

    // For grouping, handle a bit differently.
    if ($this->options['grouping']) {
      $features = $this->coalesce_groups($features, $handlers, $this->options['data_source']);
    }

    return $features;
  }

  /**
   * Basically a macro because
   * #state is rather verbose
   *
   * openlayers_views_style_data specific
   */
  function datasource_dependent($type) {
    return array('visible' => array('#edit-style-options-data-source-value' => array('value' => $type)));
  }

  /**
   * Find and compute styling attributes.
   */
  function get_style($feature, $handlers, $datasource, $record) {
    $style = NULL;

    if (isset($datasource['style_field']) && !empty($datasource['style_field'])) {
      $style_field = $handlers[$datasource['style_field']];
      // Check if field is not empty
      if ($style_field->original_value) {
        $style = $style_field->options['settings'];

        if ($style_field->original_value) {
          $image_info = image_get_info($style_field->original_value);
          $style['graphicWidth'] = $image_info['width'];
          $style['graphicHeight'] = $image_info['height'];

          unset($style['imageStyle']);
          $style['externalGraphic'] = file_create_url($style_field->original_value);
        }

        foreach ($style as $prop => $value) {
          if (is_numeric($value)) {
            $style[$prop] = (float) $value;
          }
          if (empty($value)) {
            unset($style[$prop]);
          }
        }
      }
    }
    return $style;
  }

  /**
   * Find the data source of an element and pull it into a wkt field
   *
   * openlayers_views_style_data specific
   */
  function get_wkt($feature, $handlers, $datasource) {
    $feature['projection'] = '4326';
    switch ($datasource['value']) {
      case 'wkt':
        return strip_tags($feature[$datasource['wkt']]);
        break;

      case 'other_latlon':
        return 'POINT(' . strip_tags($feature[$datasource['other_lon']]) . ' ' . strip_tags($feature[$datasource['other_lat']]) . ')';
        break;
    }
  }

  /**
   * Coalesce features into single grouped feature when grouping is enabled.
   *
   * openlayers_views_style_data specific
   */
  function coalesce_groups($features, $handlers, $ds) {

    // Combine wkt into geometry collections if they are an array
    foreach ($features as &$feature) {
      if (is_array($feature['wkt'])) {
        if (count($feature['wkt']) > 1) {
          $feature['wkt'] = $this->get_group_wkt($feature['wkt']);
        }
        else {
          $feature['wkt'] = $feature['wkt'][0];
        }
      }
    }

    // Process title and description for groups
    foreach ($features as $k => &$feature) {
      $feature['attributes']['name'] = $k;
      $feature['attributes'] = array_merge($feature['attributes'], $feature['features'][0]['attributes']);

      $formatted_features = array();
      foreach ($feature['features'] as $subfeature) {

        // Create name and description attributes.  Note that there are a
        // couple exceptions to using fields.
        $exceptions = array('#row');

        // Run the output through a theme.
        $formatted_features[] = theme('openlayers_views_group_display_item',
          array(
            'name' => isset($handlers[$ds['name_field']]) ?
              $subfeature['attributes'][$ds['name_field'] . '_rendered'] : FALSE,
            'description' => (in_array($ds['description_field'], $exceptions) ||
              isset($handlers[$ds['description_field']])) ?
              $subfeature['attributes'][$ds['description_field'] . '_rendered'] : FALSE
          )
        );

        // Remove rendered rows to keep data size down for JS.
        if (in_array($ds['description_field'], $exceptions)) {
          unset($subfeature['attributes'][$ds['description_field'] . '_rendered']);
        }
      }

      // Then run all gathered features through item_ist theme.
      $feature['attributes']['description'] = theme('item_list',
        array('items' => $formatted_features)
      );
    }
    return $features;
  }

  /**
   * Combine all group wkt into a single geometry collection
   *
   * openlayers_views_style_data specific
   */
  function get_group_wkt($wkt_array) {
    geophp_load();
    $geophp = geoPHP::load($wkt_array, 'wkt');
    return $geophp->out('wkt');
  }

  /**
   * Split string according to first match of passed regEx index of $regExes
   */
  function preg_explode($regEx, $str) {
    $matches = array();
    preg_match($this->regExes[$regEx], $str, $matches);
    return empty($matches)?array(trim($str)):explode($matches[0], trim($str));
  }

  /**
   * Basically an algebraic reduction; given whether to group,
   * a feature, a list of features, etc., return a full $features
   * array with the element added, either straight non-grouped,
   * or within a new or existing group
   *
   * openlayers_views_style_data specific
   */
  function reduce_features($is_grouped, $features, $feature, $group) {
    if ($is_grouped) {
      if (isset($features[$group])) {
        $features[$group]['attributes']['count']++;
        $features[$group]['wkt'][] = $feature['wkt'];
        $features[$group]['features'][] = $feature;
        return $features;
      }
      else {
        $features[$group] = array(
          'attributes' => array('count' => 1),
          'wkt' => array($feature['wkt']),
          'projection' => $feature['projection'],
          'features' => array($feature)
        );
        return $features;
      }
    }
    else {
      array_push($features, $feature);
      return $features;
    }
  }

}
