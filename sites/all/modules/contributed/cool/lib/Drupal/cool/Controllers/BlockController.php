<?php

namespace Drupal\cool\Controllers;

interface BlockController {

  /**
   * Path to be used by hook_info().
   */
  static public function getId();

  /**
   * Passed to hook_block_info().
   */
  static public function getAdminTitle();

  /**
   * Passed to hook_block_info().
   */
  static public function getDefinition();

  /**
   * Passed to hook_block_info().
   */
  static public function getConfiguration();

  /**
   * Passed to hook_block_save().
   */
  static public function saveConfiguration($edit);

  /**
   * Passed to hook_block_view().
   */
  static public function getSubject();

  /**
   * Passed to hook_block_view().
   */
  static public function getContent();
}
