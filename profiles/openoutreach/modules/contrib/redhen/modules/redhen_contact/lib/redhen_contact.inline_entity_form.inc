<?php

/**
 * @file
 * Defines the inline entity form controller for RedHen contacts.
 */

class RedHenContactInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::labels().
   */
  public function labels() {
    $labels = array(
      'singular' => t('contact'),
      'plural' => t('contacts'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $contact = $entity_form['#entity'];

    // Do some prep work on the contact, similarly to node_form().
    if (!isset($contact->first_name)) {
      $contact->first_name = NULL;
    }
    if (!isset($contact->last_name)) {
      $contact->last_name = NULL;
    }

    $entity_form['name'] = array();
    $entity_form['name']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#default_value' => $contact->first_name,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#weight' => -6,
    );
    $entity_form['name']['middle_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Middle name'),
      '#default_value' => $contact->middle_name,
      '#maxlength' => 255,
      '#weight' => -6,
    );
    $entity_form['name']['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#default_value' => $contact->last_name,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#weight' => 5,
    );

    field_attach_form('redhen_contact', $contact, $entity_form, $form_state);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    $contact = & $entity_form['#entity'];

    // Save default parameters back into the $contact object.
    $contact->first_name = $contact->name['first_name'];
    $contact->last_name = $contact->name['last_name'];

    // Set the contact's author uid.
    global $user;
    $contact->author_uid = $user->uid;

    // Get form_state array, only including the subform of this entity.
    $child_form_state = form_state_defaults();
    $child_form_state['values'] = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);

    // Save the contact.
    $contact = redhen_contact_save($contact);
  }
}
