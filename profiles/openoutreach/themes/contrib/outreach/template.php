<?php

/**
 * @file
 * Process theme data.
 *
 * Use this file to run your theme specific implimentations of theme functions,
 * such preprocess, process, alters, and theme function overrides.
 *
 * Preprocess and process functions are used to modify or create variables for
 * templates and theme functions. They are a common theming tool in Drupal, often
 * used as an alternative to directly editing or adding code to templates. Its
 * worth spending some time to learn more about these functions - they are a
 * powerful way to easily modify the output of any template variable.
 * 
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "outreach" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "outreach".
 * 2. Uncomment the required function to use.
 */


/**
 * Preprocess variables for the html template.
 */
function outreach_preprocess_html(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Add a class for the active color scheme
  if (module_exists('color')) {
    $class = check_plain(get_color_scheme_name($theme_name));
    $vars['classes_array'][] = 'color-scheme-' . drupal_html_class($class);
  }
}


/**
 * Process variables for the html template.
 */
function outreach_process_html(&$vars) {
  // Hook into the color module.
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}


/**
 * Override or insert variables for the page templates.
 */
function outreach_process_page(&$vars) {
  // Hook into the color module.
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function outreach_preprocess_node(&$vars) {
}
function outreach_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function outreach_preprocess_comment(&$vars) {
}
function outreach_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function outreach_preprocess_block(&$vars) {
}
function outreach_process_block(&$vars) {
}
// */
