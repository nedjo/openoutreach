<?php

/**
 * By default, designkit produces a full img tag. Override to get just the path.
 * This allows us to e.g. pass the path as a $logo page template variable and also
 * generate dynamic CSS url() values.
 */
function granada_designkit_image($variables) {
  return image_style_url("designkit-image-{$variables['name']}", $variables['uri']);
}

/**
 * If there is no logo from designkit, provide a default one.
 */
function granada_preprocess_page(&$vars) {
  if (!isset($vars['logo']) || empty($vars['logo'])) {
    $vars['logo'] = url(drupal_get_path('theme', 'granada') . '/img/logo.png', array('absolute' => TRUE));
  }
}
