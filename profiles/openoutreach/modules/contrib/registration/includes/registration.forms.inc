<?php

/**
 * @file
 * Form definitions and callbacks for Registration.
 */

/**
 * Form callback: create or edit a registration.
 *
 * @param $registration
 *   The registration object to edit or for a create form an empty registration
 *   object with a node defined.
 */
function registration_form($form, &$form_state, Registration $registration) {
  $wrapper = entity_metadata_wrapper('registration', $registration);
  $user = $wrapper->user->value();
  $host = $wrapper->entity->value();
  $state = $wrapper->state->value();

  $form_state['registration'] = $registration;

  $who_options = registration_access_people($registration);

  // Default value for who is registering.
  $who_default = NULL;
  if (isset($registration->registration_id)) {
    $who_default = $registration->registrant_type($GLOBALS['user']);
  }
  elseif (count($who_options) == 1) {
    $keys = array_keys($who_options);
    $who_default = reset($keys);
  }

  // Show a message if there's only one option as we're going to hide the form.
  if (count($who_options) == 1 && !user_is_anonymous()) {
    $form['who_message'] = array(
      '#markup' => '<div class="registration-who-msg">' .
      t('You are registering: %who', array('%who' => current($who_options))) .
      '</div>',
    );
  }

  $form['who_is_registering'] = array(
    '#type' => 'select',
    '#title' => t('This registration is for:'),
    '#options' => $who_options,
    '#default_value' => $who_default,
    '#required' => TRUE,
    '#access' => (count($who_options) > 1),
  );

  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('User'),
    '#default_value' => ($user ? $user->name : ''),
    '#maxlength' => 60,
    '#size' => 30,
    '#description' => t('Select a user by typing their username to get a list of matches.'),
    '#autocomplete_path' => 'user/autocomplete',
    '#access' => isset($who_options[REGISTRATION_REGISTRANT_TYPE_USER]),
    '#states' => array(
      'visible' => array(
        ':input[name="who_is_registering"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_USER),
      ),
    ),
  );

  $form['anon_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#description' => t('The email to associate with this registration.'),
    '#default_value' => isset($registration->anon_mail) ? $registration->anon_mail : '',
    '#size' => 40,
    '#maxlength' => 255,
    '#access' => isset($who_options[REGISTRATION_REGISTRANT_TYPE_ANON]),
    '#states' => array(
      'visible' => array(
        ':input[name="who_is_registering"]' => array('value' => REGISTRATION_REGISTRANT_TYPE_ANON),
      ),
    ),
  );

  $settings = registration_entity_settings($registration->entity_type, $registration->entity_id);
  $capacity = $settings['capacity'];
  $limit = isset($settings['settings']['maximum_spaces']) ? $settings['settings']['maximum_spaces'] : 1;
  // Just in case it was unset:
  $settings['settings']['maximum_spaces'] = $limit;
  $remaining = $capacity - registration_event_count($registration->entity_type, $registration->entity_id);
  if ($capacity && $limit) {
    $description = t('The number of spaces you wish to reserve. @spaces_remaining spaces remaining. You may register up to @max spaces.',
      array(
        '@spaces_remaining' => $remaining,
        '@max' => min($limit, $remaining),
      )
    );
  }
  elseif ($capacity) {
    $description = t('The number of spaces you wish to reserve. @spaces_remaining spaces remaining.', array('@spaces_remaining' => $remaining));
  }
  elseif ($limit) {
    $description = t('The number of spaces you wish to reserve. You may register up to @max spaces.', array('@max' => $limit));
  }
  else {
    $description = t('The number of spaces you wish to reserve.');
  }

  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Spaces'),
    '#description' => $description,
    '#default_value' => isset($registration->count) ? $registration->count : 1,
    '#size' => drupal_strlen($remaining),
    '#access' => (isset($settings['settings']['maximum_spaces']) && $settings['settings']['maximum_spaces'] == 1) ? FALSE : TRUE,
    '#element_validate' => array('element_validate_integer_positive', '_registration_validate_space_request'),
  );

  $default_state = registration_get_default_state();
  $states = registration_get_states_options(array('show_on_form' => TRUE));

  $form['state'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#description' => t('State of this registration'),
    '#default_value' => ($state ? $state->identifier() : $default_state->identifier()),
    '#options' => $states,
    '#access' => !empty($states) && user_access('edit ' . $registration->type . ' registration state'),
  );

  field_attach_form('registration', $registration, $form, $form_state);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Registration'),
  );

  // Add a delete button for existing registration:
  if (isset($registration->registration_id) && entity_access('delete', 'registration', $registration)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('registration_form_delete_submit'),
      "#limit_validation_errors" => array(),
    );
  }

  if ($host && entity_access('view', $registration->entity_type, $host)) {
    $uri = entity_uri($registration->entity_type, $host);
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => $uri['path'],
    );
  }
  $form['#registration_settings'] = $settings;

  return $form;
}

