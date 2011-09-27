<?php

/**
 * Maintenance page preprocessing
 */
function fusion_core_preprocess_maintenance_page(&$vars) {
  if (class_exists('Database', FALSE)) {
    // set html vars (html.tpl.php is in maintenance-page.tpl.php)
    fusion_core_preprocess_html($vars);  
    // set page vars
    fusion_core_preprocess_page($vars);  
  }
}


/**
 * HTML preprocessing
 */
function fusion_core_preprocess_html(&$vars) {
  global $theme_key, $user;

  // Add to array of helpful body classes.
  if (isset($vars['node'])) {
    // For full nodes.
    $vars['classes_array'][] = ($vars['node']) ? 'full-node' : '';
    // For forums.
    $vars['classes_array'][] = (($vars['node']->type == 'forum') || (arg(0) == 'forum')) ? 'forum' : '';
  }
  else {
    // Forums.
    $vars['classes_array'][] = (arg(0) == 'forum') ? 'forum' : '';
  }
  if (module_exists('panels') && function_exists('panels_get_current_page_display')) {
    $vars['classes_array'][] = (panels_get_current_page_display()) ? 'panels' : '';
  }
  $vars['classes_array'][] = theme_get_setting('sidebar_layout');
  $vars['classes_array'][] = (theme_get_setting('theme_font') != 'none') ? theme_get_setting('theme_font') : '';
  $vars['classes_array'][] = theme_get_setting('theme_font_size');
  $vars['classes_array'][] = (user_access('administer blocks', $user) && theme_get_setting('grid_mask')) ? 'grid-mask-enabled' : '';

  // Add grid classes
  $grid = fusion_core_grid_info();
  
  // Fixed or fluid.
  $vars['classes_array'][] = 'grid-type-' . $grid['type'];
  
  // Number of units in the grid (12, 16, etc.)
  $vars['classes_array'][] = 'grid-width-' . sprintf("%02d", $grid['width']);
  
  // Fluid grid width in %.
  $vars['classes_array'][] = ($grid['type'] == 'fluid') ? theme_get_setting('fluid_grid_width') : '';
  
  // Remove any empty elements in the array.
  $vars['classes_array'] = array_filter($vars['classes_array']);

  // Add a unique page id.
  $vars['body_id'] = 'pid-' . strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', drupal_get_path_alias($_GET['q'])));

  // Add grid, local, & IE stylesheets, including versions inherited from parent themes
  $themes = fusion_core_theme_paths($theme_key);
  foreach ($themes as $name => $path) {
    $file = theme_get_setting('theme_grid') . '.css';
    if (file_exists($path . '/css/' . $file)) {
      drupal_add_css($path . '/css/' . $file, array('basename' => $name . '-' . $file, 'group' => CSS_THEME, 'preprocess' => TRUE));
    }
    if (file_exists($path . '/css/local.css')) {
      drupal_add_css($path . '/css/local.css', array('basename' => $name . '-local.css', 'group' => CSS_THEME, 'preprocess' => TRUE));
    }
    for ($v = 6; $v <= 9; $v++) {
      $file = 'ie' . $v . '-fixes.css';
      if (file_exists($path . '/css/' . $file)) {
        drupal_add_css($path . '/css/' . $file, 
          array(
            'basename' => $name . '-' . $file, 
            'group' => CSS_THEME, 
            'browsers' => array(
              'IE' => 'IE ' . $v, 
              '!IE' => FALSE), 
            'preprocess' => FALSE)
        );
      }
    }
  }
}


/**
 * Page preprocessing
 */
function fusion_core_preprocess_page(&$vars) {
  // Set grid width
  $grid = fusion_core_grid_info();
  $vars['grid_width'] = $grid['name'] . $grid['width'];

  // Adjust width variables for nested grid groups
  $grid_adjusted_groups = (theme_get_setting('grid_adjusted_groups')) ? theme_get_setting('grid_adjusted_groups') : array();
  foreach (array_keys($grid_adjusted_groups) as $group) {
    $width = $grid['width'];
    foreach ($grid_adjusted_groups[$group] as $region) {
      $width = $width - $grid['regions'][$region]['width'];
    }
    if (!$grid['fixed'] && isset($grid['fluid_adjustments'][$group])) {
      $vars[$group . '_width'] = '" style="width:' . $grid['fluid_adjustments'][$group] . '%"';
    }
    else {
      $vars[$group . '_width'] = $grid['name'] . $width;
    }
  }

  // Remove breadcrumbs if disabled
  if (theme_get_setting('breadcrumb_display') == 0) {
    $vars['breadcrumb'] = '';
  }
}


