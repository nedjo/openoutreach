(function ($) {

/**
 * Attaches the states.
 */
Drupal.behaviors.subprofiles = {
  attach: function (context, settings) {
    $('#install-configure-form select[name="subprofile"]').show();
    $('#install-configure-form #edit-features .form-type-checkbox', context).once('subprofiles', function() {
      // Override the standard visible state effect.
      $(this).bind('state:visible', function(e) {
        if (e.trigger) {
          $(e.target).closest('.form-item, .form-submit, .form-wrapper').fadeToggle(e.value);
        }
      })
    });
    // Set to equal heights for better alignment.
    var tallest = 0;
    $('#install-configure-form #edit-features .form-type-checkbox', context)
      .each(function() {
        var eltHeight = $(this).height();
        if (eltHeight > tallest) {
          tallest = eltHeight;
        }
      })
      .height(tallest);
  }
};

})(jQuery);
