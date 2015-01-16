<?php

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'text' => t('Text color'),
    'link' => t('Links color'),
    'linkhover' => t('Links hover color'),
    'headings' => t('Headings color'),
    'sitename' => t('Site-name color'),
    'sitenamehover' => t('Site-name hover color'),
    'slogan' => t('Slogan color'),
    'bodyborder' => t('Body border top color'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Blue (default)'),
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
      'title' => t('Grape'),
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
      'title' => t('Happy'),
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
      'title' => t('Earth'),
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
      'title' => t('Caribbean'),
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

  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'color/colors.css',
  ),
  
  // Files to copy.
  'copy' => array(
    'logo.png',
  ),

  // Gradient definitions.
  'gradients' => array(
    array(
      // (x, y, width, height).
      'dimension' => array(0, 0, 0, 0),
      // Direction of gradient ('vertical' or 'horizontal').
      'direction' => 'vertical',
      // Keys of colors to use for the gradient.
      'colors' => array('top', 'bottom'),
    ),
  ),

  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_css' => 'color/preview.css',
  'preview_js' => 'color/preview.js',
  'preview_html' => 'color/preview.html',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
