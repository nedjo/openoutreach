<?php
// $Id: media_youtube.styles.inc,v 1.1.2.6 2011/01/11 19:37:33 aaron Exp $

/**
 * @file media_youtube/includes/media_youtube.styles.inc
 * Styles definitions for Media: YouTube.
 */

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_youtube_styles_default_containers() {
  // We append YouTube to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_youtube' => array(
          'class' => 'MediaYouTubeStyles',
          'name' => 'media_youtube',
          'label' => t('YouTube'),
          'preview' => 'media_youtube_preview_style',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_youtube_styles_default_presets() {
  return array(
    'file' => array(
      'containers' => array(
        'media_youtube' => array(
          'default preset' => 'linked_thumbnail',
          'styles' => array(
            'original' => array(
              'default preset' => 'video',
            ),
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'linked_medium',
            ),
            'large' => array(
              'default preset' => 'large_video',
            ),
          ),
          'presets' => array(
            'unlinked_thumbnail' => array(
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_thumbnail' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_square_thumbnail' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'image_style',
                'settings' => array(
                  'image_style' => 'square_thumbnail',
                ),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_medium' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'image_style',
                'settings' => array(
                  'image_style' => 'medium',
                ),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'video' => array(
              array(
                'name' => 'video',
                'settings' => array(),
              ),
            ),
            'large_video' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 480,
                  'height' => 360,
                ),
              ),
              array(
                'name' => 'video',
                'settings' => array(),
              ),
            ),
          ),
        ),
      ),
    ),
  );
}

class MediaYouTubeStyles extends FileStyles {
  public $autoplay;
  public $fullscreen;

  function get_autoplay() {
    return $this->get('autoplay');
  }
  function set_autoplay($value) {
    return $this->set('autoplay', $value);
  }
  function get_fullscreen() {
    return $this->get('fullscreen');
  }
  function set_fullscreen($value) {
    return $this->set('fullscreen', $value);
  }

  function get_image_uri() {
    if ($image_uri = $this->get('image_uri')) {
      return $image_uri;
    }
    $object = $this->get_object();
    if ($object->uri) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($object->uri);
      return $wrapper->getLocalThumbnailPath();
    }
  }
  function video($effect) {
    $variables = array(
      'uri' => $this->get_uri(),
      'width' => $this->get_width(),
      'height' => $this->get_height(),
      'autoplay' => $this->get_autoplay(),
      'fullscreen' => $this->get_fullscreen(),
    );
    $this->set_output(theme('media_youtube_video', $variables));
  }
}
