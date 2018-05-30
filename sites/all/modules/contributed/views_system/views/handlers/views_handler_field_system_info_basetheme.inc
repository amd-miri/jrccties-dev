<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the base theme field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_basetheme extends views_handler_field {


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    return isset($info['base theme']) ? $info['base theme'] : '';
  }
}
