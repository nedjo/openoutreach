<?php
/**
 * @file
 * Redhen Group entity classes
 */

/**
 * The class used for note entities.
 */
class RedhenNote extends Entity {

  public
    $note_id = NULL,
    $author_uid = NULL,
    $type = '',
    $created = '',
    $updated = '';

  public function __construct(array $values = array()) {
    parent::__construct($values, 'redhen_note');

    // New note. is_new might not be set so check for id
    if (!$this->note_id) {
      global $user;
      $this->created = REQUEST_TIME;
      $this->author_uid = $user->uid;
    }
  }

  /**
   * Override buildContent() to add note properties.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {

    $wrapper = entity_metadata_wrapper('redhen_note', $this);
    $author = $wrapper->author->value();

    $content['author'] = array(
      '#theme' => 'redhen_property_field',
      '#label' => t('Author'),
      '#items' => array(
        array(
          '#markup' => $author->name,
        ),
      ),
      '#classes' => 'field field-label-inline clearfix',
    );

    $content['created'] = array(
      '#theme' => 'redhen_property_field',
      '#label' => t('Created'),
      '#items' => array(
        array(
          '#markup' => redhen_format_date($this->created),
        ),
      ),
      '#classes' => 'field field-label-inline clearfix',
    );

    return entity_get_controller($this->entityType)
      ->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Override label() to add note label.
   */
  public function label() {
    $wrapper = entity_metadata_wrapper('redhen_note', $this);
    $entity = $wrapper->entity->value();
    // Don't sanitize here as this function should produce unsanitized output.
    return t('Note !id on !label', array('!id' => $this->note_id, '!label' => entity_label($wrapper->entity_type->value(), $wrapper->entity)));
  }

  /**
   * Permanently saves the entity.
   *
   * @return bool
   *  Returns FALSE if entity was not saved.
   */
  public function save() {
    $this->updated = REQUEST_TIME;
    return parent::save();
  }

  /**
   * Specifify URI
   */
  protected function defaultUri() {
    switch ($this->entity_type) {
      case 'redhen_contact':
        $path = 'contact';
        break;
      case 'redhen_org':
        $path = 'org';
        break;
    }
    return array('path' => 'redhen/' . $path . '/' . $this->entity_id . '/note/' . $this->note_id . '/view');
  }


}


