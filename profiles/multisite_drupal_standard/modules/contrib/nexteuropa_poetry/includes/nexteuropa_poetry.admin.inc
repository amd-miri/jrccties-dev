<?php

/**
 * @file
 * Administration form.
 */

use Psr\Log\LogLevel;

/**
 * Form callback.
 *
 * @see nexteuropa_poetry_menu()
 *
 * @return array
 *   Poetry client settings form.
 */
function nexteuropa_poetry_client_settings_form() {
  $form['service'] = array(
    '#type' => 'fieldset',
    '#title' => t('Remote service'),
  );
  $form['service']['nexteuropa_poetry_service_username'] = array(
    '#title' => t('Username'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('nexteuropa_poetry_service_username', ''),
    '#description' => t('The Poetry client username, as provided by the Poetry remote service.'),
  );
  $form['service']['nexteuropa_poetry_service_password'] = array(
    '#title' => t('Password'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('nexteuropa_poetry_service_password', ''),
    '#description' => t('The Poetry client password, as provided by the Poetry remote service.'),
  );
  $form['service']['nexteuropa_poetry_service_wsdl'] = array(
    '#title' => t('Service WSDL'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('nexteuropa_poetry_service_wsdl', ''),
    '#description' => t('The Poetry client WSDL for the Poetry remote service.'),
  );

  $form['notification'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notification handler'),
  );
  $form['notification']['nexteuropa_poetry_notification_username'] = array(
    '#title' => t('Username'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('nexteuropa_poetry_notification_username', ''),
    '#description' => t('Drupal notification callback username, Poetry remote service will use it to authenticate against it.'),
  );
  $form['notification']['nexteuropa_poetry_notification_password'] = array(
    '#title' => t('Password'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('nexteuropa_poetry_notification_password', ''),
    '#description' => t('Drupal notification callback password, Poetry remote service will use it to authenticate against it.'),
  );

  $form['logger'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logger settings'),
  );
  $form['logger']['nexteuropa_poetry_log_level'] = array(
    '#title' => t('Log level'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array(
      'none'              => t('Do not log any message'),
      LogLevel::DEBUG     => t('Log debug messages'),
      LogLevel::INFO      => t('Log informational messages'),
      LogLevel::NOTICE    => t('Log notice messages'),
      LogLevel::WARNING   => t('Log warning messages'),
      LogLevel::ERROR     => t('Log error messages'),
      LogLevel::CRITICAL  => t('Log critical messages'),
      LogLevel::ALERT     => t('Log alert messages'),
      LogLevel::EMERGENCY => t('Log emergency messages'),
    ),
    '#default_value' => variable_get('nexteuropa_poetry_log_level', 'none'),
    '#description' => t('Log from the selected level up, sorted by severity.'),
  );

  return system_settings_form($form);
}
