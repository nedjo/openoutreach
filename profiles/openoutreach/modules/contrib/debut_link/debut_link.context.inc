<?php
/**
 * @file
 * debut_link.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_link_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'link-content-type';
  $context->description = 'Display links vocabulary terms as well as featured block.';
  $context->tag = 'Content types';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'link' => 'link',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'views' => array(
      'values' => array(
        'link:page_1' => 'link:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-link_terms-block' => array(
          'module' => 'views',
          'delta' => 'link_terms-block',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'views-link-block_1' => array(
          'module' => 'views',
          'delta' => 'link-block_1',
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
      ),
    ),
    'breadcrumb' => 'link',
    'menu' => 'link',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('Display links vocabulary terms as well as featured block.');
  $export['link-content-type'] = $context;

  return $export;
}
