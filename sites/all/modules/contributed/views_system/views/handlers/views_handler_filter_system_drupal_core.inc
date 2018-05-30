<?php

/**
 * @file
 * Views filter handler for the views_system module.
 */


/**
 * Provides Drupal core filter for the system item.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_system_drupal_core extends views_handler_filter_boolean_operator {


  function query() {

    $this->ensure_my_table();

    $field = "$this->table_alias.$this->real_field";
    $operator = empty($this->value) ? 'NOT IN' : 'IN';

    $this->query->add_where($this->options['group'], $field, array_keys(_views_system_get_drupal_core()), $operator);
  }
}
