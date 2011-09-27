<?php

/**
 * @file media_vimeo/includes/media_vimeo.styles.inc
 * Styles definitions for Media: Vimeo.
 */

/**
 * Implementation of Styles module hook_styles_register().
 */
function media_vimeo_styles_register() {
  return array(
    'MediaVimeoStyles' => array(
      'field_types' => 'file',
      'name' => t('MediaVimeo'),
      'description' => t('Media Vimeo styles.'),
      'path' => drupal_get_path('module', 'media_vimeo') .'/includes',
      'file' => 'media_vimeo.styles.inc',
    ),
  );
}

/**
 *  Implements hook_styles_containers(). (Deprecated in version 2)
 */
function media_vimeo_styles_containers() {
  return array(
    'file' => array(
      'containers' => array(
        'media_vimeo' => array(
          'label' => t('Vimeo Styles'),
          'data' => array(
            'streams' => array(
              'vimeo',
            ),
            'mimetypes' => array(
              'video/vimeo',
            ),
          ),
          'weight' => 0,
          'filter callback' => 'media_vimeo_formatter_filter',
          'themes' => array(
            'field_formatter_styles' => 'media_vimeo_field_formatter_styles',
            'styles' => 'media_vimeo_styles',
            'preview' => 'media_vimeo_preview_style',
          ),
          'description' => t('Vimeo Styles will display embedded Vimeo videos and thumbnails to your choosing, such as by resizing, setting colors, and autoplay. You can !manage.', array('!manage' => l(t('manage your Vimeo styles here'), 'admin/config/media/media-vimeo-styles'))),
        ),
      ),
    ),
  );
}

function media_vimeo_formatter_filter($variables) {
  if (isset($variables['object'])) {
    $object = isset($variables['object']->file) ? $variables['object']->file : $variables['object'];
    return (file_uri_scheme($object->uri) == 'vimeo') && ($object->filemime == 'video/vimeo');
  }
}

/**
 * Implementation of the File Styles module's hook_file_styles_filter().
 */
function media_vimeo_file_styles_filter($object) {
  $file = isset($object->file) ? $object->file : $object;
  if ((file_uri_scheme($file->uri) == 'vimeo') && ($file->filemime == 'video/vimeo')) {
    return 'media_vimeo';
  }
}

/**
 *  Implements hook_styles_styles().
 */
function media_vimeo_styles_styles() {
  $styles = array(
    'file' => array(
      'containers' => array(
        'media_vimeo' => array(
          'styles' => array(
            'vimeo_thumbnail' => array(
              'name' => 'vimeo_thumbnail',
              'effects' => array(
                array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 100, 'height' => 75)),
              ),
            ),
            'vimeo_preview' => array(
              'name' => 'vimeo_preview',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 220, 'height' => 165)),
              ),
            ),
            'vimeo_full' => array(
              'name' => 'vimeo_full',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 640, 'height' => 480)),
                array('label' => t('Full screen'), 'name' => 'fullscreen', 'data' => array('fullscreen' => 1)),
              ),
            ),
          ),
        ),
      ),
    ),
  );

  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $styles['file']['containers']['media_vimeo']['styles']['vimeo_thumbnail_' . $style_name] = array(
      'name' => 'vimeo_thumbnail_' . $style_name,
      'image_style' => $style_name,
      'effects' => array(
        array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
      ),
    );
  }

  return $styles;
}

/**
 *  Implements hook_styles_presets().
 */
function media_vimeo_styles_presets() {
  $presets = array(
    'file' => array(
      'square_thumbnail' => array(
        'media_vimeo' => array(
          'vimeo_thumbnail_square_thumbnail',
        ),
      ),
      'thumbnail' => array(
        'media_vimeo' => array(
          'vimeo_thumbnail',
        ),
      ),
      'small' => array(
        'media_vimeo' => array(
          'vimeo_preview',
        ),
      ),
      'large' => array(
        'media_vimeo' => array(
          'vimeo_full',
        ),
      ),
      'original' => array(
        'media_vimeo' => array(
          'vimeo_full',
        ),
      ),
    ),
  );
  return $presets;
}

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_vimeo_styles_default_containers() {
  // We append Vimeo to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_vimeo' => array(
          'class' => 'MediaVimeoStyles',
          'name' => 'media_vimeo',
          'label' => t('Vimeo'),
          'preview' => 'media_vimeo_preview_style',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_vimeo_styles_default_presets() {
  $presets = array(
    'file' => array(
      'containers' => array(
        'media_vimeo' => array(
          'default preset' => 'unlinked_thumbnail',
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
                  'width' => 640,
                  'height' => 390,
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
  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $presets['file']['containers']['media_vimeo']['presets']['linked_' . $style_name] = array(
      array(
        'name' => 'linkToMedia',
        'settings' => array(),
      ),
      array(
        'name' => 'imageStyle',
        'settings' => array(
          'image_style' => $style_name,
        ),
      ),
      array(
        'name' => 'thumbnail',
        'settings' => array(),
      ),
    );
    $presets['file']['containers']['media_vimeo']['presets']['unlinked_' . $style_name] = $presets['file']['containers']['media_vimeo']['presets']['linked_' . $style_name];
    array_shift($presets['file']['containers']['media_vimeo']['presets']['unlinked_' . $style_name]);
    foreach ($image_style['effects'] as $effect) {
      if (in_array($effect['name'], array('image_scale', 'image_scale_and_crop', 'image_resize', 'image_crop'))) {
        $presets['file']['containers']['media_vimeo']['presets']['video_' . $style_name] = array(
          array(
            'name' => 'resize',
            'settings' => $effect['data'],
          ),
          array(
            'name' => 'video',
            'settings' => array(),
          ),
        );
      }
    }
  }
  return $presets;
}
