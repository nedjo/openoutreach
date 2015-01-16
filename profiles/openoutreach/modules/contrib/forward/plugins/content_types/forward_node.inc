<?php

$plugin = array(
  'title' => t('Forward link'),
  'description' => t('A forward link for this node.'),
  'category' => t('Node'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback' => 'forward_panels_node_render',
);

function forward_panels_node_render($subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  // Get a shortcut to the node.
  $node = $context->data;

  // Build the link
  $widget_code = array(
    '#markup' => theme('forward_link', array('node' => $node)),
  );

  // Build the content type block.
  $block = new stdClass();
  $block->module = 'forward';
  $block->content = $widget_code;
  $block->delta = $node->nid;

  return $block;
}
