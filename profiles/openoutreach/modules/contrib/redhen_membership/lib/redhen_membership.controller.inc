<?php
/**
 * @file
 * The controller for the membership entity containing the CRUD operations.
 */

/**
 * The controller class for memberships contains methods for the membership CRUD
 * operations. The load method is inherited from the default controller.
 */
class RedhenMembershipEntityController extends EntityAPIController {

  /**
   * Saves a membership.
   *
   * @param RedhenMembership $membership
   *   The full membership object to save.
   *
   * @return
   *   The saved membership object.
   */
  public function save($membership) {
    $transaction = db_transaction();
    try {
      $membership->updated = REQUEST_TIME;

      parent::save($membership, $transaction);

      // Toggle user roles as needed after saving the membership
      redhen_membership_toggle_roles($membership);

      return $membership;
    } catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('redhen_membership', $e);
      throw $e;
    }
  }

  /**
   * Deletes multiple memberships by id.
   *
   * @param $membership_ids
   *   An array of membership IDs to delete.
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($membership_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($membership_ids)) {
      $memberships = $this->load($membership_ids, array());

      // Toggle all roles for each of the memberships.
      foreach ((array) $memberships as $membership_id => $membership) {
        $membership->setState(REDHEN_MEMBERSHIP_INACTIVE);
      }

      $transaction = db_transaction();
      try {
        parent::delete($membership_ids, $transaction);

      } catch (Exception $e) {
        if (isset($transaction)) {
          $transaction->rollback();
        }
        watchdog_exception($this->entityType, $e);
        throw $e;
      }
    }

    return TRUE;
  }

}
