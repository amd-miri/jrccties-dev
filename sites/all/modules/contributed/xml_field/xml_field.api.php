<?php
/**
 * @file
 * API Description
 *
 * @ingroup xml_field
 * @{
 */

/**
 * Implements hook_xml_field_files().
 *
 * Be aware that if two modules are calling defaults for the same nid, the
   module with the heigher weight in the system table wins.
 *
 * @return array
 *   The array is keyed by nid. Each value is an array that mimics the field
     array structure of the node, e.g.
     $defaults[{nid}][{fieldname}]['und'][0]['xml'] = {default xml}
 */
function hook_xml_field_defaults() {
  $defaults = array();
  $defaults[3]['field_xml_metadata']['und'][0]['xml'] = "<page><button>Go to Home</button></page>";
  return $defaults;
}

/** @} */ //end of groupxml_field xml_field
