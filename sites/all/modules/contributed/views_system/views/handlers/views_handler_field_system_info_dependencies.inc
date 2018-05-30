<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the dependencies field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_dependencies extends views_handler_field_prerender_list {


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['dependencies'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['dependencies'] as $module) {
          $this->items[$field][] = array('module' => $module);
        }
      }
    }
  }


  function render_item($count, $item) {

    return $item['module'];
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-module' . ']'] = t('The name of the required module.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-module' . ']'] = $item['module'];
  }
}
