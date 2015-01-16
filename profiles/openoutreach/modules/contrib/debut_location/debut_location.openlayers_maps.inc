<?php
/**
 * @file
 * debut_location.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function debut_location_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'location_map';
  $openlayers_maps->title = 'Location map';
  $openlayers_maps->description = 'A map of locations.';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '600px',
    'image_path' => '',
    'css_path' => '',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => '0',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
        'div' => '',
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'location_map_data_openlayers_1' => 'location_map_data_openlayers_1',
          'location_region_data_openlayers_1' => 0,
        ),
        'panMapIfOutOfView' => 0,
        'keepInMap' => 1,
        'zoomToPoint' => 0,
        'zoomToCluster' => 0,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'location_region_data_openlayers_1' => 'location_region_data_openlayers_1',
          'mapquest_osm' => 0,
          'location_map_data_openlayers_1' => 0,
        ),
        'point_zoom_level' => '5',
        'zoomtolayer_scale' => '1',
      ),
      'openlayers_behavior_cluster' => array(
        'clusterlayer' => array(
          'location_map_data_openlayers_1' => 'location_map_data_openlayers_1',
          'location_region_data_openlayers_1' => 0,
        ),
        'distance' => '20',
        'threshold' => '2',
        'display_cluster_numbers' => 1,
        'middle_lower_bound' => '15',
        'middle_upper_bound' => '50',
        'low_color' => 'rgb(141, 203, 61)',
        'low_stroke_color' => 'rgb(141, 203, 61)',
        'low_opacity' => '0.8',
        'low_point_radius' => '10',
        'low_label_outline' => '1',
        'middle_color' => 'rgb(49, 190, 145)',
        'middle_stroke_color' => 'rgb(49, 190, 145)',
        'middle_opacity' => '0.8',
        'middle_point_radius' => '16',
        'middle_label_outline' => '1',
        'high_color' => 'rgb(35, 59, 177)',
        'high_stroke_color' => 'rgb(35, 59, 177)',
        'high_opacity' => '0.8',
        'high_point_radius' => '22',
        'high_label_outline' => '1',
        'label_low_color' => '#000000',
        'label_low_opacity' => '0.8',
        'label_middle_color' => '#000000',
        'label_middle_opacity' => '0.8',
        'label_high_color' => '#000000',
        'label_high_opacity' => '0.8',
      ),
      'openlayers_behavior_fullscreen' => array(
        'activated' => 0,
      ),
      'openlayers_behavior_scaleline' => array(),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'location_map_data_openlayers_1' => 'location_map_data_openlayers_1',
      'location_region_data_openlayers_1' => 'location_region_data_openlayers_1',
    ),
    'layer_weight' => array(
      'location_map_data_openlayers_1' => '0',
      'location_region_data_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => '0',
      'location_region_data_openlayers_1' => 'invisible',
      'location_map_data_openlayers_1' => 'location_type',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => '0',
      'location_region_data_openlayers_1' => 'invisible',
      'location_map_data_openlayers_1' => 'location_type',
    ),
    'layer_styles_temporary' => array(
      'geofield_formatter' => '0',
      'openlayers_kml_example' => '0',
      'openlayers_geojson_picture_this' => '0',
      'location_region_data_openlayers_1' => '0',
      'location_map_data_openlayers_1' => '0',
    ),
    'layer_activated' => array(
      'location_region_data_openlayers_1' => 'location_region_data_openlayers_1',
      'location_map_data_openlayers_1' => 'location_map_data_openlayers_1',
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_kml_example' => 0,
      'openlayers_geojson_picture_this' => 0,
      'location_map_data_openlayers_1' => 0,
      'location_region_data_openlayers_1' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['location_map'] = $openlayers_maps;

  return $export;
}
