<?php
/**
 * @file
 * Simplenews statistics encoder file for admin settings.
 */

/**
 * Simplenews encoder settings.
 */
function simplenews_statistics_encoder_settings_form($form, &$form_state) {
  $form['simplenews_statistics_encoder_type'] = array(
    '#type' => 'select',
    '#title' => t('Parameter encoding type:'),
    '#options' => array(
      'md5' => 'MD5 hash style encoding',
      'shorturl' => 'ShortURL style encoding',
      'none' => 'None',
    ),
    '#description' => t('Select how the encoding should be done.'),
    '#default_value' => variable_get('simplenews_statistics_encoder_type', 'md5'),
  );

  return system_settings_form($form);
}
