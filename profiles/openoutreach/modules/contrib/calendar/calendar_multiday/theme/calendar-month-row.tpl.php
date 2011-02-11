<?php
// $Id: calendar-month-row.tpl.php,v 1.3 2010/12/30 15:38:02 karens Exp $
/**
 * @file
 * Template to display a row
 * 
 * - $inner: The rendered string of the row's contents.
 */
$attrs = ($class) ? 'class="' . $class . '"': '';
$attrs .= ($iehint > 0) ? ' iehint="' . $iehint . '"' : '';
?>
<?php if ($attrs != ''):?>
<tr <?php print $attrs?>>
<?php else:?>
<tr>
<?php endif;?>
  <?php print $inner ?>
</tr>
