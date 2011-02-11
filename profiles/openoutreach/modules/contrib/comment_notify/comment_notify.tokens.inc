<?php
// $Id: comment_notify.tokens.inc,v 1.1 2010/10/11 01:32:06 greggles Exp $

/**
 * @file
 * Builds placeholder replacement tokens for comment_notify.module.
 */

/**
 * Implements hook_token_info().
 */
function comment_notify_token_info() {
  $info['tokens']['comment']['unsubscribe-url'] = array(
    'name' => t('Unsubscribe URL'),
    'description' => t('The URL to disable notifications for the comment.'),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function comment_notify_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'comment' && !empty($data['comment'])) {
    $comment = $data['comment'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'unsubscribe-url':
          module_load_include('inc', 'comment_notify', 'comment_notify');
          if ($hash = comment_notify_get_notify_hash($cid)) {
            $replacements[$original] = url('comment_notify/disable/' . $hash, $url_options);
          }
          break;
      }
    }
  }
}
