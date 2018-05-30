<?php

/**
 * @file
 * Contains forms for the Single profile tools module.
 */

/**
 * Constructs Mapeditor settings form.
 */
function mapeditor_settings() {
  $form = array();
  $form['warning']['#markup'] = t('Warning. At this moment this can only be used to create fields on the destination entity.');

  $form['webtools_environment'] = array(
    '#type' => 'textfield',
    '#title' => t('Webtools environment'),
    '#default_value' => variable_get('webtools_environment', MAPEDITOR_WEBTOOLS_ENVIRONMENT),
    '#description' => t('Webtools environment from where to use the load.js library'),
    '#size' => '60',
  );

  $geofields = variable_get('geofields', 'field_location, location');
  $form['geofields'] = array(
    '#type' => 'textarea',
    '#title' => t('Geo fields'),
    '#default_value' => $geofields,
    '#description' => t('Comma separated list fields that can hold geo data. Bundles that have any of the listed fields will be available in the entity checkboxes list.'),
  );

  $geobundles = mapeditor_geo_bundles(array_map('trim', explode(',', $geofields)));

  // Excludes the Map content type to prevent confusion.
  if (array_key_exists('node__mapeditor_map', $geobundles)) {
    unset($geobundles['node__mapeditor_map']);
  }
  if ($geobundles) {
    $form['geobundles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Bundles'),
      '#options' => $geobundles,
      '#default_value' => variable_get('geobundles', array()),
      '#description' => t('Choose which bundles are available for creating maps'),
    );

    // Iterates through chosen geo bundles to find taxo term fields.
    // $taxonomy_term_fields_options = array();
    if (variable_get('geobundles')) {
      foreach (variable_get('geobundles') as $geobundle) {
        if ($geobundle !== 0) {
          $geobundle_shraps = explode('__', $geobundle);
          $fields = field_info_instances($geobundle_shraps[0], $geobundle_shraps[1]);
          foreach ($fields as $field) {
            $field_info = field_info_field($field['field_name']);
            if ($field_info['type'] == 'taxonomy_term_reference') {
              $taxonomy_term_fields_options[$field['field_name']] = $field['label'];
            }
          }
        }
      }
    }

    if (isset($taxonomy_term_fields_options)) {

      // Removes nuts_regions to prevent confusion.
      if (array_key_exists('nuts_region', $taxonomy_term_fields_options)) {
        unset($taxonomy_term_fields_options['nuts_region']);
      }
      $form['taxonomy_term_fields_map'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Taxonomy vocabularies'),
        '#options' => $taxonomy_term_fields_options,
        '#default_value' => variable_get('taxonomy_term_fields_map', array()),
        '#description' => t('Choose which vocabularies are available for generating maps'),
      );
    }
    else {
      $form['taxonomy_term_fields_map']['#markup'] = t('Select a node type first that has taxo terms.');
    }
  }
  else {
    $form['notice']['#prefix'] = '<p>';
    $form['notice']['#markup'] = t('There are no bundles available.');
    $form['notice']['#suffix'] = '</p>';
  }

  $form['#submit'][] = 'mapeditor_settings_submit';
  return system_settings_form($form);
}

/**
 * Provides custom submit functionality for the settings form.
 *
 * Creates fields on the map node type.
 * // @todo : delete fields.
 */
function mapeditor_settings_submit($form, &$form_state) {

  if (isset($form_state['values']['taxonomy_term_fields_map'])) {
    // Fetches selected taxonomy terms.
    foreach ($form_state['values']['taxonomy_term_fields_map'] as $key => $term) {
      if ($term !== 0) {

        // Fetches field information to construct fields for the map node.
        $field = field_info_field($term);

        // Flattens a multivalue bundle list in order to fetch values from first
        // item.
        reset($field['bundles']);
        $first_bundle = key($field['bundles']);
        $field_instance = field_info_instance($first_bundle, $term, $field['bundles'][$first_bundle][0]);

        // Skips if the field instance already exists on map node type.
        if ($instance = field_info_instance('node', $key, 'mapeditor_map')) {
          continue;
        }

        // Deletes already existing fields.
        // @todo: futher develop
        // if ($term == NULL) {
        // $instance = field_info_instance('node', $key, 'mapeditor_map');
        // field_delete_instance($instance);
        // }

        // Defines field instance.
        $t = get_t();
        $field_instance = array(
          'field_name' => $key,
          'label' => $field_instance['label'],
          'widget' => array(
            'active' => 1,
            'module' => 'options',
            'settings' => array(),
            'type' => 'options_select',
          ),
          'display' => array(
            'default' => array(
              'label' => 'above',
              'module' => 'taxonomy',
              'settings' => array(),
              'type' => 'taxonomy_term_reference_link',
            ),
          ),
          'entity_type' => 'node',
          'bundle' => 'mapeditor_map',
        );
        field_create_instance($field_instance);
      }
    }
  }
}

/**
 * Provides list of bundles that have geographical field attached to it.
 */
function mapeditor_geo_bundles($geofields) {
  $bundles = array();
  foreach ($geofields as $geofield) {
    $field = field_info_field($geofield);
    if ($field['bundles']) {
      foreach ($field['bundles'] as $entname => $ent) {
        foreach ($ent as $bundle) {
          $key = $entname . '__' . $bundle;
          $field_info = field_info_bundles($entname);
          $bundles[$key] = "{$field_info[$bundle]['label']} ({$entname})";
        }
      }
    }
  }
  return $bundles;
}
