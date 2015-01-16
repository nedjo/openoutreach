(function ($) {

  Drupal.behaviors.redhenForms = {
    attach:function (context) {
      $('.redhen-field-type-date').datepicker({
        autoSize:true,
        showButtonPanel:true
      });
    }
  };

})(jQuery);
