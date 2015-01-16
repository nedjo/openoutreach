<?php

/**
 * @file
 * Implementation of a Skinr plugin.
 */


/**
 * Implements hook_skinr_group_info().
 */
function mix_and_match_skinr_group_info() {
  $groups['skinr_styles_colors'] = array(
    'title' => t('Mix and Match Styles'),
    'description' => t('<h3>Colors for backgrounds, headers, and links, and CSS3 styles</h3>'),
    'weight' => -14,
  );

  return $groups;
}

/**
 * Implements hook_skinr_skin_info().
 *
 *
 */
function mix_and_match_skinr_skin_info() {
  $skins = array();
  $skins['skinr_background_color'] = array(
    'title' => t('Background Color'),
    'type' => 'select',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'no_bg' => array(
        'title' => t('No background - clears a default style'),
        'class' => array('no-bbg'),
      ),
      'white_bg' => array(
        'title' => t('White'),
        'class' => array('wh-bbg'),
      ),
      'black_bg' => array(
        'title' => t('Black'),
        'class' => array('bk-bbg'),
      ),
      'ltgray_bg' => array(
        'title' => t('Light Gray'),
        'class' => array('lgy-bbg'),
      ),
      'medgray_bg' => array(
        'title' => t('Gray'),
        'class' => array('gy-bbg'),
      ),
      'dkgray_bg' => array(
        'title' => t('Dark Gray'),
        'class' => array('dgy-bbg'),
      ),
      'lttan_bg' => array(
        'title' => t('Light Tan'),
        'class' => array('ltn-bbg'),
      ),
      'medtan_bg' => array(
        'title' => t('Tan'),
        'class' => array('tn-bbg'),
      ),
      'dktan_bg' => array(
        'title' => t('Dark Tan'),
        'class' => array('dtn-bbg'),
      ),     
      'brown_bg' => array(
        'title' => t('Brown'),
        'class' => array('brn-bbg'),
      ),
      'ltblue_bg' => array(
        'title' => t('Light Blue'),
        'class' => array('lbl-bbg'),
      ),        
      'blue_bg' => array(
        'title' => t('Blue'),
        'class' => array('bl-bbg'),
      ),  
      'dkblue_bg' => array(
        'title' => t('Dark Blue'),
        'class' => array('dbl-bbg'),
      ),             
      'ltgreen_bg' => array(
        'title' => t('Light Green'),
        'class' => array('lgr-bbg'),
      ),
      'green_bg' => array(
        'title' => t('Green'),
        'class' => array('gr-bbg'),
      ),        
      'dkgreen_bg' => array(
        'title' => t('Dark Green'),
        'class' => array('dgr-bbg'),
      ),
      'ltteal_bg' => array(
        'title' => t('Light Teal'),
        'class' => array('ltl-bbg'),
      ),
      'teal_bg' => array(
        'title' => t('Teal'),
        'class' => array('tl-bbg'),
      ),              
      'red_bg' => array(
        'title' => t('Red'),
        'class' => array('rd-bbg'),
      ),
      'ltorange_bg' => array(
        'title' => t('Light Orange'),
        'class' => array('lor-bbg'),
      ),
      'orange_bg' => array(
        'title' => t('Orange'),
        'class' => array('or-bbg'),
      ),
      'ltmaroon_bg' => array(
        'title' => t('Light Maroon'),
        'class' => array('lmr-bbg'),
      ),
      'maroon_bg' => array(
        'title' => t('Maroon'),
        'class' => array('mr-bbg'),
      ),
      'ltpurple_bg' => array(
        'title' => t('Light Purple'),
        'class' => array('lpr-bbg'),
      ),
      'purple_bg' => array(
        'title' => t('Purple'),
        'class' => array('pr-bbg'),
      ),
    ),
  );

  $skins['skinr_header_background_color'] = array(
    'title' => t('Header Background Color'),
    'type' => 'select',
    'description' => 'Select a color if you would like a header background different from the body background.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'no_header_bg' => array(
        'title' => t('No background - clears a default style'),
        'class' => array('no-bhd'),
      ),
      'gray_header_bg' => array(
        'title' => t('Gray'),
        'class' => array('gy-bhd'),
      ),
      'black_header_bg' => array(
        'title' => t('Black'),
        'class' => array('bk-bhd'),
      ),
      'brown_header_bg' => array(
        'title' => t('Brown'),
        'class' => array('br-bhd'),
      ),
      'blue_header_bg' => array(
        'title' => t('Blue'),
        'class' => array('bl-bhd'),
      ),
      'dkblue_header_bg' => array(
        'title' => t('Dark Blue'),
        'class' => array('dbl-bhd'),
      ),
      'green_header_bg' => array(
        'title' => t('Green'),
        'class' => array('gr-bhd'),
      ),
      'dkgreen_header_bg' => array(
        'title' => t('Dark Green'),
        'class' => array('dgr-bhd'),
      ),
      'teal_header_bg' => array(
        'title' => t('Teal'),
        'class' => array('tl-bhd'),
      ),
      'red_header_bg' => array(
        'title' => t('Red'),
        'class' => array('rd-bhd'),
      ),
      'orange_header_bg' => array(
        'title' => t('Orange'),
        'class' => array('or-bhd'),
      ),
      'maroon_header_bg' => array(
        'title' => t('Maroon'),
        'class' => array('mr-bhd'),
      ),
      'purple_header_bg' => array(
        'title' => t('Purple'),
        'class' => array('pr-bhd'),
      ),
    ),
  );

  $skins['skinr_header_text_color'] = array(
    'title' => t('Header Text Color'),
    'type' => 'select',
    'description' => 'Select a color for the block or node title text.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'white_header_text' => array(
        'title' => t('White'),
        'class' => array('wh-bht'),
      ),
      'gray_header_text' => array(
        'title' => t('Gray'),
        'class' => array('gy-bht'),
      ),
      'black_header_text' => array(
        'title' => t('Black'),
        'class' => array('bk-bht'),
      ),
      'brown_header_text' => array(
        'title' => t('Brown'),
        'class' => array('br-bht'),
      ),
      'blue_header_text' => array(
        'title' => t('Blue'),
        'class' => array('bl-bht'),
      ),
      'dkblue_header_text' => array(
        'title' => t('Dark Blue'),
        'class' => array('dbl-bht'),
      ),
      'green_header_text' => array(
        'title' => t('Green'),
        'class' => array('gr-bht'),
      ),
      'dkgreen_header_text' => array(
        'title' => t('Dark Green'),
        'class' => array('dgr-bht'),
      ),
      'red_header_text' => array(
        'title' => t('Red'),
        'class' => array('rd-bht'),
      ),
     'orange_header_text' => array(
        'title' => t('Orange'),
        'class' => array('or-bht'),
      ),
     'maroon_header_text' => array(
        'title' => t('Maroon'),
        'class' => array('mr-bht'),
      ),
     'purple_header_text' => array(
        'title' => t('Purple'),
        'class' => array('pr-bht'),
      ),
    ),
  );

  $skins['skinr_link_text_color'] = array(
    'title' => t('Link Color'),
    'type' => 'select',
    'description' => 'Select a color for the link text.',
    'group' => 'skinr_styles_colors',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'gray_link_text' => array(
        'title' => t('Gray'),
        'class' => array('gy-lnk'),
      ),
      'white_link_text' => array(
        'title' => t('White'),
        'class' => array('wh-lnk'),
      ),
      'brown_link_text' => array(
        'title' => t('Brown'),
        'class' => array('br-lnk'),
      ),
      'blue_link_text' => array(
        'title' => t('Blue'),
        'class' => array('bl-lnk'),
      ),
      'green_link_text' => array(
        'title' => t('Green'),
        'class' => array('gr-lnk'),
      ),
      'red_link_text' => array(
        'title' => t('Red'),
        'class' => array('rd-lnk'),
      ),
     'orange_link_text' => array(
        'title' => t('Orange'),
        'class' => array('or-lnk'),
      ),
     'purple_link_text' => array(
        'title' => t('Purple'),
        'class' => array('pr-lnk'),
      ),
     'maroon_link_text' => array(
        'title' => t('Maroon'),
        'class' => array('mr-lnk'),
      ),
    ),

   $skins['skinr_round_corners'] = array(
    'title' => t('CSS3 Round Corners'),
    'type' => 'select',
    'description' => 'Add CSS3-based round corners (only displays in compliant browsers)',
    'group' => 'skinr_styles_colors',
    'weight' => 10,
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'nopx' => array(
        'title' => t('Square corners - clear a default style'),
        'class' => array('rc0'),
      ),
      'threepx' => array(
        'title' => t('3px radius'),
        'class' => array('rc3'),
      ),
      'sevenpx' => array(
        'title' => t('7px radius'),
        'class' => array('rc7'),
      ),
      'elevenpx' => array(
        'title' => t('11px radius'),
        'class' => array('rc11'),
      ),
    ),  
  ),

   $skins['skinr_shadows'] = array(
    'title' => t('CSS3 Box Shadow'),
    'type' => 'select',
    'description' => 'Add a CSS3-based drop shadow (only displays in compliant browsers)',
    'group' => 'skinr_styles_colors',
    'weight' => 10,
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'node'),
    'default status' => TRUE,
    'options' => array(
      'zeropx' => array(
        'title' => t('No shadow - clear a default style'),
        'class' => array('ds0'),
      ),
      'twopx' => array(
        'title' => t('2px shadow'),
        'class' => array('ds2'),
      ),
      'fourpx' => array(
        'title' => t('4px shadow'),
        'class' => array('ds4'),
      ),
    ),  
  ),
                
);
  return $skins;
}
