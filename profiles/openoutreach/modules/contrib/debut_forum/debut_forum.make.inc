; $Id: debut_forum.make.inc,v 1.1 2011/02/23 23:31:10 nedjo Exp $

; Drupal version
core = 7.x
api = 2

; Contrib modules
projects[advanced_forum][subdir] = contrib
projects[advanced_forum][version] = 2.0-beta1
projects[captcha][subdir] = contrib
projects[captcha][version] = 1.0-alpha2
projects[captcha][patch][http://drupal.org/files/issues/825088-19-captcha_ctools_export.patch] = http://drupal.org/files/issues/825088-19-captcha_ctools_export.patch
projects[ctools][subdir] = contrib
projects[ctools][version] = 1.x-dev
projects[debut][subdir] = contrib
projects[debut][version] = 1.x-dev
projects[debut_comment][subdir] = contrib
projects[debut_comment][version] = 1.x-dev
projects[debut_forum][subdir] = contrib
projects[debut_forum][version] = 1.x-dev
projects[features][subdir] = contrib
projects[features][version] = 1.0-beta4
projects[pathauto][subdir] = contrib
projects[pathauto][version] = 1.0-rc2
projects[strongarm][subdir] = contrib
projects[strongarm][version] = 2.0-beta3
