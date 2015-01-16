<?php

/**
 * @file
 * Form definition and handling for redhen relations.
 */

/**
 * Return a form array for adding/editing a connection.
 *
 * @param $form
 * @param $form_state
 * @param RedhenContact|RedhenOrg $entity
 * @param stdClass $relation
 *
 * @return array
 */
function redhen_relation_connection_form($form, &$form_state, $entity) {
  $relation_types = redhen_relation_get_available_types($entity->entityType(), $entity->bundle(), 'both');

  // there are no valid relation types for this entity, so exit w/message.
  if (empty($relation_types)) {
    $form['message'] = array(
      '#markup' => t('%label has no valid relation types so a connection cannot be made.', array('%label' => $entity->label()))
    );
    return $form;
  }

  // instantiate new relation based on default or submitted relation type
  $relation_type = isset($form_state['values']['relation_type']) ?
    $form_state['values']['relation_type'] :
    reset($relation_types)->relation_type;
  $relation = relation_create($relation_type, array());

  // store contact and relation entities for use on submit
  $form_state['entity'] = $entity;
  $form_state['relation'] = $relation;

  // load all available relation types
  $options = array();
  foreach ($relation_types as $type) {
    list($endpoint_entity_type) = explode(':', $type->source_bundles[0]);
    $reverse = $type->directional & ($endpoint_entity_type == $entity->entityType());

    $options[$type->relation_type] = relation_get_type_label($type, $reverse);
  }
  $form['relation_type'] = array(
    '#title' => t('Connection type'),
    '#type' => 'select',
    '#options' => $options,
    '#default value' => isset($relation) ? $relation->relation_type : NULL,
    '#ajax' => array(
      'callback' => 'redhen_relation_relation_type_callback',
      'wrapper' => 'redhen_relation_fields',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array(
        'type' => 'throbber',
        'message' => t('Retrieving fields for this connection type.')
      )
    ),
    '#description' => t('Connections are only allowed between contacts and organizations.')
  );

  // determine the entity type we're going to relate to
  $active_relation_type = $relation_types[$relation_type];
  $entity_type_to_relate = '';
  if (!empty($active_relation_type->target_bundles)) {
    list($tgt_entity_type) = explode(':', $active_relation_type->target_bundles[0]);
    if ($entity->entityType() != $tgt_entity_type) {
      $entity_type_to_relate = $tgt_entity_type;
    }
  }

  if (empty($entity_type_to_relate)) {
    list($entity_type_to_relate) = explode(':', $active_relation_type->source_bundles[0]);
  }

  $form_state['entity_to_relate_type'] = $entity_type_to_relate;

  $form['fields'] = array(
    '#type' => 'fieldset',
    '#id' => 'redhen_relation_fields'
  );

  $info = entity_get_info($entity_type_to_relate);
  $plural_label = isset($info['plural label']) ? $info['plural label'] : $info['label'] . 's';
  $form['fields']['entity_to_relate'] = array(
    '#title' => $plural_label,
    '#type' => 'textfield',
    '#required' => ($active_relation_type->min_arity == 1) ? FALSE : TRUE,
    '#access' => ($active_relation_type->max_arity == 1) ? FALSE : TRUE,
    '#autocomplete_path' => 'redhen/relation/autocomplete/' . $relation->relation_type . '/' . $entity_type_to_relate . '/' . $entity->entityType() . '/' . $entity->internalIdentifier(),
  );

  // attach any fields
  field_attach_form('relation', $relation, $form['fields'], $form_state);

  // hide the endpoints field widget. @TODO: Find out why appearing.
  $form['fields']['endpoints']['#access'] = FALSE;

  $form['fields']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save connection'),
    '#weight' => 999,
  );

  return $form;
}

/**
 * AJAX callback to return fields for a given relation type.
 */
function redhen_relation_relation_type_callback($form, $form_state) {
  return $form['fields'];
}

/**
 * Validation handler for redhen_relation_connection_form().
 */
function redhen_relation_connection_form_validate($form, &$form_state) {
  // only validate if a entity to relate has been selected
  if (isset($form_state['values']['entity_to_relate'])) {
    $entity = $form_state['entity'];
    $relation = $form_state['relation'];

    // Load the relation information, to determine arity.
    $relation_type = relation_type_load($form_state['values']['relation_type']);

    // parse out the entity id from the autocomplete string
    preg_match('/(.+) \((\d+)\)$/', $form_state['values']['entity_to_relate'], $matches);

    if (isset($matches[2]) && ($matches[2] > 0)) {
      list($src_relation_entity_type) = explode(":", $relation_type->source_bundles[0]);

      // ensure source/target order are correct
      if ($relation_type->directional && $form_state['entity_to_relate_type'] == $src_relation_entity_type) {
        $endpoints = array(
          array(
            'entity_type' => $form_state['entity_to_relate_type'],
            'entity_id' => $matches[2]
          ),
          array(
            'entity_type' => $entity->entityType(),
            'entity_id' => $entity->internalIdentifier()
          )
        );
      }
      else {
        $endpoints = array(
          array(
            'entity_type' => $entity->entityType(),
            'entity_id' => $entity->internalIdentifier()
          ),
          array(
            'entity_type' => $form_state['entity_to_relate_type'],
            'entity_id' => $matches[2]
          )
        );
      }

      $form_state['values']['endpoints'][LANGUAGE_NONE] = $endpoints;
    }
    else if ($relation_type->min_arity == 1 && empty($form_state['values']['entity_to_relate'])) {
      $endpoints = array(
        array(
          'entity_type' => $entity->entityType(),
          'entity_id' => $entity->internalIdentifier()
        )
      );
      $form_state['values']['endpoints'][LANGUAGE_NONE] = $endpoints;
    }
    else {
      form_set_error('entity_to_relate', 'Invalid connection.');
    }

    // set the relation type based on selected value before validating
    $relation->relation_type = $form_state['values']['relation_type'];

    field_attach_form_validate('relation', $relation, $form, $form_state);
  }
}

/**
 * Submit handler for redhen_relation_connection_form().
 */
function redhen_relation_connection_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  $relation = $form_state['relation'];

  $relation->relation_type = $form_state['values']['relation_type'];

  field_attach_submit('relation', $relation, $form, $form_state);
  if (relation_save($relation)) {
    drupal_set_message(t('The connection has been saved.'));
    $uri = entity_uri($entity->entityType(), $entity);
    $form_state['redirect'] = $uri['path'] . "/connections";
  }
  else {
    drupal_set_message(t('The connection could not be saved.'), 'error');
  }
}
