/**
 * @file
 * The private messages.
 */

(function ($) {
  Drupal.behaviors.privateMessages = {
    attach: function (context, settings) {
      $(".privatemsg-message .privatemsg-message-column").each(function () {
        if ($(this).find(".privatemsg-author-name").text() == "You") {
          $(this).find(".privatemsg-message-body").addClass("message-own");
        }
      });
    }
  };
})(jQuery);
