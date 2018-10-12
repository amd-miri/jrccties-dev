<?php

/**
 * @file
 * API documentation for the jQuery Multi module
 */

 /**
  * @addtogroup hooks
  * @{
  */

 /**
  * Add files to be loaded with jQuery Multi's jQuery library
  * @return
  *   An array of full paths to files that should be loaded with the jqmulti's jQuery library
  *   (paths are relative to Drupal root)
  */
 function hook_jqmulti_files() {
   return array(
    'path/to/file.js',
    'another/full/file/path.js',
   );
 }

 /**
  * Add libraries to be loaded with jQuery Multi's jQuery library.
  * @return
  *   An array of library names, where the name corresponds to the name of a directory
  *   in the sites/all/libraries directory. All and only the .js files in this directory will
  *   be automatically loaded by jQuery Multi.
  */
 function hook_jqmulti_libraries() {
   return array(
    'some_library',
    'another_library',
   );
 }

 /**
  * @} End of "addtogroup hooks".
  */

/**
 * Gets the version of jQuery to load.
 *
 * Modules that rely on jQuery Multi can
 * use this method in their installation procedures to make sure that a
 * satisfactory version of jQuery is present.
 *
 * @param $reset
 *   whether to reset the cached version number. When using this to check for
 *   a required jQuery version, it's a good idea to set this to TRUE
 */
function jqmulti_get_version($reset = FALSE) {
  $libraries = libraries_get_libraries();
  if (isset($libraries['jquery'])) {
    $files = jqmulti_get_library_files('jquery', $reset);
    if ($files) {
      foreach ($files as $file) {
        // Get the file name.
       $version = jqmulti_jquery_version_from_path($file);
       if ($version) {
         cache_set('jqmulti_version', $version);
         return $version;
       }
      }
    }
  }
  return FALSE;
}