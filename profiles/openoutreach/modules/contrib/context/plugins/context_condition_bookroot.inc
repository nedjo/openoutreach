<?php
// $Id: context_condition_bookroot.inc,v 1.1.2.2.2.1 2010/09/14 19:11:28 yhahn Exp $

/**
 * Set the context on the basis of the node type of page's book root.
 */
class context_condition_bookroot extends context_condition_node {
  function execute($node, $op) {
    if ($this->condition_used() && !empty($node->book['bid'])) {
      $type = db_select('node')
        ->fields('node', array('type'))
        ->condition('nid', $node->book['nid'])
        ->execute()
        ->fetchField();
      $book = new stdClass();
      $book->type = $type;
      parent::execute($book, $op);
    }
  }
}
