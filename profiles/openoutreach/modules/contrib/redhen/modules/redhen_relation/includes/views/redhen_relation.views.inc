<?php

/**
 * @file
 * RedHen Relation Views integration
 */

/**
 * Implement hook_views_data_alter().
 *
 */
function redhen_relation_views_data_alter(&$data) {

  $data['relation']['redhen_relation_primary_contact'] = array(
    'group' => t('Relation'),
    'title' => t('Is primary contact'),
    'help' => t('Boolean value of if a contact is the primary contact.'),
    'field' => array(
      'handler' => 'redhen_relation_handler_field_primary_contact',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'redhen_relation_handler_sort_primary_contact',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
  );

}
