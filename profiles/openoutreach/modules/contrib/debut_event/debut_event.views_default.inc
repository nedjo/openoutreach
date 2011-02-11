<?php

/**
 * Implementation of hook_views_default_views().
 */
function debut_event_views_default_views() {
  $views = array();

  $options = array(
    'name' => 'event_calendar',
    'description' => 'A multi-dimensional event calendar view with back/next navigation.',
    'path' => 'event',
    'types' => array('event'),
    'date_fields' => array('field_event_date'),
  );

  $view = calendar_views_construct($options);
  // Customize the view further.
  $view->human_name = 'Event calendar';
  $view->display['default']->display_options['title'] = 'Event calendar';
  // Use a custom date format type.
  $view->display['default']->display_options['fields']['entity_id']['type'] = 'date_event_time';
  $view->display['default']->display_options['fields']['entity_id']['settings']['format_type'] = 'event_time';
  $view->display['calendar_1']->display_title = 'Event calendar page';
  $view->display['calendar_block_1']->display_title = 'Event calendar block';
  $view->display['calendar_block_1']->display_options['block_description'] = 'Event calendar';
  $view->display['block_1']->display_title = 'Upcoming events';
  $view->display['block_1']->display_options['block_description'] = 'Upcoming events';
  $views[$view->name] = $view;

  $translatables['event_calendar'] = array(
    t('Defaults'),
    t('Event calendar'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('Event calendar page'),
    t('Event calendar block'),
    t('Year view'),
    t('Month view'),
    t('Day view'),
    t('Week view'),
    t('Block view'),
    t('Upcoming events'),
    t('Upcoming'),
  );

  return $views;
}
