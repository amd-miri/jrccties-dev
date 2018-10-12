<?php
/**
 * @file
 * freepager_example.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function freepager_example_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function freepager_example_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function freepager_example_node_info() {
  $items = array(
    'news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('An example content type, using sections. Sections are in turn used as an example of how Free pager can be utilized.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
