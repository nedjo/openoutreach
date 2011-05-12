<?php

/**
 * @file
 * Administrative page callbacks for Widget Services module.
 */

/**
 * Menu callback administration settings for widget options.
 */
function  widget_services_admin() {
  $form['twitter_widget'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Twitter Widget'),
  );
  $form['twitter_widget']['service_links_tw_data_count'] = array(
    '#type' => 'select',
    '#title' => t('Counter'),
    '#default_value' => variable_get('service_links_tw_data_count', 'horizontal'),
    '#options' => array(
      'horizontal' => t('Horizontal'),
      'vertical' => t('Vertical'),
      'none' => t('None'),
    ),
  );
  $form['twitter_widget']['service_links_tw_data_via'] = array(
    '#type' => 'textfield',
    '#field_prefix' => '@',
    '#title' => t('Via user'),
    '#description' => t('Add here your screen name.'),
    '#default_value' => variable_get('service_links_tw_data_via', ''),
    '#size' => 40,
  );
  //data-related
  //lang
  //counturl

  $form['facebook_like'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Facebook Like'),
  );
  $form['facebook_like']['service_links_fl_layout'] = array(
    '#type' => 'select',
    '#title' => t('Layout'),
    '#default_value' => variable_get('service_links_fl_layout', 'button_count'),
    '#options' => array(
      'standard' => t('Standard'),
      'button_count' => t('Button Count'),
      'box_count' => t('Box Count'),
    ),
  );
  $form['facebook_like']['service_links_fl_width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('service_links_fl_width', '100'),
    '#description' => t('A good value for button layout is 100, for box layout is 80 and for standard layout 450'),
    '#size' => '10',
  );
  $form['facebook_like']['service_links_fl_font'] = array(
    '#title' => t('Font'),
    '#type' => 'select',
    '#default_value' => variable_get('service_links_fl_font', ''),
    '#options' => array(
      '' => t('None'),
      'arial' => t('Arial'),
      'lucida grande' => t('Lucida Grande'),
      'segoe ui' => t('Segoe Ui'),
      'tahoma' => t('Tahoma'),
      'trebuchet ms' => t('Trebuchet Ms'),
      'verdana' => t('Verdana'),
    ),
  );
  $form['facebook_like']['service_links_fl_show_faces'] = array(
    '#title' => t('Show Faces'),
    '#type' => 'radios',
    '#default_value' => variable_get('service_links_fl_show_faces', 'false'),
    '#options' => array(
      'true' => t('Yes'),
      'false' => t('No'),
    ),
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['facebook_like']['service_links_fl_colorscheme'] = array(
    '#title' => t('Color Scheme'),
    '#type' => 'radios',
    '#default_value' => variable_get('service_links_fl_colorscheme', 'light'),
    '#options' => array(
      'light' => t('Light'),
      'dark' => t('Dark'),
    ),
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['facebook_like']['service_links_fl_action'] = array(
    '#title' => t('Action'),
    '#type' => 'radios',
    '#default_value' => variable_get('service_links_fl_action', 'like'),
    '#options' => array(
      'like' => t('Like'),
      'recommended' => t('Recommended'),
    ),
    '#attributes' => array('class' => array('container-inline')),
  );
 
  $form['facebook_widget'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Facebook Share'),
  );
  $form['facebook_widget']['service_links_fs_type'] = array(
    '#title' => t('Type'),
    '#type' => 'select',
    '#default_value' => variable_get('service_links_fs_type', 'button_count'),
    '#options' => array(
      'button_count' => t('Button Count'),
      'box_count' => t('Box Count'),
      'icon_link' => t('Icon Link'),
    ),
  );

  return system_settings_form($form);
}
