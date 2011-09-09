
// Ensure the $ alias is owned by jQuery.
(function($) {

Drupal.PanelsIPE = {
  editors: {},
  bindClickDelete: function(context) {
    $('a.pane-delete:not(.pane-delete-processed)', context)
      .addClass('pane-delete-processed')
      .click(function() {
        if (confirm('Remove this pane?')) {
          $(this).parents('div.panels-ipe-portlet-wrapper').fadeOut('medium', function() {
            $(this).empty().remove();
          });
          $(this).parents('div.panels-ipe-display-container').addClass('changed');
        }
        return false;
      });
  }
}

// A ready function should be sufficient for this, at least for now
$(function() {
  $.each(Drupal.settings.PanelsIPECacheKeys, function() {
    Drupal.PanelsIPE.editors[this] = new DrupalPanelsIPE(this, Drupal.settings.PanelsIPESettings[this]);
  });
});

Drupal.behaviors.PanelsIPE = {
  attach: function(context) {
    Drupal.PanelsIPE.bindClickDelete(context);
  }
};

/**
 * Base object (class) definition for the Panels In-Place Editor.
 *
 * A new instance of this object is instanciated for every unique IPE on a given
 * page.
 *
 * Note that this form is provisional, and we hope to replace it with a more
 * flexible, loosely-coupled model that utilizes separate controllers for the
 * discrete IPE elements. This will result in greater IPE flexibility.
 */
function DrupalPanelsIPE(cache_key, cfg) {
  var ipe = this;
  this.key = cache_key;
  this.state = {};
  this.control = $('div#panels-ipe-control-' + cache_key);
  this.initButton = $('div.panels-ipe-startedit', this.control);
  this.cfg = cfg;
  this.changed = false;
  this.sortableOptions = $.extend({
    revert: 200,
    dropOnEmpty: true, // default
    opacity: 0.75, // opacity of sortable while sorting
    // placeholder: 'draggable-placeholder',
    // forcePlaceholderSize: true,
    items: 'div.panels-ipe-portlet-wrapper',
    handle: 'div.panels-ipe-draghandle',
    tolerance: 'pointer',
    cursorAt: 'top',
    update: this.setChanged,
    scroll: true
    // containment: ipe.topParent,
  }, cfg.sortableOptions || {});

  this.initEditing = function(formdata) {
    ipe.topParent = $('div#panels-ipe-display-' + cache_key);
    ipe.backup = this.topParent.clone();

    // See http://jqueryui.com/demos/sortable/ for details on the configuration
    // parameters used here.
    ipe.changed = false;

    $('div.panels-ipe-sort-container', ipe.topParent).sortable(ipe.sortable_options);

    // Since the connectWith option only does a one-way hookup, iterate over
    // all sortable regions to connect them with one another.
    $('div.panels-ipe-sort-container', ipe.topParent)
      .sortable('option', 'connectWith', ['div.panels-ipe-sort-container']);

    $('div.panels-ipe-sort-container', ipe.topParent).bind('sortupdate', function() {
      ipe.changed = true;
    });

    $('.panels-ipe-form-container', ipe.control).append(formdata);

    $('input:submit:not(.ajax-processed)', ipe.control).addClass('ajax-processed').each(function() {
      var element_settings = {};

      element_settings.url = $(this.form).attr('action');
      element_settings.setClick = true;
      element_settings.event = 'click';
      element_settings.progress = { 'type': 'throbber' };

      var base = $(this).attr('id');
      Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
      if ($(this).attr('id') == 'panels-ipe-save') {
        Drupal.ajax[base].options.beforeSerialize = function (element_settings, options) {
          ipe.saveEditing();
          return Drupal.ajax[base].beforeSerialize(element_settings, options);
        };
      }
      if ($(this).attr('id') == 'panels-ipe-cancel') {
        Drupal.ajax[base].options.beforeSend = function () {
          return ipe.cancelEditing();
        };
      }
    });

    // Perform visual effects in a particular sequence.
    ipe.initButton.css('position', 'absolute');
    ipe.initButton.fadeOut('normal');
    $('.panels-ipe-on').show('normal');
//    $('.panels-ipe-on').fadeIn('normal');
    ipe.topParent.addClass('panels-ipe-editing');
  }

  this.endEditing = function(data) {
    $('.panels-ipe-form-container', ipe.control).empty();
    // Re-show all the IPE non-editing meta-elements
    $('div.panels-ipe-off').show('fast');

    // Re-hide all the IPE meta-elements
    $('div.panels-ipe-on').hide('fast');
    ipe.initButton.css('position', 'static');
    ipe.topParent.removeClass('panels-ipe-editing');
   $('div.panels-ipe-sort-container', ipe.topParent).sortable("destroy");
  };

  this.saveEditing = function() {
    $('div.panels-ipe-region', ipe.topParent).each(function() {
      var val = '';
      var region = $(this).attr('id').split('panels-ipe-regionid-')[1];
      $(this).find('div.panels-ipe-portlet-wrapper').each(function() {
        var id = $(this).attr('id').split('panels-ipe-paneid-')[1];
        if (id) {
          if (val) {
            val += ',';
          }
          val += id;
        }
      });
      $('input[name="panel[pane][' +  region + ']"]', ipe.control).val(val);
    });
  }

  this.cancelEditing = function() {
    if (ipe.topParent.hasClass('changed')) {
      ipe.changed = true;
    }

    if (!ipe.changed || confirm(Drupal.t('This will discard all unsaved changes. Are you sure?'))) {
      ipe.topParent.fadeOut('medium', function() {
        ipe.topParent.replaceWith(ipe.backup.clone());
        ipe.topParent = $('div#panels-ipe-display-' + ipe.key);

        // Processing of these things got lost in the cloning, but the classes remained behind.
        // @todo this isn't ideal but I can't seem to figure out how to keep an unprocessed backup
        // that will later get processed.
        $('.ctools-use-modal-processed', ipe.topParent).removeClass('ctools-use-modal-processed');
        $('.pane-delete-processed', ipe.topParent).removeClass('pane-delete-processed');
        ipe.topParent.fadeIn('medium');
        Drupal.attachBehaviors();
      });
    }
    else {
      // Cancel the submission.
      return false;
    }
  };

  this.createSortContainers = function() {
    $('div.panels-ipe-region', this.topParent).each(function() {
      $('div.panels-ipe-portlet-marker', this).parent()
        .wrapInner('<div class="panels-ipe-sort-container" />');

      // Move our gadgets outside of the sort container so that sortables
      // cannot be placed after them.
      $('div.panels-ipe-portlet-static', this).each(function() {
        $(this).appendTo($(this).parent().parent());
      });

      // Add a marker so we can drag things to empty containers.
      $('div.panels-ipe-sort-container', this).append('<div>&nbsp;</div>');
    });
  }

  this.createSortContainers();

  var element_settings = {
    url: ipe.cfg.formPath,
    event: 'click',
    keypress: false,
    // No throbber at all.
    progress: { 'type': 'none' }
  };

  Drupal.ajax['ipe-ajax'] = new Drupal.ajax('ipe-ajax', $('div.panels-ipe-startedit', this.control).get(0), element_settings);

/*
  var ajaxOptions = {
    type: "POST",
    url: ,
    data: { 'js': 1 },
    global: true,
    success: Drupal.CTools.AJAX.respond,
    error: function(xhr) {
      Drupal.CTools.AJAX.handleErrors(xhr, ipe.cfg.formPath);
    },
    dataType: 'json'
  };

  $('div.panels-ipe-startedit', this.control).click(function() {
    var $this = $(this);
    $.ajax(ajaxOptions);
  });
  */
};

$(function() {
  Drupal.ajax.prototype.commands.initIPE = function(ajax, data, status) {
    if (Drupal.PanelsIPE.editors[data.key]) {
      Drupal.PanelsIPE.editors[data.key].initEditing(data.data);
    }
  };

  Drupal.ajax.prototype.commands.unlockIPE = function(ajax, data, status) {
    if (confirm(data.message)) {
      var ajaxOptions = {
        type: "POST",
        url: data.break_path,
        data: { 'js': 1 },
        global: true,
        success: Drupal.CTools.AJAX.respond,
        error: function(xhr) {
          Drupal.CTools.AJAX.handleErrors(xhr, ipe.cfg.formPath);
        },
        dataType: 'json'
      };

      $.ajax(ajaxOptions);
    };
  };

  Drupal.ajax.prototype.commands.endIPE = function(ajax, data, status) {
    if (Drupal.PanelsIPE.editors[data.key]) {
      Drupal.PanelsIPE.editors[data.key].endEditing(data);
    }
  };


});

})(jQuery);
