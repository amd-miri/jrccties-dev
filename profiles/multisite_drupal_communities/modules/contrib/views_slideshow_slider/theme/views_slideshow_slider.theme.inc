<?php

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: slider module.
 */

/**
 * Create the divs that will be turned into the slider.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_widget_render($vars) {

  // Default number of items per slide
  $items_per_slide = 1;

  if (isset($vars['view']->style_plugin->options['views_slideshow_cycle']['items_per_slide']) && $vars['view']->style_plugin->options['views_slideshow_cycle']['items_per_slide'] > 1) {
    $items_per_slide = $vars['view']->style_plugin->options['views_slideshow_cycle']['items_per_slide'];
  }
  return theme('views_slideshow_slider_slider', array('vss_id' => $vars['vss_id'], 'view' => $vars['view'], 'settings' => $vars['settings'], 'location' => $vars['location'], 'rows' => $vars['rows'], 'items_per_slide' => $items_per_slide));
}

function template_preprocess_views_slideshow_slider_slider(&$vars) {
  drupal_add_library('system', 'ui.slider');
  // Build our javascript settings.
  $js_vars = array(
    'viewsSlideshowSlider' => array(
      $vars['vss_id'] => array(
        'location' => $vars['location'],
        // Take the number of items per slide into consideration
        'max' => intval(ceil(count($vars['rows']) / $vars['items_per_slide'])) -1, // The count in the slider starts from 0, this is the max.
        'orientation' => 'horizontal', // @TODO
      ),
    ),
  );
  drupal_add_js($js_vars, 'setting');
  
  drupal_add_js(drupal_get_path('module', 'views_slideshow_slider') . '/views_slideshow_slider.js');
}

