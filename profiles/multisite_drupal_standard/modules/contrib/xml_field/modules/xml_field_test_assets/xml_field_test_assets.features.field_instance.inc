<?php
/**
 * @file
 * xml_field_test_assets.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function xml_field_test_assets_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-xml_test-body'
  $field_instances['node-xml_test-body'] = array(
    'bundle' => 'xml_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'fh_common_news' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 31,
    ),
  );

  // Exported field_instance: 'node-xml_test-field_xml_no_validation'
  $field_instances['node-xml_test-field_xml_no_validation'] = array(
    'bundle' => 'xml_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'xml_field',
        'settings' => array(),
        'type' => 'xml_field_safe',
        'weight' => 1,
      ),
      'fh_common_news' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_xml_no_validation',
    'label' => 'xml_no_validation',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
      'validation_callback' => 0,
      'xml_example_collapsed' => 1,
      'xml_example_show' => 1,
      'xml_schema' => '',
      'xml_schema_collapsed' => 1,
      'xml_schema_errors' => 1,
      'xml_schema_show' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'xml_field',
      'settings' => array(),
      'type' => 'xml_field_text',
      'weight' => 41,
    ),
  );

  // Exported field_instance: 'node-xml_test-field_xml_schema'
  $field_instances['node-xml_test-field_xml_schema'] = array(
    'bundle' => 'xml_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'xml_field',
        'settings' => array(),
        'type' => 'xml_field_safe',
        'weight' => 4,
      ),
      'fh_common_news' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_xml_schema',
    'label' => 'xml_schema',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
      'validation_callback' => 'xml_field_is_valid_xml_string',
      'xml_example_collapsed' => 1,
      'xml_example_show' => 1,
      'xml_schema' => '<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" attributeFormDefault="unqualified" elementFormDefault="qualified">
  <xs:element name="test">
    <xs:complexType>
      <xs:simpleContent>
        <xs:extension base="xs:string">
          <xs:attribute type="xs:string" name="name"/>
        </xs:extension>
      </xs:simpleContent>
    </xs:complexType>
  </xs:element>
</xs:schema>',
      'xml_schema_collapsed' => 1,
      'xml_schema_errors' => 1,
      'xml_schema_show' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'xml_field',
      'settings' => array(),
      'type' => 'xml_field_text',
      'weight' => 44,
    ),
  );

  // Exported field_instance: 'node-xml_test-field_xml_valid_xml'
  $field_instances['node-xml_test-field_xml_valid_xml'] = array(
    'bundle' => 'xml_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'xml_field',
        'settings' => array(),
        'type' => 'xml_field_safe',
        'weight' => 2,
      ),
      'fh_common_news' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_xml_valid_xml',
    'label' => 'xml_valid_xml',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
      'validation_callback' => 'xml_field_is_valid_xml_string',
      'xml_example_collapsed' => 1,
      'xml_example_show' => 1,
      'xml_schema' => '',
      'xml_schema_collapsed' => 1,
      'xml_schema_errors' => 1,
      'xml_schema_show' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'xml_field',
      'settings' => array(),
      'type' => 'xml_field_text',
      'weight' => 42,
    ),
  );

  // Exported field_instance: 'node-xml_test-field_xml_youtube'
  $field_instances['node-xml_test-field_xml_youtube'] = array(
    'bundle' => 'xml_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'xml_field',
        'settings' => array(),
        'type' => 'xml_field_safe',
        'weight' => 3,
      ),
      'fh_common_news' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_xml_youtube',
    'label' => 'xml_youtube',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
      'validation_callback' => 'xml_field_youtube_validator',
      'xml_example_collapsed' => 1,
      'xml_example_show' => 1,
      'xml_schema' => '',
      'xml_schema_collapsed' => 1,
      'xml_schema_errors' => 1,
      'xml_schema_show' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'xml_field',
      'settings' => array(),
      'type' => 'xml_field_text',
      'weight' => 43,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('xml_no_validation');
  t('xml_schema');
  t('xml_valid_xml');
  t('xml_youtube');

  return $field_instances;
}
