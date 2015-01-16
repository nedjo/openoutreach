# RedHen Membership

## Description

The RedHen Membership module provides a framework for managing individual
(Contact) and organizational memberships. Optionally, you could assign Drupal
user roles to Drupal users associated with active individual or organizational
memberships. Memberships are a custom entity type/bundle. Therefore, memberships
can be extended with additional fields.

## Configuration

* First, decide if you want to associate Drupal user accounts with RedHen
  Contacts. This is not a requirement for managing memberships. However, if you
  want to apply Drupal user roles to user accounts associated with RedHen
  Contacts, you need to enable this option at: Configuration > RedHen
  (http://configuration/admin/config/redhen).
* Second, decide if you want RedHen to manage membership activation/expiration
  dates programmatically at: Configuration > RedHen (http://configuration/admin/config/redhen)
  * Then, create and configure one or more membership bundles at:
  Structure > RedHen > Membership Types (http://yoursite.com/admin/structure/redhen/membership_types).
  Optionally, you can select a Drupal user role to be assigned to user accounts
  associated with Contacts entities that are associated with active individual
  or organizational memberships.
* Note this cascade.If an organization has an active membership that is
  configured to apply a Drupal user role. All Drupal user accounts associated
  with Contact entities that are, in turn, associated with this organization
  will receive the Drupal user role.

## Usage

* When looking at a Contact or Organization entity, go to the "Memberships" tab.
* Click "Add membership." If more than one membership bundle is available,
  choose the type of membership you want to create.
* Optionally, enter the start/end dates for the membership.
* Choose the "state" of the membership. ("Active" memberships will apply the
  associated Drupal user role(s).)

## Exportables and role IDs

Special care should be taken with Role IDs if exporting membership types to
features. The relationship between a membership_type and a Drupal role is
tracked by role ID in the redhen_membership_type.role_id field. When used in
features, a membership type is mapped to a given role by role ID, which may
differ from the role on the site on which the membership type was generated.

Sites installing such a feature could risk assigning indeterminate roles to
members, potentially creating serious security breaches.

The problem has been fixed by the introduction of role machine names for Drupal
8. Meantime, if you need to tie an exported membership type to a role ID,
consider using one of the following approaches:

1. After generating your feature, make the following manual edits:
 * Edit the exported membership type (in your [featurename].features.inc file)
   to remove the exported role_id value.
 * Edit your [featurename].module file and add a
   hook_default_redhen_membership_type_alter() implementation that inserts the
   correct role ID. Example:
<code>
/**
* Implements hook_default_redhen_membership_type_alter().
*
* If there is a 'member' role, tie it to the 'standard' membership type.
*/
function featurename_default_redhen_membership_type_alter_items(&$items) {
  if (isset($items['standard']) && $role = user_role_load_by_name('member')) {
    $items['standard']->role_id = $role->rid;
  }
}
</code>
2. Alternately, use the [Role export](http://drupal.org/project/role_export)
module. If correctly installed and configured, it can be used to ensure
exported role IDs correctly map to specific roles.
