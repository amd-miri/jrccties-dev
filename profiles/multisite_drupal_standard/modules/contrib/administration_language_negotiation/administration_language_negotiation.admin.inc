<?php

/**
 * @file
 * The admin page of the administration language negotiation module.
 */

/**
 * Custom form.
 *
 * @return array
 */
function administration_language_negotiation_admin() {
  $language_default = language_default();
  $languages = language_list('enabled');

  $options = array();
  foreach ($languages[1] as $language) {
    $options[$language->language] = $language->name;
  }

  $form['administration_language_negotiation_default'] = array(
    '#title' => t('Select the default administration language.'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => variable_get('administration_language_negotiation_default', $language_default->language),
    '#required' => TRUE,
  );

  $form['administration_language_negotiation_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#default_value' => implode(variable_get('administration_language_negotiation_paths', array()), "\r\n"),
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %admin for one specific admin page and %admin-wildcard for every admin pages.", array('%admin' => 'admin', '%admin-wildcard' => 'admin/*')),
    '#size' => 10,
  );

  $form['#validate'][] = 'administration_language_negotiation_admin_validate';

  return system_settings_form($form);
}

/**
 * Custom form validate callback.
 */
function administration_language_negotiation_admin_validate($form, &$form_state) {
  $values = &$form_state['values'];
  $values['administration_language_negotiation_paths'] = explode("\r\n", $values['administration_language_negotiation_paths']);
}