/*global Drupal: false, jQuery: false */
/*jslint devel: true, browser: true, maxerr: 50, indent: 2 */
(function ($) {
  "use strict";

  Drupal.behaviors.ckeditor_lite = {};
  Drupal.behaviors.ckeditor_lite.attach = function(context, settings) {
    var $changes_ins = $('.ice-ins', context);
    var $changes_del = $('.ice-del', context);
    var $show_with_changes_button = $('.block-ckeditor-lite .content .show-with-changes-button', context);
    var $show_without_changes_button = $('.block-ckeditor-lite .content .show-without-changes-button', context);
    var $show_changes_button = $('.block-ckeditor-lite .content .show-changes-button', context);
    var $hide_changes_button = $('.block-ckeditor-lite .content .hide-changes-button', context);

    if (Drupal.settings.ckeditor_lite.show_with_changes) {
      $changes_ins.addClass('ckeditor-lite-ins');
      $changes_del.addClass('ckeditor-lite-del');
      $show_with_changes_button.toggle();
      // $hide_changes_button.toggle();
    }
    else {
      $changes_ins.addClass('ckeditor-lite-ins-inv');
      $changes_del.addClass('ckeditor-lite-del-inv');
      $show_without_changes_button.toggle();
      // $hide_changes_button.toggle();
    }
    $hide_changes_button.toggle();

    $show_with_changes_button.click(function() {
      $show_with_changes_button.toggle();
      $show_without_changes_button.toggle();

      $changes_ins.toggleClass('ckeditor-lite-ins').toggleClass('ckeditor-lite-ins-inv');
      $changes_del.toggleClass('ckeditor-lite-del').toggleClass('ckeditor-lite-del-inv');
    });
    $show_without_changes_button.click(function() {
      $show_with_changes_button.toggle();
      $show_without_changes_button.toggle();

      $changes_ins.toggleClass('ckeditor-lite-ins').toggleClass('ckeditor-lite-ins-inv');
      $changes_del.toggleClass('ckeditor-lite-del').toggleClass('ckeditor-lite-del-inv');
    });

    $show_changes_button.click(function() {
      $show_changes_button.toggle();
      $hide_changes_button.toggle();

      $('body').toggleClass('ICE-Tracking');
    });
    $hide_changes_button.click(function() {
      $show_changes_button.toggle();
      $hide_changes_button.toggle();

      $('body').toggleClass('ICE-Tracking');
    });
  };

})(jQuery);
