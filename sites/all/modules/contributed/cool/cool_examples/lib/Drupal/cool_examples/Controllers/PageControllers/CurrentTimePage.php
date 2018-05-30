<?php

namespace Drupal\cool_examples\Controllers\PageControllers;

class CurrentTimePage implements \Drupal\cool\Controllers\PageController {

  /**
   * Path to be used by hook_menu().
   */
  static public function getPath() {
    return 'current-time';
  }

  /**
   * Passed to hook_menu()
   */
  static public function getDefinition() {
    return array(
      'title' => 'Current time'
    );
  }

  public static function accessCallback() {
    return TRUE;
  }

  public static function pageCallback() {
    return \Drupal\cool_examples\Controllers\FormControllers\FormCurrentTime::getForm();
  }

}
