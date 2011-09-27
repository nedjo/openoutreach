<?php
if (empty($secondary_color)) {
  $secondary_color = $primary_color;
}
?>

body {
  background-color: <?php print designkit_colorshift($secondary_color, '#ffffff', .8); ?>;
<?php if (!empty($background_image)) : ?>
  background-image: url(<?php print $background_image; ?>);
  background-repeat: no-repeat;
  background-attachment:fixed;
  background-position:center;
<?php endif; ?>
}

#block-system-main-menu {
  background-color: <?php print $primary_color ?>;
}

.region-main-menu ul li a:hover {
  background-color: <?php print designkit_colorshift($primary_color, '#ffffff', .5) ?>;
}

h1.title, h2.title, h3.title {
  color: <?php print designkit_colorshift($secondary_color, '#000000', .4) ?>;
}

#site-name > a {
  color: <?php print designkit_colorshift($secondary_color, '#000000', .4) ?>;
}

#slogan {
  color: <?php print designkit_colorshift($primary_color, '#000000', .5) ?>;
}

/* Style for individual dropdown menu items, add border-bottom for separators */
.region-main-menu ul.sf-menu li li {
  background-color: <?php print designkit_colorshift($primary_color, '#000000', .5) ?>;
}

#postscript-bottom-wrapper {
  border-top: 5px solid <?php print $primary_color ?>;
}

#content-tabs ul.tabs.primary {
  border-bottom: 3px solid <?php print $primary_color ?>;
}

#content-tabs ul.primary li a.active,
#content-tabs ul.secondary li a.active,
#content-tabs ul.primary li a.active:hover,
#content-tabs ul.secondary li a.active:hover,
#content-tabs ul.primary li.active a {
  background-color: <?php print $primary_color ?>;
}

#content-tabs ul.primary li a:hover,
#content-tabs ul.secondary li a:hover {
  background-color: <?php print designkit_colorshift($primary_color, '#ffffff', .5); ?>;
} 

div.comment {
  border:1px solid <?php print designkit_colorshift($primary_color, '#ffffff', .5) ?>;
}

.comments div.odd {
  background-color:#ffffff;
}

.comments div.even {
  background-color:<?php print designkit_colorshift($primary_color, '#ffffff', .95) ?>;
}

.block ul.links {
  background-color:<?php print designkit_colorshift($primary_color, '#ffffff', .95) ?>;
  border:1px solid <?php print designkit_colorshift($primary_color, '#ffffff', .5) ?>;
}

.fusion-border .inner {
  background: <?php print designkit_colorshift($primary_color, '#ffffff', .95) ?>;
  border:1px solid <?php print designkit_colorshift($primary_color, '#ffffff', .3) ?>;
}

body #space-tools .block-title { background-color:<?php print designkit_colorshift($primary_color, '#000000', .3) ?>; }

body #header .block-widget .block-content,
body #header .block .block-title { background-color:<?php print designkit_colorshift($primary_color, '#000000', .15) ?>; }

ul.pager a,
ul.pager li.pager-current {
  border-color: <?php print designkit_colorshift($primary_color, '#000000', .3) ?>;
}

ul.pager li.pager-current {
  background-color: <?php print $primary_color ?>;
  color: #ffffff;
}

ul.pager a:hover,
ul.pager a:active,
ul.pager a:focus {
  background-color: <?php print $primary_color ?>;
  border-color: <?php print designkit_colorshift($primary_color, '#000000', .3) ?>;
  color: #ffffff;
}

.calendar-calendar tr td.today, .calendar-calendar tr.odd td.today, .calendar-calendar tr.even td.today {
  background-color: <?php print designkit_colorshift($primary_color, '#ffffff', .7) ?>;
}

body .page-region .block .block-title {
  background-color:<?php print designkit_colorshift($primary_color, '#eeeeee', .8) ?>;
  border-color:<?php print designkit_colorshift($primary_color, '#dddddd', .8) ?>;
  border-bottom-color:<?php print designkit_colorshift($primary_color, '#cccccc', .8) ?>;
}

form input.form-submit:hover,
form input.form-submit.hover,
form input.form-submit:focus {
  background-color: <?php print designkit_colorshift($primary_color, '#ffffff', .5) ?>;
}

.search-box-inner input#edit-search-theme-form-header { 
  border:1px solid <?php print designkit_colorshift($primary_color, '#ffffff', .3) ?>;
}
