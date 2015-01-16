<?php

/**
 * @file
 * Page callbacks for redhen membership.
 */

module_load_include('inc', 'redhen', 'includes/redhen.forms');

/**
 * Page callback for membership overview page.
 */
function redhen_membership_page($entity = NULL, $entity_type = NULL) {

  // setup the header for both the query and table
  $header = array(
    'type' => array(
      'field' => 'type',
      'type' => 'property',
      'data' => 'Type',
      'sort' => 'asc',
      'specifier' => 'type'
    ),
    'Applies to',
    'start_date' => array(
      'field' => 'start_date',
      'type' => 'property',
      'data' => 'Start Date',
      'sort' => 'asc',
      'specifier' => 'start_date'
    ),
    'expire_date' => array(
      'field' => 'expire_date',
      'type' => 'property',
      'data' => 'Expiration Date',
      'sort' => 'asc',
      'specifier' => 'expire_date'
    ),
    'note' => array(
      'field' => 'note',
      'type' => 'property',
      'data' => 'Note',
      'sort' => 'asc',
      'specifier' => 'note'
    ),
    'State',
    'Actions',
  );

  // need to ensure the query doesn't execute when posing the form
  $membership_keys = array();
  $result = FALSE;
  if (!isset($_POST['form_id'])) {
    $bundle = isset($_GET['bundle']) ? $_GET['bundle'] : '';
    $properties = isset($_GET['properties']) ? $_GET['properties'] : array();
    $fields = isset($_GET['fields']) ? $_GET['fields'] : array();
    // If page is for a specific entity, add that entity_type and id to the property filters
    if (isset($entity)) {
      $entity_filter = array(
        'entity_type' => $entity_type,
        'entity_id' => entity_id($entity_type, $entity),
      );
      $properties = array_merge($properties, $entity_filter);
    }
    $result = redhen_filter_query('redhen_membership', $header, $bundle, $properties, $fields);
    if ($result) {
      $membership_keys = array_keys($result['redhen_membership']);
    }
  }

  // If page is for a redhen contact, run a second query for memberships on
  // affiliated organizations
  $org_membership_keys = array();
  $result_org_memberships = NULL;
  if ($entity_type == 'redhen_contact') {
    $entity_ids = array();
    $relations = redhen_relation_relations($entity, REDHEN_RELATION_AFFILIATION);
    foreach ($relations as $relation => $related_entities) {
      foreach ($related_entities as $id => $related_entity) {
        $entity_ids[] = $related_entity->internalIdentifier();
      }
    }
    if ($entity_ids) {
      // Unset previous entity_type and entity_id property values
      unset($properties['entity_type']);
      unset($properties['entity_id']);
      $properties['entity_type'] = 'redhen_org';
      $properties['entity_id'] = $entity_ids;

      $result_org_memberships = redhen_filter_query('redhen_membership', $header, $bundle, $properties, $fields);
      if ($result_org_memberships) {
        $org_membership_keys = array_keys($result_org_memberships['redhen_membership']);
      }
    }
  }

  $memberships = array();
  if ($result || $result_org_memberships) {
    $membership_keys = array_merge($membership_keys, $org_membership_keys);
    $memberships = redhen_membership_load_multiple($membership_keys);
  }

  return array(
    'form' => drupal_get_form('redhen_filter_form', 'redhen_membership'),
    'memberships' => array(
      '#theme' => 'redhen_membership_list',
      '#memberships' => $memberships,
      '#header' => $header
    )
  );
}

/**
 * Return a list of available memberships to add or the add membership page if there's
 * only a single membership type.
 */
function redhen_membership_types_list_page() {
  $item = menu_get_item();

  $types = redhen_membership_get_types();

  // Bypass the rehen_membership/add listing if only one membership type is available.
  if (count($types) == 1) {
    $type = array_shift($types);
    drupal_goto($item['href'] . '/' . $type->name);
  }

  $render = array(
    '#theme' => 'redhen_membership_add_list',
    '#path' => $item['href'],
    '#content' => $types,
  );

  return $render;

}

/**
 * Page callback for adding a membership.
 *
 * @param $type
 *
 * @return array|mixed
 */
function redhen_membership_add_page($type, $entity_type, $entity) {
  $membership = entity_get_controller('redhen_membership')->create(array('type' => $type));
  module_load_include('inc', 'redhen_membership', 'includes/redhen_membership.forms');
  return drupal_get_form('redhen_membership_membership_form', $membership, $entity, $entity_type);
}
