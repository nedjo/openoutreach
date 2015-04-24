<?php

/**
 * @file
 * The class used for registration state entities
 */
class RegistrationState extends Entity {

  public $name, $label, $description, $default_state,
    $active, $held, $show_on_form, $weight;

  public function __construct($values = array()) {
    parent::__construct($values, 'registration_state');
  }

}
