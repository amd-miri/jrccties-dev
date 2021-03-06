<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function atomium_atomium_theme_select() {
  return array(
    'select' => array(
      'render element' => 'element',
      'template' => 'select',
    ),
  );
}

/**
 * Implements hook_preprocess_hook().
 */
function atomium_preprocess_select(array &$variables, $hook) {
  element_set_attributes($variables['element'], array('id', 'name', 'size'));
  _form_set_class($variables['element'], array('form-select'));
  $attributes = _atomium_get_attributes($variables['element']);

  if (isset($variables['element']['#field_name'])) {
    $variables['theme_hook_suggestions'][] = 'select__' . $variables['element']['#field_name'];
  }
  if (isset($variables['element']['#entity_type'])) {
    $variables['theme_hook_suggestions'][] = 'select__' . $variables['element']['#entity_type'];
    if (isset($variables['element']['#field_name'])) {
      $variables['theme_hook_suggestions'][] = 'select__' . $variables['element']['#entity_type'] . '__' . $variables['element']['#field_name'];
    }
    if (isset($variables['element']['#bundle'])) {
      $variables['theme_hook_suggestions'][] = 'select__' . $variables['element']['#entity_type'] . '__' . $variables['element']['#bundle'];
    }
  }

  if (isset($variables['element']['#atomium']['attributes']['element'])) {
    $variables['atomium']['attributes']['element']
      ->merge($variables['element']['#atomium']['attributes']['element']);
  }

  $variables['atomium']['attributes']['element']->merge($attributes);
}
