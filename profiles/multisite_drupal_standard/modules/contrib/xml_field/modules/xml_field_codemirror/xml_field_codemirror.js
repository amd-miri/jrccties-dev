/**
 * @file
 * The main javascript file for the xml_field_codemirror module
 *
 * @ingroup xml_field_codemirror
 * @{
 */

(function ($) {

  Drupal.XMLFieldCodeMirror = Drupal.XMLFieldCodeMirror || {};

  /**
  * Core behavior for xml_field_codemirror.
  */
  Drupal.behaviors.XMLFieldCodeMirror = Drupal.behaviors.XMLFieldCodeMirror || {};

  Drupal.XMLFieldCodeMirror.editors = Drupal.XMLFieldCodeMirror.editors || [];

  /**
   * Attach behaviors
   */
  Drupal.behaviors.XMLFieldCodeMirror.attach = function (context, settings) {
    var editor = {};
    var cm_options = {};

    function passAndHint(cm) {
      setTimeout(function() {cm.execCommand("autocomplete");}, 100);
      return CodeMirror.Pass;
    }

    $('.xml-field-codemirror', context).once('xml-field-codemirror', function() {
      var id = $(this).attr('id');
      cm_options = $.extend({
        extraKeys: {
          "' '": passAndHint,
          "'<'": passAndHint,
          "Ctrl-Space": "autocomplete"
        }
      // Get the settings passed in by Drupal for this element id.
      }, Drupal.settings.XMLFieldCodeMirror[id]);

      editor = CodeMirror.fromTextArea($(this).get(0), cm_options);
      editor.xmlHints = editor.xmlHints || [];

      //http://codemirror.net/demo/xmlcomplete.html
      editor.xmlHints['<'] = [
          'levelTop',
          'levelRoot',
          'mainLevel'
      ];

      editor.xmlHints['<levelTop '] =
      editor.xmlHints['<levelRoot '] =
      editor.xmlHints['<mainLevel '] = [
          'property1111',
          'property2222'
      ];

      editor.xmlHints['<levelTop><'] =
      editor.xmlHints['<levelRoot><'] =
      editor.xmlHints['<mainLevel><'] = [
          'second',
          'two'
      ];

      editor.xmlHints['<levelTop><second '] = [
        'secondProperty'
      ];

      editor.xmlHints['<levelTop><second><'] = [
        'three',
        'x-three'
      ];

      editor.commands = editor.commands || {};
      editor.commands.autocomplete = function(cm) {
        editor.showHint(cm, editor.xmlHint);
      }

      Drupal.XMLFieldCodeMirror.editors[id] = editor;
    });
  }

  /**
   * Detach behaviors
   */
  Drupal.behaviors.XMLFieldCodeMirror.detach = function (context, settings, trigger) {
    //Copy the content of the editor into the textarea
    if (trigger == 'serialize') {
      $.each(Drupal.XMLFieldCodeMirror.editors, function () {
        this.save();
      });
    }
  };

  /**
  * @} End of "defgroup xml_field_codemirror".
  */

})(jQuery);
