<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_media_menu_default_menu_links() {
  $menu_links = array();

  if (module_exists('debut')) {
    // Exported menu link: main-menu:file
    $menu_links['main-menu:file'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'file',
      'router_path' => 'file',
      'link_title' => 'Multimedia',
      'options' => array(
        'attributes' => array(
          'title' => 'View media files.',
        ),
      ),
      'module' => 'menu',
      'hidden' => '0',
      'external' => '0',
      'has_children' => '1',
      'expanded' => '0',
      'weight' => '15',
    );
    // Exported menu link: main-menu:file/images
    $menu_links['main-menu:file/image'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'file/image',
      'router_path' => 'file/image',
      'link_title' => 'Images',
      'options' => array(
        'attributes' => array(
          'title' => 'View images.',
        ),
      ),
      'module' => 'menu',
      'hidden' => '0',
      'external' => '0',
      'has_children' => '0',
      'expanded' => '0',
      'weight' => '0',
      'parent_path' => 'file',
    );
    // Exported menu link: main-menu:file/video
    $menu_links['main-menu:file/video'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'file/video',
      'router_path' => 'file/video',
      'link_title' => 'Video',
      'options' => array(
        'attributes' => array(
          'title' => 'View all videos.',
        ),
      ),
      'module' => 'menu',
      'hidden' => '0',
      'external' => '0',
      'has_children' => '0',
      'expanded' => '0',
      'weight' => '0',
      'parent_path' => 'file',
    );
    // Translatables
    // Included for use with string extractors like potx.
    t('Images');
    t('Media');
    t('Video');
  }

  return $menu_links;
}
