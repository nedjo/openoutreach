<?php
// $Id: media.pages.inc,v 1.29 2011/01/13 01:42:01 effulgentsia Exp $

/**
 * @file
 * Common pages for the Media module.
 */

/**
 * Menu callback; view a single piece of media.
 */
function media_file_view($media) {
  // @todo Implement granular editorial access: http://drupal.org/node/696970.
  //   In the meantime, protect information about private files from being
  //   discovered by unprivileged users. Media IDs are autoincrement, so one can
  //   attempt discovery by trying to access different media/ID paths. See also
  //   media_browser_list(). This logic potentially belongs within
  //   media_access(), but that would require extending that function's
  //   signature to accept a $media paramter, and this is temporary code anyway.
  if (!user_access('administer media') && (file_uri_scheme($media->uri) === 'private')) {
    return MENU_ACCESS_DENIED;
  }

  drupal_set_title($media->filename);

  // @TODO maybe something more elegant... ?
  field_attach_prepare_view('media', array($media->fid => $media), 'media_original');
  $build['media'][$media->fid] = field_attach_view('media', $media, 'media_original');

  return $build;
}

/**
 *  Menu callback; display a thumbnail for an AJAX preview.
 */
function media_preview_ajax() {
  $url = $_GET['url'];
  $uri = media_parse_to_uri($url);
  if ($uri) {
    $media = file_uri_to_object($uri);
    drupal_json_output(array(
      'preview' => theme('media_admin_thumbnail', array('file' => $media)),
    ));
  }
  else {
    drupal_json_output(array(
      'error' => t('Invalid URL.'),
    ));
  }
  die();
}

/**
 * Menu callback; presents the Media editing form.
 */
function media_page_edit($media) {
  drupal_set_title(t('<em>Edit @type</em> @title', array('@type' => $media->type, '@title' => $media->filename)), PASS_THROUGH);
  return drupal_get_form('media_edit', $media);
}

/**
 * Menu callback; presents the Media editing form for multiple items.
 */
function media_page_multiedit($media_items) {
  if (!module_exists('multiform')) {
    drupal_set_message('To edit multiple media items, you must install the multiform module.');
  }
  $i = 0;
  foreach ($media_items as $item) {
    // To maintain unique form_ids, increment this counter.
    // @see media_forms().
    $i++;
    $forms[] = array("media_edit_$i", $item);
  }
  
  $form = call_user_func_array('multiform_get_form', $forms);
  $form['#attributes']['class'][] = 'media-multiedit-form';
  
  unset($form['buttons']['Delete']);
  // Would be nice to add this to show a message, but not working.
  // Can debug.
  //$form['buttons']['Save']['#submit'][] = 'media_page_multiedit_submit';
  
  drupal_set_title(t('Editing multiple media files'));
  return $form;
}

/**
 * Menu callback; shows delete confirmation form.
 */
function media_page_delete($media) {
  drupal_set_title(t('<em>Delete @type</em> @title', array('@type' => $media->type, '@title' => $media->filename)), PASS_THROUGH);
  // Don't bother showing the form if the item is in use, since we won't allow
  // them to delete it anyway. Note that file_usage_list() requires a stdClass,
  // so we can't pass the $media object in directly.
  $file = file_load($media->fid);
  $references = file_usage_list($file);
  if (!empty($references)) {
    return t('The file %title is in use and cannot be deleted.', array('%title' => $media->filename));
  }
  else {
    $files = array($media->fid => $media);
    return drupal_get_form('media_multiple_delete_confirm', $files, '<front>', 'media/' . $media->fid);
  }
}

/**
 * Confirm the request to delete files.
 */
