<?php
/**
 * @file
 * jrc_pending_drafts_import.features.user_permission.inc.
 */

/**
 * Implements hook_user_default_permissions().
 */
function jrc_pending_drafts_import_user_default_permissions() {
  $permissions = array();

  $permissions['advanced migration information'] = array(
    'name' => 'advanced migration information',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'migrate',
  );

  $permissions['migration information'] = array(
    'name' => 'migration information',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'migrate',
  );

  return $permissions;
}
