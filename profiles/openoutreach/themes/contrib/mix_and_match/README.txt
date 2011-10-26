
NOTE: NOT UPDATED FOR VERSION 7.x YET; WAITING UNTIL FINAL FEATURES TO BE ADDED

ABOUT THIS THEME
=================

Mix and Match is a subtheme of the Fusion Core base theme. It was designed to
take advantage of the power and flexibility provided by Fusion and the Skinr
module to allow users to create highly customized styles through Drupal's UI.
On the main theme configuration page users can set colors for basic elements of
their site (background, navigation, footer, headers, links). With Skinr enabled,
users can also customize the appearance of nodes, comments, and individual blocks.
Color options include white, black, red, and multiple shades of gray, blue,
green and orange.


THEME FEATURES
==============

Mix and Match configuration options:

- Set body, content area and footer background colors
- Choose an accent color for navigation bar and submit buttons
- Select default colors for page titles, block headers and links
- Add CSS3-based rounded corners to blocks and other page elements

Features provide by Fusion base theme:

- Select 960px fixed or fluid layout (grid-based)
- 13 available block regions
- Adjustable sidebar widths and layouts
- Font family and font size options
- Customizable search results
- Extra administrator and developer settings

Using the Skinr module:

- Set colors and styles for each block on the block configuration page
- Set colors for nodes and comments on content type configuration page


INSTALLATION AND BASIC CONFIGURATION
======================================

1. Download both Mix and Match and Fusion themes

2. Extract them in your themes directory.

3. Enable Mix and Match and Fusion Core (you don't need to enable Fusion Starter)
on your themes page (/admin/build/themes)

4. Set Mix and Match as your default theme

5. Download and enable the Skinr module (optional, but highly recommended)

6. Set any necessary permissions for the Skinr module (/admin/user/permissions)

7. Go to the Mix and Match theme configuration page (admin/build/themes/settings/mixnmatch)
to set your main theme colors and other aspects of layout, typography, etc.


USING SKINR TO STYLE BLOCKS, NODES AND COMMENTS
==================================================

BLOCKS:

1. After enabling the Skinr module, go to the Blocks page (/admin/build/block),
assign your blocks to regions and save your settings

2. Visit the configuration page for a specific block you want to style. You can
access the block configuration pages from the main blocks administration page.
Alternatively, when you hover over a block with the cursor, a gear icon will
appear and this will take you to the block configuration page.

3. On the configuration page, you should see a "Skinr block settings" section
where you can set block styles. Mix and Match adds a number of color options
toward the end of this section and it also includes a large number of options
provided by the Fusion theme (block width, positioning, menu styles, etc.)

NODES AND COMMENTS:

1. Skinr styling options for nodes and comments are found on the configuration
page for a specific content type. For example, for the content type "Page", it
is on /admin/content/node-type/page. After enabling Skinr, you should see two
items on the page: "Skinr node settings" and "Skinr comment settings".

2. To add styles to your node, click on the node settings link to expand the
fieldset. You will see options for Content alignment and Image floating styles
that are part of Fusion. Mix and Match adds options for Background color and
link text color.

3. Similar options are provided for comments. These styles will only be applied
to comments associated with the specific content type you are editing.


ADDING YOUR OWN STYLES
=======================

SETTING UP LOCAL.CSS:

If you want to modify the theme or add additional styles, it is recommended to
override CSS or add new CSS in local.css instead of modifying the existing
stylesheets. This will make upgrades to the theme much simpler. To set up
local.css, simply follow the instructions at the top of the local-sample.css
file found in the CSS directory of the theme.

USING SKINR TO ADD YOUR OWN CLASSES:

Skinr allows you to add your own classes to individual blocks, making styling
easier and avoiding modifications to templates. To use this feature, simply
click on the "Advanced features" link to expand the fieldset at the bottom of
the Skinr section on the block configuration page. Enter your own classes in the
field and then add your styles to local.css. This feature is also available for
nodes and comments.

ADDING CSS3 PIE TO DISPLAY ROUND CORNERS IN IE
==============================================

**IMPORTANT NOTE: Previously, the instructions were to add the library
to the PIE directory in the theme, but now there is a module available for
incorporating this library.  So the current recommendation is to use the module.
If you previously used it within the theme, delete the PIE directory and its
contents and any code in local.css for CSS3 PIE, then follow these instructions.

- Download and install the css3pie module (http://drupal.org/project/css3pie)
- Follow instructions on module page for downloading and extracting the PIE
  library
- Go to the css3pie settings page at Site building > Themes > css3pie Settings
  (/admin/build/themes/css3pie) and paste the following into the "CSS Selectors"
  section:

.round-corners-3 .primary-menu
.round-corners-3 h2.block-title
.round-corners-3 .main-wrapper .block .inner
.round-corners-3 .preface-top-wrapper .block .inner
.round-corners-3 .postscript-bottom-wrapper .block .inner
.round-corners-3 .footer-wrapper .block .inner
.round-corners-3 div.comment
.round-corners-3 .node div.links
.round-corners-3 #footer
.round-corners-7 .primary-menu
.round-corners-7 h2.block-title
.round-corners-7 .main-wrapper .block .inner
.round-corners-7 .preface-top-wrapper .block .inner
.round-corners-7 .postscript-bottom-wrapper .block .inner
.round-corners-7 .footer-wrapper .block .inner
.round-corners-7 div.comment
.round-corners-7 .node div.links
.round-corners-7 #footer
.round-corners-11 .primary-menu
.round-corners-11 h2.block-title
.round-corners-11 .main-wrapper .block .inner
.round-corners-11 .preface-top-wrapper .block .inner
.round-corners-11 .postscript-bottom-wrapper .block .inner
.round-corners-11 .footer-wrapper .block .inner
.round-corners-11 div.comment
.round-corners-11 .node div.links
.round-corners-11 #footer


**NOTE - this is a suggested way to handle the lack of CSS3 compliance in IE, but as this
is not code I am maintaining, I do not guarantee its performance. If you run into
problems, please check out the troubleshooting help on the css3pie module issue queue
or the CSS3 PIE website.
