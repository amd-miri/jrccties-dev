<?php

/**
 * @file
 * Provides page content for Mapeditor module.
 */

/**
 * Provides an example of a webtools map.
 */
function example_page() {
  global $base_url;
  $load_js = variable_get('webtools_environment', MAPEDITOR_WEBTOOLS_ENVIRONMENT);
  $element = array(
    '#type' => 'markup',
    '#markup' => "<script async src='${load_js}' type='text/javascript'></script>",
  );
  drupal_add_html_head($element, 'async_script');
  $map = mapeditor_default_map_settings();
  $map['settings']['zoom'] = 3;
  $js_path = $base_url . '/' . drupal_get_path('module', 'mapeditor') . '/js/map.js?v=' . rand(0, 33333);
  $options = drupal_json_encode(array(
      'service' => 'map',
      'custom' => $js_path,
    )
  );
  $build['script_init'] = array(
    '#type' => 'markup',
    '#markup' => "<script type='application/json'>${options}</script>",
  );
  $mapeditor_map_settings = drupal_json_encode($map['settings']);
  $js_inline = "var map_height = '400px';
  mapeditor_map_settings = {$mapeditor_map_settings};
var features = [{'type':'Feature','properties':{'name':'Gunwalls','popupContent':'Pops'},'geometry':{'type':'Point','coordinates':[-0.09, 51.5]}},{'type':'Feature','properties':{'name':'Gunwalls','popupContent':'Pops'},'geometry':{'type':'Point','coordinates':[-51.16823,-5.91042]}}];
      var all_coordinates = [[51.5, -0.09],[-5.91042,-51.16823]];

  ";
  $build['#attached']['js'][] = array(
    'data' => $js_inline,
    'type' => 'inline',
    'scope' => 'footer',
  );
  return $build;
}

/**
 * Provides an example of a webtools map with nuts.
 */
function example_page_nuts() {
  global $base_url;
  $load_js = variable_get('webtools_environment', MAPEDITOR_WEBTOOLS_ENVIRONMENT);
  $element = array(
    '#type' => 'markup',
    '#markup' => "<script async src='${load_js}' type='text/javascript'></script>",
  );
  drupal_add_html_head($element, 'async_script');
  $map = mapeditor_default_map_settings();
  $map['settings']['zoom'] = 4;
  $js_path = $base_url . '/' . drupal_get_path('module', 'mapeditor') . '/js/nuts.js?doh=' . rand(0, 33333);
  $options = drupal_json_encode(array(
      'service' => 'map',
      'custom' => $js_path,
    )
  );
  $build['script_init'] = array(
    '#type' => 'markup',
    '#markup' => "<script type='application/json'>${options}</script>",
  );

  $mapeditor_nuts = array(
    'NL' => array('title' => 'Netherlands', 'url' => 'http://example.com'),
    'BE' => array('title' => 'Belgium', 'url' => 'http://example.com'),
    'DE' => array('title' => 'Germany', 'url' => 'http://example.com'),
    'EL' => array('title' => 'Greece', 'url' => 'http://example.com'),
    'IE' => array('title' => 'Ireland', 'url' => 'http://example.com'),
    'SE' => array('title' => 'Sweden', 'url' => 'http://example.com'),
  );

  $mapeditor_map_settings = drupal_json_encode($map['settings']);
  $mapeditor_nuts = drupal_json_encode($mapeditor_nuts);
  $js_inline = "var map_height = '400px';
  mapeditor_map_settings = {$mapeditor_map_settings};
  mapeditor_nuts = {$mapeditor_nuts};
  var mapeditor_nuts_keys = ['NL','BE','DE','EL','IE','SE']";
  $build['#attached']['js'][] = array(
    'data' => $js_inline,
    'type' => 'inline',
    'scope' => 'footer',
  );
  return $build;
}
