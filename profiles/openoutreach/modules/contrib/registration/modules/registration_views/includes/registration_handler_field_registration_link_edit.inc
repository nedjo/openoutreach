<?php
/**
 * @file
 * Field handler to render a link to edit a registration.
 */
class registration_handler_field_registration_link_edit extends registration_handler_field_registration_link {

  /**
   * Renders the link.
   */
  function render_link($entity, $values) {
    // Ensure user has access to edit this registration.
    if (!entity_access('update', 'registration', $entity)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "registration/{$entity->registration_id}/edit";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return $text;
  }
}