/**
 * Validation callback for registration_form().
 */
function registration_form_validate($form, &$form_state) {
  $registration = $form_state['registration'];

  $count = $form_state['values']['count'];

  $label = entity_label($registration->entity_type,
    entity_load_single($registration->entity_type, $registration->entity_id));

  // Test status on new registrations.
  if (isset($registration->is_new) && $registration->is_new) {
    $registration_status = registration_status($registration->entity_type, $registration->entity_id, TRUE, $count, $registration->registration_id, $errors);

    if (!$registration_status) {
      form_set_error('', t('Sorry, unable to register for %label due to: %errors.',
        array('%label' => $label, '%errors' => implode(', ', $errors))
      ));
    }
  }
  // Only check capacity for existing registrations that are active.
  elseif (in_array($registration->state, registration_get_active_states())) {
    $has_room = registration_has_room($registration->entity_type, $registration->entity_id, $count, $registration->registration_id);
    if (!$has_room) {
      form_set_error('', t('Sorry, unable to register for %label due to: insufficient spaces remaining.',
        array('%label' => $label)));
    }
  }

  $settings = registration_entity_settings($registration->entity_type, $registration->entity_id);
  $allow_multiple = !empty($settings['settings']['multiple_registrations']) && $settings['settings']['multiple_registrations'];

  // Validate according to who's registering.
  switch ($form_state['values']['who_is_registering']) {
    case REGISTRATION_REGISTRANT_TYPE_ANON:
      if (!valid_email_address($form_state['values']['anon_mail'])) {
        form_set_error('anon_mail', t('The email address is invalid.'));
      }
      if (!$allow_multiple && registration_is_registered($registration, $form_state['values']['anon_mail'])) {
        form_set_error('anon_mail', t('%mail is already registered for this event.',
          array('%mail' => $form_state['values']['anon_mail'])));
      }
      break;
    case REGISTRATION_REGISTRANT_TYPE_ME:
      global $user;
      if (!$allow_multiple && registration_is_registered($registration, NULL, $user->uid)) {
        form_set_error('user', t('You are already registered for this event.'));
      }
      break;
    case REGISTRATION_REGISTRANT_TYPE_USER:
      $user = user_load_by_name($form_state['values']['user']);
      if ($user) {
        if (!$allow_multiple && registration_is_registered($registration, NULL, $user->uid)) {
          form_set_error('user', t('%user is already registered for this event.', array('%user' => $user->name)));
        }
      }
      else {
        form_set_error('user', t('%user is not a valid user.', array('%user' => $form_state['values']['user'])));
      }
      break;
  }

  // Notify field widgets to validate their data.
  field_attach_form_validate('registration', $registration, $form, $form_state);
}

/**
 * Submit callback for registration_form().
 */