/**
 * Region preprocessing
 */
function fusion_core_preprocess_region(&$vars) {
  static $grid;

  // Initialize grid info once per page
  if (!isset($grid)) {
    $grid = fusion_core_grid_info();
  }

  // Set region variables
  $vars['region_style'] = $vars['fluid_width'] = '';
  $vars['region_name'] = str_replace('_', '-', $vars['region']);
  $vars['classes_array'][] = $vars['region_name'];
  if (in_array($vars['region'], array_keys($grid['regions']))) {
    // Set region full-width or nested style
    $vars['region_style'] = $grid['regions'][$vars['region']]['style'];
    $vars['classes_array'][] = ($vars['region_style'] == 'nested') ? $vars['region_style'] : '';
    $vars['classes_array'][] = $grid['name'] . $grid['regions'][$vars['region']]['width'];
    // Adjust & set region width
    if (!$grid['fixed'] && isset($grid['fluid_adjustments'][$vars['region']])) {
      $vars['fluid_width'] = ' style="width:' . $grid['fluid_adjustments'][$vars['region']] . '%"';
    }
  }
  // Sidebar regions receive common class, "sidebar".
  $sidebar_regions = array('sidebar_first', 'sidebar_second');
  if (in_array($vars['region'], $sidebar_regions)) {
    $vars['classes_array'][] = 'sidebar';
  }
  
}


/**
 * Block preprocessing
 */
function fusion_core_preprocess_block(&$vars) {
  global $theme_info, $user;
  static $grid;

  // Exit if block is outside a defined region
  if (!in_array($vars['block']->region, array_keys($theme_info->info['regions']))) {
    return;
  }

  // Initialize grid info once per page
  if (!isset($grid)) {
    $grid = fusion_core_grid_info();
  }

  // Increment block count for current block's region, add first/last position class
  $grid['regions'][$vars['block']->region]['count'] ++;
  $region_count = $grid['regions'][$vars['block']->region]['count'];
  $total_blocks = $grid['regions'][$vars['block']->region]['total'];
  $vars['classes_array'][] = ($region_count == 1) ? 'first' : '';
  $vars['classes_array'][] = ($region_count == $total_blocks) ? 'last' : '';
  $vars['classes_array'][] = $vars['block_zebra'];

  // Set a default block width if not already set by Skinr
  $classes = implode(' ', $vars['classes_array']);
  
  // Special treatment for node_top and node_bottom regions.  
  // They are rendered inside of the $content region, so they need to be adjusted to fit the grid properly.
  $assign_grid_units = ($vars['block']->region == 'node_top' || $vars['block']->region == 'node_bottom') ? FALSE : TRUE;
    
  if (strpos($classes, $grid['name']) === false && $assign_grid_units) {
    // Stack blocks vertically in sidebars by setting to full sidebar width
    if ($vars['block']->region == 'sidebar_first') {
      $width = $grid['fixed'] ? $grid['sidebar_first_width'] : $grid['width'];  // Sidebar width or 100% (if fluid)
    }
    elseif ($vars['block']->region == 'sidebar_second') {
      $width = $grid['fixed'] ? $grid['sidebar_second_width'] : $grid['width'];  // Sidebar width or 100% (if fluid)
    }
    else {
      // Default block width = region width divided by total blocks, adding any extra width to last block
      $region_width = ($grid['fixed']) ? $grid['regions'][$vars['block']->region]['width'] : $grid['width'];  // fluid grid regions = 100%
      $width_adjust = (($region_count == $total_blocks) && ($region_width % $total_blocks)) ? $region_width % $total_blocks : 0;
      $width = ($total_blocks) ? floor($region_width / $total_blocks) + $width_adjust : 0;
    }
    $vars['classes_array'][] = $grid['name'] . $width;
  }
}


