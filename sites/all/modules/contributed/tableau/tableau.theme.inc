<?php

/**
 * @file tableau.theme.inc
 * Theme and preprocess functions for Tableau.
 */

/**
 * Preprocess function for theme('tableau_view').
 */
function theme_tableau_view(&$variables) {
  switch ($variables['format']) {
    case 'static':
      return theme('tableau_view_static', $variables);
    case 'thumbnail':
      return theme('tableau_view_thumbnail', $variables);
    case 'interactive':
    default:
      return theme('tableau_view_interactive', $variables);
  }
}

/**
 * Preprocess function for theme('tableau_view_interactive').
 */
function tableau_preprocess_tableau_view_interactive(&$variables) {
  // Build the URL for display
  $variables['server'] = check_plain(variable_get('tableau_server', TABLEAU_SERVER));
  $variables['script_url'] = $variables['server'] . '/javascripts/api/viz_v1.js';
  $variables['host_url'] = $variables['server'] . '/';
  $variables['site'] = '';
  if (property_exists($variables['view'], 'site')) {
    $variables['site'] = 't/' . $variables['view']->site->url_namespace;
  }
  $variables['name'] = $variables['view']->view_url;
  $variables['static_image'] = $variables['view']->thumbnail;
  $variables['tabs'] = $variables['tabs'] && $variables['tabs'] != 'no' ? 'yes' : 'no';
  $variables['toolbar'] = $variables['toolbar'] && $variables['toolbar'] != 'no' ? 'yes' : 'no';

  // Set dimension units
  $variables['width'] = !strpos($variables['width'], 'px') && !strpos($variables['width'], '%') ? $variables['width'] . 'px' : $variables['width'];
  if (!strpos($variables['height'], '%')) {
    // Add 23px for tabs and 27px for toolbar
    $variables['height'] = (str_replace('px', '', $variables['height']) + ($variables['tabs'] == 'yes' ? 23 : 0) + ($variables['toolbar'] == 'yes' ? 27 : 0)) . 'px';
  }

  // If `render` is default, unset from template to avoid forcing the configuration
  if ($variables['render'] == 'default') {
    unset($variables['render']);
  }
  elseif ($variables['render'] == 'threshold') {
    // Use the custom threshold value when set
    if (is_numeric($variables['render_threshold'])) {
      $variables['render'] = $variables['render_threshold'];
    }
    else {
      // Or revert to default behavior
      unset($variables['render']);
    }
  }
}

/**
 * Preprocess function for theme('tableau_view_static').
 */
function tableau_preprocess_tableau_view_static(&$variables) {
  $source = $variables['view']->path . '.png';

  // Determine if static image has been cached locally
  if (variable_get('tableau_cache_images', 0)) {
    // Prepare URI directory
    $path = 'public://tableau';
    if (file_prepare_directory($path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      // Determine filepath
      $uri = '';
      if ($variables['view']->site && property_exists($variables['view']->site, 'url_namespace') && $variables['view']->site->url_namespace) {
        $uri .= $variables['view']->site->url_namespace . '/';
      }
      $uri .= $variables['view']->view_url . '-' . strtotime($variables['view']->workbook->updated_at) . '.png';
      $path .= '/' . str_replace('/', '-', $uri);

      // Attempt to load image
      if ($image = image_load($path)) {
        $source = $image->source;
      }
      else {
        // Get image from server
        if ($data = @file_get_contents($source)) {
          // Cache image locally
          if ($path = file_unmanaged_save_data($data, $path, FILE_EXISTS_REPLACE)) {
            $source = $path;
          }
        }
      }
    }
  }

  $variables['source'] = $source;
}

/**
 * Theme function for static Tableau views.
 */
function theme_tableau_view_static(&$variables) {
  $options = array(
    'path' => $variables['source'],
    'alt' => tableau_entity_title($variables['view']),
    'title' => tableau_entity_title($variables['view']),
    'width' => empty($variables['width']) ? NULL : $variables['width'],
    'height' => empty($variables['height']) ? NULL : $variables['height'],
  );
  return theme('image', $options);
}

/**
 * Theme function for Tableau views thumbnails.
 */
function theme_tableau_view_thumbnail(&$variables) {
  $options = array(
    'path' => $variables['view']->thumbnail,
    'alt' => tableau_entity_title($variables['view']),
    'title' => tableau_entity_title($variables['view']),
    'width' => empty($variables['width']) ? NULL : $variables['width'],
    'height' => empty($variables['height']) ? NULL : $variables['height'],
  );
  return theme('image', $options);
}
