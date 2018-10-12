////////////////////////////////////////////
//
//  jQuery Multi
//
////////////////////////////////////////////

-- SUMMARY --

Need to use a higher version of jQuery for your module or theme than the one provided by Drupal/jQuery Update?

jQuery Multi allows you to load an extra version of the jQuery library in parallel to Drupal's version, without
conflicting with Drupal's version. You can then choose any JavaScript library or files to use the new version
of jQuery. No need to alter packaged jQuery plugins!

-- INSTALLATION --

  1. Place a version of the minified jQuery library in the libraries folder, so that
     the path to the actual jQuery library will be: sites/all/libraries/jquery/jquery-<version>.min.js
  2. Download and install jQuery Multi in the usual fashion.

-- USAGE --

  1. Enable the module.
  2. Navigate to the settings page at admin/config/settings/jqmulti.
  3. Ensure that your jQuery library has been detected.

  4. To "target" any existing JS code to the jqmulti jQuery you have the following options:

     NOTE: Targeting files to jQuery Multi using any of these methods will not actually load the JS files on
           any pages. To load the files, use any existing Drupal method (e.g. drupal_load_js(), a .info file, etc).
           Once the files are loaded, they will automatically use the newer jQuery.

           Alternatively, you can select the "Always load libraries assigned to this version of jQuery" option. This
           will cause libraries targeted with option A or B to load on every page.

    A) Put the JS in sites/all/libraries/ and use the jQuery Multi UI to select your library.
       Whenever this library's file are loaded, they will automatically use the jqmulti jQuery version.
       This is ideal if you're using a prepackaged jQuery library or plugin.
    B) Put the JS in sites/all/libraries/ and use hook_jqmulti_libraries() to target the library (see jqmulti.api.php).
       This is ideal if you're using a prepackaged jQuery library or plugin, and is equivalent to method A.
    C) Put the JS anywhere (e.g. module, theme, library), and use hook_jqmulti_files() to target it (see jqmulti.api.php).
    D) Put the JS anywhere (e.g. module, theme, library), and use the provided alias to taget it. To do this, load
       the JS with drupal_add_js() or any other metho. If you're only using this method, make sure to select
       the 'Always load jQuery' checkbox in the jQuery Multi config.

        To use the provided jQuery alias in your custom scripts, reference
        the alias in your script closure. The alias name is generated using
        the jQuery version number, with the periods removed.

        For instance, if you're loading jQuery-1.7.1, the alias will be jq171, and you can
        use it in your scripts by wrapping your code as follows:

          (function($){
            // your code here, using jQuery 1.7.1
          })(jq171)

  NOTE: All jQuery targeted to use jQuery Multi (using methods A, B, or C above) must properly use a
        closure around the jQuery code, as is best practice for all Drupal jQuery code, i.e.:

            (function($){
              // your code here, using jQuery 1.7.1
            })(jQuery)

