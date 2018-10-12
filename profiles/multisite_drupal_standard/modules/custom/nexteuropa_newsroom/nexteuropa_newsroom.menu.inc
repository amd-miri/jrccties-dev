<?php

/**
 * @file
 * Code for the nexteuropa newsroom menu hooks.
 */

/**
 * Implements hook_menu().
 */
function nexteuropa_newsroom_menu() {
  // Configuration page.
  $items['admin/config/content/newsroom'] = [
    'title' => 'Newsroom',
    'description' => 'Configure Newsroom settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => ['nexteuropa_newsroom_admin_settings'],
    'access arguments' => [NEXTEUROPA_NEWSROOM_ADMIN_ACCESS],
    'file' => 'nexteuropa_newsroom.admin.inc',
  ];
  $items['admin/config/content/newsroom/delete'] = [
    'title' => 'Delete existing items',
    'description' => 'Delete items imported by Newsroom connector.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('_nexteuropa_newsroom_delete_items_confirm'),
    'access arguments' => [NEXTEUROPA_NEWSROOM_ADMIN_ACCESS],
    'file' => 'nexteuropa_newsroom.admin.inc',
  ];
  $items['news-redirect'] = [
    'title' => 'Newsroom Item Redirect',
    'page callback' => '_nexteuropa_newsroom_item_redirect',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
  ];
  $items['news-proposal'] = [
    'title' => 'Newsroom item proposal',
    'page callback' => 'drupal_get_form',
    'page arguments' => ['nexteuropa_newsroom_proposal_form'],
    'access arguments' => [NEXTEUROPA_NEWSROOM_PROPOSAL_ACCESS],
  ];
  $items['newsroom-agenda'] = [
    'title' => 'Newsroom Agenda',
    'description' => 'Displays Newsroom items as Agenda',
    'page callback' => '_nexteuropa_newsroom_agenda',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];
  $items['newsletters'] = [
    'title' => 'Newsletters',
    'description' => 'Newsletters service list',
    'page callback' => '_nexteuropa_newsroom_newsletters_page',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];
  $items['newsroom-redirect/%/%'] = [
    'title' => 'Newsroom item redirect',
    'page callback' => '_nexteuropa_newsroom_redirect',
    'page arguments' => [1, 2],
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
  ];
  $items['newsroom-import/%/%'] = [
    'title' => 'Newsroom item import',
    'page callback' => '_nexteuropa_newsroom_import_item',
    'page arguments' => [1, 2],
    'access callback' => '_nexteuropa_newsroom_item_import_access',
    'type' => MENU_CALLBACK,
  ];
  $items['newsroom-delete/%/%'] = [
    'title' => 'Newsroom item delete',
    'page callback' => '_nexteuropa_newsroom_delete_item',
    'page arguments' => [1, 2],
    'access callback' => '_nexteuropa_newsroom_item_import_access',
    'type' => MENU_CALLBACK,
  ];
  $items['newsroom'] = [
    'page callback' => '_nexteuropa_newsroom_page',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];
  $items['newsroom-rss'] = [
    'title' => 'Newsroom RSS feed',
    'description' => 'Newsroom RSS feed',
    'page callback' => '_nexteuropa_newsroom_rss',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];

  return $items;
}
