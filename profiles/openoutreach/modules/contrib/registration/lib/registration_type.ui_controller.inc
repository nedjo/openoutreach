<?php

/**
 * @file
 * Registration Type UI controller.
 */
class RegistrationTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = t('Manage registration entity types, including adding and removing fields and the display of fields.');
    return $items;
  }

}
