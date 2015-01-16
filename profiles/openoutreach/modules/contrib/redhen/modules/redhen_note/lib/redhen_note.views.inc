<?php

/**
 * RedhenMembership Views Controller class.
 */
class RedhenNoteViewsController extends EntityDefaultViewsController {

  /**
   * Add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    $entity_info = entity_get_info();

    foreach ($entity_info as $entity_type => $info) {
      if ($entity_type == 'redhen_contact' || $entity_type == 'redhen_org') {
        // Entity to note.
        $data[$info['base table']]['redhen_note_rel'] = array(
          'group' => t('Note'),
          'title' => t('@entity to Note',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The Note associated with the @entity entity.',
            array('@entity' => drupal_ucfirst($info['label']))),
          'relationship' => array(
            'entity' => $entity_type,
            'label' => t('@entity being the Note',
              array('@entity' => $entity_type)),
            'base' => 'redhen_note',
            'base field' => 'entity_id',
            'relationship field' => $info['entity keys']['id'],
          ),
        );

        // Note to entity.
        $data['redhen_note']['redhen_note_related_' . $entity_type] = array(
          'group' => t('Note'),
          'title' => t('Note to @entity',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The @entity entity that is associated with the Note.',
            array('@entity' => $info['label'])),
          'relationship' => array(
            'handler' => 'views_handler_relationship',
            'label' => t('@entity from Note',
              array('@entity' => $entity_type)),
            'base' => $info['base table'],
            'base field' => $info['entity keys']['id'],
            'relationship field' => 'entity_id',
          ),
        );
      }
    }

    return $data;
  }
}
