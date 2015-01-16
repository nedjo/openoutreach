<?php

/**
 * @file
 * Support for migration into Geofield fields
 *
 * Based on addressfield.migrate.inc
 * in the Address Field module.
 *
 */

/**
 * Implements hook_migrate_api().
 */
function geofield_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array('MigrateGeofieldFieldHandler'),
  );
  return $api;
}

/**
 * Primary value passed to this field must be the Geometry type string.
 *
 * Arguments are used to specify all the other values.
 *
 * Add the source field mappings to the argument array then add null mappings to
 * avoid having fields flagged as as unmapped:
 * @code
 *
 *   $this->addFieldMapping('field_geofield','foo');
 *   $this->addFieldMapping('field_geofield:wkt', 'wkt');
 *   $this->addFieldMapping('field_geofield:lat', 'lat');
 *   $this->addFieldMapping('field_geofield:lon', 'lon');
 * @endcode
 */
class MigrateGeofieldFieldHandler extends MigrateFieldHandler {

  public function __construct() {
    $this->registerTypes(array('geofield'));
  }

  /**
   * Implementation of MigrateFieldHandler::fields().
   *
   * @param $type
   *  The field type.
   * @param $instance
   *  Instance info for the field.
   * @param Migration $migration
   *  The migration context for the parent field. We can look at the mappings
   *  and determine which subfields are relevant.
   * @return array
   */
  public function fields($type, $instance, $migration = NULL) {
    return array(
      'input_format' => t('Subfield: Input Format'),
      'wkt' => t('Subfield: WKT'),
      'json' => t('Subfield: GeoJSON'),
      'lat' => t('Subfield: Lat'),
      'lon' => t('Subfield: Lon'),
      'left' => t('Subfield: Left'),
      'top' => t('Subfield: Top'),
      'right' => t('Subfield: Right'),
      'bottom' => t('Subfield: Bottom'),
    );
  }

  /**
   * Implements MigrateFieldHandler::prepare().
   *
   * @param $entity
   * @param array $field_info
   * @param array $instance
   * @param array $values
   *
   * @return null
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Setup a Field API array for saving.
    // Use https://drupal.org/node/1854188 as a guide for geoPHP field type
    $delta = 0;
    foreach ($values as $value) {
      $input_format = $arguments['input_format'];
      if (isset($input_format)) {
        $return[$language][$delta]['input_format'] = $arguments['input_format'];
        switch ($input_format) {
          case 'wkt':
            // wkt - Well known text - array of WKT data
            $return[$language][$delta]['geom'] = $value;
            break;
          case 'json':
            // json - GeoJSON - requires array of JSON data
            $return[$language][$delta]['geom'] = $value;
            break;
          case 'lat/lon':
            // lat/lon - Lat/Long - requires array of lat and lon source fields
            $return[$language][$delta]['lat'] = $arguments['lat'];
            $return[$language][$delta]['lon'] = $arguments['lon'];
            break;
          case 'bounds':
            // bounds - delimited area marked by an array of
            //   left (lon), top (lat), right (long), bottom (lat) values
            $return[$language][$delta]['left'] = $arguments['left'];
            $return[$language][$delta]['top'] = $arguments['top'];
            $return[$language][$delta]['right'] = $arguments['right'];
            $return[$language][$delta]['bottom'] = $arguments['bottom'];
            break;
        }
      }
      else {
        // if no input format specified the $value is assumed to represent a
        // a WKT value or another format that can be parsed by geoPHP.
        $return[$language][$delta]['geom'] = $value;
      }
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }

  /**
   * Builds an array with additional data for the current $delta.
   *
   * @param  array $arguments
   * @param  array $field_info
   * @param  $delta
   *
   * @return array
   */
  protected function prepareArguments(array $arguments, array $field_info, $delta) {
    $result = array();

    foreach ($arguments as $column_key => $column_value) {
      $value = NULL;

      if (is_array($arguments[$column_key])) {
        if (!empty($arguments[$column_key][$delta])) {
          $value = $arguments[$column_key][$delta];
        }
      }
      else {
        $value = $arguments[$column_key];
      }

      if ($value && isset($field_info['columns'][$column_key])) {
        $result[$column_key] = $value;
      }
    }

    return $result;
  }

}

