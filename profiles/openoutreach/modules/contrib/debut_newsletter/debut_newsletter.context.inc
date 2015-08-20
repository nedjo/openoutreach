<?php
/**
 * @file
 * debut_newsletter.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_newsletter_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsletter-content-type';
  $context->description = 'When viewing a newsletter, show contextual information.';
  $context->tag = 'Content types';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'simplenews' => 'simplenews',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'simplenews-0' => array(
          'module' => 'simplenews',
          'delta' => '0',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'views-newsletter-block' => array(
          'module' => 'views',
          'delta' => 'newsletter-block',
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
      ),
    ),
    'breadcrumb' => array(
      0 => 'main-menu:newsletter',
    ),
    'menu' => array(
      0 => 'main-menu:newsletter',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('When viewing a newsletter, show contextual information.');
  $export['newsletter-content-type'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsletter-signup';
  $context->description = 'Sign up block for newsletter';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'newsletter' => 'newsletter',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'simplenews-0' => array(
          'module' => 'simplenews',
          'delta' => '0',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sign up block for newsletter');
  $export['newsletter-signup'] = $context;

  return $export;
}
