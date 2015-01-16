Entity based registration system for Drupal.

# Configuration
1. Download and enable the module.
2. Create at least one registration bundle (or type) at
/admin/structure/admin/structure/registration/registration_types, much like you would a content type.
3. Add a registration field to any entity you want to enable registrations
for. Note the display options: default, link to the registration form,
and embedding the actual form.
4. When you add or edit an entity, select the registration bundle you want to
 use for.
5. Registrations are now enabled for the entity and you can configure the
registration settings via a local task.

# Settings
1. Enable: Turn registrations on / off for a given node.
2. Capacity: The maximum number of registrants for a given node. Leave at 0 for
no limit.
3. Allow Multiple: If selected, users can register for more than one slot for
this event.
4. Send a reminder. Checking this exposes reminder date and message template
fields.

# Usage / Features
1. Manage registrations for any enabled entity.
2. Per entity registration settings.
3. Broadcast emails to all event registrants.
4. Associate any field types to a registration to collect the information needed
for your event.
5. Send reminders on a given date.

# Integrations for more functionality
## [Fields](http://api.drupal.org/api/drupal/modules--field--field.module/group/field/7)
This is where things get interesting. You can add any Drupal field to customize
your registrations. The fields widgets will automatically appear on the register
form and will be available from a registration detail page.

## [Views](http://drupal.org/project/views)
Not happy with the default tabular list of registrations? No problem,
registrations and their fields are all Views friendly. You can override the
default event registrations list, create additional ones, etc.

## [Rules](http://drupal.org/project/rules)
Rules is a great companion for Registration to send confirmation emails, event
notifications, etc.

## Registrants via [Field Collection](http://drupal.org/project/field_collection)
Attaching a field collection field to a registration allows you to collect
granular information for multiple registrants for a single registration. Here's
how it works.

1. Download and enable Field Collection.
2. Add a field collection field to your registration entity.
3. Add any fields that you want to collect to the field collection entity and
configure widget and display settings. You might also want to consider field
collection table to create tabular lists of registrants.

That's it. Now, when a registration is added, users can complete one or more
field collections for each registrant.

# Roadmap
1. Tighter integration with Field Collection for a more robust registration ->
registrant system. Namely, mapping the registration capacity to the number of
field collections per registration.
3. Registration Feature that bundles everything you need in a tidy package to
start using registrations out of the box.
