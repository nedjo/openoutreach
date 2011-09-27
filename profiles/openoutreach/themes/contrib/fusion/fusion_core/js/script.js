(function ($) {

Drupal.behaviors.fusionEqualheights = {
  attach: function (context, settings) {
    if (jQuery().equalHeights) {
      $("#header-top-wrapper div.equal-heights div.content").equalHeights();
      $("#header-group-wrapper div.equal-heights div.content").equalHeights();
      $("#preface-top-wrapper div.equal-heights div.content").equalHeights();
      $("#preface-bottom div.equal-heights div.content").equalHeights();
      $("#sidebar-first div.equal-heights div.content").equalHeights();
      $("#content-region div.equal-heights div.content").equalHeights();
      $("#node-top div.equal-heights div.content").equalHeights();
      $("#node-bottom div.equal-heights div.content").equalHeights();
      $("#sidebar-second div.equal-heights div.content").equalHeights();
      $("#postscript-top div.equal-heights div.content").equalHeights();
      $("#postscript-bottom-wrapper div.equal-heights div.content").equalHeights();
      $("#footer-wrapper div.equal-heights div.content").equalHeights();
    }
  }
};

Drupal.behaviors.fusionIE6fixes = {
  attach: function (context, settings) {
    // IE6 & less-specific functions
    // Add hover class to main menu li elements on hover
    if ($.browser.msie && ($.browser.version < 7)) {
      $('form input.form-submit').hover(function() {
        $(this).addClass('hover');
        }, function() {
          $(this).removeClass('hover');
      });
      $('#search input#search_header').hover(function() {
        $(this).addClass('hover');
        }, function() {
          $(this).removeClass('hover');
      });
    };
  }
};

Drupal.behaviors.fusionOverlabel = {
  attach: function (context, settings) {
    if (jQuery().overlabel) {
      $("div.fusion-horiz-login label").overlabel();
    }
  }
};

Drupal.behaviors.fusionGridMask = {
  attach: function (context, settings) {
    // Exit if grid mask not enabled
    if ($('body.grid-mask-enabled').size() == 0) {
      return;
    }

    var grid_width_pos = parseInt($('body').attr('class').indexOf('grid-width-')) + 11;
    var grid_width = $('body').attr('class').substring(grid_width_pos, grid_width_pos + 2);
    var grid = '<div id="grid-mask-overlay" class="full-width"><div class="region">';
    for (i = 1; i <= grid_width; i++) {
      grid += '<div class="block grid' + grid_width + '-1"><div class="gutter"></div></div>';
    }
    grid += '</div></div>';
    $('body.grid-mask-enabled').prepend(grid);
    $('#grid-mask-overlay .region').addClass('grid' + grid_width + '-' + grid_width);
    $('#grid-mask-overlay .block .gutter').height($('body').height());
  }
};

Drupal.behaviors.fusionGridMaskToggle = {
  attach: function (context, settings) {
    // Exit if grid mask not enabled
    if ($('body.grid-mask-enabled').size() == 0) {
      return;
    }

    $('body.grid-mask-enabled').prepend('<div id="grid-mask-toggle">grid</div>');
    $('div#grid-mask-toggle')
    .toggle( function () {
      $(this).toggleClass('grid-on');
      $('body').toggleClass('grid-mask');
    },
    function() {
      $(this).toggleClass('grid-on');
      $('body').toggleClass('grid-mask');
    });
  }
};

})(jQuery);