function registration_form_submit($form, &$form_state) {
  $registration = $form_state['registration'];

  // Set the registration's author uid
  if (!isset($registration->registration_id)) {
    $registration->author_uid = $GLOBALS['user']->uid;
  }
  $registration->count = $form_state['values']['count'];

  if (!empty($form_state['values']['state'])) {
    $registration->state = $form_state['values']['state'];
  }

  switch ($form_state['values']['who_is_registering']) {
    case REGISTRATION_REGISTRANT_TYPE_ANON:
      $registration->anon_mail = $form_state['values']['anon_mail'];
      break;
    case REGISTRATION_REGISTRANT_TYPE_ME:
      global $user;
      $registration->user_uid = $user->uid;
      break;
    case REGISTRATION_REGISTRANT_TYPE_USER:
      if ($reg_user = user_load_by_name($form_state['values']['user'])) {
        $registration->user_uid = $reg_user->uid;
      }
      break;
  }

  // Notify field widgets.
  field_attach_submit('registration', $registration, $form, $form_state);

  // Save the registration and redirect.
  if (registration_save($registration)) {
    $reg_config = registration_entity_settings($registration->entity_type, $registration->entity_id);
    if (!empty($reg_config['settings']['confirmation']) && strlen($reg_config['settings']['confirmation'])) {
      drupal_set_message(t($reg_config['settings']['confirmation']));
    }
    $wrapper = entity_metadata_wrapper('registration', $registration);
    $host = $wrapper->entity->value();

    // Redirect to registration
    if (entity_access('view', 'registration', $registration)) {
      $uri = entity_uri('registration', $registration);
      $form_state['redirect'] = $uri['path'];
    }
    // Redirect to host entity
    else {
      if (entity_access('view', $registration->entity_type, $host)) {
        $uri = entity_uri($registration->entity_type, $host);
        $form_state['redirect'] = $uri['path'];
      }
    }
  }
  else {
    drupal_set_message(t('There was a problem submitting your registration.'));
  }
}

/**
 * Button submit function: handle the 'Delete' button on the node form.
 */
function registration_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $registration = $form_state['registration'];
  $form_state['redirect'] = array(
    'registration/' .
      $registration->registration_id . '/delete',
    array('query' => $destination),
  );
}

/**
 * Menu callback -- ask for confirmation of node deletion
 */
function registration_delete_confirm($form, &$form_state, $registration) {
  // Always provide entity id in the same form key as in the entity edit form.
  $form['registration'] = array(
    '#type' => 'value',
    '#value' => $registration,
  );
  return confirm_form($form,
    t('Are you sure you want to delete registration %title?',
      array('%title' => $registration->registration_id)
    ),
    'registration/' . $registration->registration_id,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute node deletion
 */
function registration_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $registration = $form_state['values']['registration'];
    registration_delete_multiple(array($registration->registration_id));
    watchdog('registration', 'Registration %id deleted.', array('%id' => $registration->registration_id));
    drupal_set_message(t('Registration %id has been deleted.', array('%id' => $registration->registration_id)));

    $wrapper = entity_metadata_wrapper('registration', $registration);
    $host = $wrapper->entity->value();
    $uri = entity_uri($registration->entity_type, $host);
    $form_state['redirect'] = $uri['path'];
  }
}

/**
 * Return a form for sending a broadcast email to participants.
 */
