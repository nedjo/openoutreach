// $Id: service_links_fisheye.js,v 1.1.2.2.2.2 2010/10/22 09:36:18 thecrow Exp $
(function ($) {
  $(document).ready(function(){
    $('.fisheye').Fisheye({
      maxWidth: 32,
      items: 'a',
      itemsText: 'span',
      container: '.fisheyeContainer',
      itemWidth: 16,
      proximity: 60,
      halign : 'center'
    })
  });
})(jQuery);
