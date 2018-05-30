/**
 * @file
 * Defines mediaFormatSelector popup dialog for the media project.
 */

(function($) {

  Drupal.media.popups.mediaFormatSelector = function(data, callback, options) {
    var defaults = Drupal.media.popups.mediaFormatSelector.getDefaults();
    if ('object' === typeof data) {
      var map = {
        ID: data.id,
        FORMAT: data.format,
        PARAMS: data.params ? encodeURIComponent(data.params) : ''
      };
    }
    else {
      map = {
        ID: data,
        FORMAT: '',
        PARAMS: ''
      };
    }
    Object.keys(map).forEach(function(key) {
      defaults.src = defaults.src.replace(key, map[key]);
    });
    options = jQuery.extend({}, defaults, options);
    var popup = Drupal.media.popups.getPopupIframe(options.src, 'mediaFormatSelector');
    popup.bind('load', options, options.onLoad);
    var dialogOptions = Drupal.media.popups.getDialogOptions();
    dialogOptions.buttons['ok'] = function() {
      callback(this.contentWindow.Drupal.mediaFormatSelectorData);
      $(this).dialog('close');
    };
    var dialog = popup.dialog(dialogOptions);
    Drupal.media.popups.sizeDialog(dialog);
    Drupal.media.popups.resizeDialog(dialog);
    Drupal.media.popups.scrollDialog(dialog);
    Drupal.media.popups.overlayDisplace(dialog.parents('.ui-dialog'));

    return popup;
  };


  Drupal.media.popups.mediaFormatSelector.onLoad = function(e) {
  };


  Drupal.media.popups.mediaFormatSelector.getDefaults = function() {
    return {
      src: Drupal.settings.media.mediaFormatSelectorUrl,
      onLoad: Drupal.media.popups.mediaFormatSelector.onLoad
    };
  };

})(jQuery);
