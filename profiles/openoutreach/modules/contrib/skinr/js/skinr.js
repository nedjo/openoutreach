
(function ($) {

// Make sure our objects are defined.
Drupal.CTools = Drupal.CTools || {};
Drupal.Skinr = Drupal.Skinr || {};
Drupal.Skinr.editUrl = 'admin/settings/skinr/edit/nojs';
Drupal.Skinr.infoUrl = 'admin/settings/skinr/info';

Drupal.behaviors.Skinr = {
  attach: function(context, settings) {
    for (var i in settings.skinr['areas']) {
      var $module = settings.skinr['areas'][i]['module'];
      var $elements = settings.skinr['areas'][i]['elements'];
      var $id = settings.skinr['areas'][i]['id'];

      var $region = $('.skinr-id-' + $id).once('skinr-region', function() {});
      if (settings.skinr['areas'][i]['classes'] == undefined) {
        settings.skinr['areas'][i]['classes'] = $($region).attr('class');
      }

      if ($region.length > 0) {
        var $links = '';
        for (var $j in $elements) {
          var $classes = '';
          if ($j == 0) {
            $classes += ' first';
          }
          if ($j == $elements.length - 1) {
            $classes += ' last';
          }
          if ($elements.length > 1) {
            $links += '<li class="skinr-link-' + $j + $classes + '"><a href="' + settings.basePath + Drupal.Skinr.editUrl + '/' + $module + '/' + $elements[$j] + '/' + $elements +'" class="skinr-link ctools-use-dialog">' + Drupal.t('Edit skin') + ' ' + (parseInt($j) + 1) + '</a></li>';
          }
          else {
            $links = '<li class="skinr-link-0 first last"><a href="' + settings.basePath + Drupal.Skinr.editUrl + '/' + $module + '/' + $elements[$j] +'" class="skinr-link ctools-use-dialog">' + Drupal.t('Edit skin') + '</a></li>';
          }
        }

        var $wrapper_classes = '';
        if ($module == 'page') {
          $wrapper_classes += ' skinr-links-wrapper-page';
        }

        $region.prepend('<div class="skinr-links-wrapper' + $wrapper_classes + '"><ul class="skinr-links">' + $links + '</ul></div>');
        $region.get(0).skinr = { 'module': $module, 'elements': $elements, 'id': $id };

        Drupal.behaviors.Dialog($region);
      };
    }

    $('div.skinr-links-wrapper', context).once('skinr-links-wrapper', function () {
      var $wrapper = $(this);
      var $region = $wrapper.closest('.skinr-region');
      var $links = $wrapper.find('ul.skinr-links');
      var $trigger = $('<a class="skinr-links-trigger" href="#" />').text(Drupal.t('Configure')).click(
        function () {
          $wrapper.find('ul.skinr-links').stop(true, true).slideToggle(100);
          $wrapper.toggleClass('skinr-links-active');
          return false;
        }
      );

      // Attach hover behavior to trigger and ul.skinr-links.
      $trigger.add($links).hover(
        function () { $region.addClass('skinr-region-active'); },
        function () { $region.removeClass('skinr-region-active'); }
      );
      // Hide the contextual links when user rolls out of the .skinr-links-region.
      $region.bind('mouseleave', Drupal.Skinr.hideLinks).click(Drupal.Skinr.hideLinks);
      // Prepend the trigger.
      $links.end().prepend($trigger);
    });

    // Add a close handler to the dialog.
    if (Drupal.Dialog.dialog && !Drupal.Dialog.dialog.hasClass('skinr-dialog-processed')) {
      Drupal.Dialog.dialog.addClass('skinr-dialog-processed').bind('dialogbeforeclose', function(event, ui) {
        // Reset all the applied style changes.
        for (var i in Drupal.settings.skinr['areas']) {
          var $id = Drupal.settings.skinr['areas'][i]['id'];
          var $classes = Drupal.settings.skinr['areas'][i]['classes'];
          $('.skinr-id-' + $id).attr('class', $classes);
        }
      });
    }
  }
}

/**
 * Disables outline for the region contextual links are associated with.
 */
Drupal.Skinr.hideLinks = function () {
  $(this).closest('.skinr-region')
    .find('.skinr-links-active').removeClass('skinr-links-active')
    .find('ul.skinr-links').hide();
};

Drupal.behaviors.SkinrLivePreview = {
  attach: function(context, settings) {
    $('#skinr-ui-form .skinr-ui-current-theme :input:not(.skinr-live-preview-processed)', context).addClass('skinr-live-preview-processed').change(function () {
      var $tag = $(this).attr('tagName');
      $tag = $tag.toLowerCase();

      var $module = $('#skinr-ui-form #edit-module').val();
      var $element = $('#skinr-ui-form #edit-element').val();
      var $elements = $('#skinr-ui-form #edit-elements').val();
      if (!$elements) {
        $elements = $element;
      }

      var $name = $(this).attr('name');
      $name = $name.replace(/skinr_settings\[.*_group\]\[[^\]]*\]\[([^\]]*)\]/, '$1');

      var $classes = '';
      var $add_classes = $(this).val();

      if ($tag == 'select') {
        $(this).find('option').each(function() {
          $classes += ' ' + $(this).attr('value');
        });
      }
      else if ($tag == 'input') {

      }

      // Use AJAX to grab the CSS and JS filename.
      $.ajax({
        type: 'GET',
        dataType: 'json',
        url: Drupal.settings.basePath + Drupal.Skinr.infoUrl + '/' + $name + '/' + $add_classes,
        success: function($data) {

          var $command = {
            command: 'skinrAfterupdate',
            module: $module,
            elements: $elements,
            classes: {
              remove: $classes,
              add: $add_classes
            },
            css: $data.css,
            js: $data.js,
            nosave: true
          };

          Drupal.CTools.AJAX.commands.skinrAfterupdate($command);
        }
      });
    });
  }
}

/**
 * AJAX responder command to dismiss the modal.
 */
Drupal.CTools.AJAX.commands.skinrAfterupdate = function(command) {
  if (command.module && command.elements && (command.classes.remove || command.classes.add)) {
    if (command.css) {
      for (var j in command.css) {
        $(document.createElement('link')).attr({href: Drupal.settings.basePath + command.css[j].path, media: command.css[j].media, rel: 'stylesheet', type: 'text/css'}).appendTo('head');
      }
    }
    if (command.js) {
      for (var j in command.js) {
        $.getScript(Drupal.settings.basePath + command.js[j].path);
      }
    }

    for (var i in Drupal.settings.skinr['areas']) {
      if (Drupal.settings.skinr['areas'][i]['module'] == command.module && Drupal.settings.skinr['areas'][i]['elements'] == command.elements) {
        $('.skinr-id-' + Drupal.settings.skinr['areas'][i]['id']).removeClass(command.classes.remove).addClass(command.classes.add);
        if (command.nosave == undefined || command.nosave == false) {
          Drupal.settings.skinr['areas'][i]['classes'] = $('.skinr-id-' + Drupal.settings.skinr['areas'][i]['id']).attr('class');
        }
      }
    }
  }
}

})(jQuery);
