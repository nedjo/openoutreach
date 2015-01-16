<?php
/**
 * @file
 * openoutreach_front_page.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function openoutreach_front_page_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front_page';
  $page->task = 'page';
  $page->admin_title = 'Front page';
  $page->admin_description = 'Front page panel that uses mini panels for displaying views content panes.';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'front_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'css_id' => 'front-page',
    'css' => '.view-front-page-top-stories .views-field-field-content-image img {
  float: left; /* LTR */
  margin-right: 15px;
  margin-bottom: 15px;
  border: 1px solid #C0C0C0;
}

.view-blog .views-row {
  clear: both;
}


#mini-panel-front_page_upper_section div.view-display-id-panel_pane_1 .views-row, #mini-panel-front_page_upper_section .center-wrapper,
#mini-panel-front_page_upper_section > .pane-title {
  clear: both;
  border-top: 1px solid #DDDDDD;
  padding-top: 10px;
}

#mini-panel-front_page_upper_section div.view-display-id-panel_pane_1 .views-field-teaser {
  font-size: 110%;
}

#mini-panel-front_page_upper_section div.view-display-id-panel_pane_2 .views-field-title {
  font-size: 105%;
  font-weight: bold;
}

#mini-panel-front_page_upper_section div.view-display-id-panel_pane_2 .views-row {
  margin-bottom: 9px;
}

#mini-panel-front_page_upper_section div.view-display-id-panel_pane_3 .views-row {
  margin-bottom: 9px;
}

#mini-panel-front_page_upper_section div.view-display-id-panel_pane_3 .views-field-title {
  font-size: 105%;
  font-weight: bold;
}

h2.pane-title {
  font-size: 1.8em;
  font-weight: bold;
  margin-bottom: 5px;
}

#mini-panel-front_page_lower_section div.view-display-id-panel_pane_4 .views-field-title {
  font-size: 105%;
  font-weight: bold;
}

#mini-panel-front_page_lower_section div.view-display-id-panel_pane_4 .views-row {
  border-bottom: 1px dotted #CCCCCC;  
  margin-bottom: 10px;
}

#mini-panel-front_page_lower_section {
  border-top: 1px solid #DDDDDD; 
  padding-top: 10px;
}

#front-page .view-features img {
  float: left;
  margin-right: 5px;
  margin bottom: 5px;
}',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'left_above' => NULL,
      'right_above' => NULL,
      'left_below' => NULL,
      'right_below' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'c0111ac5-9e5b-428a-9cc6-32ec373587eb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-330210f1-27b7-4753-8e31-5dff8a2c6469';
    $pane->panel = 'left_below';
    $pane->type = 'views';
    $pane->subtype = 'article';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'block',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '330210f1-27b7-4753-8e31-5dff8a2c6469';
    $display->content['new-330210f1-27b7-4753-8e31-5dff8a2c6469'] = $pane;
    $display->panels['left_below'][0] = 'new-330210f1-27b7-4753-8e31-5dff8a2c6469';
    $pane = new stdClass();
    $pane->pid = 'new-c9402380-80ad-4004-811b-e3249517a4e9';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'media';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'block',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'c9402380-80ad-4004-811b-e3249517a4e9';
    $display->content['new-c9402380-80ad-4004-811b-e3249517a4e9'] = $pane;
    $display->panels['middle'][0] = 'new-c9402380-80ad-4004-811b-e3249517a4e9';
    $pane = new stdClass();
    $pane->pid = 'new-83bb7725-d215-43dd-9c50-7691283557ae';
    $pane->panel = 'right_below';
    $pane->type = 'views';
    $pane->subtype = 'blog';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'block',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '83bb7725-d215-43dd-9c50-7691283557ae';
    $display->content['new-83bb7725-d215-43dd-9c50-7691283557ae'] = $pane;
    $display->panels['right_below'][0] = 'new-83bb7725-d215-43dd-9c50-7691283557ae';
    $pane = new stdClass();
    $pane->pid = 'new-5df0cd68-8244-45ff-b462-a46ce7d24167';
    $pane->panel = 'top';
    $pane->type = 'views';
    $pane->subtype = 'highlighted';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_content',
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
    $pane->uuid = '5df0cd68-8244-45ff-b462-a46ce7d24167';
    $display->content['new-5df0cd68-8244-45ff-b462-a46ce7d24167'] = $pane;
    $display->panels['top'][0] = 'new-5df0cd68-8244-45ff-b462-a46ce7d24167';
    $pane = new stdClass();
    $pane->pid = 'new-e8840cca-ef6d-4f43-b0b6-91be974d4da8';
    $pane->panel = 'top';
    $pane->type = 'panels_mini';
    $pane->subtype = 'front_page_upper_section';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = 'e8840cca-ef6d-4f43-b0b6-91be974d4da8';
    $display->content['new-e8840cca-ef6d-4f43-b0b6-91be974d4da8'] = $pane;
    $display->panels['top'][1] = 'new-e8840cca-ef6d-4f43-b0b6-91be974d4da8';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front_page'] = $page;

  return $pages;

}
