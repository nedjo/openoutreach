<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_article_menu_default_menu_links() {
  $menu_links = array();

  if (module_exists('debut')) {
    // Exported menu link: main-menu:article
    $menu_links['main-menu:article'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'article',
      'router_path' => 'article',
      'link_title' => 'Articles',
      'options' => array(
        'attributes' => array(
          'title' => 'View a listing of articles.',
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
    t('Articles');
  }

  return $menu_links;
}
