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
 * 1. Rename each function and instance of "adaptivetheme_subtheme" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "adaptivetheme_subtheme".
 * 2. Uncomment the required function to use.
 */


/**
 * HTML preprocessing
 */
function mix_and_match_preprocess_html(&$vars) {
  // Add body classes for custom design options
  $settings = array('mix_and_match_body_bg', 'mix_and_match_accent_color', 'mix_and_match_page_bg', 'mix_and_match_secondary_bg', 
    'mix_and_match_tertiary_bg', 'mix_and_match_footer_bg', 'mix_and_match_text_color', 'mix_and_match_link_color', 
    'mix_and_match_page_title_color', 'mix_and_match_block_bg', 'mix_and_match_block_header', 'mix_and_match_block_header_txt',
    'mix_and_match_round_corners', 'mix_and_match_shadows');
  foreach($settings as $setting){
    $class = theme_get_setting($setting);
    if($class != '1'  && $class != '') {
      $vars['classes_array'][] = $class;
    }
  }

  if(theme_get_setting('mix_and_match_body_texture') == '1'){ $vars['classes_array'][] = 'txt-bod'; }

  // only load skins.css if Skinr module in use
  if(module_exists('skinr')){
     $path = path_to_theme();
     $filepath = $path . '/css/skins.css';
     //print $filepath;
       if (file_exists($filepath)) {
         drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'weight' => 1000,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
  }
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