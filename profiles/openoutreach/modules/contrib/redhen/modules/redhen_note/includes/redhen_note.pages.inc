<?php

/**
 * @file
 * Page callbacks for redhen ntoes.
 */

module_load_include('inc', 'redhen', 'includes/redhen.forms');

/*
 * Create new Redhen note object and call note form
 */
function redhen_note_add($entity, $entity_type) {
  $redhen_note = entity_get_controller('redhen_note')->create(array('type' => 'redhen_note'));
  $redhen_note->entity_type = $entity_type;
  module_load_include('inc', 'redhen_note', 'includes/redhen_note.forms');
  return drupal_get_form('redhen_note_form', $redhen_note, $entity);
}

/*
 * Show notes and actions
 */
function redhen_note_notes_page($entity, $entity_type) {
  list($entity_id, ,) = entity_extract_ids($entity_type, $entity);

  $header = array(
    'teaser' => t('Body'),
    'type' => t('Note Type'),
    'author' => t('Author'),
    'updated' => array(
      'field' => 'updated',
      'type' => 'property',
      'data' => t('Updated'),
      'sort' => 'asc',
      'specifier' => 'updated'
    ),
    'created' => array(
      'field' => 'created',
      'type' => 'property',
      'data' => t('Created'),
      'sort' => 'asc',
      'specifier' => 'created'
    ),
  );

  $header['operations'] = array('data' => t('Operations'));

  // need to ensure the query doesn't execute when posing the form
  $result = FALSE;
  if (!isset($_POST['form_id'])) {
    $bundle = '';
    $properties = isset($_GET['properties']) ? $_GET['properties'] : array();
    $properties['entity_id'] = $entity_id;
    $properties['entity_type'] = $entity_type;
    $fields = isset($_GET['fields']) ? $_GET['fields'] : array();
    $result = redhen_filter_query('redhen_note', $header, $bundle, $properties, $fields);
  }

  $rows = array();
  if ($result) {
    $notes = redhen_note_load_multiple(array_keys($result['redhen_note']));
    $destination = drupal_get_destination();
    foreach ($notes as $note) {
      $wrapper = entity_metadata_wrapper('redhen_note', $note);
      $author = $wrapper->author->value();
      $entity = $wrapper->entity->value();
      $uri = entity_uri('redhen_note', $note);

      $teaser = field_view_value('redhen_note', $note, 'redhen_note_body',
        $wrapper->redhen_note_body->value(),
        array(
          'label' => 'hidden',
          'type' => 'text_trimmed',
          'settings' => array('trim_length' => 100)
      ));
      $note_type = NULL;
      if ($note_type_object = $wrapper->redhen_note_type->value()) {
        $note_type = $note_type_object->name;
      }
      $rows[$note->note_id] = array(
        'data' => array(
          'teaser' => render($teaser),
          'type' => $note_type,
          'author' => (isset($author->name)) ? $author->name : '',
          'update' => redhen_format_date($note->updated),
          'created' => redhen_format_date($note->created),
        ),
      );

      // Build a list of all the accessible operations for the current note.
      $ops = array();

      $ops['view'] = array(
        'title' => t('view'),
        'href' => $uri['path'],
        'query' => $destination,
      );

      if (redhen_note_access('update', $entity)) {
        $ops['edit'] = array(
          'title' => t('edit'),
          'href' => $uri['path'] . '/edit',
          'query' => $destination,
        );
      }
      if (redhen_note_access('delete', $entity)) {
        $ops['delete'] = array(
          'title' => t('delete'),
          'href' => $uri['path'] . '/delete',
          'query' => $destination,
        );
      }
      if (count($ops) > 1) {
        // Render an unordered list of operations links.
        $rows[$note->note_id]['data']['operations'] = array(
          'data' => array(
            '#theme' => 'links__node_operations',
            '#links' => $ops,
            '#attributes' => array('class' => array('links', 'inline')),
          ),
        );
      }
      elseif (!empty($ops)) {
        // Render the first and only operation as a link.
        $link = reset($ops);
        $rows[$note->note_id]['data']['operations'] = array(
          'data' => array(
            '#type' => 'link',
            '#title' => $link['title'],
            '#href' => $link['href'],
            '#options' => array('query' => $link['query']),
          ),
        );
      }
      else {
        unset($header['operations']);
      }
    }
  }

  $render = array(
    'form' => drupal_get_form('redhen_filter_form', 'redhen_note'),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('Sorry, there are no notes that match your criteria.'),
    ),
    'pager' => array(
      '#theme' => 'pager'
    )
  );

  return $render;
}
