/**
 * @file
 * Javascript for format selector form.
 */

Drupal.ajax.prototype.commands.MediaFormatSelectorSubmit = function(ajax, response, status) {
  Drupal.mediaFormatSelectorData = response.data;
  jQuery(parent.window.document.body).find('#mediaFormatSelector')
    .parent('.ui-dialog').find('.ui-dialog-buttonpane button').click();
};
