<?php

/**
 * @file
 * The controller class used for registration type entities
 */
class RegistrationTypeController extends EntityAPIControllerExportable {

  /**
   * Overridden.
   */
  public function export($entity, $prefix = '') {
    // Ensure our data properties are properly structured.
    $data_properties = array('held_expire', 'held_expire_state');
    foreach ($data_properties as $data_property) {
      if (isset($entity->$data_property)) {
        $entity->data[$data_property] = $entity->$data_property;
        unset($entity->$data_property);
      }
    }

    return parent::export($entity, $prefix);
  }

}
