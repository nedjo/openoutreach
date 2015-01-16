<?php
/**
 * @file
 * debut_social.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_social_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'social-follow-site';
  $context->description = 'Display social media follow links sitewide.';
  $context->tag = 'Social media';
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
        'follow-site' => array(
          'module' => 'follow',
          'delta' => 'site',
          'region' => 'sidebar_second',
          'weight' => '-21',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display social media follow links sitewide.');
  t('Social media');
  $export['social-follow-site'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'social-follow-user';
  $context->description = 'Display social media follow links on user profile pages.';
  $context->tag = 'Social media';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'all',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'follow-user' => array(
          'module' => 'follow',
          'delta' => 'user',
          'region' => 'sidebar_second',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display social media follow links on user profile pages.');
  t('Social media');
  $export['social-follow-user'] = $context;

  return $export;
}
