<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the Drupal core field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_drupal_core extends views_handler_field_boolean {


  function render($values) {

    $value = _views_system_get_drupal_core($values->{$this->field_alias});

    if (!empty($this->options['not'])) {
      $value = !$value;
    }

    if (isset($this->formats[$this->options['type']])) {
      $output = $value ? $this->formats[$this->options['type']][0] : $this->formats[$this->options['type']][1];
    }
    else {
      $output = $value ? $this->formats['yes-no'][0] : $this->formats['yes-no'][1];
    }

    return $output;
  }
}
