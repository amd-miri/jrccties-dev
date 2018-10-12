<?php
/**
 * @file
 * Admin settings for Menu Token.
 */

/**
 * Display settings form for Menu Token.
 *
 * @see menu_token_menu()
 */
function menu_token_settings_form() {
  $form = array();
  $options = array();

  foreach (entity_get_info() as $entity => $info) {
    $options[$entity] = $info['label'];
  }

  $form['menu_token_entities'] = array(
    '#title' => t('Available entities'),
    '#description' => t("Limit which entities are available in Menu Token's context settings select boxes."),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('menu_token_entities', array('node', 'user')),
  );

  $form['#submit'][] = 'menu_token_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Form submission handler form menu_token_settings_form().
 */
function menu_token_settings_form_submit($form, &$form_state) {
  // Clear plugin cache.
  cache_clear_all('plugins:menu_token:plugins', 'cache');
}
