<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the regions hidden field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_regions_hidden extends views_handler_field_prerender_list {


  function pre_render($values) {

    foreach ($values as $value) {

      $info = unserialize($value->{$this->field_alias});

      if (isset($info['regions_hidden'])) {

        $field = $value->{$this->field_alias};
        $this->items[$field] = array();
        foreach ($info['regions_hidden'] as $region_hidden) {
          $this->items[$field][] = array('region_hidden' => $region_hidden);
        }
      }
    }
  }


  function render_item($count, $item) {

    return $item['region_hidden'];
  }


  function document_self_tokens(&$tokens) {

    $tokens['[' . $this->options['id'] . '-region_hidden' . ']'] = t('The hidden region of the theme.');
  }


  function add_self_tokens(&$tokens, $item) {

    $tokens['[' . $this->options['id'] . '-region_hidden' . ']'] = $item['region_hidden'];
  }
}
