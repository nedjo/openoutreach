<?php
/**
 * @file
 * openoutreach_front_page.strongarm.inc
 */

/**
 * Implementation of hook_strongarm().
 */
function openoutreach_front_page_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'home';
  $export['site_frontpage'] = $strongarm;

  return $export;
}
