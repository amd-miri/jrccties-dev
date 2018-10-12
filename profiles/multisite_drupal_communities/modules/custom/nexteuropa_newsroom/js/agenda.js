/**
 * @file
 * Agenda page switcher.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_newsroom = {
     showHiddenAgendaItems: function (id, caller) {
         $('.' + id).show();
         $(caller).hide();
        return false;
    }
  };
})(jQuery);
