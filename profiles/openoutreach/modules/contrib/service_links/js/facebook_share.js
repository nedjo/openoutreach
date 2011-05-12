(function ($) {
  $(document).ready(function(){
    $('a.service-links-facebook-widget').each(function(){
      $(this).attr('expr:share_url', $(this).attr('rel'));
      $(this).attr('type', Drupal.settings.ws_fs.type);
      $(this).attr('name', 'fb_share');
    });
  });
})(jQuery);
