<?php

namespace Drupal\cool;

class Loader {

  /**
   * Simplify the API
   * @param string $folder_name
   * @param string $parent_class_name
   * @param boolean $include or not the $parent_class_name as the first item
   * @return array
   */
  static public function mapSubclassesAvailable($folder_name, $parent_class_name, $include = FALSE) {
    self::includeLibClassFilesWithPattern($folder_name);
    $classes = self::getSubclassImplementations($parent_class_name);
    if ($include) {
      array_unshift($classes, $parent_class_name);
    }
    return $classes;
  }

  /**
   * Simplify the API
   * Returns an array with the classes that implements the specified interface
   * @param string $folder_name
   * @param string $interface_name
   * @return array
   */
  static public function mapImplementationsAvailable($folder_name, $interface_name) {
    self::includeLibClassFilesWithPattern($folder_name);
    $classes = self::getInterfaceImplementations($interface_name);
    return $classes;
  }

  /**
   * Returns an array with the classes that extends the specified class
   */
  static public function getSubclassImplementations($parent_class_name) {
    $classes = array();
    foreach (get_declared_classes() as $class_name) {
      $reflection_class = new \ReflectionClass($class_name);
      if ($reflection_class->isSubclassOf($parent_class_name)) {
        $classes[$class_name] = $class_name;
      }
    }
    return $classes;
  }

  /**
   * Returns an array with the classes that implements the specified interface
   */
  static public function getInterfaceImplementations($interface_name) {
    $classes = array();
    foreach (get_declared_classes() as $class_name) {
      $reflection_class = new \ReflectionClass($class_name);
      if (!$reflection_class->isAbstract()) {
        if ($reflection_class->implementsinterface($interface_name)) {
          $classes[$class_name] = $class_name;
        }
      }
    }
    return $classes;
  }

  /**
   * @param string $folder_name
   */
  static private function includeLibClassFilesWithPattern($folder_name) {
    $enabled_modules = module_list();
    foreach ($enabled_modules as $module_name) {
      $module_path = drupal_get_path('module', $module_name);
      // PSR-0 compliant search
      $path = $module_path . '/lib/Drupal/' . $module_name;
      if (is_dir($path)) {
        $folders = self::listFoldersWithPattern($path, $folder_name);
        if (!empty($folders)) {
          foreach ($folders as $folder) {
            foreach (self::listClassesWithinFolder($folder) as $class_name) {
              include_once $class_name;
            }
          }
        }
      }
      // PSR-4 compliant search
      $path = $module_path . '/src';
      if (is_dir($path)) {
        $folders = self::listFoldersWithPattern($path, $folder_name);
        if (!empty($folders)) {
          foreach ($folders as $folder) {
            foreach (self::listClassesWithinFolder($folder) as $class_name) {
              include_once $class_name;
            }
          }
        }
      }
    }
  }

  /**
   * @param string $dir
   * @param string $pattern
   * @return type
   */
  static private function listFoldersWithPattern($dir, $pattern) {
    $folders = array();
    $ffs = scandir($dir);
    foreach ($ffs as $ff) {
      if ($ff != '.' && $ff != '..') {
        $full_path = $dir . '/' . $ff;
        if (is_dir($full_path)) {
          if (preg_match('/' . $pattern . '/', $full_path)) {
            $folders[] = $full_path;
          }
          else {
            $folders = array_merge($folders, self::listFoldersWithPattern($full_path, $pattern));
          }
        }
      }
    }
    return $folders;
  }

  /**
   * @param string $dir
   * @return array
   */
  static private function listClassesWithinFolder($dir) {
    $classes = array();
    $ffs = scandir($dir);
    foreach ($ffs as $ff) {
      if ($ff != '.' && $ff != '..') {
        $classes[] = $dir . '/' . $ff;
      }
    }
    return $classes;
  }

}
