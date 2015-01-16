<?php

/**
 * @file
 * Redhen Membership type classes.
 */


/**
 * The class used for model type entities
 */
class RedhenMembershipType extends Entity {

  public $name;
  public $label;
  public $role_id = NULL;
  public $locked;

  public function __construct($values = array()) {
    parent::__construct($values, 'redhen_membership_type');
  }

  /**
   * Override save method to rebuild the menu when a new type is created.
   */
  public function save() {
    $ret = parent::save();
    menu_rebuild();
    return $ret;
  }

}

