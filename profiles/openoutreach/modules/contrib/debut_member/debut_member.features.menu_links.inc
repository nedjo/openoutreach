<?php
/**
 * @file
 * debut_member.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function debut_member_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-member:node/add/member-page
  $menu_links['menu-member:node/add/member-page'] = array(
    'menu_name' => 'menu-member',
    'link_path' => 'node/add/member-page',
    'router_path' => 'node/add/member-page',
    'link_title' => 'Add member page',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new members-only page.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '5',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add member page');


  return $menu_links;
}
