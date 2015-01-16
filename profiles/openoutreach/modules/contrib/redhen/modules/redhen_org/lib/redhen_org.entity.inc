<?php
/**
 * @file
 * Redhen Group entity classes
 */

/**
 * The class used for group entities.
 */
class RedhenOrg extends Entity {

  // @codingStandardsIgnoreStart
  public
    $label = '',
    $org_id = NULL,
    $primary_contact_id = NULL,
    $author_uid = NULL,
    $redhen_state = REDHEN_STATE_ACTIVE,
    $type = '',
    $created = '',
    $updated = '';
  // @codingStandardsIgnoreEnd

  /**
   * Override parent constructor.
   */
  public function __construct(array $values = array()) {
    global $user;

    parent::__construct($values, 'redhen_org');

    // New organization. is_new might not be set so check for id.
    if (!$this->org_id) {
      $this->author_uid = $user->uid;
      $this->redhen_state = REDHEN_STATE_ACTIVE;
      $this->created = REQUEST_TIME;
    }

  }

  /**
   * Override buildContent() to add organization properties.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {

    $wrapper = entity_metadata_wrapper('redhen_org', $this);
    $primary_contact = $wrapper->primary_contact->value();

    $content['redhen_state'] = array(
      '#theme' => 'redhen_property_field',
      '#label' => t('State'),
      '#items' => array(
        array(
          '#markup' => ($this->redhen_state == REDHEN_STATE_ACTIVE) ? t('Active') : t('Inactive'),
        ),
      ),
      '#classes' => 'field field-label-inline clearfix',
    );
    if (isset($primary_contact->contact_id)) {
      $contact_array = $primary_contact->view('teaser');
      $content['primary_contact'] = array(
        '#theme' => 'fieldset',
        '#title' => t('Primary Contact'),
        '#children' => drupal_render($contact_array),
      );
    }

    return entity_get_controller($this->entityType)
      ->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Permanently saves the entity.
   *
   * @return bool
   *   Returns FALSE if entity was not saved.
   */
  public function save() {
    $this->updated = REQUEST_TIME;
    return parent::save();
  }

  /**
   * Set the primary contact for an organization.
   *
   * @param RedhenContact $contact
   *   The RedhenContact to use as the primary contact
   *
   * @return bool
   *   Return FALSE if we are unable to set the primary contact
   */
  public function setPrimaryContact(RedhenContact $contact) {
    // @TODO Check that $contact has a relationship with $this.
    $this->primary_contact_id = $contact->contact_id;
    return $this->save();
  }

  /**
   * Set the redhen_state for an organization.
   *
   * @param string $state
   *   The REDHEN_STATE_* value to use.
   */
  public function setState($state) {
    $this->redhen_state = $state;
    return $this->save();
  }

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    $type = redhen_org_get_types($this->type);
    return $this->label . ' (' . $type->label . ')';
  }

  /**
   * Specify URI.
   */
  protected function defaultUri() {
    return array('path' => 'redhen/org/' . $this->internalIdentifier());
  }

}
