<?php

namespace Drupal\cool\Controllers;

interface PageController {

  /**
   * Path to be used by hook_menu().
   */
  static public function getPath();

  /**
   * Passed to hook_menu().
   */
  static public function getDefinition();

  /**
   * Responsible for the page access restriction.
   * This method cannot be called directly from hook_menu, like pageCallback,
   * without the "cool_default_page_access_callback" function, because 
   * "_menu_check_access" checks for function_exists()
   */
  static public function accessCallback();

  /**
   * Responsible for the page construction itself.
   */
  static public function pageCallback();
}
