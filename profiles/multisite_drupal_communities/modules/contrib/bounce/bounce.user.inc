<?php

/**
 * @file
 * Implementations of user hooks and other integration with the user
 * experience.
 */

/**
 * Implements hook_preprocess_page().
 *
 * Deliver messages to users who are blocked when they visit their own account
 * page or account editing page.
 */
function bounce_preprocess_page(&$vars) {
  global $user;
  if (!$user->uid) {
    return;
  }

  $path = current_path();
  if (preg_match('/^user\/' . $user->uid . '($|\/edit$)/', $path) && ($warn = variable_get('bounce_notify_user_on_account_page', TRUE))) {
    $account = user_load($user->uid);
    $blocked = bounce_is_mail_blocked($user->mail);

    if ($blocked) {
      $message = variable_get('bounce_notify_user_message');
      if ($message) {
        drupal_set_message(check_plain($message), 'warning', FALSE);
      }
    }
  }
}

/**
 * Check to see if a user is using a blocked email address.
 *
 * This used to be done by adding a property to the user object via
 * hook_user_load, but that is apparently not a good plan anymore due to
 * caching.
 */
function bounce_is_mail_blocked($mail) {
  $count = db_select('bounce_blocked', 'b')
    ->condition('b.mail', $mail, '=')
    ->countQuery()
    ->execute()
    ->fetchField();

  return $count > 0;
}

/**
 * Implements hook_user_login().
 *
 * If we are notifying users that their email is blocked, then do so on login.
 */
function bounce_user_login(&$edit, $account) {
  $notify = variable_get('bounce_notify_user_on_login', TRUE);
  $blocked = bounce_is_mail_blocked($account->mail);

  if ($notify && $blocked) {
    $message = variable_get('bounce_notify_user_message');
    if ($message) {
      drupal_set_message(check_plain($message), 'warning', FALSE);
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_register_form().
 *
 * Add a validation method to the password reset form.
 */
function bounce_form_user_register_form_alter(&$form, &$form_state) {
  $form['#validate'][] = 'bounce_user_register_form_validate';
}

/**
 * Validation function for the registration form.
 *
 * Send back an error if a user is registering with a blocked mail, and if the
 * admin settings say we should do that.
 */
function bounce_user_register_form_validate($form, &$form_state) {
  $notify = variable_get('bounce_error_on_registration', TRUE);
  $mail = preg_replace('/^\s+|\s+$/', '', $form_state['values']['mail']);

  if ($notify && $mail) {
    $blocked = bounce_is_mail_blocked($mail);
    $message = variable_get('bounce_error_on_registration_message');
    if ($message && $blocked) {
      form_set_error('mail', check_plain($message));
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_pass().
 *
 * Add a validation method to the password reset form.
 */
function bounce_form_user_pass_alter(&$form, &$form_state) {
  $form['#validate'][] = 'bounce_user_pass_validate';
}

/**
 * Validation function for the reset password form.
 *
 * Send back an error if a user enters a blocked mail, and if the admin
 * settings say we should do that.
 */
function bounce_user_pass_validate($form, &$form_state) {
  $user = user_load_by_mail($form_state['values']['name']);
  if (!$user) {
    $user = user_load_by_name($form_state['values']['name']);
  }

  if (!$user) {
    return;
  }

  $blocked = bounce_is_mail_blocked($user->mail);

  if ($user && $blocked) {
    $notify = variable_get('bounce_error_on_password_reset', TRUE);
    $message = variable_get('bounce_error_on_password_reset_message');
    if ($message && $notify) {
      form_set_error('mail', check_plain($message));
    }
  }
}
