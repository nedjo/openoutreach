<?php

/**
 * @file
 * The controller for the contact type entity containing the CRUD operations.
 */

/**
 * The controller class for contact types contains methods for CRUD
 * operations. The load method is inherited from the default controller.
 */
class RedhenContactTypeController extends EntityAPIControllerExportable {

  /**
   * Delete one or more contact types.
   *
   * @param array $ids
   *   Array of contact type IDs.
   * @param DatabaseTransaction $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   * @param bool $delete_entities
   *   If true, all redhen_contact entities of the type being deleted will also
   *   be deleted.
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL, $delete_entities = FALSE) {
    $transaction = isset($transaction) ? $transaction : db_transaction();
    try {
      if ($delete_entities) {
        $query = new EntityFieldQuery();
        $result = $query
          ->entityCondition('entity_type', 'redhen_contact')
          ->entityCondition('bundle', $ids, 'IN')
          ->execute();

        if ($result) {
          redhen_contact_delete_multiple(array_keys($result['redhen_contact']));
        }
      }
      parent::delete($ids, $transaction);
    }
    catch(Exception $e) {
      $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

}
