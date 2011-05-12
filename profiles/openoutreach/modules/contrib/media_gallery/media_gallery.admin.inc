<?php

/**
 * The Galleries settings page will just return the term edit form for the "all galleries" tid.
 *
 */
function media_gallery_admin_settings() {
  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $edit = media_gallery_get_default_gallery_collection();
  return drupal_get_form('taxonomy_form_term', $edit);
}