function registration_registrations_broadcast_form($form, &$form_state, $entity_type, $entity) {
  // we'll need this info when we submit the form
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $form_state['entity'] = array(
    'entity_id' => $entity_id,
    'entity_type' => $entity_type
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#description' => t('The subject of the message.'),
    '#required' => TRUE,
    '#size' => 40,
    '#maxlength' => 40,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#description' => t(
      'Enter the message you want to send to %name registrants. Tokens are supported if the module is enabled, E.g., [node:title].',
      array('%name' => entity_label($entity_type, $entity))
    ),
    '#required' => TRUE,
    '#cols' => 60,
    '#rows' => 5,
  );

  // Message preview
  if (isset($form_state['registration_broadcast_preview'])) {
    $form['preview'] = array(
      '#type' => 'textarea',
      '#title' => t('Message preview'),
      '#value' => $form_state['registration_broadcast_preview'],
      '#resizable' => FALSE,
      '#disabled' => TRUE
    );
  }

  // add token support
  if (module_exists('token')) {
    $form['token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array(
        $entity_type,
        'registration',
      ),
      '#global_types' => FALSE,
    );
  }

  $form['actions']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
    '#weight' => 10,
    '#submit' => array('registration_broadcast_preview'),
  );

  $form['actions']['send'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );

  return $form;
}

