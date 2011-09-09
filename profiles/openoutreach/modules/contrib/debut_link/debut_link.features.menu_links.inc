<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_link_menu_default_menu_links() {
  $menu_links = array();
  
  if (module_exists('debut')) {
    // Exported menu link: main-menu:link
    $menu_links['main-menu:link'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'link',
      'router_path' => 'link',
      'link_title' => 'Links',
      'options' => array(
        'attributes' => array(
          'title' => 'View a listing of links.',
        ),
      ),
      'module' => 'system',
      'hidden' => '0',
      'external' => '0',
      'has_children' => '0',
      'expanded' => '0',
      'weight' => '0',
    );
    // Translatables
    // Included for use with string extractors like potx.
    t('Link');
  }

  return $menu_links;
}
