<?php
/**
 * @file
 *   Integration with File Entity module for display.
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_dailymotion_file_formatter_info() {
  $formatters = array();
  $formatters['media_dailymotion_video'] = array(
    'label' => t('Dailymotion Video'),
    'file types' => array('video'),
    'default settings' => array(
      'width' => media_dailymotion_variable_get('width'),
      'height' => media_dailymotion_variable_get('height'),
      'autoplay' => media_dailymotion_variable_get('autoplay'),
      'iframe' => media_dailymotion_variable_get('iframe'),
    ),
    'view callback' => 'media_dailymotion_file_formatter_video_view',
    'settings callback' => 'media_dailymotion_file_formatter_video_settings',
  );
  $formatters['media_dailymotion_image'] = array(
    'label' => t('Dailymotion Preview Image'),
    'file types' => array('video'),
    'default settings' => array(
      'image_style' => '',
      'width' => '',
      'height' => '',
    ),
    'view callback' => 'media_dailymotion_file_formatter_image_view',
    'settings callback' => 'media_dailymotion_file_formatter_image_settings',
  );
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_dailymotion_file_formatter_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'dailymotion' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'media_dailymotion_video',
      '#uri' => $file->uri,
    );
    foreach (array('width', 'height', 'autoplay', 'iframe') as $setting) {
      $element['#' . $setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_dailymotion_file_formatter_video_settings($form, &$form_state, $settings) {
  $element = array();
  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['iframe'] = array(
    '#title' => t('Use iframe Mode (compatible with iPhone, iPad, Android ...)'),
    '#type' => 'checkbox',
    '#default_value' => $settings['iframe'],
  );
  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_dailymotion_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'dailymotion') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(),
        '#width' => $display['settings']['width'],
        '#height' => $display['settings']['height'],
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
      );
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_dailymotion_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
    '#states' => array(
      'visible' => array(
       ':input[name="displays[media_dailymotion_image][settings][image_style]"]' => array('value' => ''),
      ),
    ),
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
    '#states' => array(
      'visible' => array(
       ':input[name="displays[media_dailymotion_image][settings][image_style]"]' => array('value' => ''),
      ),
    ),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_dailymotion_file_default_displays() {
  $default_displays = array();

  // Default settings for displaying as a video.
  $default_video_settings = array(
    'media_large' => array(
      'width' => 480,
      'height' => 360,
      'autoplay' => FALSE,
      'iframe' => TRUE,
    ),
    'media_original' => array(
      'width' => 640,
      'height' => 480,
      'autoplay' => media_dailymotion_variable_get('autoplay'),
      'iframe' => TRUE,
    ),
  );
  foreach ($default_video_settings as $view_mode => $settings) {
    $display_name = 'video__' . $view_mode . '__media_dailymotion_video';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a video preview image. We enable preview
  // images even for view modes that also play video, for use inside a running
  // WYSIWYG editor. The higher weight ensures that the video display is used
  // where possible.
  $default_image_styles = array(
    'media_preview' => 'square_thumbnail',
    'media_large' => 'large',
    'media_original' => ''
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'video__' . $view_mode . '__media_dailymotion_image';
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
