/**
 * @file
 * JS configuration file to add js POP up.
 */

(function ($) {
    'use strict';
    // Allow Submit/Edit button.
    var click = false;
    // Dirty form flag.
    var edit = false;
    var input_value = [];
    Drupal.behaviors.jsConfirmPopUp = {
        attach: function (context, settings) {
            // If they leave an input field, assume they changed it.
            $('.js-confirm-pop-up :input').each(function () {
                $(this).blur(function () {
                    var id = $(this).attr('id');
                    if ($.inArray(id, input_value) === -1) {
                        input_value.push(id);
                    }
                    if (form_element_value(input_value).length !== 0) {
                        edit = true;
                    } else {
                        edit = false;
                    }
                });
            });

            // Let all form submit buttons through.
            $(".js-confirm-pop-up input[type='submit']").each(function () {
                $(this).addClass('node-edit-processed');
                $(this).click(function () {
                    click = true;
                });
            });

            // Catch all links and buttons EXCEPT for "#" links.
            $("a, button, input[type='submit']:not(.node-edit-processed)")
                    .each(function () {
                        $(this).click(function () {
                            // Return when a "#" link is clicked so as to skip the,
                            // Window.onbeforeunload function.
                            if (edit && $(this).attr('href') !== '#') {
                                return 0;
                            }
                        });
                    });

            // Handle backbutton, exit etc.
            $(window).on('beforeunload', function() {
                // Add CKEditor support.
                if (typeof (CKEDITOR) != 'undefined' && typeof (CKEDITOR.instances) != 'undefined') {
                    for (var i in CKEDITOR.instances) {
                        if (CKEDITOR.instances[i].checkDirty()) {
                            edit = true;
                            break;
                        }
                    }
                }
                if (edit && !click) {
                    click = false;
                    return (Drupal.t('You will lose all unsaved work.'));
                }
            });
            function form_element_value(input_value) {
                var id_val = [];
                $.each(input_value, function (index, value) {
                    if ($("#" + value).val().length !== 0) {
                        id_val.push($("#" + value).val());
                    }
                });
                return id_val;
            }
        }
    };
})(jQuery);
