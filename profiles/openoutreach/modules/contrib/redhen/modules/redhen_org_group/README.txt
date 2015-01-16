# RedHen Organization Groups

## Description

The RedHen Organization Groups module allows you to *groupify* organization entity bundles. This module provides functionality similar to [Organic Groups][1]. A groupified organization can have node content associated with it. Optionally, this content can be made private, and therefore only viewable to Drupal user accounts associated with RedHen contact entities which are in turn associated with a specific RedHen organization entity.

## So, why not just use Organic Groups?

The description above begs the question: Why not just use OG? In developing this feature, we considered leveraging Organic Groups. However, the relationships between Drupal user records, contacts and organizations were too complex to cleanly build this feature on top of both RedHen and Organic Groups. That said, much of the architecture of this module is based upon design patterns from Organic Groups.

## Set up

* Enable the RedHen Organization Groups module.
* Go to the organization bundle settings screen, such as: http://yoursite.com/admin/structure/redhen/org_types/manage/example_bundle.
* Select "Groupify."
* Optionally select where group content should be private to Drupal user accounts associated with contact entities associated with a specific organization.
* Select the content types that can be posted to these groupified organizations.
* Finally, when viewing an organization entity, you will see a "Content" tab that lists nodes that have been associated with the organization.

## References

[1]: http://drupal.org/project/og