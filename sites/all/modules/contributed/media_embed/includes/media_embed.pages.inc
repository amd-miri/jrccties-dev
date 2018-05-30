<?php

/**
 * @file
 * Common pages for the Media Embed module.
 */


/**
 * Form constructor for format selector form.
 */
function media_embed_format_selector_form($form, &$form_state, $file) {
  form_load_include($form_state, 'inc', 'media_embed', 'media_embed.pages');
  $class = 'media-format-selector-form';
  $form_wrapper = "$class-wrapper";
  $path = drupal_get_path('module', 'media_embed');
  $form['#tree'] = TRUE;
  $form['#prefix'] = '<div id="' . $form_wrapper . '">';
  $form['#suffix'] = '</div>';
  $form['#attached']['css'][] = $path . '/css/format_selector_form.css';
  $form['#attributes'] = array(
    'class' => array($class),
  );

  $form['title'] = array(
    '#markup' => t('Embedding @type "@name"', array(
      '@type' => $file->type,
      '@name' => $file->filename,
    )),
  );

  $preview = media_get_thumbnail_preview($file);
  $form['preview'] = array(
    '#type' => 'markup',
    '#title' => check_plain(basename($file->uri)),
    '#markup' => drupal_render($preview),
  );

  $form['file'] = array(
    '#type' => 'value',
    '#value' => $file,
  );

  $formatters = media_embed_formatter_options($file);
  $g = $_GET;
  if (!empty($form_state['values'])) {
    $default_formatter = $form_state['values']['formatter'];
  }
  elseif (!empty($g['format']) && isset($formatters[$g['format']])) {
    $default_formatter = $g['format'];
  }
  else {
    $default_formatter = media_embed_default_formatter($file);
  }

  if (!$formatters) {
    $form['formatter'] = array(
      '#type' => 'item',
      '#title' => t('Formatter'),
      '#description' => t('There are no available formatters.'),
    );

    return $form;
  }

  $params = media_embed_params();
  $settings = $params['settings'];
  $wrapper = $params['wrapper'];
  $settings_wrapper = "$class-settings-wrapper";
  $form['#attached']['js'][] = $path . '/js/format_selector_form.js';

  $type = isset($formatters[$default_formatter]) ? $default_formatter : key($formatters);
  $form['formatter'] = array(
    '#type' => 'select',
    '#title' => t('Formatter'),
    '#options' => $formatters,
    '#default_value' => $type,
    '#ajax' => array(
      'callback' => 'media_embed_format_selector_form_ajax',
      'wrapper' => $settings_wrapper,
    ),
  );

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#prefix' => '<div id="' . $settings_wrapper . '">',
    '#suffix' => '</div>',
  );

  $formatter = file_info_formatter_types($type);
  $callback = isset($formatter['settings callback']) ? $formatter['settings callback'] : '';
  if ($callback && function_exists($callback)) {
    $settings = media_embed_formatter_settings($formatter, $settings);
    $form['settings'] += $callback($form, $form_state, $settings, $type, $file->type, '_custom');
  }
  else {
    $form['settings']['empty'] = array(
      '#markup' => t('This formatter does not have any settings.'),
    );
  }

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Wrapper'),
  );

  $form['wrapper']['wrap'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create wrapper'),
    '#default_value' => !!$wrapper,
  );

  $states = array(
    'visible' => array(
      ':input[name="wrapper[wrap]"]' => array('checked' => TRUE),
    ),
  );

  $form['wrapper']['class'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS classes'),
    '#description' => t('A list of space-separated CSS classes.'),
    '#default_value' => $wrapper ? $wrapper['class'] : '',
    '#states' => $states,
  );

  $form['wrapper']['id'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS ID'),
    '#default_value' => $wrapper ? $wrapper['id'] : '',
    '#states' => $states,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#ajax' => array(
      'callback' => 'media_embed_format_selector_form_submit_ajax',
      'wrapper' => $form_wrapper,
      'event' => 'click',
    ),
  );

  return $form;
}


/**
 * Form validation handler for format selector form.
 */
function media_embed_format_selector_form_validate($form, &$form_state) {
  $values = &$form_state['values']['wrapper'];
  if (!empty($values['wrap'])) {
    unset($values['wrap']);
    $values['class'] = media_embed_filter_wrapper_class($values['class']);
    $values['id'] = media_embed_filter_wrapper_id($values['id']);
  }
  else {
    $values = array();
  }
}


/**
 * AJAX callback for formatter element change of format selector form.
 */
function media_embed_format_selector_form_ajax($form, &$form_state) {
  return $form['settings'];
}


/**
 * AJAX submit callback for format selector form.
 */
function media_embed_format_selector_form_submit_ajax($form, $form_state) {
  if (form_get_errors()) {
    $form['title']['#access'] = FALSE;
    return $form;
  }
  $values = $form_state['values'];
  $params = array(
    'settings' => !empty($values['settings']) ? $values['settings'] : array(),
    'wrapper' => $values['wrapper'],
  );
  $plugin_params = array();
  $params['settings'] && $plugin_params['settings'] = $params['settings'];
  $params['wrapper'] && $plugin_params['wrapper'] = $params['wrapper'];
  $data = array(
    'id' => $values['file']->fid,
    'format' => $values['formatter'],
    'params' => $plugin_params ? drupal_json_encode($plugin_params) : NULL,
  );
  $commands = array(array(
    'command' => 'MediaFormatSelectorSubmit',
    'data' => array(
      'content' => media_embed_formatted_wysiwyg($values['file'], $values['formatter'], $params),
      'data' => $data,
      'token' => media_embed_generate_token($data),
    ),
  ));

  return array('#type' => 'ajax', '#commands' => $commands);
}
