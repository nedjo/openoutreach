<?php
// $Id: calendar.views.inc,v 1.14 2011/01/18 01:27:43 karens Exp $
/**
 *  Implementation of hook_views_query()
 *  
 *  Handle the date_popup calendar goto date.
 */
function calendar_views_query_alter(&$view, &$query) {
  // Check if a new date has been selected and if so redirect.
  if (isset($_POST['calendar_goto']) && $_POST['view_name'] == $view->name) {
    $format = date_limit_format(variable_get('date_format_short', 'm/d/Y - H:i'), array('year', 'month', 'day'));
    $date = new DateObject($_POST['calendar_goto']['date'], date_default_timezone(), $format);  
    switch ($_POST['calendar_type']) {
      case 'year':
        $arg = $date->format('Y');
        break; 
      case 'month':
        $arg = $date->format('Y-m');
        break; 
      case 'week':
        $arg = $date->format('Y') . '-W' . date_pad(date_week($date));
        break; 
      default:
        $arg = $date->format('Y-m-d');
        break; 

    }
    drupal_goto(str_replace($_POST['calendar_previous_arg'], $arg, $_POST['view_url']));
  }
}

function calendar_views_pre_view(&$view, &$display_id, &$args) {
  //
}

/**
 * @file
 * 
 * Creates calendar displays of Views results.
 * 
 * Create a new calendar by enabling or cloning the default calendar,
 * changing the date argument to use the correct date field(s), and setting
 * up the year, month, day, week, and block views with the desired styles 
 * and fields.
 * 
 * Unlike previous versions of the Calendar module, there is just a single
 * Date argument instead of year, month, and day arguments. The argument
 * value will be YYYY-MM-DD for a day, YYYY-MM for a month, YYYY for a
 * year, and YYYY-W99 for a week. There is a default option to set the 
 * argument to the current date when the argument is empty.
 * 
 * A calendar display creates calendar navigation and links to 
 * multiple displays for the year, month, day, or week views. The actual
 * displays are created by attaching calendar views that use whatever
 * styles are desired for those pages. 
 * 
 * Calendar views are attachments to create the year, month, day,
 * and week displays. They can be set to use any style, either a
 * calendar style or any other Views style, like teasers or lists.
 * If you don't want to use one of them, don't attach it to
 * anything. Only the attached views will show up in the calendar.
 * 
 * A calendar block will create a calendar block for the
 * view results. Attach a block view to the block and set up the
 * desired style in the block view. 
 */
/**
 * Implementation of hook_views_plugins
 */
function calendar_views_plugins() {
  $views_path = drupal_get_path('module', 'views');
  $module_path = drupal_get_path('module', 'calendar');
  if (module_exists('calendar_multiday')) {
    $theme_path = drupal_get_path('module', 'calendar_multiday');
    module_load_include('inc', 'calendar_multiday', 'theme/theme');
  }
  else {
    $theme_path = $module_path;
    module_load_include('inc', 'calendar', 'theme/theme');
  }

  $data = array(
    'module' => 'calendar', // This just tells our themes are elsewhere.
    'display' => array(
      // Main calendar display plugin.
      'calendar' => array(
        'title' => t('Calendar page'),
        'help' => t('Calendar page. Attach Calendar period attachments to this page, set to show the year, month, day, and week views.'),
        'handler' => 'calendar_plugin_display_page',
        'path' => "$module_path/includes",
        'parent' => 'page',
        'theme' => 'views_view',
        'no ui' => TRUE,
        'no remove' => TRUE,
        'uses hook menu' => TRUE,
        'uses hook block' => FALSE,
        'use ajax' => TRUE,
        'use pager' => FALSE,
        'accept attachments' => TRUE,
        'admin' => t('Calendar page'),
        'help topic' => 'getting-started',
        'js' => array(
          'misc/farbtastic/farbtastic.js', 
          $module_path . '/js/calendar_colorpicker.js',
        ),
      ),
      // Calendar block display plugin.
      'calendar_block' => array(
        'title' => t('Calendar block'),
        'help' => t('Calendar page. Attach a Calendar period attachment to this block, set to show the year, month, day, or week view.'),
        'handler' => 'calendar_plugin_display_block',
        'path' => "$module_path/includes",
        'parent' => 'block',
        'theme' => 'views_view',
        'no ui' => TRUE,
        'no remove' => TRUE,
        'uses hook block' => TRUE,
        'use ajax' => TRUE,
        'use pager' => FALSE,
        'use more' => TRUE,
        'accept attachments' => TRUE,
        'admin' => t('Calendar block'),
        'help topic' => 'getting-started',
      ),
      // Display plugins for calendar displays.
      'calendar_period' => array(
        'title' => t('Calendar period'),
        'help' => t('An attachment for a Year, Month, Day, or Week calendar display, using any style you choose. Attach to a Calendar page and/or a Calendar block.'),
        'handler' => 'calendar_plugin_display_attachment',
        'path' => "$module_path/includes",
        'parent' => 'attachment',
        'theme' => 'views_view',
        'no ui' => TRUE,
        'no remove' => TRUE,
        'use ajax' => TRUE,
        'use pager' => TRUE,
        'admin' => t('Calendar page year, month, week, or day view'),
        'help topic' => 'getting-started',
      ),
    ),
    'style' => array(
      'parent' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_plugin_style',
        'path' => "$views_path/plugins",
        'parent' => '',
      ),
      // Style plugin for the navigation.
      'calendar_nav' => array(
        'title' => t('Calendar navigation'),
        'help' => t('Creates back/next navigation and calendar links.'),
        'handler' => 'calendar_plugin_style',
        'path' => "$module_path/includes",
        'parent' => 'parent',
        'theme' => 'calendar_main',
        'theme file' => 'theme.inc',
        'theme path' => "$theme_path/theme",
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => FALSE,
        'type' => 'calendar', // Only used on calendar page or block displays.
        'even empty' => TRUE,
      ),
      'calendar_style' => array(
        'title' => t('Calendar'),
        'help' => t('Displays Views results in a calendar.'),
        'handler' => 'calendar_view_plugin_style',
        'path' => "$module_path/includes",
        'parent' => 'calendar_nav',
        'theme' => 'calendar_month',
        'theme file' => 'theme.inc',
        'theme path' => "$theme_path/theme",
        'additional themes' => array(
          'calendar_year' => 'style',
          'calendar_day' => 'style',
          'calendar_week' => 'style',
          'calendar_mini' => 'style',
          ),
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );

  if (module_exists('calendar_multiday')) {
    $data['style']['calendar_style']['additional themes'] += array(
      'calendar_day_overlap' => 'style',
      'calendar_week_overlap' => 'style',
    );
  }
  return $data;
}
