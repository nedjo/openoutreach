<?php
/**
 * @file
 * debut_member.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_member_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'member-page-content-type';
  $context->description = 'When viewing a member page, show contextual information.';
  $context->tag = 'Content types';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'member' => 'member_page',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-member_page-block_1' => array(
          'module' => 'views',
          'delta' => 'member_page-block_1',
          'region' => 'sidebar_second',
          'weight' => 0,
        ),
        'views-member-block_2' => array(
          'module' => 'views',
          'delta' => 'member_page-block_2',
          'region' => 'sidebar_second',
          'weight' => 1,
        ),
      ),
    ),
    'breadcrumb' => 'member-page',
    'menu' => 'member-page',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('When viewing a member page, show contextual information.');
  $export['member-page-content-type'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'members_only';
  $context->description = 'Display the members-only menu.';
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
        'menu-menu-member' => array(
          'module' => 'menu',
          'delta' => 'menu-member',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display the members-only menu.');
  $export['members_only'] = $context;

  return $export;
}
