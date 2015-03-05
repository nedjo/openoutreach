<?php
/**
 * @file
 * debut_member.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function debut_member_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-member.
  $menus['menu-member'] = array(
    'menu_name' => 'menu-member',
    'title' => 'Members',
    'description' => 'Menu for member-only links.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Members');
  t('Menu for member-only links.');


  return $menus;
}
