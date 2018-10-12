<?php

/**
 * @file
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_node_file_formatter_info() {
  $formatters['media_node_image'] = array(
    'label' => t('Node Preview Image'),
    'file types' => array('image'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'media_node_file_formatter_image_view',
    'settings callback' => 'media_node_file_formatter_image_settings',
  );
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_node_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'node') {
    $element = array(
      '#theme' => 'media_node',
      '#file' => $file,
      '#display' => $display,
      '#langcode' => $langcode,
    );
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_node_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_node_file_default_displays() {
  $default_displays = array();

  // Default settings for displaying as a image.
  $default_image_settings = array(
    'media_large' => array(
      'width' => 480,
      'height' => 360,
      'autoplay' => FALSE,
    ),
    'media_original' => array(
      'width' => 640,
      'height' => 480,
      'autoplay' => media_node_variable_get('autoplay'),
    ),
  );
  foreach ($default_image_settings as $view_mode => $settings) {
    $display_name = 'image__' . $view_mode . '__media_node_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a image preview image. We enable preview
  // images even for view modes that also play image, for use inside a running
  // WYSIWYG editor. The higher weight ensures that the image display is used
  // where possible.
  $default_image_styles = array(
    'media_preview' => 'square_thumbnail',
    'media_large' => 'large',
    'media_original' => ''
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'image__' . $view_mode . '__media_node_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}
