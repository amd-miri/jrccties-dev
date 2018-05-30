<?php

/**
 * @file
 * Mapeditor field formatter functions.
 */

/**
 * Implements hook_field_formatter_info().
 */
function mapeditor_field_formatter_info() {
  $formatters = array();

  if (module_exists('geofield')) {
    $formatters['geofield_leaflet_mapeditor'] = array(
      'label' => t('EC map service map'),
      'field types' => array('geofield'),
      'settings' => array(
        'leaflet_map' => '',
        'height' => 400,
      ),
    );
  }

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function mapeditor_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $entity_type = $instance['entity_type'];

  $element = array();

  if ($display['type'] == 'geofield_leaflet_mapeditor') {

    $element['leaflet_map'] = array(
      '#title' => t('Leaflet Map'),
      '#type' => 'select',
      '#options' => mapeditor_tiles(),
      '#default_value' => $settings['leaflet_map'],
      '#required' => TRUE,
    );

    $element['height'] = array(
      '#title' => t('Map Height'),
      '#type' => 'textfield',
      '#default_value' => $settings['height'],
      '#field_suffix' => t('px'),
      '#element_validate' => array('element_validate_integer_positive'),
    );
  }
  return $element;
}

/**
 * Validation callback for icon urls.
 *
 * function leaflet_icon_validate($element, &$form_state, $form) {
 * if (!empty($element['#value']) && !valid_url($element['#value'])) {
 * form_error($element, t('Icon URL is invalid'));
 * }
 * }
 *
 * /**
 * Implements hook_field_formatter_settings_summary().
 */
function mapeditor_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == 'geofield_leaflet_mapeditor') {
    $summary = t('Leaflet map: @height px, @map', array(
      '@height' => $settings['height'],
      '@map' => $settings['leaflet_map'],
    ));
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function mapeditor_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $field_settings = $display['settings'];
  $other_settings = array(
    'dragging' => FALSE,
  );
  $settings = array_merge($field_settings, $other_settings);

  if (count($items) == 0) {
    return '';
  }
  else {
    switch ($display['type']) {
      case 'geofield_leaflet_mapeditor':

        // $map = mapeditor_map_info()[$settings['leaflet_map']];
        $map = array();
        $features = array();
        foreach ($items as $item) {
          $features[] = array(
            'type' => 'Feature',
            'properties' => array(),
            'geometry' => array(
              'type' => mapeditor_geojson_type($item['geo_type']),
              'coordinates' => array(

                // Sets coordinates in GeoJSON standard: X,Y (lon, lat).
                round($item['lon'], 4),
                round($item['lat'], 4),
              ),
            ),
          );
        }

        // Sets initial map center to first point. Needs to revert lon & lat.
        $map['settings']['center'] = array_reverse($features[0]['geometry']['coordinates']);

        // Sets initial zoom level.
        $map['settings']['zoom'] = 8;
        $map['settings']['height'] = $settings['height'];
        $map['settings']['map'] = $settings['leaflet_map'];
        $element[0] = mapeditor_build_map($map, $features, $settings);
        break;
    }

    return $element;
  }
}

/**
 * Converts a geofield into an array of map points.
 *
 * @param array $items
 *   A collection of geofield values.
 *
 * @return array
 *   Points built for consumption by the leaflet module as expected by
 * leaflet_render_map().
 */
function mapeditor_process_geofield($items = array()) {
  $data = array();

  // geophp_load();
  // @todo: check what this does.

  foreach ($items as $delta => $item) {
    $datum = array('type' => $item['geo_type']);
    switch ($item['geo_type']) {
      case 'point':
        $datum += array(
          'lat' => (float) $item['lat'],
          'lon' => (float) $item['lon'],
        );
        $data[] = $datum;
        break;

    }
  }
  return $data;
}

/**
 * Helper function to standardize forms between field formatters and others.
 *
 * $group - String
 *  The name of the group element to generate.
 *
 * $settings - Array
 *  Current form settings (for defaults, etc)
 *
 * $options - Array
 *  Special options needed for this form element, if necessary.
 *
 * Return - A fully loaded form element.
 */
