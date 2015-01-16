(function ($) {
  Drupal.behaviors.ContentDisplayToggleDraw = {
    attach: function(context) {
      $('#toggle-wrapper a').bind('click', function() {
          $('#draw').slideToggle('400');
        event.preventDefault();
      });
    }
  }
})(jQuery);
