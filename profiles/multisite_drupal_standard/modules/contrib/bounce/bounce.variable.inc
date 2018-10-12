<?php

/**
 * @file
 * Provide definitions for use by the Variable module.
 */

/**
 * Implements hook_variable_info().
 */
function bounce_variable_info($options) {
  $variable['bounce_notify_user_message'] = array(
    'title' => t(
      'Bounce password account page error message',
      array(),
      $options
    ),
    'description' => t(
      'User notification on account page for blocked email addresses',
      array(),
      $options
    ),
    'default' => t(
      'Please update your email address: it has been blocked from receiving further mails due to failed delivery of past mail.',
      array(),
      $options
    ),
    'type' => 'text',
    'access' => 'administer email non-delivery report processing',
  );

  $variable['bounce_error_on_registration_message'] = array(
    'title' => t(
      'Bounce password registration error message',
      array(),
      $options
    ),
    'description' => t(
      'Error message on account registration for blocked email addresses',
      array(),
      $options
    ),
    'default' => t(
      'You cannot register with the provided email address: it has been blocked from receiving further mails due to failed delivery of past mail. Please choose another e-mail address.',
      array(),
      $options
    ),
    'type' => 'text',
    'access' => 'administer email non-delivery report processing',
  );

  $variable['bounce_error_on_password_reset_message'] = array(
    'title' => t('Bounce password reset error message',
      array(),
      $options
    ),
    'description' => t(
      'Error message on password reset for blocked email addresses',
      array(),
      $options
    ),
    'default' => t(
      'You cannot reset your password. The email address associated with your account been blocked from receiving further mails due to failed delivery of past mail.',
      array(),
      $options
    ),
    'type' => 'text',
    'access' => 'administer email non-delivery report processing',
  );

  return $variable;
}
