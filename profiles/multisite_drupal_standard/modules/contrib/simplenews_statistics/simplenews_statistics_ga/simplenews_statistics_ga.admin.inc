<?php
/**
 * @file
 * Simplenews statistics Google Analytics file for admin settings.
 */

/**
 * Simplenews Google Analytics settings.
 */
function simplenews_statistics_ga_admin_settings_form($form, &$form_state) {
  $ga_account = variable_get('googleanalytics_account', 'UA-');
  if (module_exists('googleanalytics') && !empty($ga_account) && $ga_account != 'UA-') {
    $form['simplenews_statistics_ga_use_hash'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use hash (#) symbol for the Google Analytics part of the URL.'),
      '#default_value' => variable_get('simplenews_statistics_ga_use_hash', 0),
    );
    $form['simplenews_statistics_ga_utm_source'] = array(
      '#type' => 'textfield',
      '#title' => t('Campaign source'),
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 128,
      '#default_value' => variable_get('simplenews_statistics_ga_utm_source', 'newsletter'),
    );
    $form['simplenews_statistics_ga_utm_medium'] = array(
      '#type' => 'textfield',
      '#title' => t('Campaign medium'),
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 128,
      '#default_value' => variable_get('simplenews_statistics_ga_utm_medium', 'email'),
    );
    $form['simplenews_statistics_ga_utm_campaign'] = array(
      '#type' => 'textfield',
      '#title' => t('Campaign name'),
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 128,
      '#default_value' => variable_get('simplenews_statistics_ga_utm_campaign', '!newsletter_title'),
      '#description' => t('Newsletter name, product, promo code, or slogan. Use <em>!newsletter_title</em> to use the title of the newsletter.'),
    );
  }

  return system_settings_form($form);
}
