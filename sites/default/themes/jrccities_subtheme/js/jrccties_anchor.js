/**
 * @file
 * Code for fixing the anchor link.
 *
 * Code for move from behind the navbar to the anchor link.
 */

(function ($) {
  Drupal.behaviors.jrccties_anchorModule = {
    attach: function (context, settings) {
      // Wait for images to load for proper offsets.
      $(window).load(function () {
        // Get the anchor.
        var hashVal = window.location.hash.substring(1);
        if (hashVal) {
        // Get the element offset.
        var elOffset = $("a[name=" + hashVal + "]").offset();
        var offsetTop = elOffset.top;
        $(document).scrollTop(offsetTop - 60);
        }
      });
      $("a[href^='#']").click(function (event) {
        // All anchor links but top page link.
        var className = $(this).attr('class');
        if (className !== "btn-back-top") {
          // Prevent the default action for the click event.
          event.preventDefault();
          // Get the full url.
          var full_url = this.href;
          // Split the url by # and get the anchor target name.
          var parts = full_url.split("#");
          var trgt = parts[1];
          if (trgt) {
            // Get the top offset of the target anchor.
            var target_offset = $("a[name=" + trgt + "]").offset();
            var target_top = target_offset.top;
            $(document).scrollTop(target_top - 60);
          }
        }
      });
    }
  }
}(jQuery));
