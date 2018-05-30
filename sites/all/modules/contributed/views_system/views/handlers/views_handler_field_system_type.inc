<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the type field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_type extends views_handler_field {


  function render($values) {

    return _views_system_get_type_name($values->{$this->field_alias});
  }
}
