<?php

/**
 * @file
 * Forms for creating, editing, and deleting contacts.
 */

/**
 * Form callback: create or edit a contact.
 *
 * @param $contact
 *   The contact object to edit or for a create form an empty contact object
 *     with only a contact type defined.
 */
function redhen_contact_contact_form($form, &$form_state, $contact) {
  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_contact') . '/includes/redhen_contact.forms.inc';

  // Add the default field elements.
  $form['name'] = array('#type' => 'container');
  $form['name']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $contact->first_name,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -6,
  );
  $form['name']['middle_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name'),
    '#default_value' => $contact->middle_name,
    '#maxlength' => 255,
    '#weight' => -6,
  );
  $form['name']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $contact->last_name,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => 5,
  );

  // Add the field related form elements.
  $form_state['redhen_contact'] = $contact;
  field_attach_form('redhen_contact', $contact, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 40,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array('redhen_contact_contact_form_submit');

  if (!empty($form['#submit'])) {
    $submit = array_merge($submit, $form['#submit']);
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save contact'),
    '#submit' => $submit,
  );

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'redhen_contact_contact_form_validate';

  return $form;
}

/**
 * Validation callback for redhen_contact_contact_form().
 */
function redhen_contact_contact_form_validate($form, &$form_state) {
  $contact = $form_state['redhen_contact'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('redhen_contact', $contact, $form, $form_state);

  // If mirroring a connected and contact email's, ensure the email is not used
  // by anther Drupal user.
  if (variable_get('redhen_contact_mirror_email', FALSE) && $contact->uid) {
    foreach ($form_state['values'][REDHEN_CONTACT_EMAIL_FIELD][LANGUAGE_NONE] as $email) {
      if (is_array($email) && !empty($email['value']) && $email['default']) {
        $user = user_load_by_mail($email['value']);
        if ($user && ($user->uid != $contact->uid)) {
          form_set_error(
            REDHEN_CONTACT_EMAIL_FIELD,
            t('This contact\'s primary email is configured to mirror the associated Drupal user and email address %email is already in use by another Drupal user.',
              array('%email' => $email['value'])
            )
          );
          break;
        }
      }
    }
  }
}

/**
 * Submit callback for redhen_contact_contact_form().
 */
function redhen_contact_contact_form_submit($form, &$form_state) {
  $contact = &$form_state['redhen_contact'];

  // Set the contact's author uid
  global $user;
  $contact->author_uid = $user->uid;

  // Save default parameters back into the $contact object.
  $contact->first_name = $form_state['values']['first_name'];
  $contact->middle_name = $form_state['values']['middle_name'];
  $contact->last_name = $form_state['values']['last_name'];

  // Notify field widgets.
  field_attach_submit('redhen_contact', $contact, $form, $form_state);

  // Save the contact.
  $contact = redhen_contact_save($contact);

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);

  drupal_set_message(t('Contact %name saved.', array('%name' => $wrapper->full_name->value())));
  $form_state['redirect'] = 'redhen/contact/' . $contact->contact_id;
}

/**
 * Form callback: confirmation form for deleting a contact.
 *
 * @param $contact
 *   The contact object to be deleted.
 *
 * @see confirm_form()
 */
