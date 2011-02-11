<?php
// $Id: calendar_ical.views.inc,v 1.8 2010/08/04 10:32:08 karens Exp $

/**
 * @file
 * Views handlers for the Calendar iCal module.
 */

//views_include_handlers();
/**
 * Implementation of hook_views_plugins
 */
function calendar_ical_views_plugins() {
  $views_path = drupal_get_path('module', 'views');
  $module_path = drupal_get_path('module', 'calendar_ical');
  module_load_include('inc', 'calendar_ical', 'theme.inc');

  $data = array(
    'module' => 'calendar_ical', // This just tells our themes are elsewhere.
    'display' => array(
      // Parents are not really displays, just needed so the files can
      // be included.
      'parent' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display',
        'path' => "$views_path/plugins",
        'parent' => '',
      ),
      'page' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display_page',
        'path' => "$views_path/plugins",
        'parent' => 'parent',
      ),
      'calendar_ical' => array(
        'title' => t('iCal feed'),
        'help' => t('Display the view as an iCal feed.'),
        'handler' => 'calendar_plugin_display_ical',
        'path' => "$module_path",
        'parent' => 'page',
        'uses hook menu' => TRUE,
        'theme' => 'views_view',
        'no ui' => TRUE,
        'no remove' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('iCal feed'),
        'help topic' => 'display-ical',
      ),
    ),
    'style' => array(
      'parent' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_plugin_style',
        'path' => "$views_path/plugins",
        'parent' => '',
      ),
      'rss' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_plugin_style_rss',
        'path' => "$views_path/plugins",
        'parent' => 'parent',
      ),
      'ical' => array(
        'title' => t('iCal feed'),
        'help' => t('Generates an iCal feed from a view.'),
        'handler' => 'calendar_plugin_style_ical',
        'path' => "$module_path",
        'theme' => 'calendar_view_ical',
        'theme file' => 'theme.inc',
        'theme path' => "$module_path",
        'parent' => 'rss',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'type' => 'ical',
        'even empty' => TRUE,
      ),
    ),
  );
  return $data;
}
