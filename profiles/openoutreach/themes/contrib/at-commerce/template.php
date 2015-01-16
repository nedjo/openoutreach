<?php

// AT commerce
function at_commerce_preprocess(&$vars) {
  if (!array_key_exists('adaptivetheme', list_themes())) {
    drupal_set_message(t('Error! <a href="!link">AT Core</a> base theme not found. Please install and enable Adaptivetheme Core.', array('!link' => 'http://drupal.org/project/adaptivetheme')), 'error', false);
  }
}

/**
 * Override or insert variables into the html template.
 */
function at_commerce_preprocess_html(&$vars) {

  global $theme_key;

  $theme_name = 'at_commerce';
  $path_to_theme = drupal_get_path('theme', $theme_name);

  // Add a class for the active color scheme
  if (module_exists('color')) {
    $class = check_plain(get_color_scheme_name($theme_key));
    $vars['classes_array'][] = 'color-scheme-' . drupal_html_class($class);
  }

  // Add class for the active theme
  $vars['classes_array'][] = drupal_html_class($theme_key);

  // Add browser and platform classes
  $vars['classes_array'][] = css_browser_selector();

  // Add theme settings classes
  $settings_array = array(
    'body_background',
    'header_layout',
    'menu_bullets',
    'main_menu_alignment',
    'corner_radius_form_input_text',
    'corner_radius_form_input_submit',
  );
  foreach ($settings_array as $setting) {
    $vars['classes_array'][] = at_get_setting($setting);
  }

  // Special case for PIE htc rounded corners, not all themes include this
  if (at_get_setting('ie_corners') == 1) {
    drupal_add_css($path_to_theme . '/css/ie-htc.css', array(
      'group' => CSS_THEME,
      'browsers' => array(
        'IE' => 'lte IE 8',
        '!IE' => FALSE,
        ),
      'preprocess' => FALSE,
      )
    );
  }

  // Custom settings for AT Commerce
  // Content displays
  $show_frontpage_grid = at_get_setting('content_display_grids_frontpage') == 1 ? TRUE : FALSE;
  $show_taxopage_grid = at_get_setting('content_display_grids_taxonomy_pages') == 1 ? TRUE : FALSE;
  if ($show_frontpage_grid == TRUE || $show_taxopage_grid == TRUE) {drupal_add_js($path_to_theme . '/scripts/equalheights.js');}
  if ($show_frontpage_grid == TRUE) {
    $cols_fpg = at_get_setting('content_display_grids_frontpage_colcount');
    $vars['classes_array'][] = $cols_fpg;
    drupal_add_js($path_to_theme . '/scripts/eq.fp.grid.js');
  }
  if ($show_taxopage_grid == TRUE) {
    $cols_tpg = at_get_setting('content_display_grids_taxonomy_pages_colcount');
    $vars['classes_array'][] = $cols_tpg;
    drupal_add_js($path_to_theme . '/scripts/eq.tp.grid.js');
  }

  // Do stuff for the slideshow
  if (at_get_setting('show_slideshow') == 1) {
    // Add some js and css
    drupal_add_css($path_to_theme . '/css/styles.slideshow.css', array(
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'media' => 'screen',
      'every_page' => TRUE,
      )
    );
    drupal_add_js($path_to_theme . '/scripts/jquery.flexslider-min.js');
    drupal_add_js($path_to_theme . '/scripts/slider.options.js');

    // Add some classes to do evil hiding of elements with CSS...
    if (at_get_setting('show_slideshow_navigation_controls') == 0) {
      $vars['classes_array'][] = 'hide-ss-nav';
    }
    if (at_get_setting('show_slideshow_direction_controls') == 0) {
      $vars['classes_array'][] = 'hide-ss-dir';
    }

    // Write some evil inline CSS in the head, oh er..
    $slideshow_width = check_plain(at_get_setting('slideshow_width'));
    $slideshow_css = '.flexible-slideshow,.flexible-slideshow .article-inner,.flexible-slideshow .article-content,.flexslider {max-width: ' .  $slideshow_width . 'px;}';
    drupal_add_css($slideshow_css, array(
      'group' => CSS_DEFAULT,
      'type' => 'inline',
      )
    );
  }

  // Draw stuff
  drupal_add_js($path_to_theme . '/scripts/draw.js');

}

/**
 * Override or insert variables into the html template.
 */
