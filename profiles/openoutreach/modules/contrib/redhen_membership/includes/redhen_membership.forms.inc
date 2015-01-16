<?php

/**
 * @file
 * Forms for creating, editing, and deleting memberships.
 */

/**
 * Form callback: create or edit a contact.
 *
 * @param $membership
 *   The membership object to edit or for a create form an empty membership object
 *     with only a membership type defined.
 * @param RedhenContact|RedhenOrg $entity
 * @param string $entity_type
 */
function redhen_membership_membership_form($form, &$form_state, $membership, $entity = NULL, $entity_type = '') {

  // add jquery libs and
  drupal_add_library('system', 'ui.datepicker');
  drupal_add_js(drupal_get_path('module', 'redhen') . '/misc/redhen.forms.js');

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_membership') . '/includes/redhen_membership.forms.inc';

  // Store membership and entity data for use on submit
  $form_state['membership'] = $membership;
  $form_state['entity'] = $entity;

  // Add the default field elements.
  $form['note'] = array(
    '#type' => 'textfield',
    '#title' => t('Note'),
    '#default_value' => isset($membership->note) ? $membership->note : '',
    '#maxlength' => 255,
    '#required' => FALSE,
    '#weight' => -10,
  );

  $form['start_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Start Date'),
    '#description' => t('If set and RedHen is configured to automatically enable memberships, the membership state will be set to Active on this date.'),
    '#default_value' => isset($membership->start_date) ? date('m/d/Y', $membership->start_date) : '',
    '#attributes' => array('class' => array("redhen-field-type-date")),
    '#weight' => -9,
  );

  $form['expire_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Expiration Date'),
    '#description' => t('If set and RedHen is configured to automatically expire memberships, the membership state will be set to Expired on this date.'),
    '#default_value' => isset($membership->expire_date) ? date('m/d/Y', $membership->expire_date) : '',
    '#attributes' => array('class' => array("redhen-field-type-date")),
    '#weight' => -8,
  );

  $form['membership_state'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#description' => t('Membership state. Inactive or Expired memberships do not confer benefits to contacts/users.'),
    '#options' => redhen_membership_state_options(),
    '#default_value' => isset($membership->membership_state) ? $membership->membership_state : REDHEN_MEMBERSHIP_ACTIVE,
    '#weight' => -7,
  );

  // Add the field related form elements.
  field_attach_form('redhen_membership', $membership, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 40,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save membership'),
    '#submit' => $submit + array('redhen_membership_membership_form_submit'),
  );

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'redhen_membership_membership_form_validate';

  return $form;
}

/**
 * Validation callback for redhen_membership_membership_form().
 */
function redhen_membership_membership_form_validate($form, &$form_state) {
  $membership = $form_state['membership'];

  $start = ($form_state['values']['start_date'] != '') ? strtotime($form_state['values']['start_date']) : '';
  if ($start === false) {
    form_set_error('start_date', 'Start date is invalid.');
  }

  $expire =  ($form_state['values']['expire_date'] != '') ? strtotime($form_state['values']['expire_date']) : '';
  if ($expire === false) {
    form_set_error('expire_date', 'Expiration date is invalid.');
  }

  // check that expire date is after start date if both are set
  if (($start != '') && ($expire != '') && ($start >= $expire)) {
    form_set_error('expire_date', 'Expiration date must be after the start date.');
  }

  // Notify field widgets to validate their data.
  field_attach_form_validate('redhen_membership', $membership, $form, $form_state);
}

/**
 * Submit callback for redhen_membership_membership_form().
 */
function redhen_membership_membership_form_submit($form, &$form_state) {
  global $user;

  $membership = &$form_state['membership'];

  if (isset($form_state['entity'])) {
    $entity = $form_state['entity'];
  }
  else {
    $wrapper = entity_metadata_wrapper('redhen_membership', $membership);
    $entity = $wrapper->entity->value();
  }

  $entity_type = $entity->entityType();
  $entity_uri = entity_uri($entity_type, $entity);

  // Set the membership's author uid
  $membership->author_uid = $user->uid;

  // Save default parameters back into the $membership object.
  $membership->note = $form_state['values']['note'];
  $membership->start_date = ($form_state['values']['start_date'] != '') ? strtotime($form_state['values']['start_date']) : NULL;
  $membership->expire_date = ($form_state['values']['expire_date'] != '') ? strtotime($form_state['values']['expire_date']) : NULL;
  $membership->membership_state = $form_state['values']['membership_state'];
  $membership->entity_type = $entity_type;
  $membership->entity_id = entity_id($entity_type, $entity);

  // Notify field widgets.
  field_attach_submit('redhen_membership', $membership, $form, $form_state);

  // Save the membership.
  redhen_membership_save($membership);

  drupal_set_message(t('Membership %label saved.', array('%label' => $membership->label())));
  $form_state['redirect'] = $entity_uri['path'] . '/memberships';
}

/**
 * Form callback: confirmation form for deleting a membership.
 *
 * @param $membership
 *   The membership object to be deleted.
 *
 * @see confirm_form()
 */
function redhen_membership_membership_delete_form($form, &$form_state, $membership) {

  $form_state['membership'] = $membership;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'redhen_membership') . '/includes/redhen_membership.forms.inc';

  $form['#submit'][] = 'redhen_membership_membership_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete %label?', array('%label' => $membership->label())),
    entity_uri('redhen_membership', $membership),
    '<p>' . t('Deleting this membership cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for redhen_membership_membership_delete_form().
 */
function redhen_membership_membership_delete_form_submit($form, &$form_state) {
  $membership = $form_state['membership'];

  redhen_membership_delete_multiple(array($membership->membership_id));
  drupal_set_message(t('%label has been deleted.', array('%label' => $membership->label())));
  watchdog('redhen_membership', 'Deleted membership %label.', array('%label' => $membership->label()), WATCHDOG_NOTICE);

  drupal_goto();
}
