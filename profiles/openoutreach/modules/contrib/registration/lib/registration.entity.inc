<?php

/**
 * @file
 * Entity hooks and callbacks for registrations.
 */

/**
 * Main class for Registration entities.
 */
class Registration extends Entity {

  public
    $registration_id,
    $type,
    $entity_id,
    $entity_type,
    $anon_mail = NULL,
    $user_uid = NULL,
    $count,
    $author_uid,
    $state,
    $created,
    $updated;

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    $wrapper = entity_metadata_wrapper('registration', $this);
    $host = $wrapper->entity->value();
    if ($host) {
      return t('Registration for !title', array(
          '!title' => entity_label($this->entity_type, $host),
        )
      );
    }
    return '';
  }

  /**
   * Build content for Registration.
   *
   * @return array
   *   Render array for a registration entity.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {
    $build = parent::buildContent($view_mode, $langcode);
    $wrapper = entity_metadata_wrapper('registration', $this);

    $host_entity_type_info = entity_get_info($this->entity_type);
    $host_entity = $wrapper->entity->value();
    $state = $wrapper->state->value();
    $author = $wrapper->author->value();
    $user = $wrapper->user->value();
    list(, , $host_entity_bundle) = entity_extract_ids($this->entity_type, $host_entity);

    $host_label = entity_label($this->entity_type, $host_entity);

    $host_uri = $host_entity ? entity_uri($this->entity_type, $host_entity) : NULL;

    $build['mail'] = array(
      '#prefix' => '<div class="field registration-mail"><div class="field-label">' . t('Email Address') . '</div>',
      '#markup' => $wrapper->mail->value(),
      '#suffix' => '</div>',
    );

    // Link to host entity.
    $host_entity_link_label = (isset($host_entity_type_info['bundles'][$host_entity_bundle]['label'])) ? '<div class="field-label">' . $host_entity_type_info['bundles'][$host_entity_bundle]['label'] . '</div>' : '';
    $build['host_entity_link'] = array(
      '#prefix' => '<div class="field registration-entity-link">' . $host_entity_link_label,
      '#markup' => l($host_label, $host_uri['path']),
      '#suffix' => '</div>',
    );

    $build['created'] = array(
      '#prefix' => '<div class="field registration-created"><div class="field-label">' . t('Created') . '</div>',
      '#markup' => format_date($this->created),
      '#suffix' => '</div>',
    );

    $build['updated'] = array(
      '#prefix' => '<div class="field registration-updated"><div class="field-label">' . t('Updated') . '</div>',
      '#markup' => format_date($this->updated),
      '#suffix' => '</div>',
    );

    $build['slots'] = array(
      '#prefix' => '<div class="field registration-slots"><div class="field-label">' . t('Slots Used') . '</div>',
      '#markup' => $this->count,
      '#suffix' => '</div>',
    );

    $build['author'] = array(
      '#prefix' => '<div class="field registration-author"><div class="field-label">' . t('Author') . '</div>',
      '#theme' => 'username',
      '#account' => $author,
      '#suffix' => '</div>',
    );

    $build['user'] = array(
      '#prefix' => '<div class="field registration-user"><div class="field-label">' . t('User') . '</div>',
      '#theme' => 'username',
      '#account' => $user,
      '#suffix' => '</div>',
    );

    $build['state'] = array(
      '#prefix' => '<div class="field registration-state"><div class="field-label">' . t('State') . '</div>',
      '#markup' => ($state) ? filter_xss_admin(entity_label('registration_state', $state)) : '',
      '#suffix' => '</div>',
    );

    return $build;
  }

  /**
   * Save registration.
   *
   * @see entity_save()
   */
  public function save() {
    // Set a default state if not provided.
    $wrapper = entity_metadata_wrapper('registration', $this);
    $state = $wrapper->state->value();
    if (!$state) {
      $default_state = registration_get_default_state();
      if ($default_state) {
        $this->state = $default_state->identifier();
      }
    }

    $this->updated = REQUEST_TIME;

    if (!$this->registration_id && empty($this->created)) {
      $this->created = REQUEST_TIME;
    }
    return parent::save();
  }

  /**
   * Specify URI.
   */
  protected function defaultUri() {
    return array('path' => 'registration/' . $this->internalIdentifier());
  }

  /**
   * Determine registrant type relative to a given account.
   *
   * @object $account
   *   A Drupal user
   *
   * @return string|NULL
   *   Can be me, user, anon or NULL if account is empty and no anon email set.
   */
  public function registrant_type($account) {
    $reg_type = NULL;
    if (!empty($account)) {
      if ($account->uid && $account->uid === $this->user_uid) {
        $reg_type = REGISTRATION_REGISTRANT_TYPE_ME;
      }
      elseif ($this->user_uid) {
        $reg_type = REGISTRATION_REGISTRANT_TYPE_USER;
      }
    }
    if (!empty($this->anon_mail)) {
      $reg_type = REGISTRATION_REGISTRANT_TYPE_ANON;
    }
    return $reg_type;
  }

}

