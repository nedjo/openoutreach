<?php

/**
 * Implementation of hook_content_default_fields().
 */
function debut_section_content_default_fields() {
  $fields = array();

  // Exported field: field_image
  $fields['section-field_image'] = array(
    'field_name' => 'field_image',
    'type_name' => 'section',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      '4' => array(
        'format' => 'thumbnail_default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'thumbnail_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'medium_default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'images',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '3000x3000',
      'min_resolution' => '300x300',
      'alt' => '',
      'custom_alt' => 1,
      'title' => '',
      'custom_title' => 1,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '-3',
      'description' => 'Select an image to upload. Allowed image types are: png, gif, jpg and jpeg. The recommended image size is 640 by 480 pixels. Maximum size is 3000x3000 and the minimum is 300x300.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Image');

  return $fields;
}
