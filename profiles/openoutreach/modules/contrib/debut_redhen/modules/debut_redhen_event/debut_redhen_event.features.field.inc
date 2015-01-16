<?php
/**
 * @file
 * debut_redhen_event.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function debut_redhen_event_field_default_fields() {
  $fields = array();

  // Exported field: 'node-event-field_registration'.
  $fields['node-event-field_registration'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_registration',
      'foreign keys' => array(
        'registration_type' => array(
          'columns' => array(
            'registration_type' => 'name',
          ),
          'table' => 'registration_type',
        ),
      ),
      'indexes' => array(
        'registration_type' => array(
          0 => 'registration_type',
        ),
      ),
      'locked' => '0',
      'module' => 'registration',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'registration',
    ),
    'field_instance' => array(
      'bundle' => 'event',
      'default_value' => array(
        0 => array(
          'registration_type' => 'registration_type_1',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'registration',
          'settings' => array(),
          'type' => 'registration_form',
          'weight' => '5',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_registration',
      'label' => 'Register',
      'required' => 0,
      'settings' => array(
        'default_registration_settings' => array(
          'capacity' => 0,
          'reminder' => array(
            'reminder_settings' => array(
              'reminder_date' => NULL,
              'reminder_template' => NULL,
            ),
            'send_reminder' => 0,
          ),
          'scheduling' => array(
            'close' => NULL,
            'open' => NULL,
          ),
          'settings' => array(
            'from_address' => '',
            'multiple_registrations' => -1,
          ),
          'status' => 0,
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'registration',
        'settings' => array(),
        'type' => 'registration_select',
        'weight' => -3,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Register');

  return $fields;
}
