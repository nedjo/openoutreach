<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_blog_menu_default_menu_links() {
  $menu_links = array();
  
  if (module_exists('debut')) {
    // Exported menu link: main-menu:blog
    $menu_links['main-menu:blog'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'blog',
      'router_path' => 'blog',
      'link_title' => 'Blog',
      'options' => array(
        'attributes' => array(
          'title' => 'View a listing of blog posts.',
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
    t('Blog');
  }

  return $menu_links;
}
