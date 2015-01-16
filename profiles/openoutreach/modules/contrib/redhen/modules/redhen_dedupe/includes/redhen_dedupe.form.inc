<?php

/**
 * @file
 * Forms for creating, editing, and deleting contacts.
 */

define('REDHEN_DEDUPE_NOT_APPLICABLE', 'redhen_dedupe_not_applicable');

/**
 * Form to select the master contact.
 */
function redhen_dedupe_merge_form($form, &$form_state, $entity_ids) {
  // Load the entities we want to merge:
  $entity_ids = explode(',', $entity_ids);
  $contacts = redhen_contact_load_multiple($entity_ids);

  $master_options = array();

  // Loop through the entities to build out our master entity options:
  foreach ($contacts as $ent_id => $entity) {
    $wrapper = entity_metadata_wrapper('redhen_contact', $entity);
    $updated = format_date($wrapper->updated->value(), 'short');
    $master_options[$ent_id] = t('@name (Updated: !date)', array('!date' => $updated, '@name' => $wrapper->label()));
  }

  // Form field to select a merge master entity.
  $form['master'] = array(
    '#type' => 'radios',
    '#title' => t('Master Contact'),
    '#default_value' => key($master_options),
    '#required' => TRUE,
    '#options' => $master_options,
    '#description' => t('Choose a contact to merge the other contacts into.'),
    '#weight' => 0,
    '#ajax' => array(
      'callback' => 'redhen_dedupe_merge_form_callback',
      'wrapper' => 'redhen_dedupe_merge_data',
    ),
  );

  $form['merge_data'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'redhen_dedupe_merge_data'),
  );

  $master_id = isset($form_state['values']['master']) ? (int) $form_state['values']['master'] : key($master_options);
  $merge_data = &$form['merge_data'];

  $preview = $contacts[$master_id]->view();
  $merge_data['contact_preview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Master contact details'),
    'preview' => array('#markup' => render($preview)),
  );

  // Initialize our table header:
  $table_header = array(t('Field Name'));
  // Loop through the entities to build out our table headers and master
  // entity options:
  foreach ($contacts as $ent_id => $contact) {
    $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
    $updated = format_date($wrapper->updated->value(), 'short');
    $header_data = array(
      '!date' => $updated,
      '@name' => $wrapper->label(),
      '@bundle' => $wrapper->getBundle(),
      '@master' => ($ent_id == $master_id) ? t('Master') . ': ' : '',
    );
    $table_header[$ent_id] = array(
      'data' => t('@master@name (@bundle)<br/>Last Updated: !date', $header_data),
      'class' => ($ent_id == $master_id) ? 'redhen-dedupe-master-col' : 'redhen-dedupe-col',
    );
  }

  // Pass along the entity ID options & master ID to the form handler:
  $form_state['contacts'] = $contacts;

  // Now we build our merge selector form fields:
  $merge_data['values'] = array(
    '#theme' => 'redhen_dedupe_form_table',
    '#tree' => TRUE,
    '#header' => $table_header,
  );
  $info = entity_get_property_info('redhen_contact');
  $properties = entity_get_all_property_info('redhen_contact');
  // Loop through each property and build a form element for it. The form
  // element will be placed into a table in redhen_dedupe_form_table:
  $master_wrapper = entity_metadata_wrapper('redhen_contact', $contacts[$master_id]);
  foreach ($properties as $name => $property) {
    // Skip property if it does not exist on the master record.
    if (!isset($master_wrapper->{$name})) {
      continue;
    }

    // Call a helper function to determine if this is a field we want to merge:
    if (redhen_dedupe_property_mergeable($name, $property)) {
      // Need this due to a FAPI bug (https://drupal.org/node/1634364).
      if (isset($form_state['input']['values'][$name])) {
        unset($form_state['input']['values'][$name]);
      }
      $is_field = isset($properties[$name]['field']) && $properties[$name]['field'];
      if ($is_field && _redhen_dedupe_field_is_multivalue($name, $property)) {
        $merge_data['values'][$name] = array(
          '#type' => 'checkboxes',
          '#title' => filter_xss($property['label']),
          '#options' => array(),
        );
      }
      else {
        $merge_data['values'][$name] = array(
          '#type' => 'radios',
          '#title' => $property['label'],
          '#options' => array(),
        );
      }
      $options = &$merge_data['values'][$name]['#options'];
      // Loop through each contact to build a row element/radio button option:
      foreach ($contacts as $ent_id => $contact) {
        // We do some work to figure out what kind of field we are dealing with,
        // and set our values and displays appropriately. The important factors
        // are if it's a field or not, and whether it has a setter/getter
        // callback that we should be using.
        $in_bundle = isset($info['bundles'][$contact->type]['properties'][$name]);
        if (!$in_bundle && $is_field) {
          $options[$ent_id] = REDHEN_DEDUPE_NOT_APPLICABLE;
          continue;
        }

        // Set the default to match the Master record:
        if ($ent_id === $master_id) {
          $merge_data['values'][$name]['#default_value'] = $merge_data['values'][$name]['#type'] == 'radios' ? $ent_id : array($ent_id);
        }

        $options[$ent_id] = redhen_dedupe_option_label($contact, $name, $property);
      }
    }
  }

  // Exclude properties that are all the same from the merge form.
  foreach (element_children($merge_data['values']) as $name) {
    $left = array_unique($merge_data['values'][$name]['#options']);
    // Filter out any remaining items that are not applicable.
    $left = array_filter($left, function($item) {
      return ($item !== REDHEN_DEDUPE_NOT_APPLICABLE);
    });
    if (empty($left) || count($left) === 1) {
      unset($merge_data['values'][$name]);
      continue;
    }
  }

  $related_types = array();
  if (module_exists('redhen_note')) {
    $related_types['redhen_note'] = t('Notes');
  }
  if (module_exists('redhen_engagement')) {
    $related_types['redhen_engagement'] = t('Engagement Scores');
  }
  if (module_exists('redhen_membership')) {
    $related_types['redhen_membership'] = t('Memberships');
  }
  if (module_exists('redhen_relation')) {
    $related_types['relation'] = t('Relationships/Affiliations');
  }
  if (count($related_types) > 0) {
    $form['related_entities'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Move items attached to old records to Master record:'),
      '#options' => $related_types,
      '#default_value' => array_keys($related_types),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Merge'),
  );

  return $form;
}

