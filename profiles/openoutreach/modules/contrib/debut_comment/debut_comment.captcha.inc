<?php
/**
 * @file
 * debut_comment.captcha.inc
 */

/**
 * Implementation of hook_captcha_default_points().
 */
function debut_comment_captcha_default_points() {
  $export = array();

  $captcha = new stdClass;
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'user_login';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['user_login'] = $captcha;

  $captcha = new stdClass;
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'user_login_block';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['user_login_block'] = $captcha;

  $captcha = new stdClass;
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'user_register_form';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['user_register_form'] = $captcha;

  return $export;
}