function registration_broadcast_preview($form, &$form_state) {
  $entity_type = $form_state['entity']['entity_type'];
  $entity_id = $form_state['entity']['entity_id'];
  $message_template = $form_state['values']['message'];
  $entity = entity_load_single($entity_type, $entity_id);
  if (module_exists('token')) {
    $message = token_replace($message_template, array($entity_type => $entity));
  }

  $form_state['registration_broadcast_preview'] = $message;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for registration_registrations_broadcast_form.
 */
function registration_registrations_broadcast_form_submit($form, &$form_state) {
  registration_send_broadcast(
    $form_state['entity']['entity_type'],
    $form_state['entity']['entity_id'],
    $form_state['values']['subject'],
    $form_state['values']['message']
  );
}

/**
 * Return a form for an entity's registration settings.
 *
 * @param array $form
 * @param array $form_state
 * @param object $entity_type
 * @param object $entity
 *
 * @return array $form
 *
 * @see hook_registration_entity_settings().
 */
function registration_entity_settings_form($form, &$form_state, $settings, $entity_type = NULL, $entity_id = NULL) {
  if ($entity_id) {
    // We'll need this info when we submit the form:
    $form_state['entity'] = array(
      'entity_id' => $entity_id,
      'entity_type' => $entity_type
    );
  }
  // Check to see if date_popup is installed so we can provide a friendlier UI.
  $date_popup_installed = FALSE;
  if (module_exists('date_popup')) {
    $date_popup_installed = TRUE;
  }
  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Check to enable registrations.'),
    '#default_value' => isset($settings['status']) ? $settings['status'] : -1,
  );
  $form['capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#description' => t('The maximum number of registrants. Leave at 0 for no limit.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#required' => TRUE,
    '#default_value' => isset($settings['capacity']) ? $settings['capacity'] : 0,
  );

  $form['scheduling'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scheduling'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE
  );

  $form['scheduling']['open'] = array(
    '#type' => 'textfield',
    '#title' => t('Open Date'),
    '#maxlength' => 25,
    '#description' => t('When to automatically open registrations. Format: %time. The date format is YYYY-MM-DD and %timezone is the time zone offset from UTC. Leave blank to disable.', array(
        '%time' => !empty($settings['open']) ? date_format(date_create($settings['open']), 'Y-m-d H:i:s O') : format_date(time(), 'custom', 'Y-m-d H:i:s O'),
        '%timezone' => !empty($settings['open']) ? date_format(date_create($settings['open']), 'O') : format_date(time(), 'custom', 'O'),
      )
    ),
    '#default_value' => !empty($settings['open']) ? $settings['open'] : '',
  );
  if ($date_popup_installed) {
    $form['scheduling']['open']['#type'] = 'date_popup';
    $form['scheduling']['open']['#format'] = 'Y-m-d H:i:s O';
    $form['scheduling']['open']['#description'] = t('When to automatically open registrations. (This uses the !timezone.)', array(
      '!timezone' => l(t('site default time zone'), 'admin/config/regional/settings')));
    unset($form['scheduling']['open']['#maxlength']);
  }

  $form['scheduling']['close'] = array(
    '#type' => 'textfield',
    '#title' => t('Close Date'),
    '#maxlength' => 25,
    '#description' => t('When to automatically close registrations. Format: %time. The date format is YYYY-MM-DD and %timezone is the time zone offset from UTC. Leave blank to disable.', array(
        '%time' => !empty($settings['close']) ? date_format(date_create($settings['close']), 'Y-m-d H:i:s O') : format_date(time(), 'custom', 'Y-m-d H:i:s O'),
        '%timezone' => !empty($settings['close']) ? date_format(date_create($settings['close']), 'O') : format_date(time(), 'custom', 'O'),
      )
    ),
    '#default_value' => !empty($settings['close']) ? $settings['close'] : '',
  );
  if ($date_popup_installed) {
    $form['scheduling']['close']['#type'] = 'date_popup';
    $form['scheduling']['close']['#format'] = 'Y-m-d H:i:s O';
    $form['scheduling']['close']['#description'] = t('When to automatically close registrations.. (This uses the !timezone.)', array(
      '!timezone' => l(t('site default time zone'), 'admin/config/regional/settings')));
    unset($form['scheduling']['close']['#maxlength']);
  }

  $form['reminder'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reminder'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['reminder']['send_reminder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send Reminder'),
    '#description' => t('If checked, a reminder will be sent to registrants on the following date.'),
    '#default_value' => isset($settings['send_reminder']) ? $settings['send_reminder'] : -1,
  );

  $form['reminder']['reminder_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="send_reminder"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['reminder']['reminder_settings']['reminder_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Reminder Date'),
    '#maxlength' => 25,
    '#description' => t('When to send reminders. Format: %time. The date format is YYYY-MM-DD and %timezone is the time zone offset from UTC.', array(
        '%time' => !empty($settings['open']) ? date_format(date_create($settings['reminder_date']), 'Y-m-d H:i:s O') : format_date(time(), 'custom', 'Y-m-d H:i:s O'),
        '%timezone' => !empty($settings['open']) ? date_format(date_create($settings['reminder_date']), 'O') : format_date(time(), 'custom', 'O'),
      )
    ),
    '#default_value' => !empty($settings['reminder_date']) ? $settings['reminder_date'] : '',
  );
  if ($date_popup_installed) {
    $form['reminder']['reminder_settings']['reminder_date']['#type'] = 'date_popup';
    $form['reminder']['reminder_settings']['reminder_date']['#format'] = 'Y-m-d H:i:s O';
    $form['reminder']['reminder_settings']['reminder_date']['#description'] = t('When to send reminders. (This uses the !timezone.)', array(
      '!timezone' => l(t('site default time zone'), 'admin/config/regional/settings')));
    unset($form['reminder']['reminder_settings']['reminder_date']['#maxlength']);
  }

  $form['reminder']['reminder_settings']['reminder_template'] = array(
    '#type' => 'textarea',
    '#title' => t('Template'),
    '#default_value' => isset($settings['reminder_template']) ? $settings['reminder_template'] : '',
    '#description' => t('The reminder message sent to registrants. Tokens are supported if the module is enabled, E.g., [node:title].'),
  );

  // Add token support:
  if (module_exists('token')) {
    $form['reminder']['reminder_settings']['token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array(
        $entity_type,
        'registration',
      ),
      '#global_types' => FALSE,
    );
  }

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['settings']['maximum_spaces'] = array(
    '#type' => 'textfield',
    '#title' => t('Spaces allowed'),
    '#size' => 5,
    '#maxlength' => 10,
    '#required' => TRUE,
    '#description' => t('The maximum number of spaces allowed for each registrations. For no limit, use 0. (Default is 1)'),
    '#default_value' => isset($settings['settings']['maximum_spaces']) ? $settings['settings']['maximum_spaces'] : 1,
  );

  $form['settings']['multiple_registrations'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow multiple registrations'),
    '#description' => t('If selected, each person can create multiple registrations for this event.'),
    '#default_value' => isset($settings['settings']['multiple_registrations']) ? $settings['settings']['multiple_registrations'] : -1,
  );

  $form['settings']['from_address'] = array(
    '#type' => 'textfield',
    '#title' => t('From Address'),
    '#description' => t('From email address to use for confirmations, reminders, and broadcast emails.'),
    '#required' => TRUE,
    '#default_value' => isset($settings['settings']['from_address']) ? $settings['settings']['from_address'] : variable_get('site_mail', ini_get('sendmail_from')),
  );

  $form['settings']['confirmation'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation Message'),
    '#description' => t('The message to display when someone registers. Leave blank for none.'),
    '#size' => 60,
    '#maxlength' => 120,
    '#required' => FALSE,
    '#default_value' =>  isset($settings['settings']['confirmation']) ? $settings['settings']['confirmation'] : 'Registration has been saved.',
  );

  // Allow other modules to add their own custom settings:
  $form['settings'] += module_invoke_all('registration_entity_settings', $settings);

  // Only show save if we're not on the field instance defaults:
  if ($entity_id) {
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save Settings'),
    );
  }

  return $form;
}