function redhen_contact_contact_delete_form($form, &$form_state, $contact) {
  $form_state['redhen_contact'] = $contact;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_contact') . '/includes/redhen_contact.forms.inc';

  $form['#submit'][] = 'redhen_contact_contact_delete_form_submit';

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);

  $form = confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $wrapper->full_name->value())),
    entity_uri('redhen_contact', $contact),
    '<p>' . t('Deleting this contact cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for redhen_contact_contact_delete_form().
 */
function redhen_contact_contact_delete_form_submit($form, &$form_state) {
  $contact = $form_state['redhen_contact'];

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $full_name = $wrapper->full_name->value();

  if ($contact->isDefaultRevision()) {
    $contact->delete();
    drupal_set_message(t('%title has been deleted.', array('%title' => $full_name)));
    watchdog('redhen_contact', 'Deleted contact %title.', array('%title' => $full_name), WATCHDOG_NOTICE);
    $form_state['redirect'] = 'redhen/contact';
  }
  else {
    entity_revision_delete('redhen_contact', $contact->revision_id);
    drupal_set_message(t('Revision %title has been deleted.', array('%title' => $full_name)));
    watchdog('redhen_contact', 'Deleted contact revision %title.', array('%title' => $full_name), WATCHDOG_NOTICE);
    $form_state['redirect'] = 'redhen/contact/' . $contact->contact_id . '/revisions';
  }
}

/**
 * Form callback: confirmation form for archiving a contact.
 *
 * @param $contact
 *   The contact object to be archived.
 *
 * @see confirm_form()
 */
function redhen_contact_contact_archive_form($form, &$form_state, $contact) {
  $form_state['redhen_contact'] = $contact;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_contact') . '/includes/redhen_contact.forms.inc';

  $form['#submit'][] = 'redhen_contact_contact_archive_form_submit';

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $full_name = $wrapper->full_name->value();

  $form = confirm_form($form,
    t('Are you sure you want to archive %label?', array('%label' => $full_name)),
    entity_uri('redhen_contact', $contact),
    '<p>' . t('Archive this contact.') . '</p>',
    t('Archive'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for redhen_contact_contact_archive_form().
 */
function redhen_contact_contact_archive_form_submit($form, &$form_state) {
  $contact = $form_state['redhen_contact'];

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $full_name = $wrapper->full_name->value();

  if ($contact->setState(REDHEN_STATE_ARCHIVED)) {
    drupal_set_message(t('%label has been archived.', array('%label' => $full_name)));
  }
  else {
    drupal_set_message(t('%label was not archived.', array('%label' => $full_name)), WATCHDOG_ERROR);
  }
  $url = entity_uri($contact->entityType(), $contact);
  $form_state['redirect'] = $url['path'];
}

/**
 * Form callback: confirmation form for unarchiving a contact.
 *
 * @param $contact
 *   The contact object to be activated.
 *
 * @see confirm_form()
 */
function redhen_contact_contact_unarchive_form($form, &$form_state, $contact) {
  $form_state['redhen_contact'] = $contact;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_contact') . '/includes/redhen_contact.forms.inc';

  $form['#submit'][] = 'redhen_contact_contact_unarchive_form_submit';

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $full_name = $wrapper->full_name->value();

  $form = confirm_form($form,
      t('Are you sure you want to unarchive %label?', array('%label' => $full_name)),
      entity_uri('redhen_contact', $contact),
      '<p>' . t('Activate this contact.') . '</p>',
      t('Unarchive'),
      t('Cancel'),
      'confirm'
  );

  return $form;
}

/**
 * Submit callback for redhen_contact_contact_archive_form().
 */
function redhen_contact_contact_unarchive_form_submit($form, &$form_state) {
  $contact = $form_state['redhen_contact'];

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $full_name = $wrapper->full_name->value();

  if ($contact->setState(REDHEN_STATE_ACTIVE)) {
    drupal_set_message(t('%label has been unarchived.', array('%label' => $full_name)));
  }
  else {
    drupal_set_message(t('%label was not unarchived.', array('%label' => $full_name)), WATCHDOG_ERROR);
  }
  $url = entity_uri($contact->entityType(), $contact);
  $form_state['redirect'] = $url['path'];
}

/**
 * Return a form for managing contact/user links.
 *
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function redhen_contact_contact_user_form($form, &$form_state, RedhenContact $contact) {
  $form_state['redhen_contact'] = $contact;
  $form['#attributes'] = array('id' => 'redhen-contact-user-form');

  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $user = $wrapper->user->value();

  if ($user) {
    $user_uri = entity_uri('user', $user);
    $form['existing_user'] = array(
      '#type' => 'container',
      array(
        'message' => array(
          '#markup' => t('!user is currently linked with %contact.', array(
            '!user' => l($user->name, $user_uri['path']),
            '%contact' => $contact->label()
          ))
        ),
        'user' => user_view($user)
      ),
      array(
        'user_actions' => array(
          '#type' => 'actions',
          array(
            'unlink' => array(
              '#type' => 'submit',
              '#value' => t('Unlink'),
              '#submit' => array('redhen_contact_unlink_user_submit')
            ),
            'delete' => array(
              '#type' => 'submit',
              '#value' => t('Delete'),
              '#submit' => array('redhen_contact_unlink_user_submit')
            )
          )
        )
      )
    );
  }
  else {
    $form['link_user'] = array(
      '#title' => t('Link a Drupal user'),
      '#type' => 'select',
      '#options' => array(
        'existing' => t('Choose existing'),
        'new' => t('Create new')
      ),
      '#description' => t('Link a new or existing Drupal user to this contact'),
      '#ajax' => array(
        'callback' => 'redhen_contact_select_user_callback',
        'wrapper' => 'redhen-contact-user-form'
      ),
      '#weight' => -100,
      '#required' => TRUE
    );

    if (isset($form_state['values']['link_user']) && !empty($form_state['values']['link_user'])) {
      switch ($form_state['values']['link_user']) {
        case 'existing':
          // get default value based on email
          $desc = t('Start typing to select a Drupal user to link to this contact.');
          foreach ($contact->allEmail() as $email) {
            if ($user = user_load_by_mail($email)) {
              $default = $user->name;
              $desc = t('A match has been found for user %name by matching on the contact email address. It can be overriden by entering a different value.',
                array('%name' => $user->name));
              break;
            }
          }
          $form['existing'] = array(
            '#title' => t('Existing'),
            '#type' => 'textfield',
            '#description' => $desc,
            '#default_value' => $default,
            '#autocomplete_path' => 'user/autocomplete',
            '#required' => TRUE
          );

          break;

        case 'new';
          // Use the core user registration form, with some adjustments
          $form = user_register_form($form, $form_state);
          // default value for email field
          $form['account']['mail']['#default_value'] = $contact->email();
          $form['account']['name']['#default_value'] = $contact->label();
          $form['#submit'][] = 'redhen_contact_contact_user_form_submit';
      }
    }

    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Link user')
    );
  }

  return $form;
}

/**
 * Ajax callback when changing the type of linkage to create.
 *
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function redhen_contact_select_user_callback($form, &$form_state) {
  // hack to prevent validation on ajax postback, http://drupal.org/node/831900#comment-3124386
  drupal_get_messages('error');
  form_set_error(NULL, '', TRUE);

  // clear any potential error messages
  $commands[] = ajax_command_remove('#messages');

  // return the entire form since we need a certain structure for the
  // user account validation to work properly
  $commands[] = ajax_command_replace('#redhen-contact-user-form', render($form));

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Ajax callback for clearing a user from a contact.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function redhen_contact_unlink_user_submit($form, &$form_state) {
  $contact = $form_state['redhen_contact'];
  $delete = ($form_state['clicked_button']['#parents'][0] == 'delete');
  $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
  $user = $wrapper->user->value();
  $contact->deleteUser($delete);
  drupal_set_message(t('The Drupal user %name has been %action from this contact.',
    array(
      '%name' => $user->name,
      '%action' => $delete ? t('deleted') : t('unlinked')
    )
  ));
}

/**
 * Validation callback for redhen_contact_contact_user_form().
 *
 * @param $form
 * @param $form_state
 */
function redhen_contact_contact_user_form_validate($form, &$form_state) {
  // ensure user is not already linked to a contact
  if (isset($form_state['values']['link_user']) && $form_state['values']['link_user'] == 'existing' && isset($form_state['values']['existing'])) {
    $contact = $form_state['redhen_contact'];

    $user = user_load_by_name($form_state['values']['existing']);
    $result = db_select('redhen_contact_user', 'cu')
      ->fields('cu')
      ->condition('uid', $user->uid, '=')
      ->condition('status', 1, '=')
      ->execute();

    if ($result->rowCount() > 0) {
      form_set_error('existing', t('Drupal user %name is already associated with a contact.',
        array('%name' => $user->name)
      ));
    }

    $result = db_select('redhen_contact_user', 'cu')
      ->fields('cu')
      ->condition('uid', $user->uid, '=')
      ->condition('contact_id', $contact->contact_id, '=')
      ->condition('status', NULL, 'is')
      ->execute();

    if ($result->rowCount() > 0) {
      form_set_error('existing', t('Drupal user %name has been unlinked from this contact to prevent it from being reconnected.',
        array('%name' => $user->name)
      ));
    }
  }
}

/**
 * Submit handler for redhen_contact_contact_user_form().
 *
 * @param $form
 * @param $form_state
 */
function redhen_contact_contact_user_form_submit($form, &$form_state) {
  $contact = $form_state['redhen_contact'];

  switch ($form_state['values']['link_user']) {
    case 'existing':
      $user = user_load_by_name($form_state['values']['existing']);
      $contact->uid = $user->uid;
      break;
    case 'new':
      $user = $form_state['user'];
      $contact->uid = $user->uid;
      break;
  }

  if ($contact->uid) {
    if ($contact->save()) {
      drupal_set_message(t('Drupal user %name has been linked to contact %contact.',
        array(
          '%name' => $user->name,
          '%contact' => $contact->label()
        )
      ));
      $uri = entity_uri('redhen_contact', $contact);
      $form_state['redirect'] = $uri['path'];
    }
    else {
      drupal_set_message(t('Unable to link Drupal user %name to contact %contact.',
        array(
          '%name' => $user->name,
          '%contact' => $contact->label()
        )
      ), 'warning');
    }
  }
}
