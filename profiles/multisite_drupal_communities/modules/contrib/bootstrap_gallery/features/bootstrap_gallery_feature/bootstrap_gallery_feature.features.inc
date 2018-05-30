<?php
/**
 * @file
 * bootstrap_gallery_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bootstrap_gallery_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function bootstrap_gallery_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function bootstrap_gallery_feature_node_info() {
  $items = array(
    'gallery_image' => array(
      'name' => t('Bootstrap Gallery: Image'),
      'base' => 'node_content',
      'description' => t('Gallery images will be used with Bootstrap Gallery feature.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
