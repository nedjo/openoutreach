<?php
/**
 * @file
 * debut_forum.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function debut_forum_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'advanced_forum_user_picture_preset';
  $strongarm->value = 'thumbnail';
  $export['advanced_forum_user_picture_preset'] = $strongarm;

  return $export;
}
