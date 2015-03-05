<?php
/**
 * @file
 * debut_location.openlayers_styles.inc
 */

/**
 * Implements hook_openlayers_styles().
 */
function debut_location_openlayers_styles() {
  $export = array();

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'location_type';
  $openlayers_styles->title = 'Location type';
  $openlayers_styles->description = 'Location type icon based on taxonomy term.';
  $openlayers_styles->data = array(
    'externalGraphic' => '${uri}',
    'pointRadius' => 12,
    'fillColor' => '#888888',
    'strokeColor' => '#222222',
    'strokeWidth' => 4,
    'fillOpacity' => 0.5,
    'strokeOpacity' => 0.6999999999999999555910790149937383830547332763671875,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicOpacity' => 1,
    'labelAlign' => 'cm',
  );
  $export['location_type'] = $openlayers_styles;

  return $export;
}
