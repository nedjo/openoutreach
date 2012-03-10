<?php

/**
 * @file
 * Media browser plugin for remote stream wrapper URLs.
 */

class RemoteStreamWrapperMediaBrowser extends MediaBrowserPlugin {

  public static function access($account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }
    return user_access('administer files', $account) || user_access('add media from remote urls', $account);
  }

  function view() {
    return array(
      '#title' => t('Remote URL'),
      'form' => drupal_get_form('remote_stream_wrapper_file_add_form', $this->params),
    );
  }

}
