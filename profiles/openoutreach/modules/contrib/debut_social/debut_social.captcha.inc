<?php
/**
 * @file
 * debut_social.captcha.inc
 */

/**
 * Implementation of hook_captcha_default_points().
 */
function debut_social_captcha_default_points() {
  $export = array();

  $captcha = new stdClass;
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'forward_form';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['forward_form'] = $captcha;

  return $export;
}
