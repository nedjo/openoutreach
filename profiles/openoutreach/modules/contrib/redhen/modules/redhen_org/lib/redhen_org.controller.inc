<?php
/**
 * @file
 * The controller for the org entity containing the CRUD operations.
 */

/**
 * The controller class for orgs contains methods for the org CRUD
 * operations. The load method is inherited from the default controller.
 */
class RedhenOrgEntityController extends EntityAPIController {

  /**
   * Saves an org.
   *
   * @param RedhenOrg $org
   *   The full org object to save.
   *
   * @return RedhenOrg
   *   The saved org object.
   */
  public function save($org) {
    $org->updated = REQUEST_TIME;

    // New org, set created prop.
    if (isset($org->is_new) && $org->is_new) {
      $org->created = REQUEST_TIME;
    }
    // Set revision flags. By default, save a new revision and set it as
    // default.
    else {
      if (!isset($org->is_new_revision)) {
        $org->is_new_revision = TRUE;
      }
      if (!isset($org->default_revision)) {
        $org->default_revision = TRUE;
      }
    }

    parent::save($org);

    return $org;
  }

  /**
   * Deletes multiple orgs by id.
   *
   * @param array $org_ids
   *   An array of org IDs to delete.
   * @param DatabaseTransaction $transaction
   *   DB transaction object.
   *
   * @return bool
   *   TRUE on success, FALSE otherwise.
   *
   * @throws Exception
   */
  public function delete($org_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($org_ids)) {
      $orgs = $this->load($org_ids, array());

      // Ensure the orgs can actually be deleted.
      foreach ((array) $orgs as $org_id => $org) {
        if (in_array(FALSE, module_invoke_all('redhen_org_can_delete', $org))) {
          unset($orgs[$org_id]);
        }
        else {
          module_invoke_all('redhen_entity_predelete', $org, 'redhen_org');
        }
      }

      $transaction = db_transaction();
      try {
        parent::delete($org_ids, $transaction);
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

}
