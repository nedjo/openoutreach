<?php
/**
 * @file
 * Display maximum slots for an entity.
 */
class registration_handler_field_entity_capacity_total extends views_handler_field {
  function render($values) {
    $slots = $this->get_value($values);
    if (isset($slots)) {
      if (!empty($slots)) {
        return $slots;
      }
      else {
        return t('Unlimited');
      }
    }
  }
}