function media_multiple_delete_confirm($form, &$form_state, $files, $redirect_on_success = NULL, $redirect_on_cancel = NULL) {
  $form['files'] = array('#tree' => TRUE);
  $form['file_titles'] = array('#theme' => 'item_list');
  foreach ($files as $fid => $value) {
    $title = db_query('SELECT filename FROM {file_managed} WHERE fid = :fid', array(':fid' => $fid))->fetchField();
    $form['files'][$fid] = array(
      '#type' => 'value',
      '#value' => $fid,
    );
    $form['file_titles']['#items'][] = check_plain($title);
  }
  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
  if (isset($redirect_on_success)) {
    $form['redirect_on_success'] = array(
      '#type' => 'value',
      '#value' => $redirect_on_success,
    );
  }
  $form['#submit'][] = 'media_multiple_delete_confirm_submit';

  $confirm_question = format_plural(count($files),
                                  'Are you sure you want to delete this item?',
                                  'Are you sure you want to delete these items?');

  return confirm_form($form,
    $confirm_question,
    isset($redirect_on_cancel) ? $redirect_on_cancel : current_path(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel'));
}

/**
 * Attempt to delete files and notify the user of the result.
 */
function media_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $results = array();
    $files = array_keys($form_state['values']['files']);
    foreach ($files as $fid) {
      $file = file_load($fid);
      $files[$fid] = $file;
      $results[$fid] = file_delete($file);
    }
    // The result of file_delete can be an array if the file is in use, or TRUE/FALSE.
    foreach ($results as $fid => $result) {
      if (is_array($result)) {
        drupal_set_message(t('The file @title is in use and cannot be deleted.', array('@title' => $files[$fid]->filename)), 'warning');
      }
      elseif (!$result) {
        drupal_set_message(t('The file @title was not deleted due to an error.', array('@title' => $files[$fid]->filename)), 'error');
      }
      else {
        $message = t('File @title was deleted', array('@title' => $files[$fid]->filename));
        watchdog('media', $message);
        drupal_set_message($message);
      }
    }
    if (isset($form_state['values']['redirect_on_success'])) {
      $form_state['redirect'] = $form_state['values']['redirect_on_success'];
    }
  }
}


/**
 * Form callback for adding media via an upload form.
 * @todo: should use the AJAX uploader
 */
function media_add_upload($form, &$form_state, $types = NULL) {

  $validators = array(
   'file_validate_extensions' => array(media_variable_get('file_extensions')),
   'file_validate_size' => array(parse_size(media_variable_get('max_filesize'))),
  );

  //@todo add additional validators for media types allowed.
  if ($types) {
    $validators['media_file_validate_types'] = array($types);
  }
  
  // A blank set of allowed file extensions means no need to validate.
  if (!$validators['file_validate_extensions'][0]) {
    unset($validators['file_validate_extensions']);
  }
  // Use the PHP limit for filesize if no variable was set.
  if (!$validators['file_validate_size']) {
    $validators['file_validate_size'] = file_upload_max_size();
  }

  if ($validators['file_validate_size'][0] == 0) {
    unset($validators['file_validate_size']);
  }

  $form['#validators'] = $validators;
  
  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload a new file'),
    '#description' => theme('file_upload_help', array('description' => '', 'upload_validators' => $validators)),
    '#upload_validators' => $validators,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validate the generic file upload with the global media settings.
 */
function media_add_upload_validate($form, &$form_state) {
  // Save the file as a temporary file.
  $file = file_save_upload('upload', $form['#validators']);
  
  if ($file === NULL) {
    form_set_error('upload', t("No file appears to have been selected."));
  }
  elseif ($file === FALSE) {
    form_set_error('upload', t("Failed to upload the file."));
  }
  else {
    $form_state['values']['upload'] = $file;
  }
}

/**
 * Upload a file.
 */
function media_add_upload_submit($form, &$form_state) {
  $scheme = variable_get('file_default_scheme', 'public') . '://';
  $file = $form_state['values']['upload'];
  _media_save_file_permenently($file);

  $destination = file_stream_wrapper_uri_normalize($scheme . $file->filename);

  $defaults = array (
    'display' => TRUE,
  );

  // Save the uploaded file.
  $file = file_move($file, $destination, FILE_EXISTS_RENAME);

  if ($file) {
    drupal_set_message(t('The file @name was uploaded', array('@name' => $file->filename)));
  }
  else {
    drupal_set_message(t('An error occurred and no file was uploaded.'), 'error');
    return;
  }

  $form_state['redirect'] = array('media/browser', array('query' => array('render' => 'media-popup', 'fid' => $file->fid)));
}

function media_add_upload_multiple($form, &$form_state, $types) {
  $form = media_add_upload($form, $form_state, $types);
  unset($form['upload']['#title']);
  // The validators will be set from plupload anyway.  This isn't pretty, but don't
  // it to show up twice.
  unset($form['upload']['#description']);
  
  $form['upload']['#type'] = 'plupload';
  $form['submit']['#value'] = t('Start upload');
  return $form;
}

function media_add_upload_multiple_submit($form, &$form_state) {
  $scheme = variable_get('file_default_scheme', 'public') . '://';
  $saved_files = array();
  // We can't use file_save_upload() because of http://www.jacobsingh.name/content/tight-coupling-no-not
  foreach ($form_state['values']['upload'] as $uploaded_file) {
    if ($uploaded_file['status'] == 'done') {
      $source = $uploaded_file['tmppath'];
      $destination = file_stream_wrapper_uri_normalize($scheme . $uploaded_file['name']);
      // Rename it to its original name, and put it in its final home.
      // Note - not using file_move here because if we call file_get_mime
      // (in file_uri_to_object) while it has a .tmp extension, it horks.
      
      $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
      
      $file = file_uri_to_object($destination);
      file_save($file);
      _media_save_file_permenently($file);
      
      $saved_files[] = $file;
    }
    else {
      // @todo: move this to element validate or something and clean up t().
      form_set_error('pud', "Upload of {$uploaded_file['name']} failed");
    }
  }
  // Get a list of fids to pass back.
  $fids = array();
  foreach ($saved_files as $file) {
    $fids[] = $file->fid;
  }
  $form_state['redirect'] = array('media/browser', array('query' => array('render' => 'media-popup', 'fid' => $fids)));
}

/**
 * Form builder: Builds the edit file form.
 */
function media_edit($form, $form_state, $media) {
  field_attach_form('media', $media, $form, $form_state);
  unset($form['file']);

  $form['#attached'] = array(
    'css' => array(drupal_get_path('module', 'media') . '/css/media.css'),
  );

  // Not sure about this class name, seems to indicate the style.
  $form['#attributes']['class'][] = 'media-image-left';
  $form['#attributes']['class'][] = 'media-edit-form';
  
  $form['preview'] = field_view_field('media', $media, 'file', 'media_preview');
  $form['preview']['#weight'] = -10;
  $form['preview']['#suffix'] = '<div class="no-overflow">';

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['#prefix'] = '</div>';
  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 15,
    '#submit' => array('media_edit_delete_submit'),
  );
  
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('media_edit_submit'),
  );

  $form['fid'] = array(
    '#type' => 'hidden',
    '#value' => $media->fid,
  );

  return $form;
}

