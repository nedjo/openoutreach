<?php

/**
 * @file
 * The controller class used for registration state entities
 */
class RegistrationStateController extends EntityAPIControllerExportable {

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);

    if ($entity->default_state == 1) {
      $query = db_update('registration_state')
        ->fields(array('default_state' => 0))
        ->condition('registration_state_id', $entity->registration_state_id, '<>');
      $query->execute();
    }
  }

}
