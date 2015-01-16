== File Entity module ==

File admin extends the File entity module to add administrative options to
files, including published, promoted, and sticky status.

The File entity module provides a lot of functionality for creating and
editing file items, making it possible to use files as stand-along records
rather than, for example, needing a node attached to a file. However, it's
often important to be able to filter and sort files by the sort of criteria
that nodes have: is a file published? sticky at the top of lists? promoted?

== How to use File admin ==

After enabling the module, navigate to the file types page at
admin/structure/file-types. You will see a new operation available
"Settings". Click the link for a given file type. Configure the resulting form
to set the defaults for that file type. For example, to have videos default
to unpublished, click the settings link for video, uncheck the "Published"
checkbox, and submit.

When you have created one or more files, navigate to the file admin page,
admin/content/file. You will see several new options under "Update options"
(Publish, Unpublish, and so on).
You can also click the "edit" link for a particular media item. At
the bottom of the resulting form you will find a new set of vertical
tabs allowing you to edit the author, publishing date, and published,
promoted and sticky status of the file.
If you are using Views, you will find several new field, sort, and filter
options for files based on the published, promote, and sticky fields.

== Under the hood ==

To expand administrative options for files, File admin:

Adds a settings form for each file type, with vertical tabs style admin
fieldsets, allowing selection of defaults and also entering of file submission
guidelines.
Adds vertical-tabs style admin fieldsets to the file edit form, allowing
editing of author, created, published, promoted, and sticky fields.
Adds submission guidelines to the file edit form.
Alters the file admin overview form, adding a sortable column for published
status.
Adds mass update options for e.g. publishing files.
Adds new fields and filter etc. options to file views.

At the data level, File admin:

Adds four new fields to the file_managed table: created, published (not
called 'status', the name of the equivalent field in the node table, because
file_managed.status is already used for a different purpose), promote, sticky.
Adds Views exposure for these new fields.

Warning: the "published" status does not yet link to user access
restrictions. Media and File admin do not yet provide an extensible access
framework that would enable restricting access to files based on their
published status. See #1227706: Add a file entity access API. There is a
patch at #1734882: Add file access restrictions once file access improved
in file_entity to implement the planned access restrictions.

This module originated as a patch on the File entity module: #1220414: Add
created, published, promoted, and sticky fields and provide admin editing
interface plus views integration.

== Dependencies ==

Requires the 2.x branch of File entity.

