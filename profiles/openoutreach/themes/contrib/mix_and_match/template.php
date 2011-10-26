<?php

/**
 * Maintenance page preprocessing
 */
function mix_and_match_preprocess_maintenance_page(&$vars) {
  if (class_exists('Database', FALSE)) {
    mix_and_match_preprocess_html($vars);  // set html vars
    mix_and_match_preprocess_page($vars);  // set page vars
  }
}

/**
 * HTML preprocessing
 */
function mix_and_match_preprocess_html(&$vars) {
  // Add body classes for custom design options
  $vars['classes_array'][] = theme_get_setting('mix_and_match_body_bg');
  $vars['classes_array'][] = theme_get_setting('mix_and_match_accent_color');
  $vars['classes_array'][] = theme_get_setting('mix_and_match_footer_color');
  $vars['classes_array'][] = theme_get_setting('mix_and_match_header_color');
  $vars['classes_array'][] = theme_get_setting('mix_and_match_link_color');
  $vars['classes_array'][] = theme_get_setting('mix_and_match_corners');
}

/**
 * Page preprocessing
 */
function mix_and_match_preprocess_page(&$vars) {
  $vars['page_color'] = theme_get_setting('mix_and_match_page_bg');
}

/**
 * Search block preprocessing
 */
function mix_and_match_preprocess_search_block_form(&$vars, $hook) {
  // Modify elements of the search form
  unset($vars['form']['search_block_form']['#title']);

  // Set a default value for the search box
  $vars['form']['search_block_form']['#value'] = t('Search...');

  $vars['form']['search_block_form']['#attributes'] = array(
     'onclick' => "this.value='';",
     'onfocus' => "this.select()",
     'onblur' => "this.value=!this.value?'Search this site':this.value;"    
  );

  // Rebuild the rendered version (search form only, rest remains unchanged)
  unset($vars['form']['search_block_form']['#printed']);
  $vars['search']['search_block_form'] = drupal_render($vars['form']['search_block_form']);

  // Collect all form elements to print entire form
  $vars['search_form'] = implode($vars['search']);

}


