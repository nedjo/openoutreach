<?php

/**
 * @file
 * Redhen Membership type editing UI.
 */

/**
 * Generates the Redhen Membership type editing form.
 */
function redhen_membership_type_form($form, &$form_state, $redhen_membership_type, $op = 'edit') {
  if ($op == 'clone') {
    $redhen_membership_type->label .= ' (cloned)';
    $redhen_membership_type->name = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $redhen_membership_type->label,
    '#description' => t('The human-readable name of this redhen membership type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($redhen_membership_type->name) ? $redhen_membership_type->name : '',
    '#maxlength' => 32,
    '#disabled' => $redhen_membership_type->locked && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'redhen_membership_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this redhen membership type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $roles = user_roles(TRUE);
  unset($roles[2]); // remove authenticated user from options
  // Display role selection if there is at lease o
  $roles = array('' => t('-None-')) + $roles;

  $form['role_id'] = array(
    '#type' => 'select',
    '#title' => 'Assign user role',
    '#default_value' => isset($redhen_membership_type->role_id) ? $redhen_membership_type->role_id : '',
    '#description' => t('Select a role to associate users with a role when the user or their organization has an active membership of this type.'),
    '#options' => $roles,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save membership type'),
    '#weight' => 40,
  );

  if (!$redhen_membership_type->locked && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete membership type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('redhen_membership_type_form_submit_delete')
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function redhen_membership_type_form_submit(&$form, &$form_state) {
  $redhen_membership_type = entity_ui_form_submit_build_entity($form, $form_state);
  $redhen_membership_type->save();
  $form_state['redirect'] = 'admin/structure/redhen/membership_types';
}

/**
 * Form API submit callback for the delete button.
 */
function redhen_membership_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/redhen/membership_types/manage/' . $form_state['redhen_membership_type']->type . '/delete';
}
