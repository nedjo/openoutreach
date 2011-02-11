<?php
// $Id: calendar-main.tpl.php,v 1.8 2010/12/21 13:41:24 karens Exp $
/**
 * @file
 * Template to display calendar navigation and links.
 * 
 * @see template_preprocess_calendar_main.
 *
 * $view: The view.
 * $calendar_links: Array of formatted links to other calendar displays - year, month, week, day.
 * $calendar_popup: The popup calendar date selector.
 * $display_type: year, month, day, or week.
 * $mini: Whether this is a mini view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
$links = array(
  'links' => $calendar_links, 
  'attributes' => array('class' => 'inline'),
);
?>

<div class="calendar-calendar">
  <?php if (!empty($calendar_popup)) print $calendar_popup;?>
  <?php if (!empty($calendar_add_date)) print $calendar_add_date; ?>
  <?php if (empty($block)) print theme('links', $links);?>
  <?php print theme('date_navigation', array('view' => $view)) ?>
</div>