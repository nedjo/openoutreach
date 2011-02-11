<?php
// $Id: media.inc,v 1.6 2010/10/27 15:29:30 JacobSingh Exp $

/**
 *  @file
 *  Define the WYSIWYG browser plugin.
 */

/**
 * Implementation of WYSIWYG's hook_INCLUDE_plugin().
 */
function media_media_plugin() {
  // Include the required browser JS.
  module_load_include('inc', 'media', 'media.browser');
  media_include_browser_js();

  // Plugin definition
  $plugins['media'] = array(
    'title' => t(media_variable_get('wysiwyg_title')),
    'vendor url' => 'http://drupal.org/project/media',
    'icon path' => drupal_get_path('module','media').'/images/',
    'icon file' => 'wysiwyg-media.gif',
    'icon title' => t(media_variable_get('wysiwyg_icon_title')),
    // @todo: move this to the plugin directory for the wysiwyg plugin.
    'js path' => drupal_get_path('module','media').'/javascript/',
    'js file' => 'wysiwyg-media.js',
    'css file' => NULL,
    'css path' => NULL,
    'settings' => array(
      'global' => array(
        'types' => media_variable_get('wysiwyg_allowed_types'),
        'id' => 'media_wysiwyg',
      ),
    ),
   );

   return $plugins;
}
