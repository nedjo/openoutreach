<?php

/**
 * @file
 * Redhen Organization type classes.
 */


/**
 * The class used for model type entities
 */
class RedhenOrgType extends Entity {

  public $name;
  public $label;
  public $locked;

  public function __construct($values = array()) {
    parent::__construct($values, 'redhen_org_type');
  }

  /**
   * Exports the entity.
   *
   * @see entity_export()
   */
  public function export($prefix = '') {
    if (!empty($this->group)) {
      $this->data = array(
        'group' => $this->group,
        'group_settings' => $this->group_settings,
      );
      unset($this->group, $this->group_settings);
    }
    return entity_get_controller($this->entityType)->export($this, $prefix);
  }

  /**
   * Permanently deletes the entity.
   *
   * @param bool $delete_entities
   *   Indicates if all orgs of this type should be deleted as well.
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
