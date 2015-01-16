<?php

/**
 * @file
 * Administrative page for Forward module
 *
 */

/**
 * Callback function for administration menu item
 */
function forward_admin_settings($form, &$form_state) {
  global $base_url;

  $host = parse_url($base_url);

  // General Options
  $form['forward_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $types = node_type_get_types();
  $options = array();
  $defaults = array();
  foreach ($types as $type => $info) {
    $options[$type] = check_plain($info->name);
    if (variable_get('forward_display_' . $type, TRUE)) {
      $defaults[] = $type;
    }
  }
  $form['forward_options']['forward_display_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#options' => $options,
    '#default_value' => $defaults,
    '#description' => t('Choose which content types to show Forward on.'),
  );
  $form['forward_options']['forward_display_nodes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Forward on full nodes'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_display_nodes', TRUE),
  );
  $form['forward_options']['forward_display_teasers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Forward on teasers'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_display_teasers', FALSE),
  );
  $form['forward_options']['forward_theme_template'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use forward.tpl.php template instead of old style theme functions'),
    '#default_value' => variable_get('forward_theme_template', 0),
    '#description' => t('If you are upgrading from an old site and customized theme_forward_email or theme_forward_postcard, leave this unchecked unless you wish to convert your customizations to the new forward.tpl.php style.  If upgrading, make sure you flush the theme registry before making this change or Drupal may not find the new template.'),
  );
  $form['forward_options']['forward_form_type'] = array(
    '#type' => 'select',
    '#title' => t('Interface'),
    '#default_value' => variable_get('forward_form_type', 'link'),
    '#options' => array('link' => t('link'), 'form' => t('form')),
    '#description' => t('Select link for a "forward this page" link, or form to use a collapsible forwarding form in a fieldset.'),
  );
  $form['forward_options']['forward_link_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use node type'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_link_type', FALSE),
    '#description' => t('If this option is set, Forward will display &quot;email this <em>nodetype</em>&quot;; if not, it will just read &quot;email this page&quot;'),
  );
  $form['forward_options']['forward_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text / fieldset title'),
    '#size' => 40,
    '#default_value' => variable_get('forward_link_title', 'Email this !type'),
    '#description' => t('Set the text of the link or fieldset title. Use !type as a place holder for the node\'s content type or \'page\' depending on the setting above.'),
  );
  $form['forward_options']['forward_link_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link Interface Options'),
    '#collapsible' => FALSE,
  );
  $form['forward_options']['forward_link_options']['forward_link_style'] = array(
    '#type' => 'radios',
    '#title' => t('Link style'),
    '#default_value' => variable_get('forward_link_style', 0),
    '#options' => array(0 => t('Text only'), 1 => t('Icon only'), 2 => t('Icon and text')),
    '#description' => t('Select the visual style of the link.'),
  );
  $form['forward_options']['forward_link_options']['forward_link_icon'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#title' => t('Path to custom icon'),
    '#default_value' => variable_get('forward_link_icon', ''),
    '#description' => t('The path to the file you would like to use as your link icon instead of the default icon.'),
  );
  $form['forward_options']['forward_link_options']['forward_link_alias'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the path alias for the node when generating the forward link'),
    '#default_value' => variable_get('forward_link_alias', 1),
  );
  $form['forward_options']['forward_link_options']['forward_link_noindex'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a noindex meta tag on the forward page'). ' (name="robots", content="noindex, nofollow")',
    '#default_value' => variable_get('forward_link_noindex', 1),
  );
  $form['forward_options']['forward_link_options']['forward_link_nofollow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a nofollow tag on the forward link (rel="nofollow")'),
    '#default_value' => variable_get('forward_link_nofollow', 0),
  );
  $form['forward_options']['forward_message'] = array(
    '#type' => 'select',
    '#title' => t('Personal messages'),
    '#options' => array(0 => 'Disabled', 1 => 'Optional', 2 => 'Required'),
    '#default_value' => variable_get('forward_message', 1),
    '#description' => t('Choose whether the personal message field will be disabled, optional, or required.'),
  );
  $form['forward_options']['forward_filter_html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow HTML in personal messages'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_filter_html', FALSE),
    '#description' => t('Filter XSS and all tags not allowed below from the custom body field.  Otherwise, the body will converted to plain text with all HTML converted to character entities'),
  );
  $form['forward_options']['forward_filter_tags'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed HTML tags'),
    '#size' => 40,
    '#default_value' => variable_get('forward_filter_tags', 'p,br,em,strong,cite,code,ul,ol,li,dl,dt,dd'),
    '#description' => t('List of allowed tags (separated by commas) that will be allowed by the XSS filter if enabled above.  The default tags allowed are: p,br,em,strong,cite,code,ul,ol,li,dl,dt,dd'),
  );
  $form['forward_options']['forward_sender_address'] = array(
    '#type' => 'textfield',
    '#title' => t('From address'),
    '#default_value' => variable_get('forward_sender_address', variable_get('site_mail', '')),
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('If left blank, the from address entered in the form will be used as the from address for the email.  Enter a valid email address here to override that.  The sender\'s email will still appear in the body of the message.'),
  );
  // Thank You Email Values
  $form['forward_thank_you'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thank You Email'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_thank_you']['forward_thankyou_send'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send a thank you email to the person doing the forwarding'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_thankyou_send', FALSE),
  );
  $form['forward_thank_you']['forward_thankyou_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Thank you email subject'),
    '#default_value' => variable_get('forward_thankyou_subject', 'Thank you for spreading the word about [site:name]'),
  );
  $form['forward_thank_you']['forward_thankyou_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Thank you email text'),
    '#default_value' => variable_get('forward_thankyou_text', "Dear [forward:sender],\n\nThank you for spreading the word about [site:name]. We appreciate your help."),
    '#cols' => 40,
    '#rows' => 10,
  );

  // Global Defaults
  $form['forward_text_values'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Defaults'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_text_values']['forward_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Email width'),
    '#default_value' => variable_get('forward_width', 400),
    '#size' => 10,
    '#description' => t('Set a width for the table in the email template.  Ideally, this should be somewhere between 400 and 600 pixels to avoid breaking the layout in various email clients.'),
    '#attributes' => FALSE,
  );
  $form['forward_text_values']['forward_header_image'] = array(
    '#type' => 'textfield',
    '#title' => t('Header Image for Email'),
    '#default_value' => variable_get('forward_header_image', ''),
    '#size' => 40,
    '#maxlength' => 256,
    '#description' => t('Enter the URL of the image to use as a logo at the top of forwarded pages.'),
    '#attributes' => FALSE,
  );
  $form['forward_text_values']['forward_instructions'] = array(
    '#type' => 'textarea',
    '#title' => t('Forward Instructions'),
    '#default_value' => variable_get('forward_instructions', '<p>Thank you for your interest in spreading the word about [site:name].</p><p>NOTE: We only request your email address so that the person you are recommending the page to knows that you wanted them to see it, and that it is not junk mail. We do not capture any email address.</p>'),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('This message will be displayed above the form.  The token [site:name] will be replaced with the site name.'),
  );
  $form['forward_text_values']['forward_thankyou'] = array(
    '#type' => 'textarea',
    '#title' => t('Thank You Message'),
    '#default_value' => variable_get('forward_thankyou', 'Thank you for spreading the word about [site:name].  We appreciate your help.'),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('This message will be displayed after the user successfully submits the form.  The token [site:name] will be replaced with the site name.'),
  );

  // Forward Form Defaults
  $form['forward_email_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Defaults for Email This Page'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_email_defaults']['forward_email_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Forward Page Title'),
    '#default_value' => variable_get('forward_email_title', t('Forward this page to a friend')),
    '#size' => 40,
    '#maxlength' => 256,
    '#description' => t('Title to display above the Forward page form'),
  );
  $form['forward_email_defaults']['forward_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Forward Message Subject'),
    '#default_value' => variable_get('forward_email_subject', t('[forward:sender] has forwarded a page to you from [site:name]')),
    '#size' => 40,
    '#maxlength' => 256,
    '#description' => t('Email subject line. Replacement tokens, as found below, may be used'),
  );
  $form['forward_email_defaults']['forward_email_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Forward Message Body'),
    '#default_value' => variable_get('forward_email_message', t('[forward:sender] thought you would like to see this page from the [site:name] web site.')),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('Email message body. Replacement tokens, as found below, may be used. The sender will be able to add their own message after this.'),
  );
  $form['forward_email_defaults']['forward_full_body'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include full node in message body'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_full_body', FALSE),
    '#description' => t('Include the full body of the node rather than just the teaser'),
  );
  $form['forward_email_defaults']['forward_custom_viewmode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use custom display to build message body'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_custom_viewmode', FALSE),
    '#description' => t('Use a custom view mode named "Forward" to build the node, if available (clear cache twice after enabling this option)'),
  );

  // e-PostCard Form Default Values
  $form['forward_epostcard_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Defaults for e-Postcard'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_epostcard_defaults']['forward_epostcard_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Forward e-Postcard Title'),
    '#default_value' => variable_get('forward_epostcard_title', t('Send an e-Postcard')),
    '#size' => 40,
    '#maxlength' => 256,
    '#description' => t('Title to display above the Forward page form'),
  );
  $form['forward_epostcard_defaults']['forward_epostcard_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('e-Postcard Message Subject'),
    '#default_value' => variable_get('forward_epostcard_subject', t('[forward:sender] has sent you an e-postcard from [site:name]')),
    '#size' => 40,
    '#maxlength' => 256,
    '#description' => t('Postcard subject line. Replacement tokens, as found below, may be used'),
  );
  $form['forward_epostcard_defaults']['forward_epostcard_message'] = array(
    '#type' => 'textarea',
    '#title' => t('e-Postcard Message Body'),
    '#default_value' => variable_get('forward_epostcard_message', t('[forward:sender] has sent you an e-postcard from the [site:name] web site.  Please take a moment to visit our web site.')),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('Postcard message body. Replacement tokens, as found below, may be used. The sender will be able to add their own message after this. You can use HTML in this field to add a special postcard image to the email above the sender\'s message.'),
  );
  $form['forward_epostcard_defaults']['forward_ad_footer'] = array(
    '#type' => 'textarea',
    '#title' => t('Organization Ad'),
    '#default_value' => variable_get('forward_ad_footer', " "),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('This message will be just above the footer message in the email.'),
  );
  $form['forward_epostcard_defaults']['forward_footer'] = array(
    '#type' => 'textarea',
    '#title' => t('Footer Message'),
    '#default_value' => variable_get('forward_footer', " "),
    '#cols' => 40,
    '#rows' => 4,
    '#description' => t('This message will be appended as a footer message to the email.'),
  );
  $form['forward_epostcard_defaults']['forward_epostcard_return'] = array(
    '#type' => 'textfield',
    '#title' => t('e-Postcard Return URL'),
    '#default_value' => variable_get('forward_epostcard_return', ''),
    '#size' => 40,
    '#description' => t('URL of path to redirect users to after submitting the epostcard form.'),
  );

  // Replacement tokens
  $form['token_help'] = array(
    '#title' => t('Replacement patterns'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['token_help']['help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node', 'user', 'forward'),
  );

  // Colorbox integration
  $form['forward_colorbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Colorbox Integration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_colorbox']['forward_colorbox_spacer'] = array(
    '#markup' => '<div style="height: 10px; width: 1px"></div>',
  );
  $form['forward_colorbox']['forward_colorbox_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate links so the forward page displays in a colorbox overlay'),
    '#description' => t('The Colorbox module must be installed with either the "colorbox load" extra feature enabled or the Colorbox Node module enabled.<br />The Colorbox Node module is recommended. Note: Colorbox integration is not supported for e-Postcard links or links generated by the Service Links module.'),
    '#return_value' => 1,
    '#default_value' => variable_get('forward_colorbox_enable', FALSE),
  );
  $form['forward_colorbox']['forward_colorbox_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width of colorbox'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('forward_colorbox_width', '600'),
  );
  $form['forward_colorbox']['forward_colorbox_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height of colorbox'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('forward_colorbox_height', '600'),
  );

  // Dynamic Block settings
  $form['forward_dynamic_block_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Dynamic Block Settings'),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  '#description' => t('These options control whether sent emails include dynamic block content.')
  );
  $dyn_options = array(
    'node' => t('Latest Blog Articles'),
    'user' => t('Latest Users'),
    'comment' => t('Latest Comments'),
    'popular' => t('Most Popular Content'),
    'none' => t('None')
  );
  $form['forward_dynamic_block_settings']['forward_dynamic_block'] = array(
    '#type' => 'radios',
    '#title' => t('Dynamic Block'),
    '#default_value' => variable_get('forward_dynamic_block', 'none'),
    '#options' => $dyn_options,
    '#description' => t('Choose the dynamic block to send with these emails. The Most Popular Content block requires the Statistics module to be enabled with the "count content views" option selected.'),
    '#required' => TRUE,
    '#attributes' => NULL,
  );
  $acl_options = array(
    'recipient' => t('If one email address is entered in the Send To field and it corresponds to an active Drupal account, use the permissions of that account.  Otherwise use anonymous visitor permissions. <em>(default)</em>'),
    'anonymous' => t('Always use the anonymous visitor permissions.'),
    'sender' => t('Use the permissions of the person sending the email.'),
    'none' => t('Bypass access control.  This mimics the behavior prior to release 7.x-1.3. <em>Warning: selecting this option has security implications.</em>'),
  );
  $form['forward_dynamic_block_settings']['forward_block_access_control'] = array(
    '#type' => 'radios',
    '#title' => t('Dynamic Block Access Control'),
    '#default_value' => variable_get('forward_block_access_control', 'recipient'),
    '#options' => $acl_options,
    '#description' => t('Select the type of access control to apply to the dynamic block.  This determines which content will be included in the block. Most sites should use the default.'),
    '#required' => TRUE,
    '#attributes' => NULL,
  );
  // Pathologic
  $filter_options = array();
  $filter_options[''] = t('- None - ');
  foreach(filter_formats() as $key => $format) {
    if (filter_access($format)) {
      $filter_options[$key] = $format->name;
    }
  }
  if (count($filter_options) > 1) {
    $form['forward_filter_options'] = array(
      '#type' => 'fieldset',
      '#title' => t('Pathologic'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['forward_filter_options']['forward_filter_format'] = array(
      '#type' => 'select',
      '#title' => t('Filter format'),
      '#default_value' => variable_get('forward_filter_format', ''),
      '#options' => $filter_options,
      '#description' => t('Select a filter to apply to the forward message body. A filter with <a href="http://drupal.org/project/pathologic">Pathologic</a> assigned to it will convert relative links to absolute links.'),
    );
  }
  // Flood Control
  $form['forward_flood_control_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flood Control'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['forward_flood_control_options']['forward_flood_control'] = array(
    '#type' => 'select',
    '#title' => t('Flood control limit'),
    '#default_value' => variable_get('forward_flood_control', 10),
    '#options' => array('1' => '1', '5' => '5', '10' => '10', '15' => '15', '20' => '20', '25' => '25', '30' => '30', '35' => '35', '40' => '40', '50' => '50'),
    '#description' => t('How many times a user can use the form in a one hour period. This will help prevent the forward module from being used for spamming.'),
  );
  $form['forward_flood_control_options']['forward_flood_error'] = array(
    '#type' => 'textarea',
    '#title' => t('Flood control error'),
    '#default_value' => variable_get('forward_flood_error', t("You can't send more than !number messages per hour. Please try again later.")),
    '#cols' => 40,
    '#rows' => 10,
    '#description' => t('This text appears if a user exceeds the flood control limit.  The value of the flood control limit setting will appear in place of !number in the message presented to users'),
  );
  $form['forward_flood_control_options']['forward_flood_control_clicks'] = array(
    '#type' => 'select',
    '#title' => t('Flood control limit for clickthrough tracking'),
    '#default_value' => variable_get('forward_flood_control_clicks', 3),
    '#options' => array('1' => '1', '2' => '2', '3' => '3', '4' => '4', '5' => '5', '6' => '6', '7' => '7', '8' => '8', '9' => '9', '10' => '10'),
    '#description' => t('How many times per minute clickthroughs will be tracked from a single IP address. This will help prevent manipulation of forward clickthrough statistics.'),
  );

  $form['#submit'][] = 'forward_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Additional submit handler for administrative settings to handle per-node-type display settings
 */
function forward_admin_settings_submit($form, &$form_state) {
  $types = node_type_get_types();
  foreach ($types as $type => $info) {
    if (!empty($form_state['values']['forward_display_types'][$type])) {
      variable_set('forward_display_' . $type, TRUE);
    }
    else {
      variable_set('forward_display_' . $type, FALSE);
    }
  }
  unset($form_state['values']['forward_display_types']);
}
