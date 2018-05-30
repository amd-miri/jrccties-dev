<?php

/**
 * @file media_tableau/includes/themes/media_tableau.theme.inc
 *
 * Theme and preprocess functions for Media: Tableau.
 */

/**
 * Preprocess function for theme('media_tableau_visualization').
 */
function media_tableau_preprocess_media_tableau_visualization_name(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  $variables['visualization'] = check_plain($parts['v']);
  $variables['protocol'] = !empty($_SERVER['HTTPS']) ? 'https:' : 'http:';
  $variables['server'] = $variables['protocol'] . '//' . check_plain($parts['s']);
  $variables['height'] = $parts['h'];
  $variables['width'] = $parts['w'];
  
  $variables['wrapper_id'] = 'media_tableau_' . $variables['visualization'] . '_' . $variables['id'];

  $variables['script_url'] = $variables['server'] . '/javascripts/api/viz_v1.js';
  
  $variables['visualization_decoded'] = html_entity_decode($variables['visualization']);
  
  $variables['image_url_noscript'] = $variables['server'] . '/static/images/' . substr($variables['visualization_decoded'], 0, 2) . '/' . $variables['visualization_decoded'] . '/1_rss.png';
  $variables['image_url_static'] = $variables['server'] . '/static/images/' . substr($variables['visualization_decoded'], 0, 2) . '/' . $variables['visualization_decoded'] . '/1.png';
}

function media_tableau_preprocess_media_tableau_visualization_path(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  $variables['visualization'] = check_plain($parts['v']);
  $variables['protocol'] = !empty($_SERVER['HTTPS']) ? 'https:' : 'http:';
  $variables['server'] = $variables['protocol'] . '//' . check_plain($parts['s']);
  $variables['height'] = $parts['h'];
  $variables['width'] = $parts['w'];

  $variables['wrapper_id'] = 'media_tableau_' . $variables['visualization'] . '_' . $variables['id'];

  $variables['script_url'] = $variables['server'] . '/javascripts/api/viz_v1.js';

  $variables['visualization_decoded'] = html_entity_decode($variables['visualization']);

  $variables['image_url_noscript'] = $variables['server'] . '/static/images/' . substr($variables['visualization_decoded'], 0, 2) . '/' . $variables['visualization_decoded'] . '/1_rss.png';
  $variables['image_url_static'] = $variables['server'] . '/static/images/' . substr($variables['visualization_decoded'], 0, 2) . '/' . $variables['visualization_decoded'] . '/1.png';
}

function theme_media_tableau_field_formatter_styles($variables) {
  $element = $variables['element'];
  $style = $variables['style'];
  $variables['file'] = $element['#item'];
  $variables['uri'] = $variables['file']['uri'];
  $variables['style_name'] = $style['name'];
  return theme('media_tableau_embed', $variables);
}

/**
 * Preview for Styles UI.
 */
function theme_media_tableau_preview_style($variables) {
  $variables['uri'] = media_tableau_variable_get('preview_uri');
  $variables['field_type'] = 'file';
  $variables['object'] = file_uri_to_object($variables['uri']);

  return theme('styles', $variables);
}

/**
 * NOTE: Deprecated with Styles version 2.
 */
function theme_media_tableau_styles($variables) {
  $style = $variables['style'];
  $variables['file'] = $variables['object'];
  $variables['uri'] = $variables['object']->uri;
  $variables['style_name'] = $style['name'];
  return theme('media_tableau_embed', $variables);
}

/**
 * @todo: get this working
 *
 * This code is for embedding visualizations in WYSIYWG areas, not currently working.
 * NOTE: Deprecated with Styles version 2.
 */
function theme_media_tableau_embed($variables) {
  $preset_name = $variables['preset_name'];
  $preset = styles_containers_available_styles('file', 'media_tableau', $preset_name);
  $output = '';
  if (!empty($preset)) {
    // Build the URL for display.
    $uri = $variables['uri'];
    $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
    $parts = $wrapper->get_parameters();

    $fullscreen_value = $autoplay = 'false';
    $in_browser = $thumbnail = FALSE;

    foreach ($preset['effects'] as $effect) {
      switch ($effect['name']) {
        case 'autoplay':
          $autoplay = $effect['data']['autoplay'] ? 'true' : 'false';
          break;
        case 'resize':
          $width = $effect['data']['width'];
          $height = $effect['data']['height'];
          break;
        case 'fullscreen':
          $fullscreen_value = $effect['data']['fullscreen'] ? 'true' : 'false';
          break;
        case 'thumbnail':
          $thumbnail = $effect['data']['thumbnail'];
      }
    }
    if (isset($variables['object']->override)) {
      $override = $variables['object']->override;
      if (isset($override['width'])) {
        $width = $override['width'];
      }
      if (isset($override['height'])) {
        $height = $override['height'];
      }
      if (isset($override['wysiwyg'])) {
        $thumbnail = TRUE;
      }
      if (isset($override['browser']) && $override['browser']) {
        $in_browser = TRUE;
        $thumbnail = TRUE;
      }
    }
    $width = isset($width) ? $width : media_tableau_variable_get('width');
    $height = isset($height) ? $height : media_tableau_variable_get('height');
    $video_id = check_plain($parts['v']);
    if ($thumbnail) {
      // @todo Clean this up.
      $image_variables = array(
        'path' => $wrapper->getOriginalThumbnailPath(),
        'alt' => $variables['alt'],
        'title' => $variables['title'],
        'getsize' => FALSE,
      );
      if (isset($preset['image_style'])) {
        $image_variables['path'] = $wrapper->getLocalThumbnailPath();
        $image_variables['style_name'] = $preset['image_style'];
        $output = theme('image_style', $image_variables);
      }
      else {
        // We need to add this style attribute here so that it doesn't get lost
        // If you resize a visualization in a node, save it, edit it, but don't adjust
        // the sizing of the visualization while editing, the size will revert to the
        // default.  Adding the specific size here retains the original resizing
        $WYSIWYG = isset($variables['object']->override['style']) ? $variables['object']->override['style'] : '';
        $image_variables['attributes'] = array('width' => $width, 'height' => $height, 'style' => $WYSIWYG);
        $output = theme('image', $image_variables);
      }
      if ($in_browser) {
        // Add an overlay that says 'Tableau' to media library browser thumbnails.
        $output .= '<span />';
      }
    }
    else {
      $output = theme('media_tableau_visualization', array('uri' => $uri, 'width' => $width, 'height' => $height));
    }
  }
  return $output;
}
