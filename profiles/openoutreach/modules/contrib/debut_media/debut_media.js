/**
 * @file
 * Modify jcarousel behaviour to set number of items on window resize.
 */

(function($) {

Drupal.debutMedia = {};
Drupal.debutMedia.setupCallback = function(carousel) {
  Drupal.jcarousel.setupCarousel(carousel);
  if (carousel.options.navigation) {
    Drupal.jcarousel.addNavigation(carousel, carousel.options.navigation);
  }
  carousel.reload();
};
Drupal.debutMedia.reloadCallback = function(carousel) {
  // Set the clip and container to auto width so that they will fill
  // the available space.
  carousel.container.css('width', 'auto');
  carousel.clip.css('width', 'auto');
  var clipWidth = carousel.clip.width();
  var containerExtra = carousel.container.width() - carousel.clip.outerWidth(true);
  // Determine the width of an item.
  var itemWidth = carousel.list.find('li').first().outerWidth(true);
  var numItems = Math.floor(carousel.clip.width() / itemWidth) || 1;
  // Set the new scroll number.
  carousel.options.scroll = numItems;
  var newClipWidth = numItems * itemWidth;
  var newContainerWidth = newClipWidth + containerExtra;
  // Resize the clip and container.
  carousel.clip.width(newClipWidth);
  carousel.container.width(newContainerWidth);
};

})(jQuery);