/**
 * Node preprocessing
 */
function fusion_core_preprocess_node(&$vars) {
  // Add to array of handy node classes
  $vars['classes_array'][] = $vars['zebra'];                              // Node is odd or even
  $vars['classes_array'][] = (!$vars['teaser']) ? 'full-node' : '';       // Node is teaser or full-node

  $node_top_blocks = block_get_blocks_by_region('node_top');
  $node_bottom_blocks = block_get_blocks_by_region('node_bottom');
  if ($node_top_blocks) {
    $vars['node_top'] = $node_top_blocks; 
  }
  if ($node_bottom_blocks) {
    $vars['node_bottom'] = $node_bottom_blocks;
  }
}


/**
 * Comment preprocessing
 */
function fusion_core_preprocess_comment(&$vars) {
  static $comment_odd = TRUE;                                                                             // Comment is odd or even

  // Add to array of handy comment classes
  $vars['classes_array'][] = $comment_odd ? 'odd' : 'even';
  $comment_odd = !$comment_odd;
}


/**
 * Views preprocessing
 * Add view type class (e.g., node, teaser, list, table)
 */
function fusion_core_preprocess_views_view(&$vars) {
  $vars['css_name'] = $vars['css_name'] .' view-style-'. drupal_clean_css_identifier(strtolower($vars['view']->plugin_name));
}


/**
 * Search result preprocessing
 */
function fusion_core_preprocess_search_result(&$vars) {
  static $search_zebra = 'even';

  $search_zebra = ($search_zebra == 'even') ? 'odd' : 'even';
  $vars['search_zebra'] = $search_zebra;
  $result = $vars['result'];
  $vars['url'] = check_url($result['link']);
  $vars['title'] = check_plain($result['title']);

  // Check for snippet existence. User search does not include snippets.
  $vars['snippet'] = '';
  if (isset($result['snippet']) && theme_get_setting('search_snippet')) {
    $vars['snippet'] = $result['snippet'];
  }

  $info = array();
  if (!empty($result['type']) && theme_get_setting('search_info_type')) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user']) && theme_get_setting('search_info_user')) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date']) && theme_get_setting('search_info_date')) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    // $info = array_merge($info, $result['extra']);  Drupal bug?  [extra] array not keyed with 'comment' & 'upload'
    if (!empty($result['extra'][0]) && theme_get_setting('search_info_comment')) {
      $info['comment'] = $result['extra'][0];
    }
    if (!empty($result['extra'][1]) && theme_get_setting('search_info_upload')) {
      $info['upload'] = $result['extra'][1];
    }
  }

  // Provide separated and grouped meta information.
  $vars['info_split'] = $info;
  $vars['info'] = implode(' - ', $info);

  // Provide alternate search result template.
  $vars['template_files'][] = 'search-result-'. $vars['module'];
}


/**
 * Header region override
 * Prints header blocks without region wrappers
 */
function fusion_core_region__header($vars) {
  return $vars['content'];
}


/**
 * File element override
 * Sets form file input max width
 */
function fusion_core_file($vars) {
  $vars['element']['#size'] = ($vars['element']['#size'] > 40) ? 40 : $vars['element']['#size'];
  return theme_file($vars);
}


/**
 * Custom theme functions
 */
function fusion_core_theme() {
  return array(
    'grid_block' => array(
      'variables' => array('content' => NULL, 'id' => NULL),
    ),
  );
}

/**
 * Returns a list of blocks.  
 * Uses Drupal block interface and appends any blocks assigned by the Context module.
 */
function fusion_core_block_list($region) {
  $drupal_list = block_list($region);
  if (module_exists('context')) {
    $context = context_get_plugin('reaction', 'block');
    $context_list = $context->block_list($region);
    $drupal_list = array_merge($context_list, $drupal_list);
  }
  return $drupal_list;
}

