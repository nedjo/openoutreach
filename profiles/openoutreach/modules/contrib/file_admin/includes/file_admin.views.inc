<?php

/**
 * Implements hook_views_data_alter().
 *
 * Add custom fields to file_managed table. Adapted from node.views.inc.
 */
function file_admin_views_data_alter(&$data) {

  // created field
  $data['file_managed']['created'] = array(
    'title' => t('Post date'), // The item it appears as on the UI,
    'help' => t('The date the file was posted.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // published status
  $data['file_managed']['published'] = array(
    'title' => t('Published'),
    'help' => t('Whether or not the media content is published.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'published-notpublished' => array(t('Published'), t('Not published')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Published'),
      'type' => 'yes-no',
      'use equal' => TRUE, // Use published = 1 instead of published <> 0 in WHERE statment
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // published status + extra
  $data['file_managed']['status_extra'] = array(
    'title' => t('Published or admin'),
    'help' => t('Filters out unpublished media content if the current user cannot view it.'),
    'filter' => array(
      'field' => 'published',
      'handler' => 'views_handler_filter_file_admin',
      'label' => t('Published or admin'),
    ),
  );

  // promote status
  $data['file_managed']['promote'] = array(
    'title' => t('Promoted to front page'),
    'help' => t('Whether or not the media content is promoted to the front page.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Promoted to front page'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // sticky
  $data['file_managed']['sticky'] = array(
    'title' => t('Sticky'), // The item it appears as on the UI,
    'help' => t('Whether or not the media content is sticky.'), // The help that appears on the UI,
     // Information for displaying a title as a field
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'sticky' => array('', t('Sticky')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Sticky'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      'help' => t('Whether or not the media content is sticky. To list sticky content first, set this to descending.'),
    ),
  );
}

/**
 * Implements hook_views_query_substitutions().
 */
function file_admin_views_query_substitutions() {
  return array(
    '***BYPASS_FILE_ACCESS***' => intval(user_access('bypass file access')),
    '***VIEW_OWN_UNPUBLISHED_FILES***' => intval(user_access('view own unpublished files')),
  );
}
