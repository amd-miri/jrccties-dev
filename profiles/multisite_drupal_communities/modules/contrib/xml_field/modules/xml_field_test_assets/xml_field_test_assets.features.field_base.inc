<?php
/**
 * @file
 * xml_field_test_assets.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function xml_field_test_assets_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_xml_no_validation'
  $field_bases['field_xml_no_validation'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_xml_no_validation',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'xml_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'xml_field_xml',
  );

  // Exported field_base: 'field_xml_schema'
  $field_bases['field_xml_schema'] = array(
    'active' => 1,
    'cardinality' => 2,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_xml_schema',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'xml_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'xml_field_xml',
  );

  // Exported field_base: 'field_xml_valid_xml'
  $field_bases['field_xml_valid_xml'] = array(
    'active' => 1,
    'cardinality' => 3,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_xml_valid_xml',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'xml_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'xml_field_xml',
  );

  // Exported field_base: 'field_xml_youtube'
  $field_bases['field_xml_youtube'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_xml_youtube',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'xml_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'xml_field_xml',
  );

  return $field_bases;
}
