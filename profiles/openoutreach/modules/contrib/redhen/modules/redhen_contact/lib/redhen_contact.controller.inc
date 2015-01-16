<?php
/**
 * @file
 * The controller for the contact entity containing the CRUD operations.
 */

/**
 * The controller class for contacts contains methods for the contact CRUD
 * operations. The load method is inherited from the default controller.
 */
class RedhenContactEntityController extends EntityAPIController {

  /**
   * Saves a contact.
   *
   * @param RedhenContact $contact
   *   The full contact object to save.
   *
   * @return RedhenContact
   *   The saved contact object.
   */
  public function save($contact, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();
    try {
      $contact->updated = REQUEST_TIME;

      // New contact, set created prop.
      if (isset($contact->is_new) && $contact->is_new) {
        $contact->created = REQUEST_TIME;
      }
      // Set revision flags. By default, save a new revision and set it as
      // default.
      else {
        if (!isset($contact->is_new_revision)) {
          $contact->is_new_revision = TRUE;
        }
        if (!isset($contact->default_revision)) {
          $contact->default_revision = TRUE;
        }
      }

      parent::save($contact, $transaction);

      // Set the contact user.
      if ($contact->uid) {
        $this->setUser($contact, $transaction);
      }

      return $contact;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

  /**
   * Deletes multiple contacts by ID.
   *
   * @param array $contact_ids
   *   An array of contact IDs to delete.
   *
   * @return bool
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($contact_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($contact_ids)) {
      $contacts = $this->load($contact_ids, array());

      // Ensure the contacts can actually be deleted.
      foreach ((array) $contacts as $contact_id => $contact) {
        if (in_array(FALSE, module_invoke_all('redhen_contact_can_delete', $contact))) {
          unset($contacts[$contact_id]);
        }
        else {
          module_invoke_all('redhen_entity_predelete', $contact, 'redhen_contact');
        }
      }

      // If none of the specified contacts can be deleted, return FALSE.
      if (empty($contacts)) {
        return FALSE;
      }
      // Otherwise, update the list of contact IDs to those which are deletable.
      else {
        $contact_ids = array_keys($contacts);
      }

      $transaction = db_transaction();
      try {
        parent::delete($contact_ids, $transaction);

        // Delete user connections.
        db_delete('redhen_contact_user')
          ->condition('contact_id', $contact_ids, 'IN')
          ->execute();

      }
      catch (Exception $e) {
        if (isset($transaction)) {
          $transaction->rollback();
        }
        watchdog_exception($this->entityType, $e);
        throw $e;
      }
    }

    return TRUE;
  }

  /**
   * Override buildQuery to add a join for the active Drupal user.
   */
  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    $query = parent::buildQuery($ids, $conditions, $revision_id);

    $query->leftJoin('redhen_contact_user', 'rcu',
      'rcu.contact_id = base.contact_id AND rcu.status = :status',
      array(':status' => 1)
    );

    // If uid is a condition, ensure the join is against the right table.
    if (isset($conditions['uid'])) {
      $query_conditions = & $query->conditions();
      foreach ($query_conditions as $key => $condition) {
        if (isset($condition['field']) && $condition['field'] == 'base.uid') {
          $query_conditions[$key]['field'] = 'rcu.uid';
        }
      }
    }

    $query->fields('rcu', array('uid'));

    return $query;
  }

  /**
   * Set the active user for a contact.
   *
   * @param RedhenContact $contact
   *   Contact object to associate.
   *
   * @return bool
   *   TRUE if contact is successfully linked to user.
   */
  public function setUser($contact, DatabaseTransaction $transaction = NULL) {
    $user_result = db_select('redhen_contact_user', 'cu')
      ->fields('cu')
      ->condition('uid', $contact->uid, '=')
      ->execute();

    if ($user_result->rowCount() > 0) {
      $rows = $user_result->fetchAllAssoc('uid');
      foreach ($rows as $row) {
        // This user is already actively linked to this contact.
        if ($row->contact_id == $contact->contact_id && $row->status == 1) {
          return TRUE;
        }
        // This user is actively linked to a different contact.
        else {
          if ($row->contact_id != $contact->contact_id && $row->status == 1) {
            return FALSE;
          }
          // This user has been unlinked from this contact.
          else {
            if ($row->contact_id == $contact->contact_id && $row->status == NULL) {
              return FALSE;
            }
          }
        }
      }
    }

    // Now grab any record for this contact.
    $contact_result = db_select('redhen_contact_user', 'cu')
      ->fields('cu')
      ->condition('contact_id', $contact->contact_id, '=')
      ->condition('status', 1, '=')
      ->execute();

    try {
      // Contact does not have a user link, insert.
      if ($contact_result->rowCount() == 0) {
        db_insert('redhen_contact_user')
          ->fields(array(
          'contact_id' => $contact->contact_id,
          'uid' => $contact->uid,
          'status' => 1,
          'created' => REQUEST_TIME,
          'updated' => REQUEST_TIME,
        ))
          ->execute();
        module_invoke_all('redhen_contact_user_update', 'insert', $contact);
      }
      // Update existing link with different user.
      else {
        // Update with new user.
        db_update('redhen_contact_user')
          ->fields(array(
          'uid' => $contact->uid,
          'updated' => REQUEST_TIME,
        ))
          ->condition('contact_id', $contact->contact_id)
          ->condition('status', 1)
          ->execute();

        // Clone the contact to populate with the old user info.
        $old_contact = clone $contact;
        $old_user = $contact_result->fetchAssoc();
        $old_contact->uid = $old_user['uid'];

        module_invoke_all('redhen_contact_user_update', 'update', $contact, $old_contact);
      }

      return TRUE;
    }
    catch (Exception $e) {
      if (isset($transaction)) {
        $transaction->rollback();
      }
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

  /**
   * Delete or unlink the active user for a contact.
   *
   * @param RedhenContact $contact
   *   RedHen contact object.
   * @param bool $delete
   *   If true, the connection is deleted and can be recreated. False sets the
   *   connection to inactive which will prevent it from being reconnected on
   *   subsequent attempts.
   *
   * @return bool
   *   TRUE if user is successfully deleted or unlinked from contact.
   */
  public function deleteUser($contact, $delete = FALSE, DatabaseTransaction $transaction = NULL) {
    try {
      $wrapper = entity_metadata_wrapper('redhen_contact', $contact);
      $user = $wrapper->user->value();
      if ($delete) {
        db_delete('redhen_contact_user')
          ->condition('contact_id', $contact->contact_id)
          ->condition('uid', $user->uid)
          ->execute();
      }
      else {
        db_update('redhen_contact_user')
          ->condition('contact_id', $contact->contact_id)
          ->condition('uid', $user->uid)
          ->fields(array('status' => NULL))
          ->execute();
      }

      module_invoke_all('redhen_contact_user_update', 'delete', $contact);

      unset($contact->uid);

      return TRUE;
    }
    catch (Exception $e) {
      if (isset($transaction)) {
        $transaction->rollback();
      }
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }
}
