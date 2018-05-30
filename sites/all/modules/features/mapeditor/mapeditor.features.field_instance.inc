<?php
/**
 * @file
 * mapeditor.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mapeditor_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-mapeditor_map-body'
  $field_instances['node-mapeditor_map-body'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
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
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_geobundle'
  $field_instances['node-mapeditor_map-mapeditor_geobundle'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select the kind of content that should be included in the map. If there are no options, then <a href="/admin/config/system/mapeditor/settings">configure content types</a> or contact the site administrator',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_geobundle',
    'label' => 'Content to be shown on the map',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_height'
  $field_instances['node-mapeditor_map-mapeditor_height'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => array(
      0 => array(
        'value' => 480,
      ),
    ),
    'deleted' => 0,
    'description' => 'The height in pixels of the map.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_height',
    'label' => 'Height',
    'required' => 1,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_initial_zoom'
  $field_instances['node-mapeditor_map-mapeditor_initial_zoom'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => array(
      0 => array(
        'value' => 4,
      ),
    ),
    'deleted' => 0,
    'description' => 'The starting zoom level when this map is displayed. Restricted by min and max zoom settings. If in doubt, 4 is a good level to start with',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_initial_zoom',
    'label' => 'Initial zoom',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_max_zoom'
  $field_instances['node-mapeditor_map-mapeditor_max_zoom'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => array(
      0 => array(
        'value' => 10,
      ),
    ),
    'deleted' => 0,
    'description' => 'The maximum zoom level allowed. (How close in can you get?). If in doubt, 10 is a good level to start with',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_max_zoom',
    'label' => 'Maximum zoom level',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_min_zoom'
  $field_instances['node-mapeditor_map-mapeditor_min_zoom'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => array(
      0 => array(
        'value' => 2,
      ),
    ),
    'deleted' => 0,
    'description' => 'The minimum zoom level allowed. (How far away can you view from?). If in doubt, 2 is a good level to start with',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_min_zoom',
    'label' => 'Minimum zoom level',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_tile_layer'
  $field_instances['node-mapeditor_map-mapeditor_tile_layer'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => array(
      0 => array(
        'value' => 'osmec',
      ),
    ),
    'deleted' => 0,
    'description' => 'Tile layer for the map',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_tile_layer',
    'label' => 'Tile layer',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Content to be shown on the map');
  t('Height');
  t('Initial zoom');
  t('Maximum zoom level');
  t('Minimum zoom level');
  t('Select the kind of content that should be included in the map. If there are no options, then <a href="/admin/config/system/mapeditor/settings">configure content types</a> or contact the site administrator');
  t('The height in pixels of the map.');
  t('The maximum zoom level allowed. (How close in can you get?). If in doubt, 10 is a good level to start with');
  t('The minimum zoom level allowed. (How far away can you view from?). If in doubt, 2 is a good level to start with');
  t('The starting zoom level when this map is displayed. Restricted by min and max zoom settings. If in doubt, 4 is a good level to start with');
  t('Tile layer');
  t('Tile layer for the map');

  return $field_instances;
}
