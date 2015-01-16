<?php

/**
 * @file
 * Defines the inline entity form controller for RedHen Orgs.
 */

class RedHenOrgInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::labels().
   */
  public function labels() {
    $labels = array(
      'singular' => t('organization'),
      'plural' => t('organizations'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $org = $entity_form['#entity'];

    // Do some prep work on the contact, similarly to node_form().
    if (!isset($org->label)) {
      $org->label = NULL;
    }

    $entity_form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $org->label,
      '#maxlength' => 255,
      '#required' => TRUE,
    );

    field_attach_form('redhen_org', $org, $entity_form, $form_state);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    $org = & $entity_form['#entity'];


    // Set the contact's author uid.
    global $user;
    $org->author_uid = $user->uid;

    // Get form_state array, only including the subform of this entity.
    $child_form_state = form_state_defaults();
    $child_form_state['values'] = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);

    // Save the org.
    $org->save();
  }
}
