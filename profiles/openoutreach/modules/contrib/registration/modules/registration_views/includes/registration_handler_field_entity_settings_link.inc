<?php
/**
 * @file
 * Field handler to render a link to edit entity registration settings.
 */
class registration_handler_field_entity_settings_link extends registration_handler_field_registration_link {

  /**
   * Renders the link.
   */
  function render_link($entity, $values) {
    // Ensure user has access to edit registration settings.
    if (!registration_administer_registrations_access($this->entity_type, $entity)) {
      return;
    }

    $uri = entity_uri($this->entity_type, $entity);

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = $uri['path'] . '/registrations/settings';
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('settings');
    return $text;
  }
}
