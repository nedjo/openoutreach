(function ($) {
  /**
   * In most instances this will be called using the built in theme settings.
   * However, if you want to use this manually you can call this file
   * in the info file and user the ready function e.g.:
   * 
   * This will set sidebars and the main content column all to equal height:
   *  (function ($) {
   *    Drupal.behaviors.adaptivetheme = {
   *      attach: function(context) {
   *        $('#content-column, .sidebar').equalHeight();
   *      }
   *    };
   *  })(jQuery);
   */
  jQuery.fn.equalHeight = function () {
    var height = 0;
    var maxHeight = 0;

    // Store the tallest element's height
    this.each(function () {
      height = jQuery(this).outerHeight();
      maxHeight = (height > maxHeight) ? height : maxHeight;
    });

    // Set element's min-height to tallest element's height
    return this.each(function () {
      var t = jQuery(this);
      var minHeight = maxHeight - (t.outerHeight() - t.height());
      var property = jQuery.browser.msie && jQuery.browser.version < 7 ? 'height' : 'min-height';

      t.css(property, minHeight + 'px');
   });
  };

})(jQuery);