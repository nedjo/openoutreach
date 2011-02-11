// $Id: logintoboggan.js,v 1.4 2011/01/06 06:52:19 thehunmonkgroup Exp $

(function ($) {
  Drupal.behaviors.LoginToboggan = {
    attach: function (context, settings) {
      $('#toboggan-login', context).once('toggleboggan_setup', function () {
        $(this).hide();
        Drupal.logintoboggan_toggleboggan();
      });
    }
  };

  Drupal.logintoboggan_toggleboggan = function() {
    $("#toboggan-login-link").click(
      function () {
        $("#toboggan-login").slideToggle("fast");
        this.blur();
        return false;
      }
    );
  };
})(jQuery);