/**
 * Submit handler for registration_entity_settings_form().
 *
 * @param array $form
 * @param array $form_state
 */
function registration_entity_settings_form_validate($form, &$form_state) {
  // Ensure capacity is a non-negative integer.
  $capacity = $form_state['values']['capacity'];
  if (!is_numeric($capacity) || ((int) $capacity != $capacity) || ($capacity < 0)) {
    form_set_error('capacity', t('"Capacity" must be a positive integer or 0 for unlimited.'));
  }

  // Ensure slot limit is a non-negative integer.
  $slot_limit = $form_state['values']['settings']['maximum_spaces'];
  if (!is_numeric($slot_limit) || ((int) $slot_limit != $slot_limit) || ($slot_limit < 0)) {
    form_set_error('maximum_spaces', t('"Spaces allowed" must be a positive integer or 0 for unlimited.'));
  }

  // Validate from address:
  if (!valid_email_address($form_state['values']['settings']['from_address'])) {
    form_set_error('settings][from_address', t('From email address is invalid.'));
  }

  // Validate open date:
  if (!empty($form_state['values']['scheduling']['open']) && strtotime($form_state['values']['scheduling']['open']) === FALSE) {
    form_set_error('scheduling][open', t('Date is invalid.'));
  }

  // Validate close date:
  if (!empty($form_state['values']['scheduling']['close']) && strtotime($form_state['values']['scheduling']['close']) === FALSE) {
    form_set_error('scheduling][close', t('Date is invalid.'));
  }

  // if sending a reminder, ensure date and template are set
  $reminder = $form_state['values']['reminder'];
  if ($reminder['send_reminder']
    && (empty($reminder['reminder_settings']['reminder_date']) ||
      empty($reminder['reminder_settings']['reminder_template']))
  ) {
    form_set_error('reminder][send_reminder', t('If sending a reminder, provide a date and template.'));
  }

  // Validate reminder date
  if (!empty($reminder['reminder_settings']['reminder_date'])
    && strtotime($reminder['reminder_settings']['reminder_date']) === FALSE
  ) {
    form_set_error('reminder][reminder_settings][reminder_date', t('Reminder date is invalid.'));
  }
}

/**
 * Submit handler for registration_entity_settings_form().
 *
 * @param array $form
 * @param array $form_state
 */
function registration_entity_settings_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];

  $fields = registration_convert_form_settings($form_state['values']);

  registration_update_entity_settings($entity['entity_type'], $entity['entity_id'], $fields);

  $uri = entity_uri($entity['entity_type'], entity_load_single($entity['entity_type'], $entity['entity_id']));

  $form_state['redirect'] = $uri['path'];
}

/**
 * Helper to convert registration entity settings form values into a fields.
 *
 * @param $values
 *
 * @return array
 */
