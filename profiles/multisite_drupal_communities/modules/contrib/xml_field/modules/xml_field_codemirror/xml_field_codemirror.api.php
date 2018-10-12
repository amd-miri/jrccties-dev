<?php
/**
 * @file
 * API documentation for xml_field_codemirror module.
 *
 * @addtogroup hooks
 * @{
 */

/**
 * Implements hook_xml_field_codemirror_defaults_alter().
 *
 * Allow modules to alter the codemirror configuration option defaults. Note
   that field instance options (set in the UI) take precendence over any values
   here; these are just global defaults. This allows for modifications to all
   CodeMirror options though, most of which are not accessible in the UI.
 *
 * @param array &$config
 *
 * @return NULL
 *
 * @see http://codemirror.net/doc/manual.html
 * @see hook_xml_field_codemirror_config_alter()
 */
function hook_xml_field_codemirror_defaults_alter(&$config) {
  // Set the global default to be 'cobalt' instead of 'default'
  $config['theme'] = 'cobalt';
  $config['lineNumbers'] = FALSE;
}

/** @} */ //end of group hooks
