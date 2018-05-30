<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the stylesheets field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_stylesheets extends views_handler_field_prerender_list {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_stylesheets_format'] = array('default' => '[filename] ([media])');

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_stylesheets_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Display format'),
      '#description' => t('Alter the output of this field by specifying a string of text with replacement tokens. Replacement patterns: [filename], [media]'),
      '#default_value' => !empty($this->options['system_info_stylesheets_format']) ? $this->options['system_info_stylesheets_format'] : '[filename] ([media])',
    );
  }


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['stylesheets'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['stylesheets'] as $media => $value) {
          foreach ($value as $filename) {
            $this->items[$field][] = array('filename' => $filename, 'media' => $media);
          }
        }
      }
    }
  }


  function render_item($count, $item) {

    $tokens = array('[filename]', '[media]');
    $values = array($item['filename'], $item['media']);

    return str_replace($tokens, $values, check_plain($this->options['system_info_stylesheets_format']));
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-filename' . ']'] = t('The filename of the CSS file.');
    $tokens['[' . $this->options['id'] . '-media' . ']'] = t('The media type of the CSS file.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-filename' . ']'] = $item['filename'];
    $tokens['[' . $this->options['id'] . '-media' . ']'] = $item['media'];
  }
}
