
/**
 *  @file
 *  A simple jQuery Slider Div Slideshow Rotator.
 */
(function ($) {

/**
 * This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowSlider = {
  attach: function (context, settings) {
    // Proces the slider div
    $('.views_slideshow_slider:not(.viewsSlideshowSlider-processed)', context).addClass('viewsSlideshowSlider-processed').each(function() {

      var uniqueID = $(this).attr('id').replace('views_slideshow_slider_slider_', '');
      $(this).slider({
          orientation: settings.orientation,
          value: 0,
          min: 0,
          max: settings.viewsSlideshowSlider[uniqueID].max,
          range: "min",
          animate: true,
          step: 1,
          slide: Drupal.viewsSlideshowSliderMove,
          change: Drupal.viewsSlideshowSliderMove
      });
    });
  }
};

Drupal.viewsSlideshowSliderMove = function(event, ui) {
  var uniqueID = $(this).attr('id').replace('views_slideshow_slider_slider_', '');
  if (event.originalEvent) { // On machine update this is undefined.
    Drupal.viewsSlideshow.action({ "action": 'goToSlide', "slideshowID": uniqueID, "slideNum": ui.value });
  }
}

Drupal.viewsSlideshowSlider = Drupal.viewsSlideshowSlider || {};

/**
 * Implement viewsSlideshowSlider for the slider.
 */
Drupal.viewsSlideshowSlider.transitionBegin = function (options) {
  var slider = $('#views_slideshow_slider_slider_' + options.slideshowID);
  // Move the slider to the next stop. Because slider counts from 0 we don't need a slideNum + 1.
  slider.slider('value', options.slideNum);
}

})(jQuery);