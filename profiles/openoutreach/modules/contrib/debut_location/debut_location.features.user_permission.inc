<?php
/**
 * @file
 * debut_location.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function debut_location_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer openlayers'.
  $permissions['administer openlayers'] = array(
    'name' => 'administer openlayers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'openlayers_ui',
  );

  // Exported permission: 'create location content'.
  $permissions['create location content'] = array(
    'name' => 'create location content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any location content'.
  $permissions['delete any location content'] = array(
    'name' => 'delete any location content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own location content'.
  $permissions['delete own location content'] = array(
    'name' => 'delete own location content',
    'roles' => array(
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any location content'.
  $permissions['edit any location content'] = array(
    'name' => 'edit any location content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own location content'.
  $permissions['edit own location content'] = array(
    'name' => 'edit own location content',
    'roles' => array(
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'geocoder_service_all_handlers'.
  $permissions['geocoder_service_all_handlers'] = array(
    'name' => 'geocoder_service_all_handlers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_exif'.
  $permissions['geocoder_service_handler_exif'] = array(
    'name' => 'geocoder_service_handler_exif',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_google'.
  $permissions['geocoder_service_handler_google'] = array(
    'name' => 'geocoder_service_handler_google',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_gpx'.
  $permissions['geocoder_service_handler_gpx'] = array(
    'name' => 'geocoder_service_handler_gpx',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_json'.
  $permissions['geocoder_service_handler_json'] = array(
    'name' => 'geocoder_service_handler_json',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_kml'.
  $permissions['geocoder_service_handler_kml'] = array(
    'name' => 'geocoder_service_handler_kml',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_wkt'.
  $permissions['geocoder_service_handler_wkt'] = array(
    'name' => 'geocoder_service_handler_wkt',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_yahoo'.
  $permissions['geocoder_service_handler_yahoo'] = array(
    'name' => 'geocoder_service_handler_yahoo',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  // Exported permission: 'geocoder_service_handler_yandex'.
  $permissions['geocoder_service_handler_yandex'] = array(
    'name' => 'geocoder_service_handler_yandex',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'geocoder',
  );

  return $permissions;
}
