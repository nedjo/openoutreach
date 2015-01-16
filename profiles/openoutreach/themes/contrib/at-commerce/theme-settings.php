<?php
/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function at_commerce_form_system_theme_settings_alter(&$form, &$form_state) {

  // Include a hidden form field with the current release information
  $form['at-release'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Tell the submit function its safe to run the color inc generator
  // if running on AT Core 7.x-3.x
  $form['at-color'] = array(
    '#type' => 'hidden',
    '#default_value' => TRUE,
  );

  $enable_extensions = isset($form_state['values']['enable_extensions']);
  if (($enable_extensions && $form_state['values']['enable_extensions'] == 1) || (!$enable_extensions && $form['at-settings']['extend']['enable_extensions']['#default_value'] == 1)) {

    // Remove option to use full width wrappers
    $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
      '#access' => FALSE,
      '#default_value' => 0,
    );

    $form['at']['content_display'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content Displays'),
      '#description' => t('<h3>Content Displays</h3><p>Display the front page or taxonomy term pages as a grid. You can set the max number of columns to appear. These settings use the normal node teasers and format them as a grid. Article links (such as the <em>Read More</em> link) are hidden when displayed in the grid. These settings will work well with the responsive design, unlike a Views table grid which does not.</p>'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage'] = array(
      '#type' => 'fieldset',
      '#title' => t('Frontpage'),
      '#description' => t('<h3>Frontpage</h3>'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage']['content_display_grids_frontpage'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display front page teasers as a grid'),
      '#default_value' => theme_get_setting('content_display_grids_frontpage'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage']['content_display_grids_frontpage_colcount'] = array(
      '#type' => 'select',
      '#title' => t('Enter the max number of grid columns'),
      '#default_value' => theme_get_setting('content_display_grids_frontpage_colcount'),
      '#options' => array(
        'fpcc-2' => t('2'),
        'fpcc-3' => t('3'),
        'fpcc-4' => t('4'),
        'fpcc-5' => t('5'),
        'fpcc-6' => t('6'),
        'fpcc-7' => t('7'),
        'fpcc-8' => t('8'),
      ),
      '#states' => array (
        'visible' => array (
          'input[name="content_display_grids_frontpage"]' => array ('checked' => TRUE)
        )
      )
    );
    $form['at']['content_display']['content_display_grids']['taxonomy'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy'),
      '#description' => t('<h3>Taxonomy Pages</h3>'),
    );
    $form['at']['content_display']['content_display_grids']['taxonomy']['content_display_grids_taxonomy_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display taxonomy page teasers as a grid'),
      '#default_value' => theme_get_setting('content_display_grids_taxonomy_pages'),
    );
    $form['at']['content_display']['content_display_grids']['taxonomy']['content_display_grids_taxonomy_pages_colcount'] = array(
      '#type' => 'select',
      '#title' => t('Enter the max number of grid columns'),
      '#default_value' => theme_get_setting('content_display_grids_taxonomy_pages_colcount'),
      '#options' => array(
        'tpcc-2' => t('2'),
        'tpcc-3' => t('3'),
        'tpcc-4' => t('4'),
        'tpcc-5' => t('5'),
        'tpcc-6' => t('6'),
        'tpcc-7' => t('7'),
        'tpcc-8' => t('8'),
      ),
      '#states' => array (
        'visible' => array (
          'input[name="content_display_grids_taxonomy_pages"]' => array ('checked' => TRUE)
        )
      )
    );

    // Draw
    $form['at']['draw'] = array(
      '#type' => 'fieldset',
      '#title' => t('Slidedown Draw'),
      '#description' => t('<h3>Slidedown Draw</h3><p>Enter the link text to display for the Slidedown draw link. The draw is activated by placing blocks into the Draw region. When the toggle link is clicked the draw will slide open to reveal your block content. This is good for showing a login form, contact information etc.'),
    );
    $form['at']['draw']['toggle_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the toggle text:'),
      '#size' => 15,
      '#default_value' => theme_get_setting('toggle_text'),
    );

    // Header layout
    $form['at']['header'] = array(
      '#type' => 'fieldset',
      '#title' => t('Header layout'),
      '#description' => t('<h3>Header layout</h3><p>Change the position of the logo, site name and slogan. Note that his will automatically alter the header region layout also. If the branding elements are centered the header region will center below them, otherwise the header region will float in the opposite direction.</p>'),
    );
    $form['at']['header']['header_layout'] = array(
      '#type' => 'radios',
      '#title' => t('Branding position'),
      '#default_value' => theme_get_setting('header_layout'),
      '#options' => array(
        'hl-l'  => t('Left'),
        'hl-r'  => t('Right'),
        'hl-c' => t('Centered'),
      ),
    );

    // Slider
    $form['at']['slideshow'] = array(
      '#type' => 'fieldset',
      '#title' => t('Slideshow'),
      '#description' => t('<h3>Slideshow</h3><p>Unchecking this setting will disable the slideshow. If you are not using the built in slideshow it is safe to uncheck this setting.</p>'),
    );
    $form['at']['slideshow']['show_slideshow'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable slideshows'),
      '#default_value' => theme_get_setting('show_slideshow'),
    );
    $form['at']['slideshow']['slideshow_width'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the image width'),
      '#description' => t('This must match the width used for the image-style for your slides.'),
      '#default_value' => theme_get_setting('slideshow_width'),
      '#size' => 4,
      '#field_suffix' => 'px',
      '#maxlength' => 4,
      '#states' => array (
        'visible' => array (
          'input[name="show_slideshow"]' => array (
            'checked' => TRUE,
          )
        )
      )
    );
    $form['at']['slideshow']['show_slideshow_caption'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show the tile element as a caption'),
      '#default_value' => theme_get_setting('show_slideshow_caption'),
      '#description' => t('You must enable titles on the image field and enter caption text on the node edit form.'),
      '#states' => array (
        'visible' => array (
          'input[name="show_slideshow"]' => array (
            'checked' => TRUE,
          )
        )
      )
    );
    $form['at']['slideshow']['show_slideshow_direction_controls'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show the direction controls (arrows)'),
      '#description' => t('By default these show as semi-transarent arrows over the slides.'),
      '#default_value' => theme_get_setting('show_slideshow_direction_controls'),
      '#states' => array (
        'visible' => array (
          'input[name="show_slideshow"]' => array (
            'checked' => TRUE,
          )
        )
      )
    );
    $form['at']['slideshow']['show_slideshow_navigation_controls'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show the navigation controls (dots)'),
      '#description' => t('By default these show as small dots below the slides.'),
      '#default_value' => theme_get_setting('show_slideshow_navigation_controls'),
      '#states' => array (
        'visible' => array (
          'input[name="show_slideshow"]' => array (
            'checked' => TRUE,
          )
        )
      )
    );
    $form['at']['slideshow']['hide_slideshow_node_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide the node title'),
      '#default_value' => theme_get_setting('hide_slideshow_node_title'),
      '#description' => t('This will hide the node title using element-invisible.'),
      '#states' => array (
        'visible' => array (
          'input[name="show_slideshow"]' => array (
            'checked' => TRUE,
          )
        )
      )
    );

    $form['at']['corners'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners'),
      '#description' => t('<h3>Rounded Corners</h3><p>Rounded corners are implimented using CSS and only work in modern compliant browsers.</p>'),
    );
    $form['at']['corners']['forms'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners for form elements'),
      '#description' => t('Rounded corners for form elements'),
    );
    $form['at']['corners']['forms']['corner_radius_form_input_text'] = array(
      '#type' => 'select',
      '#title' => t('Form text fields'),
      '#default_value' => theme_get_setting('corner_radius_form_input_text'),
      '#description' => t('Change the corner radius for text fields.'),
      '#options' => array(
        'itrc-0' => t('none'),
        'itrc-2' => t('2px'),
        'itrc-3' => t('3px'),
        'itrc-4' => t('4px'),
        'itrc-6' => t('6px'),
        'itrc-8' => t('8px'),
        'itrc-10' => t('10px'),
        'itrc-12' => t('12px'),
      ),
    );
    $form['at']['corners']['forms']['corner_radius_form_input_submit'] = array(
      '#type' => 'select',
      '#title' => t('Submit buttons'),
      '#default_value' => theme_get_setting('corner_radius_form_input_submit'),
      '#description' => t('Change the corner radius for submit buttons.'),
      '#options' => array(
        'isrc-0' => t('none'),
        'isrc-2' => t('2px'),
        'isrc-3' => t('3px'),
        'isrc-4' => t('4px'),
        'isrc-6' => t('6px'),
        'isrc-8' => t('8px'),
        'isrc-10' => t('10px'),
        'isrc-12' => t('12px'),
      ),
    );
    $form['at']['pagestyles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Textures'),
      '#description' => t('<h3>Textures</h3><p>Textures are small, semi-transparent images that tile to fill the entire background.</p>'),
    );

    // AT Commerce does not support box shadows, they dont work well with the overall design.
    $form['at']['pagestyles']['textures'] = array(
      '#type' => 'fieldset',
      '#title' => t('Textures'),
      '#description' => t('<h3>Body Textures</h3><p>This setting adds a texture over the Featured Panels and the Bottom Panels background colors - the darker the background the more these stand out, on light backgrounds the effect is subtle.</p>'),
    );
    $form['at']['pagestyles']['textures']['body_background'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('body_background'),
      '#options' => array(
        'bb-n'   => t('None'),
        'bb-b'   => t('Bubbles'),
        'bb-hs'  => t('Horizontal stripes'),
        'bb-dp'  => t('Diagonal pattern'),
        'bb-dll' => t('Diagonal lines - loose'),
        'bb-dlt' => t('Diagonal lines - tight'),
        'bb-sd'  => t('Small dots'),
        'bb-bd'  => t('Big dots'),
      ),
    );

    $form['at']['menu_styles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Styles'),
    );
    $form['at']['menu_styles']['main_menu'] = array(
      '#type' => 'fieldset',
      '#title' => t('Main Menu Alignment'),
      '#description' => t('<h3>Main Menu Alignment</h3>'),
    );
    $form['at']['menu_styles']['main_menu']['main_menu_alignment'] = array(
      '#type' => 'radios',
      '#title' => t('Align the main menu left, centered or to the right.'),
      '#default_value' => theme_get_setting('main_menu_alignment'),
      '#options' => array(
        'mma-l' => t('Left'),
        'mma-c' => t('Centered'),
        'mma-r' => t('Right'),
      ),
    );

    $form['at']['menu_styles']['bullets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Bullets'),
      '#description' => t('<h3>Menu Bullets</h3><p>This setting allows you to customize the bullet images used on menus items. Bullet images only show on normal vertical block menus.</p>'),
    );
    $form['at']['menu_styles']['bullets']['menu_bullets'] = array(
      '#type' => 'select',
      '#title' => t('Menu Bullets'),
      '#default_value' => theme_get_setting('menu_bullets'),
      '#options' => array(
        'mb-n' => t('None'),
        'mb-dd' => t('Drupal default'),
        'mb-ah' => t('Arrow head'),
        'mb-ad' => t('Double arrow head'),
        'mb-ca' => t('Circle arrow'),
        'mb-fa' => t('Fat arrow'),
        'mb-sa' => t('Skinny arrow'),
      ),
    );
  }
}
