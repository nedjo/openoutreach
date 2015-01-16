<?php

/**
 * @file
 * Redhen Organization type editing UI.
 */

/**
 * Generates the Redhen Organization type editing form.
 */
function redhen_org_type_form($form, &$form_state, $redhen_org_type, $op = 'edit') {
  if ($op == 'clone') {
    $redhen_org_type->label .= ' (cloned)';
    $redhen_org_type->name = '';
  }

  $form['#redhen_org_type'] = $redhen_org_type;

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $redhen_org_type->label,
    '#description' => t('The human-readable name of this redhen organization type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($redhen_org_type->name) ? $redhen_org_type->name : '',
    '#maxlength' => 32,
    '#disabled' => $redhen_org_type->locked && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'redhen_org_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this redhen organization type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Settings'),
    '#tree' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save organization type'),
    '#weight' => 40,
  );

  if (!$redhen_org_type->locked && $op == 'edit') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete organization type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('redhen_org_type_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function redhen_org_type_form_submit(&$form, &$form_state) {
  $redhen_org_type = entity_ui_form_submit_build_entity($form, $form_state);
  $redhen_org_type->save();
  drupal_set_message(t('Organization type has been saved.'));
  menu_rebuild();
  $form_state['redirect'] = 'admin/structure/redhen/org_types';
}

/**
 * Form API submit callback for the delete button.
 */
function redhen_org_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/redhen/org_types/manage/' . $form_state['redhen_org_type']->name . '/delete';
}
