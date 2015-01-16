# RedHen CRM

## About RedHen

RedHen CRM is a native CRM solution for Drupal brought to you by the geeks at [ThinkShout][1]. RedHen is packed with [association management][2] features for managing detailed information on contacts and organizations, membership services, event registrations, and constituent engagement.

## Potential Uses

While RedHen CRM has been designed around the CRM needs of membership organizations and associations, the RedHen framework is flexible and can be leveraged to develop a wide range of CRM solutions. For example, RedHen could be used as a light-weight sales pipeline management tool for small businesses. RedHen CRM could also be leveraged as an integration point between Drupal and much larger, enterprise CRM solutions such as Salesforce and Blackbaud.

## Getting Started

RedHen CRM is similar to [Drupal Commerce][3] in its modular structure. As with Drupal Commerce, the core RedHen modules that can be downloaded at http://drupal.org/project/redhen won't provide you with a working CRM right out of the box. They require configuration. In the future, ThinkShout is likely to release RedHen "Features" or "Apps" that provide pre-packaged CRM solutions for different use cases.

In the short term, if you would like to explore RedHen CRM, we would encourage you to check out our demonstration RedHen CRM installation profile at:

http://drupal.org/node/1490420

This install profile will build out a simple example of how RedHen could be leveraged to support the CRM needs of a fictional "pet shelter" organization.

## Project Structure

RedHen CRM relies heavily on custom Drupal entity types and bundles. The [Entity API][4] module is leveraged to do most of the heavy lifting for these custom entities. The [Relation][5] module is leveraged to manage connections between these custom entity bundles. The core RedHen module provides shared APIs. But the majority of RedHen features are broken out into separate sub-modules that ship with the main module. As with Drupal Commerce, we will continue to include key sub-modules with the main module code base. However, we anticipate that an ecosystem of plug-in modules will soon be available to extend the core feature set.

## Basic Concepts and Features

* RedHen CRM defines two main entity types: Contacts and Organizations. Site administrators can then create different entity bundles for each of these types. Each bundle can then be *fielded.*

* **Connections** can then be made between contacts, as well as as between contacts and organizations. **Connections** are managed as custom entity bundles as well, based upon the relation entity type defined by the Relation module. As such, these connections can be fielded as well. In other words, you can create a relationship, or connection, between contacts and organizations that include field data about the relationship. Potential connection fields might include "job title" or "job start date."

* **Memberships** are another custom entity type defined by the "RedHen Membership" module. Both contacts and organizations can be associated with memberships. RedHen's membership management features are very flexible and feature rich. Memberships can be associated with the management of Drupal user roles to provide website access based upon individual and organizational membership status.

* Optionally, contact entities can be associated with Drupal user accounts. Currently, these connections are managed from the contact entity edit screen. Contacts can be associated with existing Drupal user accounts, or a new Drupal user account can be created from the contact entity edit form.

* **Notes** is another custom entity type and bundle provided by the "RedHen Notes" sub-module. Notes provide a site administrator a simple tool for capturing tagged notes about contacts and organizations. As a custom entity bundle, notes are fieldable as well.

* The Notes module also integrates with the "RedHen engagement scoring" sub-module. Engagement scores allow a site administrator to track and score various types of interactions with contact entities.

* Finally, RedHen CRM ships with a "RedHen groups" sub-module that allows you to *groupify* RedHen organizations. Groupified organizations function similarly to [Organic Groups][6], in that they provide a simple container for managing private node content associated with each organization.

## Extending RedHen CRM with Views and Rules Integration

The RedHen CRM framework does not require [Views][7]. However, because RedHen is built upon Entity API, you can easily extend RedHen to work with Views and Rules. With Views, you can extend RedHen to create custom reports of contact, organization, membership and/or engagement scoring data. With Views plugins such as [Views Bulk Operations][8] and [Views Data Export][9], you can further extend RedHen with bulk editing and export tools.

## For More Information

More complete RedHen site administration docs will be coming soon. You can also check out the README.txt files contained with each submodule. For technical issues, please use the D.O. issue queue for RedHen: http://drupal.org/project/issues/redhen. For community support and to learn about RedHen usage, please consider joining the RedHen Drupal group: http://groups.drupal.org/redhen-crm.

## References

[1]: http://thinkshout.com "ThinkShout, Inc"
[2]: http://en.wikipedia.org/wiki/Association_management_system "Description of association management CRM tools"
[3]: http://drupal.org/project/commerce "Drupal Commerce"
[4]: http://drupal.org/project/entity "Entity API module"
[5]: http://drupal.org/project/relation "Relation module"
[6]: http://drupal.org/project/og "Organic Groups module"
[7]: http://drupal.org/project/views "Views module"
[8]: http://drupal.org/project/views_bulk_operations "Views Bulk Operations"
[9]: http://drupal.org/project/views_data_export "Views Data Export"