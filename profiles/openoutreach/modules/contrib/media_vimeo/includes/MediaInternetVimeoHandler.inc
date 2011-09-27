<?php

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetVimeoHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $patterns = array(
      '@vimeo\.com/([^"\& ]+)@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1])  && is_numeric($matches[1])) {
        return file_stream_wrapper_uri_normalize('vimeo://v/' . $matches[1]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function save() {
    $file = $this->getFileObject();
    file_save($file);
    return $file;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    //@todo: this is terribly broken in some ways because the function is really
    // made for local files which are 'real'
    return file_uri_to_object($uri);
  }

  /**
   * Returns information about the media. See http://video.search.yahoo.com/mrss.
   *
   * @return
   *   If ATOM+MRSS information is available, a SimpleXML element containing
   *   ATOM and MRSS elements, as per those respective specifications.
   *
   * @todo Would be better for the return value to be an array rather than a
   *   SimpleXML element, but media_retrieve_xml() needs to be upgraded to
   *   handle namespaces first.
   */
  public function getMRSS() {
    $uri = $this->parse($this->embedCode);
    $video_id = arg(1, file_uri_target($uri));
    $rss_url = url('http://gdata.vimeo.com/feeds/api/videos/' . $video_id, array('query' => array('v' => '2')));
    // @todo Use media_retrieve_xml() once it's upgraded to include elements
    //   from all namespaces, not just the document default namespace.
    $entry = simplexml_load_file($rss_url);
    return $entry;
  }

  /**
   * Returns information about the media. See http://www.oembed.com/.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   */
  public function getOEmbed() {
    $uri = $this->parse($this->embedCode);
    $external_url = drupal_realpath($uri);
    $oembed_url = url('http://www.vimeo.com/oembed', array('query' => array('url' => $external_url, 'format' => 'json')));
    $response = drupal_http_request($oembed_url);
    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
  }
}
