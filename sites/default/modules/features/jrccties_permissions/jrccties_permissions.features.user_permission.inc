<?php

/**
 * @file
 * jrccties_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function jrccties_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'media',
  );

  // Exported permission: 'access own broken links report'.
  $permissions['access own broken links report'] = array(
    'name' => 'access own broken links report',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'linkchecker',
  );

  // Exported permission: 'access send by email'.
  $permissions['access send by email'] = array(
    'name' => 'access send by email',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'print_mail',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'user',
  );

  // Exported permission: 'add media from remote sources'.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'media_internet',
  );

  // Exported permission: 'administer menu attributes'.
  $permissions['administer menu attributes'] = array(
    'name' => 'administer menu attributes',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'menu_attributes',
  );

  // Exported permission: 'change newsletter subscription'.
  $permissions['change newsletter subscription'] = array(
    'name' => 'change newsletter subscription',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'jrccties_core',
  );

  // Exported permission: 'create advpoll content'.
  $permissions['create advpoll content'] = array(
    'name' => 'create advpoll content',
    'roles' => array(
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create files'.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own advpoll content'.
  $permissions['delete own advpoll content'] = array(
    'name' => 'delete own advpoll content',
    'roles' => array(
      'validated user' => 'validated user',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own audio files'.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own document files'.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own video files'.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete privatemsg'.
  $permissions['delete privatemsg'] = array(
    'name' => 'delete privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'edit mimemail user settings'.
  $permissions['edit mimemail user settings'] = array(
    'name' => 'edit mimemail user settings',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'mimemail',
  );

  // Exported permission: 'edit own advpoll content'.
  $permissions['edit own advpoll content'] = array(
    'name' => 'edit own advpoll content',
    'roles' => array(
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own audio files'.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own document files'.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own video files'.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit webform components'.
  $permissions['edit webform components'] = array(
    'name' => 'edit webform components',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'filter private messages'.
  $permissions['filter private messages'] = array(
    'name' => 'filter private messages',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg_filter',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'comment',
  );

  // Exported permission: 're convert video'.
  $permissions['re convert video'] = array(
    'name' => 're convert video',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'video',
  );

  // Exported permission: 'read privatemsg'.
  $permissions['read privatemsg'] = array(
    'name' => 'read privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'reply only privatemsg'.
  $permissions['reply only privatemsg'] = array(
    'name' => 'reply only privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'select text format for privatemsg'.
  $permissions['select text format for privatemsg'] = array(
    'name' => 'select text format for privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'show format selection for comment'.
  $permissions['show format selection for comment'] = array(
    'name' => 'show format selection for comment',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for node'.
  $permissions['show format selection for node'] = array(
    'name' => 'show format selection for node',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'comment moderator' => 'comment moderator',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'use media wysiwyg'.
  $permissions['use media wysiwyg'] = array(
    'name' => 'use media wysiwyg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'media_wysiwyg',
  );

  // Exported permission: 'use text format basic_html'.
  $permissions['use text format basic_html'] = array(
    'name' => 'use text format basic_html',
    'roles' => array(
      'PIWIK administrator' => 'PIWIK administrator',
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'comment moderator' => 'comment moderator',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'group creator' => 'group creator',
      'system uncomplete profile' => 'system uncomplete profile',
      'temp admin' => 'temp admin',
      'webform manager' => 'webform manager',
      'webmaster' => 'webmaster',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'PIWIK administrator' => 'PIWIK administrator',
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'comment moderator' => 'comment moderator',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'group creator' => 'group creator',
      'system uncomplete profile' => 'system uncomplete profile',
      'temp admin' => 'temp admin',
      'webform manager' => 'webform manager',
      'webmaster' => 'webmaster',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'PIWIK administrator' => 'PIWIK administrator',
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'comment moderator' => 'comment moderator',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'group creator' => 'group creator',
      'system uncomplete profile' => 'system uncomplete profile',
      'temp admin' => 'temp admin',
      'webform manager' => 'webform manager',
      'webmaster' => 'webmaster',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use token insert'.
  $permissions['use token insert'] = array(
    'name' => 'use token insert',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'token_insert',
  );

  // Exported permission: 'view own files'.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own private files'.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view private files'.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'editor' => 'editor',
      'temp admin' => 'temp admin',
      'webmaster' => 'webmaster',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'vote on polls'.
  $permissions['vote on polls'] = array(
    'name' => 'vote on polls',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'advpoll',
  );

  // Exported permission: 'write privatemsg'.
  $permissions['write privatemsg'] = array(
    'name' => 'write privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'validated user' => 'validated user',
      'temp admin' => 'temp admin',
    ),
    'module' => 'privatemsg',
  );

  return $permissions;
}
