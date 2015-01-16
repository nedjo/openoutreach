<?php
/**
 * @file
 * Display registration open or closing dates.
 */
class registration_handler_field_entity_datetime extends views_handler_field_date {
  function render($values) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->{$alias})) {
      $values->{$alias} = strtotime($values->{$alias});
      if ($values->{$alias} !== FALSE) {
        return parent::render($values);
      }
    }
  }
}
