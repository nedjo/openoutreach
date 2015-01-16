<?php
/**
 * @file
 * debut_event.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_event_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'calendar-legend';
  $context->description = 'Display legend on calendar view displays.';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'event' => 'event',
        'event/month' => 'event/month',
        'event/month*' => 'event/month*',
        'event/month/*' => 'event/month/*',
        'event/week' => 'event/week',
        'event/week*' => 'event/week*',
        'event/week/*' => 'event/week/*',
        'event/day' => 'event/day',
        'event/day*' => 'event/day*',
        'event/day/*' => 'event/day/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'calendar-calendar_legend' => array(
          'module' => 'calendar',
          'delta' => 'calendar_legend',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display legend on calendar view displays.');
  $export['calendar-legend'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'event-content-type';
  $context->description = 'When viewing an event, display upcoming event block.';
  $context->tag = 'Content types';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-event_calendar-block_2' => array(
          'module' => 'views',
          'delta' => 'event_calendar-block_2',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
    'breadcrumb' => 'event',
    'menu' => 'event',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('When viewing an event, display upcoming event block.');
  $export['event-content-type'] = $context;

  return $export;
}
