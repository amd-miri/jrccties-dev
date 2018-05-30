<?php

/**
 * @file
 * Administration page callbacks for the Media Embed module.
 */


/**
 * Form constructor for media embed settings form.
 */
function media_embed_settings_form($form, &$form_state) {
  $settings = media_embed_settings();
  $key = 'media_embed_settings';
  $form[$key] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );
  $element = &$form[$key];

  $browser_plugins = array();
  foreach (media_get_browser_plugin_info() as $key => $plugin) {
    $browser_plugins[$key] = !empty($plugin['title']) ? $plugin['title'] : $key;
  }
  asort($browser_plugins);
  $element['browser_plugins'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled browser plugins'),
    '#description' => t('If no plugins are selected, they all will be available.'),
    '#options' => $browser_plugins,
    '#default_value' => $settings['browser_plugins'],
  );

  $file_types = file_entity_type_get_names();
  asort($file_types);
  $element['file_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allowed file types'),
    '#description' => t('If no file types are selected, they all will be available.'),
    '#options' => $file_types,
    '#default_value' => $settings['file_types'],
  );

  $element['upload_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('File directory for uploaded media'),
    '#description' => t('Optional subdirectory within the upload destination where files will be stored. Do not include preceding or trailing slashes.'),
    '#default_value' => $settings['upload_directory'],
  );

  if (module_exists('token')) {
    $element['upload_directory']['#description'] .= ' ' . t('This field supports tokens.');
    $element['tokens'] = array(
      '#theme' => 'token_tree',
      '#dialog' => TRUE,
    );
  }

  return system_settings_form($form);
}


/**
 * Validation handler for media embed settings form.
 */
function media_embed_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values']['media_embed_settings'];
  $values['browser_plugins'] = array_values(array_filter($values['browser_plugins']));
  $values['file_types'] = array_values(array_filter($values['file_types']));
}
