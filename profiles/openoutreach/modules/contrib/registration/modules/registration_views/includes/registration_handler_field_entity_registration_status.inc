<?php
/**
 * @file
 * Display registration status for host entity.
 */
class registration_handler_field_entity_registration_status extends views_handler_field_entity {
  function render($values) {
    $entity = $this->get_value($values);
    list($entity_id) = entity_extract_ids($this->entity_type, $entity);

    $status = registration_status($this->entity_type, $entity_id);
    if (isset($status)) {
      return ($status) ? t('Open', array(), array('context'  =>  'registration')) : t('Closed', array(), array('context'  =>  'registration'));
    }
  }
}
