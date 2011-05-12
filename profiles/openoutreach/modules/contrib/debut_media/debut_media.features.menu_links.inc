<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_media_menu_default_menu_links() {
  $menu_links = array();

  if (module_exists('debut')) {
    // Exported menu link: main-menu:media
    $menu_links['main-menu:media'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'media',
      'router_path' => 'media',
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
    // Exported menu link: main-menu:media/images
    $menu_links['main-menu:media/image'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'media/image',
      'router_path' => 'media/image',
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
      'parent_path' => 'media',
    );
    // Exported menu link: main-menu:media/video
    $menu_links['main-menu:media/video'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'media/video',
      'router_path' => 'media/video',
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
      'parent_path' => 'media',
    );
    // Translatables
    // Included for use with string extractors like potx.
    t('Images');
    t('Media');
    t('Video');
  }

  return $menu_links;
}
