<?php
// $Id: FileStyles.inc,v 1.1.2.11 2011/01/11 16:40:36 aaron Exp $

/**
 * @file styles/contrib/file_styles/includes/styles/FileStyles.inc
 * Styles definitions for file styles.
 */

class FileStyles extends StylesDefault {
  public $fid;
  public $uri;
  public $title;
  public $alt;

  public $width;
  public $height;

  public $float;

  public $imagecache_preset = '';
  public $link;

  public $wrapper_type = 'span';
  public $classes = array('styles', 'file-styles');

  public $stream_wrapper_instance;

  function get_stream_wrapper_instance() {
    $stream_wrapper_instance = $this->get('stream_wrapper_instance');
    if (!isset($stream_wrapper_instance)) {
      $stream_wrapper_instance = $this->set_stream_wrapper_instance(file_stream_wrapper_get_instance_by_uri($this->get_uri()));
    }
    return $stream_wrapper_instance;
  }
  function set_stream_wrapper_instance($value) {
    return $this->set('stream_wrapper_instance', $value);
  }

  function get_fid() {
    return $this->get('fid');
  }
  function set_fid($value) {
    return $this->set('fid', $value);
  }
  function get_uri() {
    $uri = $this->get('uri');
    if (isset($uri)) {
      return $uri;
    }
    $object = $this->get_object();
    if (isset($object->uri)) {
      return $object->uri;
    }
  }
  function set_uri($value) {
    return $this->set('uri', $value);
  }
  function get_title() {
    return $this->override('title');
  }
  function set_title($value) {
    // @TODO: Token support.
    return $this->set('title', $value);
  }
  function get_alt() {
    return $this->override('alt');
  }
  function set_alt($value) {
    return $this->set('alt', $value);
  }
  function get_width() {
    return $this->override('width');
  }
  function set_width($value) {
    return $this->set('width', $value);
  }
  function get_height() {
    return $this->override('height');
  }
  function set_height($value) {
    return $this->set('height', $value);
  }
  function get_image_style() {
    return $this->get('image_style');
  }
  function set_image_style($value) {
    return $this->set('image_style', $value);
  }
  function get_link() {
    return $this->get('link');
  }
  function set_link($value) {
    return $this->set('link', $value);
  }
  function get_float() {
    return $this->override('float');
  }
  function set_float($value) {
    if ($value) {
      $this->set_prefix('<span class="styles file-styles file-styles-float-'. filter_xss($value) .'">');
    }
    else {
      $this->set_prefix('<span class="styles file-styles">');
    }
    return $this->set('float', $value);
  }

  function set_image_uri($value) {
    return $this->set('image_uri', $value);
  }
  function get_image_uri() {
    if ($image_uri = $this->get('image_uri')) {
      return $image_uri;
    }
    return $this->get_uri();
  }

  // Allow WYSIWYG to override the values.
  public function override($attribute) {
    $object = $this->get_object();
    if (isset($object->override) && is_array($object->override) && isset($object->override[$attribute])) {
      return $object->override[$attribute];
    }
    return $this->get($attribute);
  }

  // Effect callbacks when rendering.
  function thumbnail($effect) {
    $attributes = array();
    $width = $this->get_width();
    $height = $this->get_height();
    if (isset($width)) {
      $attributes['width'] = $width;
    }
    if (isset($height)) {
      $attributes['height'] = $height;
    }

    // Set any WYSIWYG prescribed styles.
    $styles = array();
    foreach (array('border-width', 'border-style', 'margin', 'margin-top', 'margin-right', 'margin-bottom', 'margin-left') as $attribute) {
      $value = $this->get($attribute);
      if (isset($value)) {
        $styles[$attribute] = $attribute .':'. check_plain($value);
      }
    }

    if (!empty($styles)) {
      $attributes['style'] = implode(';', $styles);
    }

    if ($image_uri = $this->get_image_uri()) {
      $this->set_output(theme('file_styles_image', array('image_uri' => $image_uri, 'attributes' => $attributes, 'alt' => $this->get_alt(), 'title' => $this->get_title(), 'image_style' => $this->get_image_style(), 'instance' => $this)));
    }
  }

  function resize($effect) {
    if (isset($effect['width'])) {
      $this->set_width($effect['width']);
    }
    if (isset($effect['height'])) {
      $this->set_height($effect['height']);
    }
  }

  function float($effect) {
    $this->set_float($effect['float']);
  }

  function image_style($effect) {
    $this->set_image_style($effect['image_style']);
  }

  function link_to_media($effect) {
    $this->set_link(TRUE);
    if (!$this->get_output() && $this->get_title()) {
      $this->set_output(l($this->get_title(), 'media/'. $this->get_fid()));
    }
  }

  function link_to_path($effect) {
    $this->set_link($effect['path']);
    if (!$this->get_output && $this->get_title()) {
      $this->set_output(l($this->get_title, $effect['path']));
    }
  }

  function teaser($effect) {
    $this->set('file', file_load($this->get_fid()));
    $this->set_output(file_view($this->get('file')));
  }

  /**
   * Override the render function to always display a thumbnail in the wysiwyg.
   */
  public function render($reset = FALSE) {
    $object = $this->get_object();
    if (isset($object->override) && is_array($object->override) && isset($object->override['wysiwyg']) && $object->override['wysiwyg']) {
      $this->push_effect(array('name' => 'thumbnail', 'settings' => array()));
    }
    return parent::render($reset);
  }

}
