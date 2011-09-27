<?php

/**
 *  @file
 *  Create a Vimeo Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $vimeo = new ResourceVimeoStreamWrapper('vimeo://?v=[video-code]');
 */
class MediaVimeoStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://vimeo.com/';

  function getTarget($f) {
    return FALSE;
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/vimeo';
  }

  function getOriginalThumbnailPath() {
    $video_properties = array();

    $parts = $this->get_parameters();
    $video_properties = $this->getVideoProperties(check_plain($parts['v']));

    return $video_properties[0]['thumbnail_large'];
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = 'public://media-vimeo/' . check_plain($parts['v']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      @copy($this->getOriginalThumbnailPath(), $local_path);
    }
    return $local_path;
  }
  
  /**
   *  Ref: http://vimeo.com/api/docs/simple-api
   *  Example of Vimeo simple API 2 request for video properties:
   *  http://vimeo.com/api/v2/video/xxx.php
   *  This request returns a serialized array.
   */
  function getVideoProperties($video_id) {
    $response = drupal_http_request($this->base_url . '/api/v2/video/'. $video_id .'.php');
    return unserialize($response->data);
  }
}
