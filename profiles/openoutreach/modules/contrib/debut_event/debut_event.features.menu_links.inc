<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function debut_event_menu_default_menu_links() {
  $menu_links = array();

  if (module_exists('debut')) {
    // Exported menu link: main-menu:event
    $menu_links['main-menu:event'] = array(
      'menu_name' => 'main-menu',
      'link_path' => 'event',
      'router_path' => 'event',
      'link_title' => 'Events',
      'options' => array(
        'attributes' => array(
          'title' => 'View a  calendar listing of events.',
        ),
      ),
      'module' => 'menu',
      'hidden' => '0',
      'external' => '0',
      'has_children' => '0',
      'expanded' => '0',
      'weight' => '0',
    );
    // Translatables
    // Included for use with string extractors like potx.
    t('Events');
  }

  return $menu_links;
}
