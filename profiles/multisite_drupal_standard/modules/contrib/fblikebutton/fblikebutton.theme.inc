<?php

/**
 * Implements template_preprocess().
 *
 * Formats variables and sanitizes data needed to build the like button.
 */
function template_preprocess_fblikebutton(&$variables) {
  $url = urlencode($variables['url']);
  $language = ($variables['language']) ? '&locale=' . $variables['language'] : '';
  // Ensure we translate the boolean into a string for the url to pass to
  // facebook.
  $show_faces = $variables['show_faces'] ? 'true' : 'false';
  $show_share = $variables['share'] ? 'true' : 'false';

  // We run the config src line through htmlentities to avoid rendering trouble
  // when we print to the page.
  $variables['src'] = htmlentities(sprintf('href=%s&layout=%s&show_faces=%s&width=%s&font=%s&height=%s&action=%s&colorscheme=%s%s&send=false&share=%s',
    $url,
    $variables['layout'],
    $show_faces,
    $variables['width'],
    $variables['font'],
    $variables['height'],
    $variables['action'],
    $variables['color_scheme'],
    $language,
    $show_share
  ));
}