function registration_convert_form_settings($values) {
  $fields = array(
    'status' => $values['status'],
    'capacity' => $values['capacity'],
    'send_reminder' => isset($values['reminder']['send_reminder']) ? $values['reminder']['send_reminder'] : 0,
    'settings' => serialize($values['settings']),
    'open' => NULL,
    'close' => NULL,
  );

  // reminder settings
  if (isset($values['reminder']['send_reminder']) && $values['reminder']['send_reminder']) {
    if (!empty($values['reminder']['reminder_settings']['reminder_date'])) {
      $fields['reminder_date'] = date('Y-m-d H:i:s', strtotime($values['reminder']['reminder_settings']['reminder_date']));
    }
    $fields['reminder_template'] = $values['reminder']['reminder_settings']['reminder_template'];
  }

  // Scheduling: open date
  if (!empty($values['scheduling']['open'])) {
    $fields['open'] = date('Y-m-d H:i:s', strtotime($values['scheduling']['open']));
  }

  // Scheduling: close date
  if (!empty($values['scheduling']['close'])) {
    $fields['close'] = date('Y-m-d H:i:s', strtotime($values['scheduling']['close']));
  }

  return $fields;
}

/**
 * Generates the Registration state editing form.
 */
function registration_state_form($form, &$form_state, $registration_state, $op = 'edit') {

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $registration_state->label,
    '#description' => t('The human-readable name of this registration state.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $registration_state->identifier(),
    '#maxlength' => 32,
    //'#disabled' => $registration_state->locked && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'registration_get_states',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for
    this registration state. It must only contain lowercase letters,
     numbers, and underscores.'),
  );
  $form['default_state'] = array(
    '#title' => t('Default'),
    '#type' => 'checkbox',
    '#default_value' => isset($registration_state->default_state) ?
      $registration_state->default_state : 0,
    '#attributes' => array('class' => array('reg-default')),
  );
  $form['weight'] = array(
    '#title' => t('Weight'),
    '#type' => 'weight',
    '#default_value' => isset($registration_state->weight) ?
      $registration_state->weight : 0,
    '#delta' => 15,
    '#attributes' => array('class' => array('registration-state-weight')),
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => isset($registration_state->description) ?
      $registration_state->description : '',
    '#maxlength' => 128,
    '#size' => 50,
  );
  $form['active'] = array(
    '#title' => t('Active'),
    '#type' => 'checkbox',
    '#default_value' => isset($registration_state->active) ?
      $registration_state->active : 0,
  );
  $form['show_on_form'] = array(
    '#title' => t('Show on form'),
    '#type' => 'checkbox',
    '#default_value' => isset($registration_state->show_on_form) ?
      $registration_state->show_on_form : 0,
  );


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Registration state'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function registration_state_form_submit(&$form, &$form_state) {
  $registration_state = entity_ui_form_submit_build_entity($form, $form_state);
  $registration_state->save();
  $form_state['redirect'] = 'admin/structure/registration/registration_states';
}

/*
 * Registration states setting form
 */
