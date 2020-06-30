<?php

/**
 * @file
 * jrccties_permissions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function jrccties_permissions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ecas_account_option';
  $strongarm->value = '1';
  $export['ecas_account_option'] = $strongarm;

  return $export;
}
