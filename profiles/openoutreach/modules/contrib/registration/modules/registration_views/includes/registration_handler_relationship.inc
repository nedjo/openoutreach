<?php

/**
 * @file
 * Contains relationship handlers.
 */

/**
 * Specialized relationship handler associating registrations and their host
 * entity.
 *
 */
class registration_handler_relationship extends views_handler_relationship {

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    $entity = $this->definition['entity'];

    if (isset($this->definition['table'])) {
      $this->definition['extra'][] = array(
        'table' => $this->definition['table'],
        'field' => 'entity_type',
        'value' => $this->definition['entity'],
      );
    }
    else {
      $this->definition['extra'][] = array(
        'field' => 'entity_type',
        'value' => $this->definition['entity'],
      );
    }
    parent::query();
  }
}
