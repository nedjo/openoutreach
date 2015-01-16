<?php
/**
 * @file
 * debut_location.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_location_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'location_map';
  $context->description = 'Display a legend filter on the location map view page.';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'location_map:page' => 'location_map:page',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views--exp-location_map-page' => array(
          'module' => 'views',
          'delta' => '-exp-location_map-page',
          'region' => 'sidebar_second',
          'weight' => '-25',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display a legend filter on the location map view page.');
  $export['location_map'] = $context;

  return $export;
}