function fusion_core_grid_block($vars) {
  $output = '';
  if ($vars['content']) {
    $id = $vars['id'];
    $output .= '<div id="' . $id . '" class="' . $id . ' block">' . "\n";
    $output .= '<div id="' . $id . '-inner" class="' . $id . '-inner gutter">' . "\n";
    $output .= $vars['content'];
    $output .= '</div><!-- /' . $id . '-inner -->' . "\n";
    $output .= '</div><!-- /' . $id . ' -->' . "\n";
  }
  return $output;
}


/**
 * Generate initial grid info
 */
function fusion_core_grid_info() {
  global $theme_key;
  static $grid;

  if (!isset($grid)) {
    $grid = array();
    $grid['name'] = substr(theme_get_setting('theme_grid'), 0, 7);
    $grid['type'] = substr(theme_get_setting('theme_grid'), 7);
    $grid['fixed'] = (substr(theme_get_setting('theme_grid'), 7) != 'fluid') ? true : false;
    $grid['width'] = (int)substr($grid['name'], 4, 2);
    $grid['sidebar_first_width'] = (fusion_core_block_list('sidebar_first')) ? theme_get_setting('sidebar_first_width') : 0;
    $grid['sidebar_second_width'] = (fusion_core_block_list('sidebar_second')) ? theme_get_setting('sidebar_second_width') : 0;
    $grid['regions'] = array();
    $regions = array_keys(system_region_list($theme_key, REGIONS_VISIBLE));
    $nested_regions = theme_get_setting('grid_nested_regions');
    $adjusted_regions = theme_get_setting('grid_adjusted_regions');
    foreach ($regions as $region) {
      $region_style = 'full-width';
      $region_width = $grid['width'];
      if ($region == 'sidebar_first' || $region == 'sidebar_second') {
        $region_width = ($region == 'sidebar_first') ? $grid['sidebar_first_width'] : $grid['sidebar_second_width'];
      }
      if ($nested_regions && in_array($region, $nested_regions)) {
        $region_style = 'nested';
        if ($adjusted_regions && in_array($region, array_keys($adjusted_regions))) {
          foreach ($adjusted_regions[$region] as $adjacent_region) {
            $region_width = $region_width - $grid[$adjacent_region . '_width'];
          }
        }
      }
      $grid['regions'][$region] = array('width' => $region_width, 'style' => $region_style, 'total' => count(fusion_core_block_list($region)), 'count' => 0);
    }

    // Adjustments for fluid width regions & groups
    $grid['fluid_adjustments'] = array();
    // Regions
    $adjusted_regions_fluid = (theme_get_setting('grid_adjusted_regions_fluid')) ? theme_get_setting('grid_adjusted_regions_fluid') : array();
    foreach (array_keys($adjusted_regions_fluid) as $adjusted_region) {
      $width = $grid['width'];
      foreach ($adjusted_regions_fluid[$adjusted_region] as $region) {
        $width = $width - $grid['regions'][$region]['width'];         // Subtract regions outside parent group to get correct parent width
      }
      $grid['fluid_adjustments'][$adjusted_region] = round(($grid['regions'][$adjusted_region]['width'] / $width) * 100, 2);
    }
    // Groups
    $adjusted_groups_fluid = (theme_get_setting('grid_adjusted_groups_fluid')) ? theme_get_setting('grid_adjusted_groups_fluid') : array();
    foreach (array_keys($adjusted_groups_fluid) as $adjusted_group) {
      $width = 100;
      foreach ($adjusted_groups_fluid[$adjusted_group] as $region) {
        $width = $width - $grid['fluid_adjustments'][$region];         // Subtract previously calculated sibling region fluid adjustments
      }
      $grid['fluid_adjustments'][$adjusted_group] = $width;            // Group gets remaining width
    }
  }
  return $grid;
}


/**
 * Theme paths function
 * Retrieves parent and current theme paths in parent-to-current order.
 */
function fusion_core_theme_paths($theme) {
  $base_themes = system_find_base_themes(list_themes(), $theme);
  foreach ($base_themes as $key => $base_theme) {
    $base_themes[$key] = drupal_get_path('theme', $key);     // Base theme paths
  }
  $base_themes[$theme] = drupal_get_path('theme', $theme);   // Current theme path
  return $base_themes;
}
