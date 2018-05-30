<?php

namespace Drupal\like_and_dislike\Controllers\PageControllers;

/**
 * @file
 * Management configuration page
 */
class ModuleConfig implements \Drupal\cool\Controllers\PageController {

  public static function getPath() {
    return 'admin/config/like_and_dislike';
  }

  public static function accessCallback() {
    return user_access('manage like dislike');
  }

  public static function getDefinition() {
    return array(
      'title' => t('Like & Dislike'),
      'description' => t('Management options for the like and dislike buttons.'),
    );
  }

  public static function pageCallback() {
    return \Drupal\like_and_dislike\Controllers\FormControllers\ModuleConfig::getForm();
  }

}
