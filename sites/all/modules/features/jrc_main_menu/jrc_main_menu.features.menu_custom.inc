<?php
/**
 * @file
 * jrc_main_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function jrc_main_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['jrc-main-menu'] = array(
    'menu_name' => 'jrc-main-menu',
    'title' => 'JRC Main menu',
    'description' => 'This is the <em>JRC Science Hub Main Menu</em>.',
    'language' => 'und',
  );

  return $menus;
}
