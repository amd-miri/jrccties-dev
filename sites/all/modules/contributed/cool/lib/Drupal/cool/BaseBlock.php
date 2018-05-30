<?php

namespace Drupal\cool;

abstract class BaseBlock implements Controllers\BlockController {

  abstract static public function getId();

  abstract static public function getAdminTitle();

  static public function getDefinition() {
    return array();
  }

  static public function getConfiguration() {
    return array();
  }

  static public function saveConfiguration($edit) {
    
  }

  static public function getSubject() {
    return '';
  }

  abstract static public function getContent();

}
