<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the PHP field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_php extends views_handler_field {


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    return isset($info['php']) ? $info['php'] : '';
  }
}
