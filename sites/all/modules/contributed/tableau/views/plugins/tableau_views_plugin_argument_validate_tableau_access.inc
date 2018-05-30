<?php

/**
 * @file
 * Contains the Tableau access argument validator plugin.
 */

/**
 * Validate whether user has access to Tableau entity.
 *
 * @ingroup views_argument_validate_plugins
 */
class tableau_views_plugin_argument_validate_tableau_access extends views_plugin_argument_validate {

  function validate_argument($arguments) {
    // Determine entity type
    $this->argument->entity_type = 'tableau_' . substr($this->argument->table, 1, strlen($this->argument->table) - 2);

    // Set argument options
    if (!empty($this->argument->options['break_phrase'])) {
      views_break_phrase_string($arguments, $this->argument);
      $arguments = $this->argument->value;
      $operator = $this->argument->operator;
    }
    else {
      $arguments = array($arguments);
      $operator = 'and';
    }

    $this->argument->entities = array();
    $this->argument->titles = array();
    // Validate available arguments
    foreach ($arguments as $key => $argument) {
      if ($this->_validate_argument($argument)) {
        if ($operator == 'or') {
          // Save the title() handlers some work.
          $this->argument->validated_title = implode(' + ', $this->argument->titles);
          return TRUE;
        }
        unset($arguments[$key]);
      }
    }

    // Save the title() handlers some work.
    $this->argument->validated_title = implode($operator == 'or' ? ' + ' : ', ', $this->argument->titles);

    return $operator == 'and' ? empty($arguments) : TRUE;
  }

  function _validate_argument($argument) {
    // Determine field to query
    if (property_exists($this->argument, 'real_field')) {
      $field = $this->argument->real_field;
    }
    else {
      $field = $this->argument->field;
    }

    // Determine query conditions and load entity
    if ($field == 'id') {
      $function = $this->argument->entity_type . '_load';
      $entity = $function($argument);
    }
    else {
      $function = $this->argument->entity_type . '_load_multiple';
      $entity = $function(FALSE, array($field => $argument));
      $entity = $entity ? reset($entity) : FALSE;
    }

    if ($entity) {
      $this->argument->entities[] = $entity;
      $this->argument->titles[] = tableau_entity_title($entity);
      return tableau_entity_access($entity);
    }

    return FALSE;
  }

}
