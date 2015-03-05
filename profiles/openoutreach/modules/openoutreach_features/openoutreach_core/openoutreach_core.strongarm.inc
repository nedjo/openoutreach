<?php
/**
 * @file
 * openoutreach_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function openoutreach_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'l, F j, Y - g:ia';
  $export['date_format_long'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'D, m/d/Y - g:ia';
  $export['date_format_medium'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'm/d/Y - g:ia';
  $export['date_format_short'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_main_links_source';
  $strongarm->value = 'main-menu';
  $export['menu_main_links_source'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_secondary_links_source';
  $strongarm->value = 'main-menu';
  $export['menu_secondary_links_source'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'superfish_arrow_superfish_1';
  $strongarm->value = 0;
  $export['superfish_arrow_superfish_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'superfish_shadow_superfish_1';
  $strongarm->value = 0;
  $export['superfish_shadow_superfish_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_outreach_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
    'bigscreen_layout' => 'three_col_grail',
    'bigscreen_sidebar_unit' => '%',
    'bigscreen_sidebar_first' => '25',
    'bigscreen_sidebar_second' => '25',
    'bigscreen_page_unit' => '%',
    'bigscreen_page_width' => '100',
    'bigscreen_set_max_width' => 1,
    'bigscreen_max_width_unit' => 'px',
    'bigscreen_max_width' => '1140',
    'bigscreen_media_query' => 'only screen and (min-width:1025px)',
    'tablet_landscape_layout' => 'three_col_grail',
    'tablet_landscape_sidebar_unit' => '%',
    'tablet_landscape_sidebar_first' => '20',
    'tablet_landscape_sidebar_second' => '20',
    'tablet_landscape_page_unit' => '%',
    'tablet_landscape_page_width' => '100',
    'tablet_landscape_media_query' => 'only screen and (min-width:769px) and (max-width:1024px)',
    'tablet_portrait_layout' => 'one_col_vert',
    'tablet_portrait_sidebar_unit' => '%',
    'tablet_portrait_sidebar_first' => '50',
    'tablet_portrait_sidebar_second' => '50',
    'tablet_portrait_page_unit' => '%',
    'tablet_portrait_page_width' => '100',
    'tablet_portrait_media_query' => 'only screen and (min-width:481px) and (max-width:768px)',
    'smalltouch_landscape_layout' => 'one_col_vert',
    'smalltouch_landscape_sidebar_unit' => '%',
    'smalltouch_landscape_sidebar_first' => '50',
    'smalltouch_landscape_sidebar_second' => '50',
    'smalltouch_landscape_media_query' => 'only screen and (min-width:321px) and (max-width:480px)',
    'smalltouch_landscape_page_width' => '100',
    'smalltouch_landscape_page_unit' => '%',
    'smalltouch_portrait_media_query' => 'only screen and (max-width:320px)',
    'smalltouch_portrait_page_width' => '100',
    'smalltouch_portrait_page_unit' => '%',
    'smalltouch_portrait_sidebar_first' => '100',
    'smalltouch_portrait_sidebar_second' => '100',
    'smalltouch_portrait_sidebar_unit' => '%',
    'smalltouch_portrait_layout' => 'one_col_stack',
    'bigscreen_two_33_66' => 'two-33-66',
    'bigscreen_two_66_33' => 'two-66-33',
    'bigscreen_two_50' => 'two-50',
    'bigscreen_two_brick' => 'two-brick',
    'bigscreen_three_50_25_25' => 'three-50-25-25',
    'bigscreen_three_25_50_25' => 'three-25-50-25',
    'bigscreen_three_25_25_50' => 'three-25-25-50',
    'bigscreen_three_3x33' => 'three-3x33',
    'bigscreen_four_4x25' => 'four-4x25',
    'bigscreen_five_5x20' => 'five-5x20-2x3-grid',
    'bigscreen_six_6x16' => 'six-6x16-3x2-grid',
    'bigscreen_three_inset_left' => 'three-inset-left',
    'bigscreen_three_inset_right' => 'three-inset-right',
    'tablet_landscape_two_33_66' => 'two-33-66',
    'tablet_landscape_two_66_33' => 'two-66-33',
    'tablet_landscape_two_50' => 'two-50',
    'tablet_landscape_two_brick' => 'two-brick',
    'tablet_landscape_three_50_25_25' => 'three-50-25-25',
    'tablet_landscape_three_25_50_25' => 'three-25-50-25',
    'tablet_landscape_three_25_25_50' => 'three-25-25-50',
    'tablet_landscape_three_3x33' => 'three-3x33',
    'tablet_landscape_four_4x25' => 'four-4x25',
    'tablet_landscape_five_5x20' => 'five-5x20-2x3-grid',
    'tablet_landscape_six_6x16' => 'six-6x16-3x2-grid',
    'tablet_landscape_three_inset_left' => 'three-inset-left',
    'tablet_landscape_three_inset_right' => 'three-inset-right',
    'tablet_portrait_two_33_66' => 'two-33-66',
    'tablet_portrait_two_66_33' => 'two-66-33',
    'tablet_portrait_two_50' => 'two-50',
    'tablet_portrait_two_brick' => 'two-brick',
    'tablet_portrait_three_50_25_25' => 'three-50-25-25-stack-top',
    'tablet_portrait_three_25_50_25' => 'three-25-50-25-stack-top',
    'tablet_portrait_three_25_25_50' => 'three-25-25-50-stack-top',
    'tablet_portrait_three_3x33' => 'three-3x33-stack-top',
    'tablet_portrait_four_4x25' => 'four-4x25-2x2-grid',
    'tablet_portrait_five_5x20' => 'five-5x20-1x2x2-grid',
    'tablet_portrait_six_6x16' => 'six-6x16-2x3-grid',
    'tablet_portrait_three_inset_left' => 'three-inset-left-wrap',
    'tablet_portrait_three_inset_right' => 'three-inset-right-wrap',
    'smalltouch_landscape_two_33_66' => 'two-33-66-stack',
    'smalltouch_landscape_two_66_33' => 'two-66-33-stack',
    'smalltouch_landscape_two_50' => 'two-50-stack',
    'smalltouch_landscape_two_brick' => 'two-brick-stack',
    'smalltouch_landscape_three_50_25_25' => 'three-50-25-25-stack',
    'smalltouch_landscape_three_25_50_25' => 'three-25-50-25-stack',
    'smalltouch_landscape_three_25_25_50' => 'three-25-25-50-stack',
    'smalltouch_landscape_three_3x33' => 'three-3x33-stack',
    'smalltouch_landscape_four_4x25' => 'four-4x25-stack',
    'smalltouch_landscape_five_5x20' => 'five-5x20-stack',
    'smalltouch_landscape_six_6x16' => 'six-6x16-stack',
    'smalltouch_landscape_three_inset_left' => 'three-inset-left-stack',
    'smalltouch_landscape_three_inset_right' => 'three-inset-right-stack',
    'global_default_layout_toggle' => 0,
    'global_default_layout' => 'smalltouch-portrait',
    'disable_responsive_styles' => 0,
    'global_files_path' => 'public_files',
    'custom_files_path' => '',
    'combine_css_files' => 0,
    'combine_js_files' => 0,
    'enable_custom_media_queries' => 1,
    'load_html5js' => 1,
    'load_matchmediajs' => 0,
    'load_onmediaqueryjs' => 0,
    'load_ltie8css' => 0,
    'load_respondjs' => 0,
    'load_scalefixjs' => 0,
    'adaptivetheme_meta_viewport' => 'width=device-width, initial-scale=1',
    'adaptivetheme_meta_mobileoptimized' => 'width',
    'adaptivetheme_meta_handheldfriendly' => 'true',
    'adaptivetheme_meta_apple_mobile_web_app_capable' => 'yes',
    'adaptivetheme_meta_ie_document_mode' => '',
    'adaptivetheme_meta_clear_type' => 0,
    'expose_regions' => 0,
    'show_window_size' => 0,
    'atcore_version_test' => 0,
    'load_all_panels' => 0,
    'load_all_panels_no_sidebars' => 0,
    'enable_extensions' => 0,
    'enable_font_settings' => 0,
    'enable_heading_settings' => 0,
    'enable_image_settings' => 0,
    'enable_apple_touch_icons' => 0,
    'enable_exclude_css' => 0,
    'enable_custom_css' => 0,
    'enable_context_regions' => 0,
    'enable_menu_toggle' => 0,
    'enable_float_region_blocks' => 0,
    'enable_markup_overides' => 0,
    'at-settings__active_tab' => '',
    'at_core' => '7.x-3.x',
    'scheme' => 'default',
    'palette' => array(
      'text' => '#444444',
      'link' => '#2883DE',
      'linkhover' => '#000000',
      'headings' => '#181818',
      'sitename' => '#262626',
      'sitenamehover' => '#3253ad',
      'slogan' => '#7d7d7d',
      'bodyborder' => '#375199',
    ),
    'theme' => 'outreach',
    'info' => array(
      'fields' => array(
        'text' => 'Text color',
        'link' => 'Links color',
        'linkhover' => 'Links hover color',
        'headings' => 'Headings color',
        'sitename' => 'Site-name color',
        'sitenamehover' => 'Site-name hover color',
        'slogan' => 'Slogan color',
        'bodyborder' => 'Body border top color',
      ),
      'schemes' => array(
        'default' => array(
          'title' => 'Blue (default)',
          'colors' => array(
            'text' => '#444444',
            'link' => '#2883DE',
            'linkhover' => '#000000',
            'headings' => '#181818',
            'sitename' => '#262626',
            'sitenamehover' => '#3253ad',
            'slogan' => '#7d7d7d',
            'bodyborder' => '#375199',
          ),
        ),
        'grape' => array(
          'title' => 'Grape',
          'colors' => array(
            'text' => '#161616',
            'link' => '#70A113',
            'linkhover' => '#5C2CB5',
            'headings' => '#5C2CB5',
            'sitename' => '#70A113',
            'sitenamehover' => '#5C2CB5',
            'slogan' => '#525252',
            'bodyborder' => '#5C2CB5',
          ),
        ),
        'happy' => array(
          'title' => 'Happy',
          'colors' => array(
            'text' => '#161616',
            'link' => '#DC143C',
            'linkhover' => '#13A0DC',
            'headings' => '#13A0DC',
            'sitename' => '#DC143C',
            'sitenamehover' => '#13A0DC',
            'slogan' => '#525252',
            'bodyborder' => '#13A0DC',
          ),
        ),
        'earth' => array(
          'title' => 'Earth',
          'colors' => array(
            'text' => '#161616',
            'link' => '#A64B00',
            'linkhover' => '#308014',
            'headings' => '#308014',
            'sitename' => '#A64B00',
            'sitenamehover' => '#308014',
            'slogan' => '#525252',
            'bodyborder' => '#308014',
          ),
        ),
        'caribbean' => array(
          'title' => 'Caribbean',
          'colors' => array(
            'text' => '#161616',
            'link' => '#1780b6',
            'linkhover' => '#FF7F50',
            'headings' => '#FF7F50',
            'sitename' => '#1780b6',
            'sitenamehover' => '#FF7F50',
            'slogan' => '#525252',
            'bodyborder' => '#FF7F50',
          ),
        ),
        '' => array(
          'title' => 'Custom',
          'colors' => array(),
        ),
      ),
      'css' => array(
        0 => 'color/colors.css',
      ),
      'copy' => array(
        0 => 'logo.png',
      ),
      'gradients' => array(
        0 => array(
          'dimension' => array(
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => array(
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => array(),
      'slices' => array(),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  );
  $export['theme_outreach_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = '1';
  $export['user_pictures'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '1024x1024';
  $export['user_picture_dimensions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_file_size';
  $strongarm->value = '800';
  $export['user_picture_file_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_style';
  $strongarm->value = 'thumbnail';
  $export['user_picture_style'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = 2;
  $export['user_register'] = $strongarm;

  return $export;
}
