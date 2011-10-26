<?php

/**
 * @file
 * Views integration for the debut_media module.
 */

/**
 * Implements hook_views_data().
 */
function debut_media_views_data() {
  // File rendered
  $data['file_managed']['rendered'] = array(
    'title' => t('File'),
    'title_short' => t('File:Rendered'),
    'help' => t('Display the file in a specific view mode.'),
    'field' => array(
      'handler' => 'views_handler_field_file_rendered',
      'click sortable' => TRUE,
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  return $data;
}

