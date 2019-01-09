/**
 * @file
 * The private messages.
 */

(function ($) {
  Drupal.behaviors.jrcctiesPdfDownloadLink = {
    attach: function (context, settings) {
      $(".pdf-reader-download-link").text("Click here to download the file.");
    }
  };
})(jQuery);
