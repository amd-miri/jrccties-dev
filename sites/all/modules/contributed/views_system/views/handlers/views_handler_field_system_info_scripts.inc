<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the scripts field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_scripts extends views_handler_field_prerender_list {


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['scripts'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['scripts'] as $script) {
          $this->items[$field][] = array('script' => $script);
        }
      }
    }
  }


  function render_item($count, $item) {

    return $item['script'];
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-script' . ']'] = t('The Javascript file of the theme.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-script' . ']'] = $item['script'];
  }
}
