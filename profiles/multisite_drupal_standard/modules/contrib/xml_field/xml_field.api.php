<?php
/**
 * @file
 * API Description
 *
 * @ingroup xml_field
 * @{
 */

/**
 * Register XML Field API information.
 *
 * This is required for your module to have its include files loaded
 *
 * @return
 *   An array with the following possible keys:
 *   - api: (required) The version of the Views API the module implements.
 *   - path: (required) Where the default and schema files are saved.
 */
function hook_xml_field_api() {
  return array(
    'api' => 1,
    'path' => drupal_get_path('module', 'example') . '/includes/xml_field',
  );
}

/**
 * DEPRECATED!!! SEE /help/xml_field/using_files FOR MORE INFO
 *
 * Implements hook_xml_field_defaults().
 *
 * Be aware that if two modules are calling defaults for the same nid, the
 * module with the heigher weight in the system table wins.
 *
 * @return array
 *   The array is keyed by nid. Each value is an array that mimics the field
 *   array structure of the node, e.g.
 *   $defaults[{nid}][{fieldname}]['und'][0]['xml'] = {default xml}
 */
function hook_xml_field_defaults() {
  $defaults = array();
  $defaults[3]['field_xml_metadata']['und'][0]['xml'] = "<page><button>Go to Home</button></page>";

  return $defaults;
}

/**
 * Implements hook_xml_field_validation_callbacks_alter().
 *
 * The callback will receive these args: $xml, $instance, &$message, &$args
 * - $xml string The XML that is being validated
 * - $instance array The field instance
 * - $message string Allows function to apply an error message to the test if
 * needed. This will be passed through t() and should contain %title or @title
 * - $args array These args will be used with $message and t(); both @title and
 * %title will be populated upon receipt
 *
 * The callback should return bool depending on validation
 */
function hook_xml_field_validation_callbacks_alter(&$callbacks) {
  $callbacks['my_module_xml_validator'] = array(
    'callback' => 'my_module_xml_validator',
    'title' => t('A superior xml validator'),
  );
}

/**
 * Allow modules to set which enties/fields have/are xml_fields.
 *
 * This can be used for automated testing if needed to set up a field
 * as being an xml_field rather than having to include the field definition
 * or node in a test feature module.  To do this add a snippet like the
 * following to the top of your module's test file; making sure your module
 * doesn't ACTUALLY implement this hook (if it does you will need a test-only
 * module to implement this hook then.)
 *
 * @code
 *   function my_module_xml_field_xml_fields_alter(&$entities, &$field_list) {
 *     $field_list['field_xml_metadata'] = array();
 *   }
 * @endcode
 *
 * @param array &$entities
 * @param array &$field_list
 *
 * @see xml_field_xml_fields() for formatting.
 */
function hook_xml_field_xml_fields_alter(&$entities, &$field_list) {
  
  // You do not have to include a field definition, it will be loaded
  // for you if it's a valid field.
  $field_list['field_xml_metadata'] = array();

  // NOTE: BETA FEATURE.
  // You can also create non-fields that contain xml on a node, so long as you
  // register the node key here, like the following; the value of the xml should
  // still follow the format of a field, e.g., ['und']['0']['xml'].
  $field_list['my_xml_non_field'] = array();
}