function registration_state_overview_form($form, &$form_state) {
  $registration_states = registration_states();

  // Form elements for existing states .
  $form['state']['#tree'] = TRUE;
  if (!empty($registration_states)) {

    foreach ($registration_states as $sid => $state) {
      $form['state'][$sid]['sid'] = array(
        '#type' => 'hidden',
        '#default_value' => $sid,
      );
      $form['state'][$sid]['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $state->label,
        '#maxlength' => 128,
        '#size' => 20,
        '#required' => TRUE,
      );
      $form['state'][$sid]['default_state'] = array(
        '#type' => 'radio',
        '#name' => 'default_state',
        '#return_value' => $sid,
        '#tree' => FALSE,
        '#default_value' => ($state->default_state) ? $sid : FALSE,
      );
      $form['state'][$sid]['weight'] = array(
        '#title' => t('Weight'),
        '#type' => 'weight',
        '#default_value' => $state->weight,
        '#delta' => 15,
        '#attributes' => array('class' => array('registration-state-weight')),
      );
      $form['state'][$sid]['description'] = array(
        '#title' => t('Description'),
        '#type' => 'textfield',
        '#default_value' => $state->description,
        '#maxlength' => 128,
        '#size' => 50,
      );
      $form['state'][$sid]['active'] = array(
        '#title' => t('Active'),
        '#type' => 'checkbox',
        '#default_value' => $state->active,
      );
      $form['state'][$sid]['show_on_form'] = array(
        '#title' => t('Show on form'),
        '#type' => 'checkbox',
        '#default_value' => $state->show_on_form,
      );
      $form['state'][$sid]['delete'] = array(
        '#type' => 'item',
        '#markup' => l(t('delete'), 'admin/structure/registration/registration_states/manage/' . $state->identifier() . '/delete', array('query' => drupal_get_destination())),
      );
      $form['state'][$sid]['export'] = array(
        '#type' => 'item',
        '#markup' => l(t('export'), 'admin/structure/registration/registration_states/manage/' . $state->identifier() . '/export'),
      );
    }
  }

  $form['help'] = array(
    '#type' => 'item',
    '#description' => t("This table defines the registration states available on this site. A default is required and will be used if no states are marked as 'Show on Form'."),
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the registration states form
 */
function registration_state_overview_form_submit($form, &$form_state) {

  $default_state = $form_state['values']['default_state'];
  foreach ($form_state['input']['state'] as $state) {
    $registration_state = entity_load_single('registration_state', $state['sid']);
    $registration_state->label = $state['label'];
    $registration_state->default_state = $state['sid'] == $default_state;
    $registration_state->active = isset($state['active']) ? $state['active'] : 0;
    $registration_state->show_on_form = isset($state['show_on_form']) ? $state['show_on_form'] : 0;
    $registration_state->weight = $state['weight'];
    $registration_state->description = $state['description'];

    $registration_state->save();
  }

  drupal_set_message(t('Your registration states have been saved.'));
}

/*
 * Theme handler for registration states form
 */
function theme_registration_state_overview_form($variables) {
  $form = $variables['form'];

  drupal_add_tabledrag('registration-state-admin-settings-table', 'order', 'self', 'registration-state-weight');
  $header = array(
    array('data' => t('Label !required', array('!required' => '<span class="form-required" title="' . t('This field is required.') . '">*</span>'))),
    array('data' => t('Description')),
    array('data' => t('Default')),
    array('data' => t('Active')),
    array('data' => t('Show on form')),
    array('data' => t('Weight')),
    array('data' => t('Operations'), 'colspan' => 2)
  );

  foreach (element_children($form['state']) as $key) {
    $row = array();
    foreach (array(
               'label',
               'description',
               'default_state',
               'active',
               'show_on_form',
               'weight',
               'delete',
               'export'
             ) as $element) {
      // Since we're rendering these in a table, remove any #title attributes.
      if (!empty($form['state'][$key][$element]['#title'])) {
        unset($form['state'][$key][$element]['#title']);
      }
      $row[] = drupal_render($form['state'][$key][$element]);
    }

    $rows[] = array(
      'class' => array('draggable'),
      'data' => $row,
    );
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'registration-state-admin-settings-table')
  ));

  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Validation helper function to confirm the spaces requested are within limits.
 */
function _registration_validate_space_request($element, &$form_state, $form) {
  if (isset($form_state['input']['count']) &&
      $form['#registration_settings']['settings']['maximum_spaces'] &&
      $form_state['input']['count'] > $form['#registration_settings']['settings']['maximum_spaces']) {
    form_error($element, t('You may not register for more than @count spaces.', array('@count' => $form['#registration_settings']['settings']['maximum_spaces'])));
  };
}
