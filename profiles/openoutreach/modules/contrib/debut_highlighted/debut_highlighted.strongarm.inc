<?php
/**
 * @file
 * debut_highlighted.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function debut_highlighted_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_highlighted';
  $strongarm->value = 0;
  $export['comment_anonymous_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_highlighted';
  $strongarm->value = 1;
  $export['comment_default_mode_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_highlighted';
  $strongarm->value = '50';
  $export['comment_default_per_page_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_highlighted';
  $strongarm->value = 1;
  $export['comment_form_location_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_highlighted';
  $strongarm->value = '0';
  $export['comment_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_highlighted';
  $strongarm->value = '1';
  $export['comment_preview_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_highlighted';
  $strongarm->value = 1;
  $export['comment_subject_field_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_highlighted';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_highlighted';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_highlighted';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_highlighted';
  $strongarm->value = '1';
  $export['node_preview_highlighted'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_highlighted';
  $strongarm->value = 0;
  $export['node_submitted_highlighted'] = $strongarm;

  return $export;
}
