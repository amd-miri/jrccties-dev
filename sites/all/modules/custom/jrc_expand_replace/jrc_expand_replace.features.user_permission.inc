<?php
/**
 * @file
 * Jrc_pubsy_import.features.user_permission.inc.
 */

/**
 * Implements hook_user_default_permissions().
 */
function jrc_expand_replace_user_default_permissions() {
  $permissions = array();

  $permissions['content administration'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
