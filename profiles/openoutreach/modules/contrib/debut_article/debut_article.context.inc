<?php
/**
 * @file
 * debut_article.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function debut_article_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'article-content-type';
  $context->description = 'When viewing an article, show contextual information.';
  $context->tag = 'Content types';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'article' => 'article',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-article-block_1' => array(
          'module' => 'views',
          'delta' => 'article-block_1',
          'region' => 'sidebar_second',
          'weight' => 0,
        ),
        'views-article-block_2' => array(
          'module' => 'views',
          'delta' => 'article-block_2',
          'region' => 'sidebar_second',
          'weight' => 1,
        ),
      ),
    ),
    'breadcrumb' => 'article',
    'menu' => 'article',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content types');
  t('When viewing an article, show contextual information.');
  $export['article-content-type'] = $context;

  return $export;
}
