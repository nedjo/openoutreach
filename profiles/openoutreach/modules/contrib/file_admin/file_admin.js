(function ($) {

Drupal.behaviors.fileAdminTypes = {
  attach: function (context) {
    // Provide the vertical tab summaries.
    $('fieldset#edit-options', context).drupalSetSummary(function(context) {
      var vals = [];
      var fields = ['published', 'promote', 'sticky'];
      $.each(fields, function(index, value) {
        $("#edit-" + value + ":checked", context).parent().each(function() {
          vals.push(Drupal.checkPlain($(this).text()));
        });
      });
      if (!$('#edit-published', context).is(':checked')) {
        vals.unshift(Drupal.t('Not published'));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