function at_commerce_process_html(&$vars) {
  // Hook the color module
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Override or insert variables into the page template.
 */
function at_commerce_process_page(&$vars) {

  // Hook the color module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }

  // We some extra classes to support the fancy branding layouts
  $branding_classes = array();
  $branding_classes[] = $vars['site_logo'] ? 'with-logo' : 'no-logo';
  $branding_classes[] = !$vars['hide_site_name'] ? 'with-site-name' : 'site-name-hidden';
  $branding_classes[] = $vars['site_slogan'] ? 'with-site-slogan' : 'no-slogan';
  $vars['branding_classes'] = implode(' ', $branding_classes);

  // Draw toggle text
  $toggle_text = at_get_setting('toggle_text') ? at_get_setting('toggle_text') : t('More info');
  $vars['draw_link'] = '<a class="draw-toggle" href="#">' . check_plain($toggle_text) . '</a>';
}

/**
 * Override or insert variables into the node template.
 */
function at_commerce_preprocess_node(&$vars) {

  // Remove the inline class
  $vars['content']['links']['#attributes']['class'] = 'links';

  // Clearfix node content wrapper
  $vars['content_attributes_array']['class'][] = 'clearfix';

  // Add class if user picture exists
  if ($vars['user_picture']) {
    $vars['header_attributes_array']['class'][] = 'with-picture';
  }

  // Add classes for the slideshow node type
  if (at_get_setting('show_slideshow') == 1) {
    if ($vars['node']->type == 'slideshow') {
      $vars['classes_array'][] = 'flexible-slideshow';
      if (at_get_setting('hide_slideshow_node_title') == 1) {
        $vars['title_attributes_array']['class'][] = 'element-invisible';
      }
    }
  }

  // Content grids - nuke links off teasers if in a content_display
  if ($vars['view_mode'] == 'teaser') {
    $show_frontpage_grid = at_get_setting('content_display_grids_frontpage') == 1 ? TRUE : FALSE;
    $show_taxopage_grid = at_get_setting('content_display_grids_taxonomy_pages') == 1 ? TRUE : FALSE;
    if ($show_frontpage_grid == TRUE || $show_taxopage_grid == TRUE) {
      unset($vars['content']['links']);
    }
  }
}

/**
 * Override or insert variables into the comment template.
 */
function at_commerce_preprocess_comment(&$vars) {

  // Remove the inline class
  $vars['content']['links']['#attributes']['class'] = 'links';

  // Picture classes for the header
  if ($vars['picture']) {
    $vars['header_attributes_array']['class'][] = 'with-picture';
  }
}

/**
 * Override or insert variables into the block template
 */
function at_commerce_preprocess_block(&$vars) {
  if ($vars['block']->module == 'superfish' || $vars['block']->module == 'nice_menu') {
    $vars['content_attributes_array']['class'][] = 'clearfix';
  }
  if (!$vars['block']->subject) {
    $vars['content_attributes_array']['class'][] = 'no-title';
  }
  if ($vars['block']->region == 'menu_bar' || $vars['block']->region == 'menu_bar_top') {
    $vars['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Override or insert variables into the field template.
 */
function at_commerce_preprocess_field(&$vars) {
  // Vars and settings for the slideshow, we theme this directly in the field template
  $vars['show_slideshow_caption'] = FALSE;
  if (at_get_setting('show_slideshow_caption') == TRUE) {
   $vars['show_slideshow_caption'] = TRUE;
  }
}

/**
 * Implements hook_css_alter().
 */
function at_commerce_css_alter(&$css) {

  // Replace all Commerce module CSS files with our own for total control over all styles.
  // Commerce module uses the BAT CSS file naming convention (base, admin, theme).
  $path = drupal_get_path('theme', 'at_commerce');

  // cart
  $cart_theme = drupal_get_path('module', 'commerce_cart') . '/theme/commerce_cart.theme.css';
  if (isset($css[$cart_theme])) {
    $css[$cart_theme]['data'] = $path . '/css/commerce/commerce_cart.theme.css';
    $css[$cart_theme]['group'] = 1;
  }

  // checkout
  $checkout_base  = drupal_get_path('module', 'commerce_checkout') . '/theme/commerce_checkout.base.css';
  $checkout_admin = drupal_get_path('module', 'commerce_checkout') . '/theme/commerce_checkout.admin.css';
  $checkout_theme = drupal_get_path('module', 'commerce_checkout') . '/theme/commerce_checkout.theme.css';
  if (isset($css[$checkout_base])) {
    $css[$checkout_base]['data'] = $path . '/css/commerce/commerce_checkout.base.css';
    $css[$checkout_base]['group'] = 1;
  }
  if (isset($css[$checkout_admin])) {
    $css[$checkout_admin]['data'] = $path . '/css/commerce/commerce_checkout.admin.css';
    $css[$checkout_admin]['group'] = 1;
  }
  if (isset($css[$checkout_theme])) {
    $css[$checkout_theme]['data'] = $path . '/css/commerce/commerce_checkout.theme.css';
    $css[$checkout_theme]['group'] = 1;
  }

  // customer
  $customer_admin = drupal_get_path('module', 'commerce_customer') . '/theme/commerce_customer.admin.css';
  if (isset($css[$customer_admin])) {
    $css[$customer_admin]['data'] = $path . '/css/commerce/commerce_customer.admin.css';
    $css[$customer_admin]['group'] = 1;
  }

  // file (contrib)
  $file_forms = drupal_get_path('module', 'commerce_file') . '/theme/commerce_file.forms.css';
  if (isset($css[$file_forms])) {
    $css[$file_forms]['data'] = $path . '/css/commerce/commerce_file.forms.css';
    $css[$file_forms]['group'] = 1;
  }

  // line items
  $line_item_admin = drupal_get_path('module', 'commerce_line_item') . '/theme/commerce_line_item.admin.css';
  $line_item_theme = drupal_get_path('module', 'commerce_line_item') . '/theme/commerce_line_item.theme.css';
  if (isset($css[$line_item_admin])) {
    $css[$line_item_admin]['data'] = $path . '/css/commerce/commerce_line_item.admin.css';
    $css[$line_item_admin]['group'] = 1;
  }
  if (isset($css[$line_item_theme])) {
    $css[$line_item_theme]['data'] = $path . '/css/commerce/commerce_line_item.theme.css';
    $css[$line_item_theme]['group'] = 1;
  }

  // order
  $order_admin = drupal_get_path('module', 'commerce_order') . '/theme/commerce_order.admin.css';
  $order_theme = drupal_get_path('module', 'commerce_order') . '/theme/commerce_order.theme.css';
  if (isset($css[$order_admin])) {
    $css[$order_admin]['data'] = $path . '/css/commerce/commerce_order.admin.css';
    $css[$order_admin]['group'] = 1;
  }
  if (isset($css[$order_theme])) {
    $css[$order_theme]['data'] = $path . '/css/commerce/commerce_order.theme.css';
    $css[$order_theme]['group'] = 1;
  }

  // payment
  $payment_admin = drupal_get_path('module', 'commerce_payment') . '/theme/commerce_payment.admin.css';
  $payment_theme = drupal_get_path('module', 'commerce_payment') . '/theme/commerce_payment.theme.css';
  if (isset($css[$payment_admin])) {
    $css[$payment_admin]['data'] = $path . '/css/commerce/commerce_payment.admin.css';
    $css[$payment_admin]['group'] = 1;
  }
  if (isset($css[$payment_theme])) {
    $css[$payment_theme]['data'] = $path . '/css/commerce/commerce_payment.theme.css';
    $css[$payment_theme]['group'] = 1;
  }

  // price
  $price_theme = drupal_get_path('module', 'commerce_price') . '/theme/commerce_price.theme.css';
  if (isset($css[$price_theme])) {
    $css[$price_theme]['data'] = $path . '/css/commerce/commerce_price.theme.css';
    $css[$price_theme]['group'] = 1;
  }

  // product
  $product_admin = drupal_get_path('module', 'commerce_product') . '/theme/commerce_product.admin.css';
  $product_theme = drupal_get_path('module', 'commerce_product') . '/theme/commerce_product.theme.css';
  if (isset($css[$product_admin])) {
    $css[$product_admin]['data'] = $path . '/css/commerce/commerce_product.admin.css';
    $css[$product_admin]['group'] = 1;
  }
  if (isset($css[$product_theme])) {
    $css[$product_theme]['data'] = $path . '/css/commerce/commerce_product.theme.css';
    $css[$product_theme]['group'] = 1;
  }

  // tax
  $tax_admin = drupal_get_path('module', 'commerce_tax') . '/theme/commerce_tax.admin.css';
  $tax_theme = drupal_get_path('module', 'commerce_tax') . '/theme/commerce_tax.theme.css';
  if (isset($css[$tax_admin])) {
    $css[$tax_admin]['data'] = $path . '/css/commerce/commerce_tax.admin.css';
    $css[$tax_admin]['group'] = 1;
  }
  if (isset($css[$tax_theme])) {
    $css[$tax_theme]['data'] = $path . '/css/commerce/commerce_tax.theme.css';
    $css[$tax_theme]['group'] = 1;
  }
}

/**
 * Returns HTML for a fieldset.
 */
function at_commerce_fieldset($vars) {

  $element = $vars['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  // add a class to the fieldset wrapper if a legend exists, in some instances they do not
  $class = "without-legend";

  if (!empty($element['#title'])) {

    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';

    // Add a class to the fieldset wrapper if a legend exists, in some instances they do not
    $class = 'with-legend';
  }

  $output .= '<div class="fieldset-wrapper ' . $class  . '">';

  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  $output .= "</fieldset>\n";

  return $output;
}
