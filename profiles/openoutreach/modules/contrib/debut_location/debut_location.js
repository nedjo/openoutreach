(function ($) {
    Drupal.behaviors.debutLocation = {
      attach:function (context, settings) {
        var i = 0;
        var ids = $.cookie('Drupal.debutLocation.menus');
        ids = ids ? ids.split(',') : [];
        $('#views-exposed-form-location-map-page li').has('ul').once('debut-location', function () {
          // Prepend a div element that will be used for click
          // expand/collapse.
          $('<div />', {'class': 'trigger'}).prependTo(this).click(function () {
            // If the node is not already open, we'll need to add it to the
            // cookie if it is expanded.
            var add = !$(this).hasClass('expanded');
            $(this)
              .toggleClass('expanded')
              .parent('li')
              .each(function () {
                // Modify cookie to reflect current collapse state.
                var ids = $.cookie('Drupal.debutLocation.menus');
                ids = ids ? ids.split(',') : [];
                var id = $(this).attr('id');
                var index = $.inArray(id, ids);
                // If a list is being expanded, add its id to the cookie if it's
                // not already there.
                if (add) {
                  if (index == -1) {
                     ids.push(id);
                     $.cookie('Drupal.debutLocation.menus', ids);
                   }
                 }
                // If a list is being closed, delete its id from the cookie if
                // it's there.
                 else {
                   if (index != -1) {
                     ids.splice(index, 1);
                     $.cookie('Drupal.debutLocation.menus', ids);
                   }
                 }
               })
               // Toggle the display of a child list.
               .find('> ul')
               .animate({
                  height: 'toggle', opacity: 'toggle'
                }, 'slow');
          });
          // Add ids to li elements with list children for use in cookie-based
          // persistence.
          var id = 'tree-' + i;
          $(this)
            .attr('id', id)
            // To respect term depth, check/uncheck child term checkboxes.
            .find('input.form-checkboxes:first')
            .click(function() {
              $(this).parents('li:first').find('ul input.form-checkboxes').attr('checked', $(this).attr('checked'));
            })
            .end()
            // When a child term is checked or unchecked, set the parent term's
            // status.
            .find('ul input.form-checkboxes')
            .click(function() {
              var checked = $(this).attr('checked');
              // Determine the number of unchecked sibling checkboxes.
              var ct = $(this).parents('ul:first').find('input.form-checkboxes:not(:checked)').size();
              // If the child term is unchecked, uncheck the parent.
              // If all sibling terms are checked, check the parent.
              if (!checked || !ct) {
                $(this).parents('li:first').parents('li:first').find('input.form-checkboxes:first').attr('checked', checked);
              }
            })
          i++;
          // Initialize collapse state and classes for menu items.
          var index = $.inArray(id, ids);
          if (index != -1) {
            $(this).find('> div.trigger').addClass('expanded').siblings('ul:first').show();
          }
        });
      }
    }
}(jQuery));
