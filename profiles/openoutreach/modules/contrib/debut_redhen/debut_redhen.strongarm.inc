<?php
/**
 * @file
 * debut_redhen.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function debut_redhen_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'redhen_contact_connect_users';
  $strongarm->value = TRUE;
  $export['redhen_contact_connect_users'] = $strongarm;

  return $export;
}
