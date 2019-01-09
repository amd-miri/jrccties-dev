
/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {

Drupal.media = Drupal.media || {};

/**
 * Prevent media markup from being left behind in the WYSIWYG during editing.
 *
 * When an embedded document is placed in the WYSIWYG, and later selected and
 * either (1) deleted, or (2) overwritten with other text, it is easy for the
 * visible markup (i.e., the file icon and filename) to completely disappear
 * but the underlying, invisible media token to be left behind in the HTML. If
 * this happens, then after the content is saved the embedded document will
 * reappear despite having already been deleted from the user's perspective.
 *
 * This function fixes the issue by forcing the full media element (including
 * the invisible token) to be selected once enough of it is.
 *
 * In addition to the above, this function also fixes a related problem in
 * which after embedding the document in the WYSIWYG (or placing the cursor
 * near it later on), the cursor is located inside the element itself (inside
 * the <span> tag). Anything typed from this position will be ignored, and
 * anything typed after hitting the "return" key from this position will be
 * replaced with a duplicate copy of the document (since CKEditor treats the
 * <span> as inline styling which should be preserved across line breaks). To
 * mitigate this, the code in this function forces the cursor outside of the
 * <span> tag whenever it is placed directly inside it.
 *
 * @todo: Make this work for editors other than CKEditor.
 */
if (typeof CKEDITOR !== 'undefined') {
  CKEDITOR.on('instanceReady', function (event) {
    event.editor.on('selectionChange', function (event) {
      // If something more than just the filename link was selected, change the
      // selection to encompass the entire media element.
      var $selected_element = $(event.data.selection.getStartElement().$);
      if (!$selected_element.is('a') && !$selected_element.hasClass('media-element')) {
        var $full_element = $selected_element.closest('.media-element');
        if ($full_element.length) {
          var full_element = new CKEDITOR.dom.element($full_element.get(0));
          event.data.selection.selectElement(full_element);
        }
      }
      // If the cursor is located inside the <span> tag directly (not inside
      // the filename link within it), put the cursor directly after the <span>
      // tag instead. We do this by finding the parent element, selecting that,
      // and that moving the cursor to the end of that selection. See
      // http://stackoverflow.com/questions/4536532/how-to-set-cursor-position-to-end-of-text-in-ckeditor
      else if ($selected_element.is('span') && $selected_element.hasClass('media-element')) {
        var parent = new CKEDITOR.dom.element($selected_element.parent().get(0));
        event.data.selection.selectElement(parent);
        selected_ranges = event.data.selection.getRanges();
        selected_ranges[0].collapse(false);
        event.data.selection.selectRanges(selected_ranges);
      }
    });
  });
}

if (typeof tinymce !== 'undefined' && tinymce.majorVersion == "3") {
  tinymce.onAddEditor.add(function(cm, ed) {
    ed.onNodeChange.add(function(ed, cm, e) {
      tinymce.each(ed.dom.select('span.media-element', e.node), function(n) {
        if (!n.hasChildNodes() || (n.hasChildNodes() && n.firstChild.nodeName.toLowerCase() == "br" )) {
          var parent = n.parentNode;
          // Workaround for Chrome
          if (tinymce.isWebKit) {
              ed.selection.select(n);
              ed.dom.remove(n); // Remove faulty node
              // The parent is empty, so fake some content,
              // otherwise the cursor jumps to the start of the editor.
              parent.innerHTML = "&nbsp;";
              ed.selection.select(parent);
              ed.selection.collapse(true);
              ed.selection.setContent("");
          }
          // All other browsers (even IE) work fine
          else {
            ed.dom.remove(parent);
          }
        }
      });
    });
  });
}

/**
 * Register the plugin with WYSIWYG.
 */
Drupal.wysiwyg.plugins.media = {

  /**
   * The selected text string.
   */
  selectedText: null,

  /**
   * Determine whether a DOM element belongs to this plugin.
   *
   * @param node
   *   A DOM element
   */
  isNode: function(node) {
    return $(node).is('img[data-media-element]');
  },

  /**
   * Execute the button.
   *
   * @param data
   *   An object containing data about the current selection:
   *   - format: 'html' when the passed data is HTML content, 'text' when the
   *     passed data is plain-text content.
   *   - node: When 'format' is 'html', the focused DOM element in the editor.
   *   - content: The textual representation of the focused/selected editor
   *     content.
   * @param settings
   *   The plugin settings, as provided in the plugin's PHP include file.
   * @param instanceId
   *   The ID of the current editor instance.
   */
  invoke: function (data, settings, instanceId) {
    if (data.format == 'html') {
      var insert = new InsertMedia(instanceId);
      // CKEDITOR module support doesn't set this setting
      if (typeof settings['global'] === 'undefined') {
        settings['global'] = {id: 'media_wysiwyg'};
      }
      if (this.isNode(data.node)) {
        // Change the view mode for already-inserted media.
        var media_file = Drupal.media.filter.extract_file_info($(data.node));
        insert.onSelect([media_file]);
      }
      else {
        // Store currently selected text.
        this.selectedText = data.content;

        // Insert new media.
        insert.prompt(settings.global);
      }
    }
  },

  /**
   * Attach function, called when a rich text editor loads.
   * This finds all [[tags]] and replaces them with the html
   * that needs to show in the editor.
   *
   * This finds all JSON macros and replaces them with the HTML placeholder
   * that will show in the editor.
   */
  attach: function (content, settings, instanceId) {
    content = Drupal.media.filter.replaceTokenWithPlaceholder(content);
    return content;
  },

  /**
   * Detach function, called when a rich text editor detaches
   */
  detach: function (content, settings, instanceId) {
    content = Drupal.media.filter.replacePlaceholderWithToken(content);
    return content;
  }
};
/**
 * Defining InsertMedia object to manage the sequence of actions involved in
 * inserting a media element into the WYSIWYG.
 * Keeps track of the WYSIWYG instance id.
 */
var InsertMedia = function (instance_id) {
  this.instanceId = instance_id;
  return this;
};

InsertMedia.prototype = {
  /**
   * Prompt user to select a media item with the media browser.
   *
   * @param settings
   *    Settings object to pass on to the media browser.
   *    TODO: Determine if this is actually necessary.
   */
  prompt: function (settings) {
    Drupal.media.popups.mediaBrowser($.proxy(this, 'onSelect'), settings);
  },

  /**
   * On selection of a media item, display item's display configuration form.
   */
  onSelect: function (media_files) {
    this.mediaFile = media_files[0];
    Drupal.media.popups.mediaStyleSelector(this.mediaFile, $.proxy(this, 'insert'), {});
  },

  /**
   * When display config has been set, insert the placeholder markup into the
   * wysiwyg and generate its corresponding json macro pair to be added to the
   * tagmap.
   */
  insert: function (formatted_media) {
    var element = Drupal.media.filter.create_element(formatted_media.html, {
          fid: this.mediaFile.fid,
          view_mode: formatted_media.type,
          attributes: this.mediaFile.attributes,
          fields: formatted_media.options,
          link_text: Drupal.wysiwyg.plugins.media.selectedText
        });
    // Get the markup and register it for the macro / placeholder handling.
    var markup = Drupal.media.filter.getWysiwygHTML(element);

    // Insert placeholder markup into wysiwyg.
    Drupal.wysiwyg.instances[this.instanceId].insert(markup);
  }
};

/** Helper functions */

/**
 * Ensures the tag map has been initialized.
 */
function ensure_tagmap () {
  return Drupal.media.filter.ensure_tagmap();
}

/**
 * Serializes file information as a url-encoded JSON object and stores it as a
 * data attribute on the html element.
 *
 * @param html (string)
 *    A html element to be used to represent the inserted media element.
 * @param info (object)
 *    A object containing the media file information (fid, view_mode, etc).
 *
 * @deprecated
 */
function create_element (html, info) {
  return Drupal.media.filter.create_element(html, info);
}

/**
 * Create a macro representation of the inserted media element.
 *
 * @param element (jQuery object)
 *    A media element with attached serialized file info.
 *
 * @deprecated
 */
function create_macro (element) {
  return Drupal.media.filter.create_macro(element);
}

/**
 * Extract the file info from a WYSIWYG placeholder element as JSON.
 *
 * @param element (jQuery object)
 *    A media element with attached serialized file info.
 *
 * @deprecated
 */
function extract_file_info (element) {
  return Drupal.media.filter.extract_file_info(element);
}

/**
 * Gets the HTML content of an element.
 *
 * @param element (jQuery object)
 *
 * @deprecated
 */
function outerHTML (element) {
  return Drupal.media.filter.outerHTML(element);
}

})(jQuery);
