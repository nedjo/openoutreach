(function ($) {

  /**
   * Ensure only a single default is selected.
   */
  Drupal.behaviors.redhenFieldsDisplayWidget = {
    attach:function (context, settings) {
      $('input[name*="default"]', $('.field-type-redhen-email')).click(function () {
        var $checked = $(this);
        $('input[name*=default]', $('.field-type-redhen-email')).each(function () {
          if ($(this).attr('id') !== $checked.attr('id')) {
            $(this).removeAttr('checked');
          }
        });
      });
    }
  };

})(jQuery);
