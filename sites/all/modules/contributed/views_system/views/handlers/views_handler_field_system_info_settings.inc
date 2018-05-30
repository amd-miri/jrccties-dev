<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the settings field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_settings extends views_handler_field_prerender_list {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_settings_format'] = array('default' => '[name] = [value]');

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_settings_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Display format'),
      '#description' => t('Alter the output of this field by specifying a string of text with replacement tokens. Replacement patterns: [name], [value]'),
      '#default_value' => !empty($this->options['system_info_settings_format']) ? $this->options['system_info_settings_format'] : '[name] = [value]',
    );
  }


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['settings'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['settings'] as $name => $value) {
          $this->items[$field][] = array('value' => $value, 'name' => $name);
        }
      }
    }
  }


  function render_item($count, $item) {

    $tokens = array('[name]', '[value]');
    $values = array($item['name'], $item['value']);

    return str_replace($tokens, $values, check_plain($this->options['system_info_settings_format']));
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-name' . ']'] = t('The name of the setting.');
    $tokens['[' . $this->options['id'] . '-value' . ']'] = t('The value of the setting.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-name' . ']'] = $item['name'];
    $tokens['[' . $this->options['id'] . '-value' . ']'] = $item['value'];
  }
}
