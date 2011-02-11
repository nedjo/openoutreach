<?php
// $Id: styles.theme.inc,v 1.1.4.5 2011/01/11 19:28:41 aaron Exp $

/**
 * @file styles.theme.inc
 * Theme and preprocess functions for the Styles project.
 */

function theme_styles_field_formatter($variables) {
  $element = $variables['element'];
  $formatter = $element['#formatter'];
  $variables['object'] = (object)$variables['object'];
  $output = '';
  if (preg_match('@^styles_(.*?)_(.*?)$@i', $formatter, $matches)) {
    $variables['field_type'] = $field_type = $matches[1];
    $variables['style_name'] = $style_name = $matches[2];
    $output = theme('styles', $variables);
  }
  return $output;
}

function template_preprocess_styles(&$variables) {
  // If we have a Styles object instance already, then honor that.
  // Otherwise, we'll build a new Styles object instance from our settings.
  $variables['instance'] = $variables['instance'] ? $variables['instance'] : styles_instance($variables['field_type'], $variables['style_name'], $variables['object']);

  $variables['instance']->array_push('classes', $variables['style_name']);

  if ($variables['instance']) {
    $variables['prefix'] = $variables['instance']->get_prefix();
    $variables['suffix'] = $variables['instance']->get_suffix();
    $variables['output'] = $variables['instance']->display(TRUE);
  }
  else {
    $variables['output'] = '';
  }
}
