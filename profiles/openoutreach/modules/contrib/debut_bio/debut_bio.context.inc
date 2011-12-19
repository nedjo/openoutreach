<?php
/**
 * @file
 * debut_bio.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_bio_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'bio_author';
  $context->description = 'Context to display related author information';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-bio_author-block' => array(
          'module' => 'views',
          'delta' => 'bio_author-block',
          'region' => 'sidebar_second',
          'weight' => '-19',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context to display related author information');
  $export['bio_author'] = $context;

  return $export;
}
