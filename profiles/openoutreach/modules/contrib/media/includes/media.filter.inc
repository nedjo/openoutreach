<?php

/**
 * @file
 * Functions related to the WYSIWYG editor and the media input filter.
 *
 * @TODO: Rename this file?
 */

/**
 * Implementation of hook_wysiwyg_include_directory()
 */
function media_wysiwyg_include_directory($type) {
  switch($type) {
    case 'plugins':
      return 'wysiwyg_plugins';
        break;
    }
}

/**
 * Filter callback for media markup filter.
 *
 * @TODO check for security probably pass text through filter_xss
 * @return unknown_type
 */
function media_filter($text) {
  $text = ' ' . $text . ' ';
  $text = preg_replace_callback("/\[\[.*?]]/s",'media_token_to_markup', $text);

  return $text;
}

/**
 *  Filter callback for media url filter.
 *  @TODO: There are currently problems with this. For instance, if a file is
 *  to be loaded from a remote location here, it will be recreated multiple
 *  times, each time this filter is called. If we want to continue supporting
 *  this feature, we would need to probably create a new stream or other way
 *  to lookup a remote file w/ its local version. Probably best as a contributed
 *  module because of this difficulty. ~ aaron.
 */
function media_url_filter($text, $filter) {
  $text = ' '. $text .' ';

  // Need to attach the variables to the callback after the regex.
  $callback = _media_url_curry('_media_url_parse_full_links', 1);

  // Match absolute URLs.
  $text = preg_replace_callback("`(<p>|<li>|<br\s*/?>|[ \n\r\t\(])((http://|https://)([a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&=/;-]))([.,?!]*?)(?=(</p>|</li>|<br\s*/?>|[ \n\r\t\)]))`i", $callback, $text);

  return $text;
}

/**
 * If one of our allowed providers knows what to do with the url,
 * then let it embed the video.
 *
 * @param int $filter
 *  The filter id.
 * @param array $match
 *  The matched text from our regex.
 *
 * @return string
 *  The replacement text for the url.
 */
function _media_url_parse_full_links($match) {
  // Get just the URL.
  $match[2] = check_url(decode_entities($match[2]));
  try {
    $file = media_parse_to_file($match[2]);
  }
  catch (Exception $e) {
    // Ignore errors; pass the original text for other filters to deal with.
    return $match[0];
  }

  if ($file->fid) {
    // Return the embedded media.
    // Now load the desired media to display.
    $medias = entity_load('media', array($file->fid));

    if (!empty($medias)) {
      $media = array_pop($medias);

      // Generate a preview of the file
      // @TODO: Allow user to change the formatter in the filter settings.
      $preview = field_view_field('media', $media, 'file', 'media_large');
      $preview['#show_names'] = TRUE;

      return drupal_render($preview);
    }
  }

  // Nothing was parsed; return the original text.
  return $match[0];
}

