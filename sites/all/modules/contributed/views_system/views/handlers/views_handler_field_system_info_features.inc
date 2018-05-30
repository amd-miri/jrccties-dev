<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the features field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_features extends views_handler_field_prerender_list {


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['features'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['features'] as $feature) {
          $this->items[$field][] = array('feature' => $feature);
        }
      }
    }
  }


  function render_item($count, $item) {

    return $item['feature'];
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-feature' . ']'] = t('The feature of the item.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-feature' . ']'] = $item['feature'];
  }
}
