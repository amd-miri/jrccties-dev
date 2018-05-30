<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the regions field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_regions extends views_handler_field_prerender_list {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_regions_format'] = array('default' => '[human_name] ([machine_name])');

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_regions_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Display format'),
      '#description' => t('Alter the output of this field by specifying a string of text with replacement tokens. Replacement patterns: [human_name], [machine_name]'),
      '#default_value' => !empty($this->options['system_info_regions_format']) ? $this->options['system_info_regions_format'] : '[human_name] ([machine_name])',
    );
  }


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['regions'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['regions'] as $machine_name => $human_name) {
          $this->items[$field][] = array('human_name' => $human_name, 'machine_name' => $machine_name);
        }
      }
    }
  }


  function render_item($count, $item) {

    $tokens = array('[human_name]', '[machine_name]');
    $values = array($item['human_name'], $item['machine_name']);

    return str_replace($tokens, $values, check_plain($this->options['system_info_regions_format']));
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-human_name' . ']'] = t('The human name of the region.');
    $tokens['[' . $this->options['id'] . '-machine_name' . ']'] = t('The machine name of the region.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-human_name' . ']'] = $item['human_name'];
    $tokens['[' . $this->options['id'] . '-machine_name' . ']'] = $item['machine_name'];
  }
}
