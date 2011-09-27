<?php

/**
 * Implements hook_skinr_skin_PLUGIN_info().
 */
function skinr_test_skinr_skin_example_info() {
  $skins['skinr_test_example'] = array(
    'title' => t('Example skin plugin'),
  );
  return $skins;
}
