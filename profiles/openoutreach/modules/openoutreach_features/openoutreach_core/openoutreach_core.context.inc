<?php
/**
 * @file
 * openoutreach_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function openoutreach_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'powered-by-openoutreach';
  $context->description = 'Show the powered by Open Outreach block with documentation links.';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'openoutreach-powered-by' => array(
          'module' => 'openoutreach',
          'delta' => 'powered-by',
          'region' => 'footer',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show the powered by Open Outreach block with documentation links.');
  $export['powered-by-openoutreach'] = $context;

  $context = new stdClass();
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