/**
 * Ajax callback for redhen_dedupe_merge_form().
 */
function redhen_dedupe_merge_form_callback($form, $form_state) {
  return $form['merge_data'];
}

/**
 * Submit handler for dedupe merge form.
 */
function redhen_dedupe_merge_form_submit($form, &$form_state) {
  $master_id = $form_state['values']['master'];
  $contacts = $form_state['contacts'];
  $master = $contacts[$master_id];
  $values = array();
  // Pull the actual data out of the #value array constructed for the form:
  if (isset($form_state['values']['values'])) {
    foreach ($form_state['values']['values'] as $name => $val) {
      if (is_array($val)) {
        $values[$name] = array(
          'type' => 'combine',
          'value' => array(),
        );
        foreach ($val as $ent_id => $selected) {
          if ($selected) {
            $wrapper = entity_metadata_wrapper('redhen_contact', $ent_id);
            $values[$name]['value'][$ent_id] = $wrapper->{$name}->value();
          }
        }
      }
      else {
        $wrapper = entity_metadata_wrapper('redhen_contact', $contacts[$val]);
        $values[$name] = array(
          'type' => 'direct',
          'value' => $wrapper->{$name}->value(),
        );
      }
    }
  }
  unset($contacts[$master_id]);
  $merge_status = redhen_dedupe_merge($master, $contacts, $values, array_filter($form_state['values']['related_entities']));
  if ($merge_status) {
    drupal_set_message(t('Contacts have successfully been merged into %master and deleted.',
      array('%master' => $master->label())
    ));
    $uri = $master->uri();
    $form_state['redirect'] = $uri['path'];
  }
  else {
    drupal_set_message(t('Error attempting to merge these contacts. Check the error log for more details.'), 'error');
  }
}

/**
 * Themes the field associations on a fieldmap edit form into a table.
 */
function theme_redhen_dedupe_form_table($variables) {
  $elements = $variables['elements'];

  // Build the rows array.
  $rows = array();
  foreach (element_children($elements) as $item_key) {
    $item = &$elements[$item_key];
    $data = array($item['#title']);
    foreach (element_children($item) as $element) {
      if (isset($item['#options']) && $item['#options'][$element] === REDHEN_DEDUPE_NOT_APPLICABLE) {
        $cell_data = t('Field not applicable to this bundle');
      }
      else {
        $cell_data = drupal_render($item[$element]);
      }

      $cell = array('data' => $cell_data);
      if (isset($item[$element]['#attributes'])) {
        foreach ($item[$element]['#attributes'] as $key => $value) {
          $cell[$key] = ($key == 'id') ? (is_array($value) ? array($value[0] . '-cell') : $value . '-cell') : $value;
        }
      }
      $data[] = $cell;

    }
    $row = array('data' => $data);
    if (isset($item_key['#attributes'])) {
      foreach ($item_key['#attributes'] as $key => $value) {
        $row[$key] = $value;
      }
    }
    $rows[] = $row;
  }

  $config = array(
    'rows' => $rows,
  );
  if (isset($elements['#header'])) {
    $config['header'] = $elements['#header'];
  }
  if (isset($elements['#attributes']) && is_array($elements['#attributes'])) {
    $config['attributes'] = $elements['#attributes'];
  }

  return theme('table', $config);
}

/**
 * Determine if a given property can be merged.
 *
 * @param array $property
 *   A property as returned by entity_get_all_property_info();
 *
 * @return bool
 *   True is mergeable.
 */
function redhen_dedupe_property_mergeable($name, $property) {

  // Don't merge computed fields:
  if (isset($property['computed']) && $property['computed']) {
    return FALSE;
  }

  // Don't merge fields that can't be edited:
  if (!isset($property['setter callback'])) {
    return FALSE;
  }

  // Don't merge any base table fields except the name fields:
  $info = entity_get_info('redhen_contact');
  if (in_array($name, $info['schema_fields_sql']['base table'])) {
    if (!strstr($name, '_name')) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Return an option label for the merge form.
 *
 * @param RedhenContact $contact
 *   Contact entity.
 * @param string $property_name
 *   Contact property name we need a label for.
 * @param array $property
 *   Full property array.
 *
 * @return string
 *   Label to use for an option field or other purpose.
 */
function redhen_dedupe_option_label(RedhenContact $contact, $property_name, $property) {
  if (isset($property['field'])) {
    $field_array = field_view_field('redhen_contact', $contact, $property_name, array('label' => 'hidden'));
    $display = render($field_array);
  }
  else {
    $built_contact = $contact->buildContent();
    if (isset($built_contact[$property_name])) {
      $display = render($built_contact[$property_name]);
    }
    else {
      $display = isset($contact->{$property_name}) ? $contact->{$property_name} : '';
    }
  }

  return !empty($display) ? $display : t('No value');
}

/**
 * Determine if a property should be merged via checkboxes instead of radios.
 */
function _redhen_dedupe_field_is_multivalue($name, $field) {
  $field_info = field_info_field($name);
  if ($field_info['cardinality'] != 1) {
    return $field_info['cardinality'];
  }
  else {
    return FALSE;
  }
}
