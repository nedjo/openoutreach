<?php

/**
 * @file
 * Form definition and handling for redhen notes.
 */

/**
 * Return a form array for adding/editing a note.
 *
 * @param $form
 * @param $form_state
 * @param RedhenContact|RedhenOrg $entity
 * @param $entity_type
 * @param stdClass $redhen_note
 *
 * @return array
 */
function redhen_note_form($form, &$form_state, $redhen_note, $entity = NULL) {
  $form_state['redhen_note'] = $redhen_note;
  $form_state['entity'] = $entity;

  field_attach_form('redhen_note', $redhen_note, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Note'),
    '#weight' => 999,
  );
  return $form;
}

/**
 * Validation handler for redhen_note_form().
 */
function redhen_note_form_validate($form, &$form_state) {
  $redhen_note = $form_state['redhen_note'];
  field_attach_form_validate('redhen_note', $redhen_note, $form, $form_state);
}

/**
 * Submit handler for redhen_note_form().
 */
function redhen_note_form_submit($form, &$form_state) {
  $redhen_note = $form_state['redhen_note'];

  if (isset($form_state['entity'])) {
    $entity = $form_state['entity'];
  }
  else {
    $wrapper = entity_metadata_wrapper('redhen_note', $redhen_note);
    $entity = $wrapper->entity->value();
  }

  list($entity_id, ,) = entity_extract_ids($redhen_note->entity_type, $entity);
  $redhen_note->entity_id = $entity_id;

  field_attach_submit('redhen_note', $redhen_note, $form, $form_state);

  if ($redhen_note->save()) {
    $entity_type = $redhen_note->entity_type;
    drupal_set_message(t('The note has been saved.'));
    $uri = entity_uri($entity_type, $entity);
    $form_state['redirect'] = $uri['path'] . "/notes";
  }
  else {
    drupal_set_message(t('There has been an issue saving this note. Please contact the site administrator.'));
    watchdog('redhen_note', 'Issue saving note %note_id.', array('%note_id' => $redhen_note->note_id), WATCHDOG_NOTICE);
  }
}

/**
 * Form callback: confirmation form for deleting an note.
 *
 * @param $note
 *   The ntoe object to be deleted.
 *
 * @see confirm_form()
 */
function redhen_note_delete_form($form, &$form_state, $note) {
  $form_state['redhen_note'] = $note;

  $form['#submit'][] = 'redhen_note_delete_form_submit';

  $title = $note->label();

  $form = confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $title)),
    entity_uri('redhen_note', $note),
    '<p>' . t('Deleting this note cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for redhen_note_delete_form().
 */
function redhen_note_delete_form_submit($form, &$form_state) {
  $note = $form_state['redhen_note'];

  $wrapper = entity_metadata_wrapper('redhen_note', $note);

  $title = entity_label('redhen_note', $note);
  $entity_url = entity_uri($note->entity_type, $wrapper->entity->value());

  // No status returned from delete(), assume it worked
  redhen_note_delete_multiple(array($note->note_id));
  drupal_set_message(t('%title has been deleted.', array('%title' => $title)));
  watchdog('redhen_note', 'Deleted note %title.', array('%title' => $title), WATCHDOG_NOTICE);
  $form_state['redirect'] = $entity_url['path'] . '/notes';
}
