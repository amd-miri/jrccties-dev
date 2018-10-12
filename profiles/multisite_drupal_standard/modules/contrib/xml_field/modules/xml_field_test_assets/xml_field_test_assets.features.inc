<?php
/**
 * @file
 * xml_field_test_assets.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function xml_field_test_assets_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function xml_field_test_assets_node_info() {
  $items = array(
    'xml_test' => array(
      'name' => t('xml_test'),
      'base' => 'node_content',
      'description' => t('Used only for testing xml_field.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
