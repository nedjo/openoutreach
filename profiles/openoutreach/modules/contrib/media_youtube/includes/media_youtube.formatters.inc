<?php

/**
 * @file
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_youtube_file_formatter_info() {
  $formatters['media_youtube_video'] = array(
    'label' => t('YouTube Video'),
    'file types' => array('video'),
    'default settings' => array(),
    'view callback' => 'media_youtube_file_formatter_video_view',
    'settings callback' => 'media_youtube_file_formatter_video_settings',
  );
  foreach (array('width', 'height', 'autoplay', 'related', 'hd', 'showsearch', 'modestbranding', 'showinfo', 'version', 'theme', 'fullscreen', 'wmode', 'chromeless') as $setting) {
    $formatters['media_youtube_video']['default settings'][$setting] = media_youtube_variable_get($setting);
  }
  $formatters['media_youtube_image'] = array(
    'label' => t('YouTube Preview Image'),
    'file types' => array('video'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'media_youtube_file_formatter_image_view',
    'settings callback' => 'media_youtube_file_formatter_image_settings',
  );
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_youtube_file_formatter_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'youtube' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'media_youtube_video',
      '#uri' => $file->uri,
      '#options' => array(),
    );
    foreach (array('width', 'height', 'autoplay', 'related', 'hd', 'showsearch', 'modestbranding', 'showinfo', 'version', 'theme', 'fullscreen', 'wmode', 'chromeless') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_youtube_file_formatter_video_settings($form, &$form_state, $settings) {
  $element = array();
  $options = array(
    0 => t('AS2'),
    3 => t('AS3'),
  );
  $element['version'] = array(
    '#title' => t('YouTube player version'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $settings['version'],
  );
  $options = array(
    'dark' => t('dark'),
    'light' => t('light'),
  );
  $element['theme'] = array(
    '#title' => t('YouTube player theme'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $settings['theme'],
  );

  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
  );
  $element['fullscreen'] = array(
    '#title' => t('Allow the video to be played in full screen mode'),
    '#type' => 'checkbox',
    '#default_value' => $settings['fullscreen'],
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['related'] = array(
    '#title' => t('Show suggested videos when the video finishes'),
    '#type' => 'checkbox',
    '#default_value' => $settings['related'],
  );
  $element['hd'] = array(
    '#title' => t('Display the high quality version of the video when available'),
    '#type' => 'checkbox',
    '#default_value' => $settings['hd'],
  );
  $element['showsearch'] = array(
    '#title' => t('Allow users to search from the video'),
    '#type' => 'checkbox',
    '#default_value' => $settings['showsearch'],
  );
  $element['modestbranding'] = array(
    '#title' => t('Use modest YouTube branding (requires AS3 version player)'),
    '#type' => 'checkbox',
    '#default_value' => $settings['modestbranding'],
  );
  $element['showinfo'] = array(
    '#title' => t('Display video title'),
    '#type' => 'checkbox',
    '#default_value' => $settings['showinfo'],
  );
  $element['chromeless'] = array(
    '#title' => t('Use chromeless player'),
    '#type' => 'checkbox',
    '#default_value' => $settings['chromeless'],
  );
  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_youtube_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'youtube') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(),
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
      );
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_youtube_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_youtube_file_default_displays() {
  $default_displays = array();

  // Default settings for displaying as a video.
  $default_video_settings = array(
    'media_large' => array(
      'width' => 480,
      'height' => 360,
      'autoplay' => FALSE,
    ),
    'media_original' => array(
      'width' => 640,
      'height' => 480,
      'autoplay' => media_youtube_variable_get('autoplay'),
    ),
  );
  foreach ($default_video_settings as $view_mode => $settings) {
    $display_name = 'video__' . $view_mode . '__media_youtube_video';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a video preview image. We enable preview
  // images even for view modes that also play video, for use inside a running
  // WYSIWYG editor. The higher weight ensures that the video display is used
  // where possible.
  $default_image_styles = array(
    'media_preview' => 'square_thumbnail',
    'media_large' => 'large',
    'media_original' => ''
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'video__' . $view_mode . '__media_youtube_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}
