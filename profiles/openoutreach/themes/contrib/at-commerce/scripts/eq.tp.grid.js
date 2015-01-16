(function ($) {
  Drupal.behaviors.ContentDisplayTaxoPageGrid = {
    attach: function(context) {
      $("body.page-taxonomy #main-content").addClass("page-taxonomy-grid content-display-grid");
      $("body.page-taxonomy #main-content .article").equalHeight();
    }
  }
})(jQuery);
