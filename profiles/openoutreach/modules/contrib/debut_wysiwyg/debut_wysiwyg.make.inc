
; Drupal version
core = 7.x
api = 2

; Contrib modules
projects[advanced_help][subdir] = contrib
projects[advanced_help][version] = 1.0-beta1
projects[debut][subdir] = contrib
projects[debut][version] = 1.0-beta2
projects[debut_wysiwyg][subdir] = contrib
projects[debut_wysiwyg][version] = 1.0-beta2
projects[entity][subdir] = contrib
projects[entity][version] = 1.0-beta8
projects[features][subdir] = contrib
projects[features][version] = 1.0-beta2
projects[features][patch][http://drupal.org/files/issues/features_views_fix-drush-make-1097560-53.patch] = http://drupal.org/files/issues/features_views_fix-drush-make-1097560-53.patch
projects[libraries][subdir] = contrib
projects[libraries][version] = 1.0
projects[media][subdir] = contrib
projects[media][version] = 1.0-beta4
projects[styles][subdir] = contrib
projects[styles][version] = 2.0-alpha5
projects[wysiwyg][subdir] = contrib
; Need dev until 2.1 is posted and http://drupal.org/node/1034476 is in stable.
projects[wysiwyg][version] = 2.x-dev
projects[wysiwyg][patch][] = http://drupal.org/files/issues/624018-138-wysiwyg-entity-exportables.patch
; Ckeditor
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.5.2/ckeditor_3.5.2.tar.gz"
libraries[ckeditor][directory_name] = "ckeditor"

