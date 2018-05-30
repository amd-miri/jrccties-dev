<?php

/**
 * @file
 * Administration page for JS confirm pop up module.
 */

/**
 * Setting form for js confirm pop up.
 */
function js_confirm_pop_up_settings() {
  $form = array();
  $form['js_confirm_pop_up_actual_form_id'] = array(
    '#type' => 'textarea',
    '#title' => t('Actual drupal form id:'),
    '#description' => t('Enter comma(,) separated form ids of drupal form(Machine name) where you want to add your javascript file. Eg. "node_form,node_edit_form".'),
    '#default_value' => variable_get('js_confirm_pop_up_actual_form_id'),
    '#size' => 10,
  );
  return system_settings_form($form);
}
