<?php
/**
 * @file
 * openoutreach_front_page.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function openoutreach_front_page_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'front_page_upper_section';
  $mini->category = 'Front';
  $mini->admin_title = 'Front page upper section';
  $mini->admin_description = 'For displaying content panes capturing top stories promoted to the front page';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '309c6425-8b81-49f7-b72a-dd1723a4aebb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3ead5cdd-f180-4bc0-83fa-9b69d6c66dde';
    $pane->panel = 'left';
    $pane->type = 'views_panes';
    $pane->subtype = 'front_page_top_stories-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '3ead5cdd-f180-4bc0-83fa-9b69d6c66dde';
    $display->content['new-3ead5cdd-f180-4bc0-83fa-9b69d6c66dde'] = $pane;
    $display->panels['left'][0] = 'new-3ead5cdd-f180-4bc0-83fa-9b69d6c66dde';
    $pane = new stdClass();
    $pane->pid = 'new-c0265b90-e8f4-4a69-81fd-82fed50eaee1';
    $pane->panel = 'right';
    $pane->type = 'views_panes';
    $pane->subtype = 'front_page_top_stories-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'c0265b90-e8f4-4a69-81fd-82fed50eaee1';
    $display->content['new-c0265b90-e8f4-4a69-81fd-82fed50eaee1'] = $pane;
    $display->panels['right'][0] = 'new-c0265b90-e8f4-4a69-81fd-82fed50eaee1';
    $pane = new stdClass();
    $pane->pid = 'new-2c1a8476-1d85-448e-ad4c-b6a5189075ea';
    $pane->panel = 'top';
    $pane->type = 'views_panes';
    $pane->subtype = 'front_page_top_stories-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '2c1a8476-1d85-448e-ad4c-b6a5189075ea';
    $display->content['new-2c1a8476-1d85-448e-ad4c-b6a5189075ea'] = $pane;
    $display->panels['top'][0] = 'new-2c1a8476-1d85-448e-ad4c-b6a5189075ea';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-2c1a8476-1d85-448e-ad4c-b6a5189075ea';
  $mini->display = $display;
  $export['front_page_upper_section'] = $mini;

  return $export;
}
