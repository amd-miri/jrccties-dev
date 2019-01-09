/**
 * @file
 * The JRC Evidence to Inform Policy Community term and conditions.
 */

(function ($) {
  Drupal.behaviors.jrcEvidenceToInformPolicy = {
    attach: function (context, settings) {
      $("#block-block-21").dialog({
        closeOnEscape: false,
        open: function (event, ui) {
          $(".ui-dialog-titlebar-close", ui.dialog | ui).hide();
        },
        modal: true,
        width: 1200,
        buttons: {
          "I agree to the Terms of Use": function () {
            $(this).dialog("close");
          }
        }
      });
    }
  };
})(jQuery);
