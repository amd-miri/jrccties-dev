<?php
/**
 * @file
 * Administration pages for the CKEditor LITE module.
 */

/**
 * Module settings form.
 */
function ckeditor_lite_settings_form() {
  $form = array();

  $form['ckeditor_lite_istracking'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable changes tracking'),
    '#description' => t('Enable the CKEditor LITE changes tracking by default.'),
    '#default_value' => variable_get('ckeditor_lite_istracking', 1),
  );

  return system_settings_form($form);
}
