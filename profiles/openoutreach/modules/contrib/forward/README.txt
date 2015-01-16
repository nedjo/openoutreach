

        FORWARD MODULE - README
______________________________________________________________________________

NAME:       Forward
AUTHORS:    Drupal 7 version:
            John Oltman <john.oltman@sitebasin.com>

            Drupal 6 version:
            Sean Robertson <seanr@ngpsoftware.com>
            Peter Feddo
______________________________________________________________________________


DESCRIPTION

Adds a "forward this page" link to each node. This module allows users to
forward a link to a specific node on your site to a friend.  You can customize
the default form field values and even view a running count of the emails sent
so far using the forward module.


INSTALLATION

Step 1) Download latest release from http://drupal.org/project/forward

Step 2)
  Extract the package into your 'modules' directory.


Step 3)
  Enable the forward module.

  Go to "/admin/modules" and put a checkmark in the 'Enabled' column next to
  'Forward'.


Step 4)
  Go to "/admin/config/user-interface/forward" to configure the module.
  This path is also linked from the Configuration page and the Modules list
  page within site administration.

  If you wish to customize the emails, copy 'forward.tpl.php' into your theme
  directory. Then you can customize the function as needed and those changes
  will only appear when sent by a user using that theme.

  If you check the 'custom display' box on the configuration page, the Forward
  view mode which defines the fields that will be sent in Forward emails can
  be configured here:

  "/admin/structure/types/manage/[machine-name]/display/forward"

  where [machine-name] is replaced by the machine name of the content type
  being configured.

  For example, for articles, the full path to the link is:
  "/admin/structure/types/manage/article/display/forward"


Step 5)
  Enable permissions appropriate to your site.

  Go to "/admin/people/permissions#module-forward" to configure permissions.
  This path is also linked from the Modules list page, click on the 
  Permissions link next to Forward.

  The forward module provides several permissions:
   - 'access forward': allow user to forward pages.
   - 'access epostcard': allow user to send an epostcard.
   - 'override email address': allow logged in user to change sender address.
   - 'administer forward': allow user to configure forward.
   - 'override flood control': allow user to bypass flood control on send.

  Note that you need to enable 'access forward' for users who should be able
  to send emails using the forward module.


Step 6)
  Go to "/admin/reports/forward" to view forward usage statistics.
  There is also a link on the Reports page within site administration.

  Statistics are captured when emails are sent and when recipients click on
  links within the sent emails.

Step 7)
  If the Views module is enabled for your site, go to "admin/structure/views"
  to optionally enable and configure Forward related views:
  
  Most forwarded
  Most recently forwarded
  Most clickthroughs

Step 8)
  Go to "admin/structure/block" to optionally enable and configure Forward
  blocks for your theme.  Several blocks are available:

  Forward: Interface - places the forward link or forward form in a block
  Forward: Statistics - most recently emailed or most emailed of all time

  If you enabled views in step 7, these blocks are also available:

  View: Most forwarded
  View: Most recently forwarded
  View: Most clickthroughs


SENDING FORWARD EMAILS AS HTML

  By default, Forward will install a new mail system named ForwardMailSystem
  that is configured to send email as HTML. If you installed a different
  mail system module for sending emails, you should visit the Mail System
  configuration page at "admin/config/system/mailsystem" to change the mail
  system setup.  For example, if you installed the HTMLMail module, you could
  change the default site wide mail system to HTMLMailSystem. The Mail System
  module also allows you to use one mail system as a default but a different
  mail system on a module by module basis.  This would allow you to use a
  special mail handler for Forward emails while not affecting emails sent
  from the rest of your site.

 
THEMEING

Sent email   - copy forward.tpl.php into your theme and modify
Forward page - add yourtheme_forward_page($variables) to template.php
Forward link - add yourtheme_forward_link($variables) to template.php

Forward links generated using Panels, Display Suite or Views integration
are fully themeable. Forward links generated into the node inline links
render array are not directly themeable; to override these links you
can write a preprocess_node function. However, the ability to provide
a custom icon and any text for the links via the Forward configuration
page should make this unnecessary for most use cases.


TEMPLATES

Forward links can be hardcoded into your theme templates as needed:

print theme('forward_link', array('node' => $node)); // for nodes
print theme('forward_link', array('path' => $path)); // for non-nodes

However, the use of Display Suite or Panels is recommended instead of
writing PHP code.

  
VIEWS INTEGRATION

The Forward Log is now integrated with Views 3 for Drupal 7. You can create
a view with log data including users who forwarded, the forwarded path, the
data and time the forwarding occurred, and other information.

You can also add a Forward link if you are using fields as the row style.


DISPLAY SUITE INTEGRATION

Forward link is now a field that is available within DS layouts.


PANELS INTEGRATION

Forward link is now available when adding content to a panel, both as a
node field and also a widget. If your panel is working within a node context,
such as when overriding a standard node view with a panel, use the node
field instead of the widget.


DYNAMIC BLOCK ACCESS CONTROL

The 7.x-1.3 release of the Forward module added a new security field
for administators on the Forward configuration page named Dynamic Block
Access Control.  This field allows the administrator to control which
permissions are used when Drupal applies access control checks to the nodes,
comments or users listed in the Dynamic Block.  Several access control
options are available, including a bypass option.  The bypass option allows
the email recipient to possibly view node titles, comment titles, or user
names that only privileged users should see. The bypass option should not
normally be selected, but is provided for sites that used prior versions
of Forward and rely on the access bypass to operate correctly.

IMPORTANT: Because the default for the new field is to apply access control,
administrators of sites that rely on the access bypass to operate correctly
need to visit the Forward configuration page and explicitly select the bypass
option after upgrading from versions of Forward prior to 7.x-1.3.


CLICKTHROUGH COUNTER FLOOD CONTROL

The Forward module tracks clicks from links in sent emails to determine which
nodes get the most clickthroughs.  The method used could allow someone to
manipulate clickthrough counts via CSRF - for example, placing an image on
a website with a src tag that points to the clickthrough counter link.  The
module uses flood control to limit the number of clickthroughs from a given
IP address in a given time period to migitate this possibility.


CREDITS & SUPPORT

Special thanks to Jeff Miccolis of developmentseed.org for supplying the
tracking features and various other edits.  Thanks also to Nick White for his
EmailPage module, some code from which was used in this module, as well as the
numerous other users who have submitted issues and patches for forward.

All issues with this module should be reported via the following form:
http://drupal.org/node/add/project_issue/forward
