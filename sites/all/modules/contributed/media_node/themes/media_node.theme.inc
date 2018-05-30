<?php

/**
 * @file
 *
 * Theme preprocessing functions for Media: Node.
 */

/**
 * Template preprocessor for theme_media_node().
 */
function template_preprocess_media_node(&$variables) {
  if (isset($variables['file'])) {
    $variables['wrapper'] = file_stream_wrapper_get_instance_by_uri($variables['file']->uri);
    $variables['image_style'] = $variables['display']['settings']['image_style'];
    $variables['valid_image_styles'] = image_style_options(FALSE);
    $variables['url'] = $variables['wrapper']->getThumbnailPath();
    $variables['nid'] = $variables['wrapper']->getNid();
    if (empty($variables['image_style']) || !isset($valid_image_styles[$variables['image_style']])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $variables['url'],
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $variables['image_style'],
        '#path' => $variables['url'],
      );
    }
    $variables['output'] = drupal_render($element);
  }
}

