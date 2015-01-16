<?php
/**
 * @file
 * Field handler to render a link to delete a registration.
 */
class registration_handler_field_registration_link_delete extends registration_handler_field_registration_link {

  /**
   * Renders the link.
   */
  function render_link($entity, $values) {
    // Ensure user has access to delete this registration.
    if (!entity_access('delete', 'registration', $entity)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "registration/{$entity->registration_id}/delete";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    return $text;
  }
}
