<?php

/**
 * @file
 * Redhen Contact type classes.
 */


/**
 * The class used for model type entities
 */
class RedhenContactType extends Entity {

  public $name;
  public $label;
  public $locked;

  /**
   * Override parent constructor to set entity type.
   *
   * @param array $values
   *   Default entity values.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'redhen_contact_type');
  }

  /**
   * Override parent save method to ensure we have an email field for each type.
   */
  public function save() {
    $ret = parent::save();

    // Associate email field instance with contact.
    if ($ret) {
      // Create email field if it doesn't exist.
      redhen_fields_create_email_field();

      // Now create an instance of the email field for this contact type.
      redhen_fields_create_email_instance($this->name);
    }
  }

  /**
   * Permanently deletes the entity.
   *
   * @param bool $delete_entities
   *   Indicates if all contacts of this type should be deleted as well.
   *
   * @see entity_delete()
   */
  public function delete($delete_entities = FALSE) {
    $id = $this->identifier();
    if (isset($id)) {
      entity_get_controller($this->entityType)->delete(array($id), NULL, $delete_entities);
    }
  }

}
