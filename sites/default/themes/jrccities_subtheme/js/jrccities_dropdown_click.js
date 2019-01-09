/**
 * @file
 * The dropdown click.
 */

(function ($) {
  Drupal.behaviors.dropdownClick = {
    attach: function (context, settings) {
      $("#block-menu-menu-communities-menu .dropdown-toggle").click(function () {
        window.location.href = $(this).attr("href");
      });
    }
  };
})(jQuery);
