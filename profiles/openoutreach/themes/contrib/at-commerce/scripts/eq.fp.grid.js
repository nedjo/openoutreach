(function ($) {
  Drupal.behaviors.ContentDisplayFrontPageGrid = {
    attach: function(context) {
      $("body.front #main-content").addClass("front-page-grid content-display-grid");
      $("body.front #main-content .article").equalHeight();
    }
  }
})(jQuery);
