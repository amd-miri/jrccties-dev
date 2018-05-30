<?php
/**
 * @file
 * Admin settings for Organic groups e-mail blast module.
 */

/**
 * E-mail group members form.
 */
function og_email_blast_group($form, &$form_state, $entity_type, $etid) {
  global $user;
  og_set_breadcrumb($entity_type, $etid, array(l(t('Group'), "$entity_type/$etid/group")));
  if ($group = og_get_group($entity_type, $etid)) {
    $form['intro'] = array(
      '#markup' => '<p>' . t('Use this form to send an e-mail message to group members.') . '</p>',
    );
    $form['group'] = array(
      '#type' => 'value',
      '#value' => check_plain($group->label),
    );
    $form['group_url'] = array(
      '#type' => 'value',
      '#value' => $entity_type . '/' . $etid . '/group',
    );
    $form['admin'] = array(
      '#type' => 'value',
      '#value' => check_plain($user->name),
    );
    $form['admin_email'] = array(
      '#type' => 'value',
      '#value' => check_plain($user->mail),
    );
    $form['to'] = array(
      '#type' => 'value',
      '#value' => _group_emails($user, $group),
    );
    $form['subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#required' => TRUE,
    );
    $form['message'] = array(
      '#type' => 'textarea',
      '#title' => t('Message'),
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Send e-mail'),
    );
    return $form;
  }
  // Not a valid group node.
  drupal_not_found();
}

/**
 * Submit handler; E-mail group members.
 */
function og_email_blast_group_submit($form, &$form_state) {
  og_email_blast_mail_send($form_state['values']);
  // Redirect to the group admin page.
  $form_state['redirect'] = $form_state['values']['group_url'];
}

/**
 * Implements hook_mail_send().
 */
function og_email_blast_mail_send($form_values) {
  $module = 'og_email_blast';
  $key = 'group_message';
  $to = $form_values['admin_email'];
  $from = variable_get('site_mail', 'admin@example.com');
  $params = $form_values;
  $language = language_default();
  $send = TRUE;
  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }
}

/**
 * Implements hook_mail().
 */
function og_email_blast_mail($key, &$message, $params) {
  switch ($key) {
    case 'group_message':
      $message['headers']['Bcc'] = $params['to'];
      $message['headers']['Reply-To'] = $params['admin_email'];
      $message['subject'] = check_plain($params['subject']);
      $message['body'][] = check_plain($params['message']);
      watchdog('og_email_blast', $params['admin'] . ' sent an e-mail blast to ' . $params['group']);
      break;
  }
}

/**
 * Utility function to get group members' e-mail addresses. This list does not
 * include the group admin's e-mail address.
 *
 * @param $user
 *   The user object of the group admin requesting/using this info.
 *
 * @param $group
 *   The group object.
 *
 * @return
 *   A string of concatenated group members' e-mail addresses.
 */
function _group_emails($user, $group) {
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'user')
    ->fieldCondition(OG_AUDIENCE_FIELD, 'gid', $group->gid, '=');
  if ($result = $query->execute()) {
    $uids = array_keys($result['user']);
    $accounts = user_load_multiple($uids);
    $emails = array();
    foreach ($accounts as $account) {
      // We do not want the current user's e-mail
      if ($account->uid != $user->uid) {
        $emails[] = $account->mail;
      }
    }
    return check_plain(implode(', ', $emails));
  }
  // Query did not execute.
  return NULL;
}
