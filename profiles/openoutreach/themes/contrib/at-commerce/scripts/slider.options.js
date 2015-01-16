(function ($) {
  $(document).ready(function() {
    /**
     * FlexSlider options, see: http://flex.madebymufffin.com/
     *
     * animation: "fade",        // Select your animation type (fade/slide)
     * slideshow: true,          // Should the slider animate automatically by default? (true/false)
     * slideshowSpeed: 7000,     // Set the speed of the slideshow cycling, in milliseconds
     * animationDuration: 600,   // Set the speed of animations, in milliseconds
     * directionNav: true,       // Create navigation for previous/next navigation? (true/false)
     * controlNav: true,         // Create navigation for paging control of each clide? (true/false)
     * keyboardNav: true,        // Allow for keyboard navigation using left/right keys (true/false)
     * touchSwipe: true,         // Touch swipe gestures for left/right slide navigation (true/false)
     * prevText: "Previous",     // Set the text for the "previous" directionNav item
     * nextText: "Next",         // Set the text for the "next" directionNav item
     * pausePlay: false,         // Create pause/play dynamic element (true/false)
     * pauseText: 'Pause',       // Set the text for the "pause" pausePlay item
     * playText: 'Play',         // Set the text for the "play" pausePlay item
     * randomize: false,         // Randomize slide order on page load? (true/false)
     * slideToStart: 0,          // The slide that the slider should start on. Array notation (0 = first slide)
     * animationLoop: true,      // Should the animation loop? If false, directionNav will received disabled classes when at either end (true/false)
     * pauseOnAction: true,      // Pause the slideshow when interacting with control elements, highly recommended. (true/false)
     * pauseOnHover: false,      // Pause the slideshow when hovering over slider, then resume when no longer hovering (true/false)
     * controlsContainer: "",    // Advanced property: Can declare which container the navigation elements should be appended too. Default container is the flexSlider element. Example use would be ".flexslider-container", "#container", etc. If the given element is not found, the default action will be taken.
     * manualControls: "",       // Advanced property: Can declare custom control navigation. Example would be ".flex-control-nav" or "#tabs-nav", etc. The number of elements in your controlNav should match the number of slides/tabs (obviously).
     * start: function(){},      // Callback: function(slider) - Fires when the slider loads the first slide
     * before: function(){},     // Callback: function(slider) - Fires asynchronously with each slider animation
     * after: function(){},      // Callback: function(slider) - Fires after each slider animation completes
     * end: function(){}         // Callback: function(slider) - Fires when the slider reaches the last slide (asynchronous)
     */
    $('article.flexible-slideshow .flexslider').flexslider({
      animation: "slide",
      slideshowSpeed: 6000,
    });
  });
}(jQuery));