function media_edit_validate($form, &$form_state) {
  $media = media_load($form_state['values']['fid']);
  field_attach_form_validate('media', $media, $form, $form_state);
}

/**
 * Process media_edit form submissions.
 */
function media_edit_submit($form, &$form_state) {
  $media = media_load($form_state['values']['fid']);
  field_attach_submit('media', $media, $form, $form_state);
  media_save($media);
  $form_state['redirect'] = 'media/' . $media->fid;
}

function media_edit_delete_submit($form, &$form_state) {
  $fid = $form_state['values']['fid'];
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $form_state['redirect'] = array('media/' . $fid . '/delete', array('query' => $destination));
}

function media_add_remote($form, &$form_state) {
  // Totally prototyping code to show designs.
  $form['sources'] = array(
    '#type' => 'vertical_tabs',
    '#title' => 'Sources',
  );

  $form['sources']['paste'] = array(
    '#type' => 'fieldset',
    '#title' => 'Paste URL or embed code',
  );


  $providers = '';
  $providers .= '<img style="height:50px; margin:20px" src="http://www.macuser.com/2008/10/09/top_youtube_logo_31_Dec_06.jpg">';
  $providers .= '<img style="height:50px; margin:20px" src="http://jasonhilldesign.com/FlikrLogo.jpg">';
  $form['sources']['paste']['code'] = array(
    '#type' => 'textarea',
    '#title' => t('URL or embed code'),
    '#description' => t('The following providers are supported: <br/>' . $providers),
  );

  $form['sources']['youtube'] = array(
    '#type' => 'fieldset',
    '#title' => 'YouTube',
    '#description' => t(''),
    '#attributes' => array('style' => 'height: 300px; overflow:auto'),
  );

  $form['sources']['flikr'] = array(
    '#type' => 'fieldset',
    '#title' => 'Flikr',
  );

  $box = '<div style="width:100px; height:100px; border:1px solid blue; padding:10px; float:left; margin:5px;"> Video </div>';
  $boxes = '';
  for ($i = 0; $i < 10; $i++) {
    $boxes .= $box;
  }
  $form['sources']['youtube']['stupid'] = array(
    '#markup' => $boxes,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#attributes' => array('style' => 'float:right'),
    '#suffix' => '<br style="clear:both" />',
  );

  return $form;
}

