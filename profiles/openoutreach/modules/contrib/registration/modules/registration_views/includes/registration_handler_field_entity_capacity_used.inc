<?php
/**
 * @file
 * Display maximum slots for an entity.
 */
class registration_handler_field_entity_capacity_used extends views_handler_field_numeric {
  function render($values) {
    $entity_id = $this->get_value($values);
    $table = $this->table;
    $alias = $this->field_alias;
    $slots_used = (int) registration_event_count($table, $entity_id);
    $values->$alias = $slots_used;
    return parent::render($values);
  }
}
