<?php
// $Id: media_internet.api.php,v 1.2 2010/09/03 21:51:13 JacobSingh Exp $

/**
 * Implementors return an multidim array, keyed by a class name
 * with the following elements:
 *
 * - title
 * - image (optional)
 * - hidden: bool If the logo should be shown on form. (optional)
 * - weight (optional)
 */
function hook_media_internet_providers() {
  return array(
    'youtube' => array(
      'title' => 'youtube',
      'image' => 'youtube.jpg'
    ),
  );
}

?>