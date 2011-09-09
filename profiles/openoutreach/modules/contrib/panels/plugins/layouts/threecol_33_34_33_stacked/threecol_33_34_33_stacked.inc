<?php


/**
 * Implementation of hook_panels_layouts().
 */
function panels_threecol_33_34_33_stacked_panels_layouts() {
  $items['threecol_33_34_33_stacked'] = array(
    'title' => t('Three column 33/34/33 stacked'),
    'icon' => 'threecol_33_34_33_stacked.png',
    'theme' => 'panels_threecol_33_34_33_stacked',
    'css' => 'threecol_33_34_33_stacked.css',
    'regions' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