function _media_url_curry($func, $arity) {
  return create_function('', "
    \$args = func_get_args();
    if(count(\$args) >= $arity)
        return call_user_func_array('$func', \$args);
    \$args = var_export(\$args, 1);
    return create_function('','
        \$a = func_get_args();
        \$z = ' . \$args . ';
        \$a = array_merge(\$z,\$a);
        return call_user_func_array(\'$func\', \$a);
    ');
  ");
}

/**
 * Replace callback to convert tag into markup
 * @param string $match
 * Takes a match of tag code
 * @param boolean $wysiwyg
 *   Set to TRUE if called from within the WYSIWYG text area editor.
 * @return
 * Return the replaced markup
 */
function media_token_to_markup($match, $wysiwyg = FALSE) {
  $match = str_replace("[[","",$match);
  $match = str_replace("]]","",$match);
  $tag = $match[0];

  try {
    if (!is_string($tag)) {
      throw new Exception('Unable to find matching tag');
    }
    
    $media = drupal_json_decode($tag);

    if (!isset($media['fid'])) {
      throw new Exception('No file Id');
    }
    if (!isset($media['view_mode'])) {
      // Should we log or throw an exception here instead?
      // Do we need to validate the view mode for fields API?
      $media['view_mode'] = media_variable_get('wysiwyg_default_view_mode');
    }
    $media_obj = media_load($media['fid']);
    if (!$media_obj) {
     throw new Exception('Could not load media object');
    }

    // Track the fid of this media object in the {media_filter_usage} table.
    media_filter_track_usage($media['fid']);

    $settings = is_array($media['attributes']) ? $media['attributes'] : array();
    $attribute_whitelist = media_variable_get('wysiwyg_allowed_attributes');
    $settings = array_intersect_key($settings, array_flip($attribute_whitelist));

    // @TODO: What case does this provide for?  Can we add this logic in JS when we embed it?
    // This doesn't look great to me.  Also won't work if the style has anything
    // between width and height (or if they are in reverse order).
    if (isset($settings['style'])) {
      if (preg_match('@width: (.+?)px; height: (.+?)px;@i', $settings['style'], $matches)) {
        $settings['width'] = $matches[1];
        $settings['height'] = $matches[2];
      }
    }
    if ($wysiwyg) {
      $settings['wysiwyg'] = $wysiwyg;
    }
  }
  catch (Exception $e) {
    watchdog('media', 'Unable to render media from %tag. Error: %error', array('%tag' => $tag, '%error' => $e->getMessage()));
    return '';
  }

  $file_field = media_get_file_without_label($media_obj, $media['view_mode'], $settings);
  return drupal_render($file_field);
}

/**
 * Builds a map of media tags in the element being rendered to their rendered HTML.
 *
 * The map is stored in JS, so we can transform them when the editor is being displayed.
 *
 * @param array $element
 */
function media_pre_render_text_format($element) {
  // filter_process_format() copies properties to the expanded 'value' child
  // element.
  if (!isset($element['format'])) {
    return $element;
  }
  
  $field = &$element['value'];
  $settings = array(
    'field' => $field['#id'],
  );

  $tagmap = _media_generate_tagMap($field['#value']);

  if (isset($tagmap)) {
    drupal_add_js(array('tagmap' => array_unique($tagmap)), 'setting');
  }
  return $element;
}

/**
 * Generates an array of [inline tags] => <html> to be used in filter
 * replacement and to add the mapping to JS.
 * @param
 * The String containing text and html markup of textarea
 * @return
 * An associative array with tag code as key and html markup as the value.
 *
 * @see
 * media_process_form
 * media_token_to_markup
 */
function _media_generate_tagMap($text) {
  // Making $tagmap static as this function is called many times and
  // adds duplicate markup for each tag code in Drupal.settings JS,
  // so in media_process_form it adds something like tagCode:<markup>,
  // <markup> and when we replace in attach see two duplicate images
  // for one tagCode. Making static would make function remember value
  // between function calls. Since media_process_form is multiple times
  // with same form, this function is also called multiple times.
  static $tagmap = array();
  preg_match_all("/\[\[.*?]]/s", $text, $matches, PREG_SET_ORDER);
  foreach($matches as $match) {
    // We see if tagContent is already in $tagMap, if not we add it
    // to $tagmap.  If we return an empty array, we break embeddings of the same
    // media multiple times.
    if(empty($tagmap[$match[0]])) {
      // @TODO: Total HACK, but better than nothing.
      // We should find a better way of cleaning this up.
      if ($markup_for_media = media_token_to_markup($match, TRUE)) {
        $tagmap[$match[0]] = $markup_for_media;
      } else {
        $tagmap[$match[0]] = '<div><img src="/broken.jpg" height="50px" width="100px"/></div>';
      }
    }
  }
  return $tagmap;
}

/**
 * Form callback used when embedding media.
 *
 * Allows the user to pick a format for their media file.
 * Can also have additional params depending on the media type.
 */
function media_format_form($form, $form_state, $media) {
  // This will vary depending on the media type.
  $form = array();
  $form['#media'] = $media;

  $instance_info = field_info_instance('media', 'file', $media->type);
  $entity_info = entity_get_info('media');
  $view_modes = $entity_info['view modes'];

  $options = array();

  drupal_alter('media_wysiwyg_allowed_view_modes', $media_type, $view_modes);

  foreach ($view_modes as $key => $title) {
    $format = field_get_display($instance_info, $key, $media);
    //If the format is set to hidden, don't offer it
    if ($format['type'] == 'hidden') {
      continue;
    }

    //@TODO: Display more verbose information about which formatter and what it does.
    $options[$key] = $title['label'];
    $file_field = media_get_file_without_label($media, $key, array('wysiwyg' => TRUE));

    // Make a pretty name out of this.
    $formats[$key] = drupal_render($file_field);
  }

  if (!count($formats)) {
    throw new Exception('Unable to continue, no available formats for displaying media.');
    return;
  }

  $default_view_mode = media_variable_get('wysiwyg_default_view_mode');
  if (!isset($formats[$default_view_mode])) {
    $default_view_mode = key($formats);
  }


  // Add JS and settings array of formats.
  $settings = array();
  $settings['media'] = array('formatFormFormats' => $formats);
  drupal_add_js($settings, 'setting');

  drupal_add_library('media', 'media_base');
  drupal_add_library('system', 'form');

  $path = drupal_get_path('module', 'media');
  $form['#attached']['js'][] = $path . '/js/media.format_form.js';
  $form['#attached']['css'][] = $path . '/css/media-format-form.css';

  $form['heading'] = array(
    '#type' => 'markup',
    '#prefix' => '<h1 class="title">',
    '#suffix' => '</h1>',
    '#markup' => t('Embedding %filename', array('%filename' => $media->filename)),
  );

  $preview = media_get_thumbnail_preview($media);

  $form['preview'] = array(
    '#type' => 'markup',
    '#title' => basename($media->uri),
    '#markup' => drupal_render($preview),
  );

  // These will get passed on to WYSIWYG
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('options'),
  );

  $form['options']['format'] = array(
    '#type' => 'select',
    '#title' => t('Current format is'),
    '#options' => $options,
    '#default_value' => $default_view_mode
  );

  // Similar to a form_alter, but we want this to run first so that media.types.inc
  // can add the fields specific to a given type (like alt tags on media).
  // If implemented as an alter, this might not happen, making other alters not
  // be able to work on those fields.
  // @TODO: We need to pass in existing values for those attributes.
  drupal_alter('media_format_form_prepare', $form, $form_state, $media);

  if (!element_children($form['options'])) {
    $form['options']['#attributes'] = array('style' => 'display:none');
  }

  return $form;
}



/**
 * Wrapper around field_view_field, returns the file field w/o a label
 *
 * @param Object $media
 * @param string $view_mode
 * @param array $settings
 *  Any attribute overrides to pass to the style formatter.
 * @return array
 *  drupal_renderable array
 */
function media_get_file_without_label($media, $view_mode, $settings = array()) {
  $instance = field_info_instance('media', 'file', $media->type);
  $format = field_get_display($instance, $view_mode, $media);
  $format['label'] = 'hidden';
  $format['settings'] = array_merge($format['settings'], $settings);
  $media->override = $settings;
  return field_view_field('media', $media, 'file', $format);
}

/**
 * Clears caches that may be affected by the media filter.
 *
 * The media filter calls media_load(). This means that if a media object
 * is updated, the check_markup() and field caches could return stale content.
 * There are several possible approaches to deal with this:
 *  - Disable filter caching in media_filter_info(), this was found to cause a
 *    30% performance hit from profiling four node teasers, due to both the
 *    media filter itself, and other filters that can't be cached.
 *  - Clear the filter and field caches whenever any media node is updated, this
 *    would ensure cache coherency but would reduce the effectiveness of those
 *    caches on high traffic sites with lots of media content updates.
 *  - The approach taken here: Record the fid of all media objects that are
 *    referenced by the media filter. Only clear the filter and field caches
 *    when one of these is updated, as opposed to all media objects.
 *  - @todo: consider an EntityFieldQuery to limit cache clearing to only those
 *    entities that use a text format with the media filter, possibly checking
 *    the contents of those fields to further limit this to fields referencing
 *    the media object being updated. This would need to be implemented
 *    carefully to avoid scalability issues with large result sets, and may
 *    not be worth the effort.
 *
 * @param $fid
 *   Optional media fid being updated. If not given, the cache will be cleared
 *   as long as any file is referenced.
 */
function media_filter_invalidate_caches($fid = FALSE) {
  // If fid is passed, confirm that it has previously been referenced by the
  // media filter. If not, clear the cache if the {media_filter_usage} has any
  // valid records.
  if (($fid && db_query('SELECT fid FROM {media_filter_usage} WHERE fid = :fid', array(':fid' => $fid))->fetchField()) || (!$fid && media_filter_usage_has_records())) {
    // @todo: support entity cache, either via a hook, or using module_exists().
    cache_clear_all('*', 'cache_filter', TRUE);
    cache_clear_all('*', 'cache_field', TRUE);
  }
}

/**
 * Determines if the {media_filter_usage} table has any entries.
 */
function media_filter_usage_has_records() {
  return  (bool) db_query_range('SELECT 1 FROM {media_filter_usage} WHERE fid > :fid', 0, 1, array(':fid' => 0))->fetchField();
}

/**
 * Tracks usage of media fids by the media filter.
 *
 * @param $fid
 *   The media fid.
 */
function media_filter_track_usage($fid) {
  // This function only tracks when fids are found by the media filter.
  // It would be impractical to check when formatted text is edited to remove
  // references to fids, however by keeping a timestamp, we can implement
  // rudimentary garbage collection in hook_flush_caches().
  // However we only need to track that an fid has ever been referenced,
  // not every time, so avoid updating this table more than once per month,
  // per fid.
  $timestamp = db_query('SELECT timestamp FROM {media_filter_usage} WHERE fid = :fid', array(':fid' => $fid))->fetchField();
  if (!$timestamp || $timestamp <= REQUEST_TIME - 86400 * 30) {
    db_merge('media_filter_usage')->key(array('fid' => $fid))->fields(array('fid' => $fid, 'timestamp' => REQUEST_TIME))->execute();
  }
}
