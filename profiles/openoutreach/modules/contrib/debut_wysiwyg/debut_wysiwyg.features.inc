<?php
/**
 * @file
 * debut_wysiwyg.features.inc
 */

/**
 * Implementation of hook_default_wysiwyg_profile().
 */
function debut_wysiwyg_default_wysiwyg_profile() {
  $items = array();
  $items['wysiwyg_contributor'] = entity_import('wysiwyg_profile', '{
    "format" : "wysiwyg_contributor",
    "editor" : "ckeditor",
    "settings" : {
      "default" : 1,
      "user_choose" : 0,
      "show_toggle" : 1,
      "theme" : "advanced",
      "language" : "en",
      "buttons" : {
        "default" : {
          "Bold" : 1,
          "Italic" : 1,
          "Underline" : 1,
          "BulletedList" : 1,
          "NumberedList" : 1,
          "Link" : 1,
          "Unlink" : 1,
          "Format" : 1
        },
        "drupal" : { "media" : 1 }
      },
      "toolbar_loc" : "top",
      "toolbar_align" : "left",
      "path_loc" : "bottom",
      "resizing" : 1,
      "verify_html" : 1,
      "preformatted" : 0,
      "convert_fonts_to_spans" : 1,
      "remove_linebreaks" : 1,
      "apply_source_formatting" : 0,
      "paste_auto_cleanup_on_paste" : 0,
      "block_formats" : "p,h2,h3,h4",
      "css_setting" : "none",
      "css_path" : "",
      "css_classes" : ""
    },
    "rdf_mapping" : []
  }');
  $items['wysiwyg_editor'] = entity_import('wysiwyg_profile', '{
    "format" : "wysiwyg_editor",
    "editor" : "ckeditor",
    "settings" : {
      "default" : 1,
      "user_choose" : 0,
      "show_toggle" : 1,
      "theme" : "advanced",
      "language" : "en",
      "buttons" : {
        "default" : {
          "Bold" : 1,
          "Italic" : 1,
          "Underline" : 1,
          "BulletedList" : 1,
          "NumberedList" : 1,
          "Outdent" : 1,
          "Indent" : 1,
          "Link" : 1,
          "Unlink" : 1,
          "PasteText" : 1,
          "Format" : 1,
          "Table" : 1
        },
        "drupal" : { "media" : 1 }
      },
      "toolbar_loc" : "top",
      "toolbar_align" : "left",
      "path_loc" : "bottom",
      "resizing" : 1,
      "verify_html" : 1,
      "preformatted" : 0,
      "convert_fonts_to_spans" : 1,
      "remove_linebreaks" : 1,
      "apply_source_formatting" : 0,
      "paste_auto_cleanup_on_paste" : 0,
      "block_formats" : "p,h2,h3,h4",
      "css_setting" : "none",
      "css_path" : "",
      "css_classes" : ""
    },
    "rdf_mapping" : []
  }');
  $items['wysiwyg_public'] = entity_import('wysiwyg_profile', '{
    "format" : "wysiwyg_public",
    "editor" : "ckeditor",
    "settings" : {
      "default" : 1,
      "user_choose" : 0,
      "show_toggle" : 1,
      "theme" : "advanced",
      "language" : "en",
      "buttons" : { "default" : {
          "Bold" : 1,
          "Italic" : 1,
          "BulletedList" : 1,
          "NumberedList" : 1,
          "Link" : 1
        }
      },
      "toolbar_loc" : "top",
      "toolbar_align" : "left",
      "path_loc" : "bottom",
      "resizing" : 1,
      "verify_html" : 1,
      "preformatted" : 0,
      "convert_fonts_to_spans" : 1,
      "remove_linebreaks" : 1,
      "apply_source_formatting" : 0,
      "paste_auto_cleanup_on_paste" : 0,
      "block_formats" : "",
      "css_setting" : "none",
      "css_path" : "",
      "css_classes" : ""
    },
    "rdf_mapping" : []
  }');
  return $items;
}
