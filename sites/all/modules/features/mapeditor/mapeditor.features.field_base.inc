<?php
/**
 * @file
 * mapeditor.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mapeditor_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'mapeditor_geobundle'
  $field_bases['mapeditor_geobundle'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_geobundle',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'mapeditor_geobundles',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'mapeditor_height'
  $field_bases['mapeditor_height'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_height',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'mapeditor_initial_zoom'
  $field_bases['mapeditor_initial_zoom'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_initial_zoom',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'mapeditor_zoom_options',
    ),
    'translatable' => 0,
    'type' => 'list_integer',
  );

  // Exported field_base: 'mapeditor_max_zoom'
  $field_bases['mapeditor_max_zoom'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_max_zoom',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'mapeditor_zoom_options',
    ),
    'translatable' => 0,
    'type' => 'list_integer',
  );

  // Exported field_base: 'mapeditor_min_zoom'
  $field_bases['mapeditor_min_zoom'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_min_zoom',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'mapeditor_zoom_options',
    ),
    'translatable' => 0,
    'type' => 'list_integer',
  );

  // Exported field_base: 'mapeditor_tile_layer'
  $field_bases['mapeditor_tile_layer'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_tile_layer',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'mapeditor_tiles',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
