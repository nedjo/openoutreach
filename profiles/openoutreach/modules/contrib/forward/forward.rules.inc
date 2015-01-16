<?php

/**
 * @file
 * forward.rules.inc
 * Expose the forward of a node event to rules
 */

/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
function forward_rules_event_info() {
  $items = array(
    'node_forward' => array(
      'label' => t('After a node has been forwarded'),
      'group' => t('Node'),
        'variables' => array(
          'user' => array(
            'type' => 'user',
            'label' => t('User who forwarded')),
          'forwarded_node' => array(
            'type' => 'node',
            'label' => t('The node being forwarded')),
        ),
    ),
  );
  return $items;
}