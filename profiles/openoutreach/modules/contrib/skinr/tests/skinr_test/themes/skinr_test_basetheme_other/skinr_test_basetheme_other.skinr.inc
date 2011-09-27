<?php

/**
 * Implements hook_skinr_skin_info().
 */
function skinr_test_basetheme_other_skinr_skin_info() {
  $skins['skinr_test_basetheme_other'] = array(
    'title' => 'Other base theme skin',
    'default status' => 1,
  );
  return $skins;
}
