<?php

/**
 * @file
 * jrccties_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function jrccties_permissions_user_default_roles() {
  $roles = array();

  // Exported role: validated user.
  $roles['validated user'] = (object) array(
    'name' => 'validated user',
    'weight' => 13,
  );

  return $roles;
}
