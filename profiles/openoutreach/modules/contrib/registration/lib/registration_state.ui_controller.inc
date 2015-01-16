<?php

/**
 * UI Controller for Registration states.
 */
class RegistrationStatesUIController extends EntityDefaultUIController {

  public function overviewForm($form, &$form_state) {
    return drupal_get_form('registration_states_overview_form');
  }

}
