<?php
/**
 * @file
 * debut_social.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function debut_social_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'forward_display_nodes';
  $strongarm->value = 1;
  $export['forward_display_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'forward_display_teasers';
  $strongarm->value = 1;
  $export['forward_display_teasers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'service_links_link_view_modes';
  $strongarm->value = array(
    'full' => 'full',
    'teaser' => 'teaser',
    'rss' => 0,
    'search_index' => 0,
    'search_result' => 0,
    'print' => 0,
    'ical' => 0,
    'token' => 0,
  );
  $export['service_links_link_view_modes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'service_links_show';
  $strongarm->value = array(
    'delicious' => 0,
    'digg' => 0,
    'stumbleupon' => 0,
    'twitter' => 1,
    'pingthis' => 0,
    'propeller' => 0,
    'reddit' => 0,
    'slashdot' => 0,
    'magnoliacom' => 0,
    'newsvine' => 0,
    'furl' => 0,
    'facebook' => 1,
    'myspace' => 0,
    'google' => 0,
    'yahoo' => 0,
    'buzz' => 0,
    'linkedin' => 0,
    'technorati' => 0,
    'technorati_favorite' => 0,
    'icerocket' => 0,
    'misterwong' => 0,
    'google_buzz' => 0,
    'mixx' => 0,
    'box' => 0,
    'blinklist' => 0,
    'identica' => 0,
    'newskicks' => 0,
  );
  $export['service_links_show'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'service_links_weight';
  $strongarm->value = array(
    'delicious' => '-95',
    'digg' => '-94',
    'stumbleupon' => '-77',
    'twitter' => '-99',
    'pingthis' => '-81',
    'propeller' => '-80',
    'reddit' => '-79',
    'slashdot' => '-78',
    'magnoliacom' => '-87',
    'newsvine' => '-82',
    'furl' => '-93',
    'facebook' => '-100',
    'myspace' => '-84',
    'google' => '-92',
    'yahoo' => '-74',
    'buzz' => '-96',
    'linkedin' => '-88',
    'technorati' => '-75',
    'technorati_favorite' => '-76',
    'icerocket' => '-90',
    'misterwong' => '-86',
    'google_buzz' => '-91',
    'mixx' => '-85',
    'box' => '-97',
    'blinklist' => '-98',
    'identica' => '-89',
    'newskicks' => '-83',
  );
  $export['service_links_weight'] = $strongarm;

  return $export;
}
