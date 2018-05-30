<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the package field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_package extends views_handler_field {


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    return isset($info['package']) ? $info['package'] : '';
  }
}
