<?php

$plugin = array(
  'title' => t('Forward link'),
  'description' => t('A forward link for this page.'),
  'category' => t('Widgets'),
  'render callback' => 'forward_panels_page_render',
);

function forward_panels_page_render($subtype, $conf, $panel_args) {
  // Build the link
  $widget_code = array(
    '#markup' => theme('forward_link', array()),
  );

  // Build the content type block.
  $block = new stdClass();
  $block->module = 'forward';
  $block->content = $widget_code;

  return $block;
}
