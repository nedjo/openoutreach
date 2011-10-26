<?php
/**
 * @file
 * openoutreach.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function openoutreach_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'shortcut';
  $context->description = 'Display the shortcuts block in a sidebar.';
  $context->tag = '';
  $context->conditions = array(
    'user' => array(
      'values' => array(
        'contributor' => 'contributor',
        'editor' => 'editor',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'shortcut-shortcuts' => array(
          'module' => 'shortcut',
          'delta' => 'shortcuts',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display the shortcuts block in a sidebar.');
  $export['shortcut'] = $context;

  return $export;
}
