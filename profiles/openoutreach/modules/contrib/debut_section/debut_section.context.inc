<?php
/**
 * @file
 * debut_section.context.inc
 */

/**
 * Implementation of hook_context_default_contexts().
 */
function debut_section_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'section-content-type';
  $context->description = 'Show child pages';
  $context->tag = 'Content types';
  $context->conditions = array(
    'bookroot' => array(
      'values' => array(
        'section' => 'section',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-section_children-block_1' => array(
          'module' => 'views',
          'delta' => 'section_children-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('Show child pages');
  $export['section-content-type'] = $context;

  return $export;
}
