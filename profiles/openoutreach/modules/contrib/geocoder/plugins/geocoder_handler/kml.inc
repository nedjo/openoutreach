<?php
// $Id$

/**
 * @file
 * Plugin to provide a kml geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("KML"),
  'description' => t('Get the geometry out of a KML string, file, or URL'),
  'callback' => 'geocoder_kml',
  'field_types' => array('text', 'text_long', 'file', 'computed'),
  'field_callback' => 'geocoder_kml_field',
);

/**
 * Process Markup
 */
function geocoder_kml($kml_string, $options = array()) {
  geophp_load();
  return geoPHP::load($kml_string, 'kml');
}

function geocoder_kml_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'computed') {
    return geocoder_kml($field_item['value']);
  }
  if ($field['type'] == 'file') {
    if ($field_item['fid']) {
      $file = file_load($field_item['fid']);
      $kml = file_get_contents($file->uri);
      return geocoder_kml($kml);
    }
  }
}
