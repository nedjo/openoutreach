<?php

/**
 * Redhen Contact Type UI controller.
 */
class RedhenMembershipTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage membership entity types, including
		  adding and removing fields and the display of fields.';
    return $items;
  }

}
