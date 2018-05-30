<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the files field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_files extends views_handler_field_prerender_list {


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['files'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['files'] as $file) {
          $this->items[$field][] = array('file' => $file);
        }
      }
    }
  }


  function render_item($count, $item) {

    return $item['file'];
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-file' . ']'] = t('The file of the item.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-file' . ']'] = $item['file'];
  }
}
