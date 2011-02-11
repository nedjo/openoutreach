

        FORWARD MODULE - README
______________________________________________________________________________

NAME:       Forward
AUTHORS:    Sean Robertson <seanr@ngpsoftware.com>
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

  Go to "administer >> build >> modules" and put a checkmark in the 'status' column next
  to 'forward'.


Step 4)
  Go to "administer >> site configuration >> forward" to configure the module.

  If you wish to customize the emails, copy 'forward.tpl.php' into your theme directory.
  Then you can customize the function as needed and those changes will only appear went
  sent by a user using that theme.


Step 5)
  Enable permissions appropriate to your site.

  The forward module provides two permissions:
   - 'access forward': allow user to forward pages.
   - 'administer forward': allow user to configure forward.

  Note that you need to enable 'access forward' for users who should be able to
  send emails using the forward module.


Step 6)
  Go to "administer >> logs >> forward tracking" to view forward usage statistics.


CREDITS & SUPPORT

Special thanks to Jeff Miccolis of developmentseed.org for supplying the
tracking features and various other edits.  Thanks also to Nick White for his
EmailPage module, some code from which was used in this module, as well as the
numerous other users who have submitted issues and patches for forward.

All issues with this module should be reported via the following form:
http://drupal.org/node/add/project_issue/forward

______________________________________________________________________________
http://www.ngpsystems.com