<?php
/**
 * @file
 * Redhen Group entity classes
 */

/**
 * The class used for group entities.
 */
class RedhenMembership extends Entity {

  public
    $note = '',
    $name = '',
    $entity_type,
    $entity_id,
    $membership_id = NULL,
    $author_uid = NULL,
    $start_date = NULL,
    $expire_date = NULL,
    $membership_state = REDHEN_MEMBERSHIP_ACTIVE,
    $type = '',
    $created = '',
    $updated = '';

  public function __construct(array $values = array()) {
    global $user;

    parent::__construct($values, 'redhen_membership');

    // New membership. is_new might not be set so check for id
    if (!$this->membership_id) {
      $this->author_uid = $user->uid;
      $this->membership_state = REDHEN_MEMBERSHIP_ACTIVE;
      $this->created = REQUEST_TIME;
    }

  }

  /**
   * Override buildContent() to add contact properties.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {

    $wrapper = entity_metadata_wrapper('redhen_membership', $this);
    $entity = $wrapper->entity->value();
    
    $entity_uri = entity_uri($entity->entityType(), $entity);
    $content['entity'] = array(
      '#theme' => 'redhen_property_field',
      '#label' => t('Applies to'),
      '#items' => array(
        array(
          '#markup' => l(entity_label($entity->entityType(), $entity), $entity_uri['path'])
        ),
      ),
      '#classes' => 'field field-label-inline clearfix',
    );
    if ($this->note != '') {
      $content['note'] = array(
        '#theme' => 'redhen_property_field',
        '#label' => t('Note'),
        '#items' => array(
          array(
            '#markup' => check_plain($this->note)
          ),
        ),
        '#classes' => 'field field-label-inline clearfix',
      );
    }

    if ($this->start_date) {
      $content['start_date'] = array(
        '#theme' => 'redhen_property_field',
        '#label' => t('Start Date'),
        '#items' => array(
          array(
            '#markup' => date('m/d/Y', $this->start_date)
          ),
        ),
        '#classes' => 'field field-label-inline clearfix',
      );
    }
    if ($this->expire_date) {
      $content['expire_date'] = array(
        '#theme' => 'redhen_property_field',
        '#label' => t('Expiration Date'),
        '#items' => array(
          array(
            '#markup' => date('m/d/Y', $this->expire_date)
          ),
        ),
        '#classes' => 'field field-label-inline clearfix',
      );
    }

    $membership_states = redhen_membership_state_options();
    $content['membership_state'] = array(
      '#theme' => 'redhen_property_field',
      '#label' => t('State'),
      '#items' => array(
        array(
          '#markup' => $membership_states[$this->membership_state],
        ),
      ),
      '#classes' => 'field field-label-inline clearfix',
    );

    return entity_get_controller($this->entityType)
      ->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Set the redhen_state for a membership
   *
   * @param $state
   *  The REDHEN_STATE_* value to use
   */
  public function setState($state) {
    $this->membership_state = $state;
    $this->save();
  }

  /**
   * Override label() to add membership label.
   */
  public function defaultLabel() {
    $type = redhen_membership_get_types($this->type);
    $wrapper = entity_metadata_wrapper('redhen_membership', $this);
    $entity = $wrapper->entity->value();
    if ($entity) {
      return t('@type membership for @title', array(
        '@type' => entity_label('redhen_membership_type', $type),
        '@title' => entity_label($wrapper->entity_type->value(), $entity),
        ));
    }
  }

  /**
   * Specifify URI
   */
  protected function defaultUri() {
    $wrapper = entity_metadata_wrapper('redhen_membership', $this);
    $entity = $wrapper->entity->value();
    $entity_uri = entity_uri($this->entity_type, $entity);
    return array('path' => $entity_uri['path'] . '/membership/' . $this->identifier());
  }

}


