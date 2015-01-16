<?php

/**
 * @file
 * Implimentation of hook_form_system_theme_settings_alter()
 *
 * To use replace "adaptivetheme_subtheme" with your themeName and uncomment by
 * deleting the comment line to enable.
 *
 * @param $form: Nested array of form elements that comprise the form.
 * @param $form_state: A keyed array containing the current state of the form.
 */
function mix_and_match_form_system_theme_settings_alter(&$form, $form_state) {
  /* Adjust order of forms */
  $form['mandm_settings'] = array(
      '#type' => 'vertical_tabs',
      '#weight' => -11,
      '#prefix' => t('<h3>Mix and Match Colors and Styles</h3>'),
  );

  // Colors
  $form['mandm_settings']['colors'] = array(
      '#type' => 'fieldset',
      '#weight' => -15,
      '#title' => t('Main Color Scheme'),
      '#description' => t('<h4>Select the base colors for your site</h4>'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  ); 

  $form['mandm_settings']['colors']['mix_and_match_body_bg'] = array(
      '#type' => 'select',
      '#title' => t('Body background color'),
      '#empty_option' => t('White (default)'),
      '#options' => array(
          'gy-bod' => t('Gray'),
          'bk-bod' => t('Black'),
          'tn-bod' => t('Tan'),
          'br-bod' => t('Brown'),
          'bl-bod' => t('Blue'),
          'gr-bod' => t('Green'),
          'tl-bod' => t('Teal'),
          'rd-bod' => t('Red'),
          'mr-bod' => t('Maroon'),
          'pr-bod' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_body_bg'),
  );
  
    $form['mandm_settings']['colors']['mix_and_match_body_texture'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add a random texture to the body background'),
      '#default_value' => theme_get_setting('mix_and_match_body_texture'),
  );

  $form['mandm_settings']['colors']['mix_and_match_page_bg'] = array(
      '#type' => 'select',
      '#title' => t('Content area background'),
      '#description' => t('<i>Select a different background color for the main content area (optional)</i>'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-pbg' => t('Add a white background to content area'),
          'tn-pbg' => t('Add a light tan background to content area'),
          'gy-pbg' => t('Add a light gray background to content area'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_page_bg'),
  );

  $form['mandm_settings']['colors']['mix_and_match_accent_color'] = array(
      '#type' => 'select',
      '#title' => t('Accent color (navigation bar and buttons)'),
      '#empty_option' => t('Gray (default)'),
      '#options' => array(
          'bk-acc' => t('Black'),
          'br-acc' => t('Brown'),
          'bl-acc' => t('Blue'),
          'dbl-acc' => t('Dark Blue'),
          'gr-acc' => t('Green'),
          'dgr-acc' => t('Dark Green'),
          'tl-acc' => t('Teal'),
          'rd-acc' => t('Red'),
          'or-acc' => t('Orange'),
          'mr-acc' => t('Maroon'),
          'pr-acc' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_accent_color'),
  );

  $form['mandm_settings']['colors']['mix_and_match_secondary_bg'] = array(
      '#type' => 'select',
      '#title' => t('Secondary region background color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-sec' => t('White'),
          'lgy-sec' => t('Light Gray'),
          'gy-sec' => t('Gray'),
          'dgy-sec' => t('Dark Gray'),
          'bk-sec' => t('Black'),
          'ltn-sec' => t('Light Tan'),
          'tn-sec' => t('Tan'),
          'dtn-sec' => t('Dark Tan'),
          'brn-sec' => t('Brown'),
          'lbl-sec' => t('Light Blue'),
          'bl-sec' => t('Blue'),
          'dbl-sec' => t('Dark Blue'),
          'lgr-sec' => t('Light Green'),
          'gr-sec' => t('Green'),
          'dgr-sec' => t('Dark Green'),
          'ltl-sec' => t('Light Teal'),
          'tl-sec' => t('Teal'),
          'red-sec' => t('Red'),
          'lor-sec' => t('Light Orange'),
          'or-sec' => t('Orange'),
          'lmr-sec' => t('Light Maroon'),
          'mr-sec' => t('Maroon'),
          'lpr-sec' => t('Light Purple'),
          'pr-sec' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_secondary_bg'),
  );

  $form['mandm_settings']['colors']['mix_and_match_tertiary_bg'] = array(
      '#type' => 'select',
      '#title' => t('Tertiary region background color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-ter' => t('White'),
          'lgy-ter' => t('Light Gray'),
          'gy-ter' => t('Gray'),
          'dgy-ter' => t('Dark Gray'),
          'bk-ter' => t('Black'),
          'ltn-ter' => t('Light Tan'),
          'tn-ter' => t('Tan'),
          'dtn-ter' => t('Dark Tan'),
          'brn-ter' => t('Brown'),
          'lbl-ter' => t('Light Blue'),
          'bl-ter' => t('Blue'),
          'dbl-ter' => t('Dark Blue'),
          'lgr-ter' => t('Light Green'),
          'gr-ter' => t('Green'),
          'dgr-ter' => t('Dark Green'),
          'ltl-ter' => t('Light Teal'),
          'tl-ter' => t('Teal'),
          'red-ter' => t('Red'),
          'lor-ter' => t('Light Orange'),
          'or-ter' => t('Orange'),
          'lmr-ter' => t('Light Maroon'),
          'mr-ter' => t('Maroon'),
          'lpr-ter' => t('Light Purple'),
          'pr-ter' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_tertiary_bg'),
  );

  $form['mandm_settings']['colors']['mix_and_match_footer_bg'] = array(
      '#type' => 'select',
      '#title' => t('Footer background color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-ftr' => t('White'),
          'lgy-ftr' => t('Light Gray'),
          'gy-ftr' => t('Gray'),
          'dgy-ftr' => t('Dark Gray'),
          'bk-ftr' => t('Black'),
          'ltn-ftr' => t('Light Tan'),
          'tn-ftr' => t('Tan'),
          'dtn-ftr' => t('Dark Tan'),
          'brn-ftr' => t('Brown'),
          'lbl-ftr' => t('Light Blue'),
          'bl-ftr' => t('Blue'),
          'dbl-ftr' => t('Dark Blue'),
          'lgr-ftr' => t('Light Green'),
          'gr-ftr' => t('Green'),
          'dgr-ftr' => t('Dark Green'),
          'ltl-ftr' => t('Light Teal'),
          'tl-ftr' => t('Teal'),
          'red-ftr' => t('Red'),
          'lor-ftr' => t('Light Orange'),
          'or-ftr' => t('Orange'),
          'lmr-ftr' => t('Light Maroon'),
          'mr-ftr' => t('Maroon'),
          'lpr-ftr' => t('Light Purple'),
          'pr-ftr' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_footer_bg'),
  );

  // Text
  $form['mandm_settings']['text'] = array(
      '#type' => 'fieldset',
      '#weight' => -14,
      '#title' => t('Text Colors'),
      '#description' => t('<h4>Select Text Colors </h4>'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );

  $form['mandm_settings']['text']['mix_and_match_link_color'] = array(
      '#type' => 'select',
      '#title' => t('Link color'),
      '#empty_option' => t('Gray (default)'),
      '#options' => array(
          'wh-lnk' => t('White'),
          'br-lnk' => t('Brown'),
          'bl-lnk' => t('Blue'),
          'gr-lnk' => t('Green'),
          'tl-lnk' => t('Teal'),
          'rd-lnk' => t('Red'),
          'or-lnk' => t('Orange'),
          'mr-lnk' => t('Maroon'),
          'pr-lnk' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_link_color'),
  );

  $form['mandm_settings']['text']['mix_and_match_page_title_color'] = array(
      '#type' => 'select',
      '#title' => t('Page title text color'),
      '#description' => t('Set a page title color to override main body text color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-pt' => t('White'),
          'gy-pt' => t('Gray'),
          'bk-pt' => t('Black'),
          'br-pt' => t('Brown'),
          'bl-pt' => t('Blue'),
          'dbl-pt' => t('Dark Blue'),
          'gr-pt' => t('Green'),
          'dgr-pt' => t('Dark Green'),
          'tl-pt' => t('Teal'),
          'rd-pt' => t('Red'),
          'or-pt' => t('Orange'),
          'mr-pt' => t('Maroon'),
          'pr-pt' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_page_title_color'),
  );

  // Blocks
  $form['mandm_settings']['blocks'] = array(
      '#type' => 'fieldset',
      '#weight' => -13,
      '#title' => t('Default Block Styles'),
      '#description' => t('<h4>Select the default styles for blocks in the main content area.</h4><i><b>NOTE: </b>These can be overridden for individual blocks using the Skinr module.</i><br /><br />'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );

  $form['mandm_settings']['blocks']['mix_and_match_block_bg'] = array(
      '#type' => 'select',
      '#title' => t('Block background color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-bbg' => t('White'),
          'lgy-bbg' => t('Light Gray'),
          'gy-bbg' => t('Gray'),
          'dgy-bbg' => t('Dark Gray'),
          'bk-bbg' => t('Black'),
          'ltn-bbg' => t('Light Tan'),
          'tn-bbg' => t('Tan'),
          'dtn-bbg' => t('Dark Tan'),
          'brn-bbg' => t('Brown'),
          'lbl-bbg' => t('Light Blue'),
          'bl-bbg' => t('Blue'),
          'dbl-bbg' => t('Dark Blue'),
          'lgr-bbg' => t('Light Green'),
          'gr-bbg' => t('Green'),
          'dgr-bbg' => t('Dark Green'),
          'ltl-bbg' => t('Light Teal'),
          'tl-bbg' => t('Teal'),
          'rd-bbg' => t('Red'),
          'lor-bbg' => t('Light Orange'),
          'or-bbg' => t('Orange'),
          'lmr-bbg' => t('Light Maroon'),
          'mr-bbg' => t('Maroon'),
          'lpr-bbg' => t('Light Purple'),
          'pr-bbg' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_block_bg'),
  );

  $form['mandm_settings']['blocks']['mix_and_match_block_header'] = array(
      '#type' => 'select',
      '#title' => t('Block header background'),
      '#empty_value' => TRUE,
      '#options' => array(
          'gy-bhd' => t('Gray'),
          'bk-bhd' => t('Black'),
          'br-bhd' => t('Brown'),
          'bl-bhd' => t('Blue'),
          'dbl-bhd' => t('Dark Blue'),
          'gr-bhd' => t('Green'),
          'dgr-bhd' => t('Dark Green'),
          'tl-bhd' => t('Teal'),
          'rd-bhd' => t('Red'),
          'or-bhd' => t('Orange'),
          'mr-bhd' => t('Maroon'),
          'pr-bhd' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_block_header'),
  );

  $form['mandm_settings']['blocks']['mix_and_match_block_header_txt'] = array(
      '#type' => 'select',
      '#title' => t('Block header text color'),
      '#empty_value' => TRUE,
      '#options' => array(
          'wh-bht' => t('White'),
          'gy-bht' => t('Gray'),
          'bk-bht' => t('Black'),
          'br-bht' => t('Brown'),
          'bl-bht' => t('Blue'),
          'dbl-bht' => t('Dark Blue'),
          'gr-bht' => t('Green'),
          'dgr-bht' => t('Dark Green'),
          'tl-bht' => t('Teal'),
          'rd-bht' => t('Red'),
          'or-bht' => t('Orange'),
          'mr-bht' => t('Maroon'),
          'pr-bht' => t('Purple'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_block_header_txt'),
  );

  // CSS3
  $form['mandm_settings']['css3'] = array(
      '#type' => 'fieldset',
      '#weight' => -12,
      '#title' => t('CSS3'),
      '#description' => t('<h4>Select CSS3-based styles (will only be rendered in compliant browsers)</h4><i><b>NOTE: </b>These can be set for individual blocks using the Skinr module.</i><br /><br />'),
      '#collapsed' => FALSE,
  );

  $form['mandm_settings']['css3']['mix_and_match_round_corners'] = array(
      '#type' => 'select',
      '#title' => t('Round Corners'),
      '#description' => t('Add round corners to blocks and other page elements'),
      '#empty_value' => TRUE,
      '#options' => array(
          'rc3' => t('3px radius'),
          'rc7' => t('7px radius'),
          'rc11' => t('11px radius'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_round_corners'),
  );

  $form['mandm_settings']['css3']['mix_and_match_shadows'] = array(
      '#type' => 'select',
      '#title' => t('Box Shadows'),
      '#description' => t('Add drop shadows to all blocks in main content area by default'),
      '#empty_value' => TRUE,
      '#options' => array(
          'ds2' => t('2px shadow'),
          'ds4' => t('4px shadow'),
      ),
      '#default_value' => theme_get_setting('mix_and_match_shadows'),
  );
}

