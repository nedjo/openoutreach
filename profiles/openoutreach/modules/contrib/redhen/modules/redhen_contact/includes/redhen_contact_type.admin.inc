<?php

/**
 * @file
 * Redhen Contact type editing UI.
 */

/**
 * Generates the Redhen Contact type editing form.
 */
function redhen_contact_type_form($form, &$form_state, $redhen_contact_type, $op = 'edit') {
  if ($op == 'clone') {
    $redhen_contact_type->label .= ' (cloned)';
    $redhen_contact_type->name = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $redhen_contact_type->label,
    '#description' => t('The human-readable name of this contact type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($redhen_contact_type->name) ? $redhen_contact_type->name : '',
    '#maxlength' => 32,
    '#disabled' => $redhen_contact_type->locked || $op == 'edit',
    '#machine_name' => array(
      'exists' => 'redhen_contact_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this contact type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save contact type'),
    '#weight' => 40,
  );

  if (!$redhen_contact_type->locked && $op == 'edit') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete contact type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('redhen_contact_type_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function redhen_contact_type_form_submit(&$form, &$form_state) {
  $redhen_contact_type = entity_ui_form_submit_build_entity($form, $form_state);
  $redhen_contact_type->save();
  menu_rebuild();
  $form_state['redirect'] = 'admin/structure/redhen/contact_types';
}

/**
 * Form API submit callback for the delete button.
 */
function redhen_contact_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/redhen/contact_types/manage/' . $form_state['redhen_contact_type']->name . '/delete';
}