function mapeditor_form_elements($group, $settings, $options = NULL) {
  $form_element = NULL;
  switch ($group) {
    case 'popup':
      $form_element = array(
        '#title' => t('Popup Settings'),
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['show'] = array(
        '#title' => t('Popup'),
        '#description' => t('Show a popup when locations are clicked.'),
        '#type' => 'checkbox',
        '#default_value' => $settings[$group]['show'],
      );
      $form_element['text'] = array(
        '#title' => t('Popup text'),
        '#description' => t('Enter the text for the popup. Tokens are supported.'),
        '#type' => 'textfield',
        '#default_value' => $settings[$group]['text'],
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[popup][show]"]' => array('checked' => TRUE),
          ),
        ),
      );
      break;

    case 'zoom':
      // Define zoom options.
      $zoom_options = array(
        -1 => t('Use map defined setting'),
        0 => t('0 - Low/Far'),
        18 => t('18 - High/Close'),
      );
      for ($i = 1; $i < 18; $i++) {
        $zoom_options[$i] = $i;
      }
      ksort($zoom_options);

      $form_element = array(
        '#title' => t('Zoom Settings'),
        '#description' => t("These settings will override the zoom settings defined in the map definition. Low values are 'zoomed out', high values are 'zoomed in'."),
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['initialZoom'] = array(
        '#title' => t('Initial zoom level'),
        '#description' => t('The starting zoom level when this map is rendered.  Restricted by min and max zoom settings.'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['initialZoom']) ? $settings[$group]['initialZoom'] : -1,
        '#element_validate' => array('leaflet_initial_zoom_validate'),
      );
      $form_element['minZoom'] = array(
        '#title' => t('Minimum zoom level'),
        '#description' => t('The minimum zoom level allowed. (How far away can you view from?)'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['minZoom']) ? $settings[$group]['minZoom'] : -1,
        '#element_validate' => array('leaflet_min_zoom_validate'),
      );
      $form_element['maxZoom'] = array(
        '#title' => t('Maximum zoom level'),
        '#description' => t('The maximum zoom level allowed. (How close in can you get?).'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['maxZoom']) ? $settings[$group]['maxZoom'] : -1,
        '#element_validate' => array('leaflet_max_zoom_validate'),
      );
      break;

    case 'icon':
      $form_element = array(
        '#title' => t('Point Icon'),
        '#description' => t('These settings will overwrite the icon settings defined in the map definition.'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['iconType'] = array(
        '#type' => 'radios',
        '#title' => t('Icon Source'),
        '#default_value' => isset($settings[$group]['iconType']) ? $settings[$group]['iconType'] : 'marker',
        '#options' => array(
          'marker' => "Icon File",
          'html' => "Field (html DivIcon)",
        ),
      );
      $form_element['iconUrl'] = array(
        '#title' => t('Icon URL'),
        '#description' => t('Can be an absolute or relative URL.'),
        '#type' => 'textfield',
        '#maxlength' => 999,
        '#default_value' => isset($settings[$group]['iconUrl']) ? $settings[$group]['iconUrl'] : '',
        '#element_validate' => array('leaflet_icon_validate'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['shadowUrl'] = array(
        '#title' => t('Icon Shadow URL'),
        '#description' => t('Can be an absolute or relative URL.'),
        '#type' => 'textfield',
        '#maxlength' => 999,
        '#default_value' => isset($settings[$group]['shadowUrl']) ? $settings[$group]['shadowUrl'] : '',
        '#element_validate' => array('leaflet_icon_validate'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['html'] = array(
        '#type' => 'select',
        '#title' => t('Marker field'),
        '#description' => t('Field to use as output for a map marker.'),
        '#options' => array_merge(array('' => ''), $options['fields']),
        '#default_value' => isset($settings[$group]['html']) ? $settings[$group]['html'] : '',
        '#empty_option' => t('-- Select --'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
          'required' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['iconImageStyle'] = array(
        '#title' => t('Icon image style'),
        '#type' => 'select',
        '#default_value' => isset($settings[$group]['iconImageStyle']) ? $settings[$group]['iconImageStyle'] : '',
        '#empty_option' => t('None (original image)'),
        '#options' => image_style_options(FALSE, PASS_THROUGH),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['htmlClass'] = array(
        '#type' => 'textfield',
        '#title' => t('Marker HTML class'),
        '#description' => t('Required class name for the div used to wrap field output. For multiple classes, separate with a space.'),
        '#default_value' => isset($settings[$group]['htmlClass']) ? $settings[$group]['htmlClass'] : 'leaflet_map_icon',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
          'required' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['iconSize'] = array(
        '#title' => t('Icon Size'),
        '#description' => "It is usually preferable to leave this blank and use the image style system to size the icons. Sizes are in pixels.",
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
      );
      $form_element['iconSize']['x'] = array(
        '#title' => t('Width'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconSize']['x']) ? $settings[$group]['iconSize']['x'] : '',
        '#element_validate' => array('element_validate_integer_positive'),
      );
      $form_element['iconSize']['y'] = array(
        '#title' => t('Height'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconSize']['y']) ? $settings[$group]['iconSize']['y'] : '',
        '#element_validate' => array('element_validate_integer_positive'),
      );
      $form_element['iconAnchor'] = array(
        '#title' => t('Icon Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t("The coordinates of the 'tip' of the icon (relative to its top left corner). The icon will be aligned so that this point is at the marker's geographical location."),
      );
      $form_element['iconAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconAnchor']['x']) ? $settings[$group]['iconAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['iconAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconAnchor']['y']) ? $settings[$group]['iconAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['shadowAnchor'] = array(
        '#title' => t('Shadow Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t('The point from which the shadow is shown.'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['shadowAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['shadowAnchor']['x']) ? $settings[$group]['shadowAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['shadowAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['shadowAnchor']['y']) ? $settings[$group]['shadowAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['popupAnchor'] = array(
        '#title' => t('Popup Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t('The point from which the marker popup opens, relative to the anchor point.'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['popupAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['popupAnchor']['x']) ? $settings[$group]['popupAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['popupAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['popupAnchor']['y']) ? $settings[$group]['popupAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );

      break;

    case "vector_display":
      $form_element = array(
        '#title' => t('Vector Display Options'),
        '#description' => t('These settings will overwrite the !options and constants shared between vector overlays (Polygon, Polyline, Circle).', array('!options' => l(t("default options"), 'http://leafletjs.com/reference.html#path'))),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['stroke_override'] = array(
        '#title' => t('Override Defaults'),
        '#description' => t('If checked, the default values will be overridden by these settings.'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['stroke_override']) ? $settings[$group]['stroke_override'] : 1,
      );
      $form_element['stroke'] = array(
        '#title' => t('Stroke'),
        '#description' => t('Draw an outline around the shape. Uncheck to disable borders on polygons and circles. (Default: True)'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['stroke']) ? $settings[$group]['stroke'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['color'] = array(
        '#title' => t('Line Color'),
        '#description' => t('Line color. (Default: #00030f)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['color']) ? $settings[$group]['color'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['weight'] = array(
        '#title' => t('Line Weight'),
        '#description' => t('Line width in pixels. (Default: 5)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['weight']) ? $settings[$group]['weight'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['opacity'] = array(
        '#title' => t('Line Opacity'),
        '#description' => t('Line opacity. A number between 0 (would make the line invisible) to 1 (no transparency at all). (Default: 0.5)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['opacity']) ? $settings[$group]['opacity'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['dashArray'] = array(
        '#title' => t('Line Dash Pattern'),
        '#description' => t("A string that defines the line's !url. Depending on your line weight, this can be hard to see. Note that this is ignored by canvas-powered layers (e.g. Android 2). Sample: 5, 5", array('!url' => l(t('dash pattern'), 'https://developer.mozilla.org/en/SVG/Attribute/stroke-dasharray'))),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['dashArray']) ? $settings[$group]['dashArray'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fill'] = array(
        '#title' => t('Fill'),
        '#description' => t('Fill the shape with color. Default: "!depends"', array('!depends' => l(t("depends"), 'http://leafletjs.com/reference.html#path-fill'))),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['fill']) ? $settings[$group]['fill'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fillColor'] = array(
        '#title' => t('Fill Color'),
        '#description' => t('Fill color. Default: #00030f'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['fillColor']) ? $settings[$group]['fillColor'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][fill]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fillOpacity'] = array(
        '#title' => t('Fill Opacity'),
        '#description' => t('Fill opacity. A number between 0 (would make the fill invisible) to 1 (no transparency at all). Default: 0.2'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['fillOpacity']) ? $settings[$group]['fillOpacity'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][fill]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['clickable'] = array(
        '#title' => t('Clickable'),
        '#description' => t('If disabled, the vector will not emit mouse events, essentially acting as a part of the underlying map. Default: True'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['clickable']) ? $settings[$group]['clickable'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      break;

    case "tokens":
      $form_element = array(
        '#title' => t('Tokens'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#weight' => $options['weight'],
      );
      $form_element['token_help'] = array(
        '#type' => 'container',
        '#theme' => 'token_tree',
        '#token_types' => array($options['entity_type']),
      );
      break;

  }
  return $form_element;
}
