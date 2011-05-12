<?php
/**
 * @file
 * debut_media.context.inc
 */

/**
 * Implementation of hook_context_default_contexts().
 */
function debut_media_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'media';
  $context->description = 'Display sidebar block and set breadcrumb.';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'media/*' => 'media/*',
        '~media/images' => '~media/images',
        '~media/video' => '~media/video',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'media',
    'menu' => 'media',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display sidebar block and set breadcrumb.');
  $export['media'] = $context;

  return $export;
}
