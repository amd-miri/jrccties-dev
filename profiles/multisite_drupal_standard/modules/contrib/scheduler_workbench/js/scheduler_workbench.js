/**
 * @file
 * Sets the summary for Scheduler Workbench on vertical tabs.
 */

(function ($) {

  Drupal.behaviors.schedulerWorkbench = {
    attach: function (context) {
      // Provide summary when editing a node.
      $('fieldset#edit-scheduler-settings', context).drupalSetSummary(function (context) {
        var vals = [];
        if ($('#edit-revision-publish-on').val() || $('#edit-revision-publish-on-datepicker-popup-0').val()) {
          vals.push(Drupal.t('Scheduled current revision for publishing'));
        }
        if ($('#edit-unpublish-on').val() || $('#edit-unpublish-on-datepicker-popup-0').val()) {
          vals.push(Drupal.t('Scheduled current revision for un-publishing'));
        }
        return vals.join('<br/>');
      });
    }
  };

})(jQuery);
