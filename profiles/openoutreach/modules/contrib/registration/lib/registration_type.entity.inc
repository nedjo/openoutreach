<?php

/**
 * @file
 * The class used for model type entities
 */
class RegistrationType extends Entity {

  public $name;
  public $label;
  public $locked;
  public $default_state;
  public $data;

  public function __construct($values = array()) {
    parent::__construct($values, 'registration_type');
  }

}
