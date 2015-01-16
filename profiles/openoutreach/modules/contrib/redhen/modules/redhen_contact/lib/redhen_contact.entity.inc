<?php
/**
 * @file
 * Redhen Contact entity classses
 */

/**
 * The class used for contact entities.
 */
class RedhenContact extends Entity {

  // @codingStandardsIgnoreStart
  public
    $first_name = '',
    $middle_name = '',
    $last_name = '',
    $contact_id = NULL,
    $uid = NULL,
    $author_uid = NULL,
    $redhen_state = REDHEN_STATE_ACTIVE,
    $type = '',
    $created = '',
    $updated = '';
  // @codingStandardsIgnoreEnd

  /**
   * Override parent constructor with entity type.
   *
   * @param array $values
   *   Entity values to populate object.
   */
  public function __construct(array $values = array()) {
    parent::__construct($values, 'redhen_contact');
  }

  /**
   * Override buildContent() to add contact properties.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {

    $wrapper = entity_metadata_wrapper('redhen_contact', $this);
    $user = $wrapper->user->value();
    $name = $wrapper->full_name->value();

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

    if (!empty($name)) {
      $content['name'] = array(
        '#theme' => 'redhen_property_field',
        '#label' => t('Name'),
        '#items' => array(
          array(
            '#markup' => $wrapper->full_name->value(),
          ),
        ),
        '#classes' => 'field field-label-inline clearfix',
        '#attributes' => '',
      );
    }

    if ($user) {
      $user_uri = entity_uri('user', $user);
      $content['user'] = array(
        '#theme' => 'redhen_property_field',
        '#label' => t('Drupal User'),
        '#items' => array(
          array(
            '#markup' => l($user->name, $user_uri['path']),
          ),
        ),
        '#classes' => 'field field-label-inline clearfix',
        '#attributes' => '',
      );
    }

    return entity_get_controller($this->entityType)
      ->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    $wrapper = entity_metadata_wrapper('redhen_contact', $this);
    return $wrapper->full_name->value();
  }

  /**
   * Specify default URI.
   */
  protected function defaultUri() {
    return array('path' => 'redhen/contact/' . $this->identifier());
  }

  /**
   * Return a contacts primary email.
   *
   * @return array
   *   Email value as an array.
   */
  public function email() {
    $wrapper = entity_metadata_wrapper($this->entityType(), $this);
    return $wrapper->email->value();
  }

  /**
   * Return all emails and their properties in an array..
   *
   * @return array
   *   Array of email value arrays.
   */
  public function allEmail() {
    $emails = array();
    if (!empty($this->{REDHEN_CONTACT_EMAIL_FIELD})) {
      $emails = $this->{REDHEN_CONTACT_EMAIL_FIELD}[LANGUAGE_NONE];
    }
    return $emails;
  }

  /**
   * Determine if contact has a given email.
   *
   * @param string $email
   *   Email to look for.
   *
   * @return bool
   *   Whether or not an email exists for a contact.
   */
  public function hasEmail($email) {
    if (!empty($this->{REDHEN_CONTACT_EMAIL_FIELD})) {
      foreach ($this->{REDHEN_CONTACT_EMAIL_FIELD}[LANGUAGE_NONE] as $contact_email) {
        if ($contact_email['value'] === $email) {
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  /**
   * Sets an email for a contact.
   *
   * @param string $email
   *   Email address.
   * @param bool $default
   *   If email is default.
   * @param bool $bulk
   *   If email is for bulk use.
   * @param bool $hold
   *   If email is on hold.
   * @param int $label_id
   *   Label id.
   */
  public function setEmail($email, $default = 1, $bulk = 1, $hold = 0, $label_id = 0) {
    $this->{REDHEN_CONTACT_EMAIL_FIELD}[LANGUAGE_NONE][] = array(
      'value' => $email,
      'default' => $default,
      'bulk' => $bulk,
      'hold' => $hold,
      'label_id' => $label_id,
    );
  }

  /**
   * Set a contact's Drupal user.
   *
   * @return bool
   *   True on success.
   */
  public function setUser() {
    return entity_get_controller($this->entityType)->setUser($this);
  }

  /**
   * Delete or unlink the active user for a contact.
   *
   * @param bool $delete
   *   Flag if contact should unlinked or deleted.
   *
   * @return bool
   *   Trust on success.
   */
  public function deleteUser($delete) {
    return entity_get_controller($this->entityType)->deleteUser($this, $delete);
  }

  /**
   * Set the redhen_state for a contact.
   *
   * @param int $state
   *   The REDHEN_STATE_* value to use.
   */
  public function setState($state) {
    // Allow other modules to act on a state change.
    module_invoke_all('redhen_contact_set_state', $this->redhen_state, $state);
    $this->redhen_state = $state;
    return entity_get_controller($this->entityType)->save($this);
  }

  /**
   * Override parent::save() to manage user association.
   */
  public function save() {
    $wrapper = entity_metadata_wrapper('redhen_contact', $this);
    $user = $wrapper->user->value();

    if (variable_get('redhen_contact_connect_users', FALSE) && !$user) {
      $emails = $this->allEmail();
      foreach ($emails as $email) {
        // Ensure email value is not set to empty string because that matches
        // Drupal's anonymous user (uid=0). This can happen when creating a
        // contact programmatically where the email field is not guaranteed to
        // be populated.
        if (!empty($email['value']) && $user = user_load_by_mail($email['value'])) {
          $wrapper->user->set($user);
          break;
        }
      }
    }

    $ret = parent::save();

    if ($ret && variable_get('redhen_contact_mirror_email', FALSE)) {
      $email = $wrapper->email->value();

      // If we have a linked user and primary email, but they don't match, set
      // the user email.
      if ($user && $user->uid != 0 && !empty($email) && ($email !== $user->mail)) {
        user_save($user, array('mail' => $email));
      }
    }

    return $ret;
  }

}
