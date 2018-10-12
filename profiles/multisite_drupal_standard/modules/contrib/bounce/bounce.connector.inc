<?php

/**
 * @file
 * Functions and forms for the default connector component.
 */

/**
 * Return a default connector component object.
 *
 * Use the connector to establish a POP3 or IMAP connection to a mailserver.
 *
 * @param array $params
 *   (optional) Parameters for the connection.
 *
 * @return object
 *   An initialized connector object.
 */
function bounce_get_mailserver_connector($params = array()) {
  $params += array(
    'server' => 'localhost',
    'protocol' => 'pop3',
    'encryption' => 'ssl',
    'port' => 993,
    'login' => '',
    'password' => '',
    'timeout' => variable_get('bounce_connector_timeout', BOUNCE_DEFAULT_CONNECTION_TIMEOUT),
    'mail_part_size_limit' => variable_get('bounce_mail_part_size_limit_bytes', BOUNCE_DEFAULT_MAIL_PART_SIZE_LIMIT_BYTES),
    // Values below are not expected to be passed in.
    'folder' => 'INBOX',
  );

  // Placing the connector class into a variable allows the test cases to use
  // a different class. Overriding this is not recommended for other modules -
  // you should instead implement hook_bounce_connector().
  $class = variable_get('bounce_connector_class', 'BounceMailServerConnector');
  return new $class($params);
}

/**
 * Callback function to check on connector configuration.
 *
 * @return boolean
 *   TRUE if configured.
 */
function bounce_connector_is_configured() {
  if ($server = variable_get('bounce_connector_server')) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Callback function for connecting to a mailserver.
 *
 * Connect via the default connector and retrieve non-delivery report email
 * data from the configured account on that server.
 *
 * @return array
 *   An indexed array of email contents for processing - hopefully non-delivery
 *   reports.
 */
function bounce_connect() {
  $reports = array();
  $params = array(
    'server' => variable_get('bounce_connector_server'),
    'protocol' => variable_get('bounce_connector_protocol'),
    'encryption' => variable_get('bounce_connector_encryption'),
    'port' => variable_get('bounce_connector_port'),
    'login' => variable_get('bounce_connector_login'),
    'password' => variable_get('bounce_connector_password'),
    'timeout' => variable_get('bounce_connector_timeout'),
    'mail_part_size_limit' => variable_get('bounce_mail_part_size_limit_bytes'),
  );
  // Check to see that configuration exists - if not, do nothing.
  foreach ($params as $name => $value) {
    $failed = false;
    switch ($name) {
      case "protocol":
        if (!array_key_exists($value, bounce_connect_options_protocol())) {
          $failed = true;
        }
        break;

      case "encryption":
        if (!array_key_exists($value, bounce_connect_options_encryption())) {
          $failed = true;
        }
        break;

      default:
        if (!$value) {
          $failed = true;
        }
    }
    if ($failed) {
      watchdog('bounce', 'Cannot connect to retrieve non-delivery reports, as "@name" parameter is invalid or missing.', array('@name' => $name), WATCHDOG_ERROR);
      return $reports;
    }
  }

  $connector = bounce_get_mailserver_connector($params);
  $limit = variable_get('bounce_connector_max_reports_per_session', BOUNCE_DEFAULT_MAX_REPORTS_PER_SESSION);
  if ($connector->login()) {
    $info = $connector->getMailboxInfo();
    if (!empty($info['Nmsgs'])) {
      $limit = min($limit, $info['Nmsgs']);
      for ($message_number = 1; $message_number <= $limit; $message_number++) {
        $reports[] = $connector->getMessage($message_number);
        $connector->markMessageForDeletion($message_number);
      }
    }
    $connector->logout();
  }
  return $reports;
}

/**
 * Callback function to validate the non-delivery report mail account details.
 *
 * @param array $params
 *   Parameters for the connection.
 *
 * @return array
 *   An indexed array of email contents for processing - hopefully non-delivery
 *   reports.
 */
function bounce_connect_validate($params) {
  $connector = bounce_get_mailserver_connector($params);
  $validated = FALSE;
  if ($connector->login()) {
    $validated = TRUE;
    $connector->logout();
  }
  return $validated;
}

/**
 * Return select options for the connection protocol parameter.
 *
 * @return array
 *   An options array.
 */
function bounce_connect_options_protocol() {
  return array(
    'pop3' => t('POP3'),
    'imap' => t('IMAP'),
  );
}

/**
 * Return select options for the connection encryption parameter.
 *
 * @return array
 *   An options array.
 */
function bounce_connect_options_encryption() {
  return array(
    '' => t('None'),
    'tls' => t('TLS'),
    'ssl' => t('SSL'),
  );
}

/**
 * Form constructor for the settings form associated with the default connector.
 *
 * @see bounce_connect_settings_validate()
 * @ingroup forms
 */
function bounce_connect_settings($form, &$form_state) {

  drupal_add_js(drupal_get_path('module', 'bounce') . '/js/bounce.connector.js');

  $form['connector'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mail server and account'),
    '#description' => t('Enter the information needed to connect to the mail account that will receive non-delivery reports.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['connector']['bounce_connector_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server'),
    '#description' => t('The domain name of your mail server, e.g. mail.mydomain.com'),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_connector_server', ''),
  );
  $form['connector']['bounce_connector_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login'),
    '#description' => t('If the recipient account is @email, the login may be "@name" or "@email" depending on your mail server configuration.', array('@name' => 'bounces', '@email' => 'bounces@' . $_SERVER['SERVER_NAME'])),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_connector_login', ''),
  );
  // Change the description for the password field depending on whether it has
  // been set or not. This is hopefully a sufficient cue for the user, given
  // that the field won't show any sign that it has a value already.
  if ($password = variable_get('bounce_connector_password', '')) {
    $description = t('The account password is set. Leave this field blank if you do not wish to change it.');
  }
  else {
    $description = t('Enter the account password.');
  }
  $form['connector']['bounce_connector_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => $description,
    '#default_value' => $password,
  );

  $form['connection'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection settings'),
    '#description' => t('Configure connection details.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['connection']['bounce_connector_protocol'] = array(
    '#type' => 'select',
    '#title' => t('Protocol'),
    '#description' => t('The protocol used to connect to the mail server. Most mail servers support POP3 and IMAP.'),
    '#options' => bounce_connect_options_protocol(),
    '#default_value' => variable_get('bounce_connector_protocol', 'pop3'),
  );
  $form['connection']['bounce_connector_encryption'] = array(
    '#type' => 'select',
    '#title' => t('Encryption Mode'),
    '#description' => t('The encryption mode used to secure connections to the mail server. Most mail servers support TLS connections on port 110 for POP3 and 143 for IMAP, SSL connections on port 993 for IMAP and 995 for POP3, and do not accept plain text connections on any port.'),
    '#options' => bounce_connect_options_encryption(),
    '#default_value' => variable_get('bounce_connector_encryption', 'ssl'),
  );
  $form['connection']['bounce_connector_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Port'),
    '#description' => t('Attempt to connect to this port number. Most servers use the standard port that is set on selecting the protocol and encryption mode.'),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_connector_port', 995),
  );
  $form['connection']['bounce_connector_max_reports_per_session'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum non-delivery reports per session'),
    '#description' => t('The maximum number of non-delivery reports to pull from a mailserver in a single session.'),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_connector_max_reports_per_session', BOUNCE_DEFAULT_MAX_REPORTS_PER_SESSION),
  );
  $form['connection']['bounce_connector_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection timeout'),
    '#description' => t('Timeout in seconds for the connection.'),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_connector_timeout', BOUNCE_DEFAULT_CONNECTION_TIMEOUT),
  );
  $form['connection']['bounce_mail_part_size_limit_bytes'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum mail part size to download, in bytes'),
    '#description' => t('Enter a number of bytes. Mail parts can include encoded text, attachments, or other items. The information needed to determine non-delivery report code and email address of the recipient is usually contained in smaller text-only parts. Any part larger than this limit will be ignored.'),
    '#required' => TRUE,
    '#default_value' => variable_get('bounce_mail_part_size_limit_bytes', BOUNCE_DEFAULT_MAIL_PART_SIZE_LIMIT_BYTES),
  );

  $form = system_settings_form($form);
  $form['#validate'][] = 'bounce_connect_settings_validate';
  return $form;
}

/**
 * Form validation handler for bounce_connect_settings().
 */
function bounce_connect_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!preg_match('/^\d+$/', $form_state['values']['bounce_connector_port'])) {
    form_set_error('bounce_connector_port', t('Connection port must be an integer number.'));
  }
  if (!preg_match('/^\d+$/', $form_state['values']['bounce_connector_max_reports_per_session']) || !$form_state['values']['bounce_connector_max_reports_per_session']) {
    form_set_error('bounce_connector_max_reports_per_session', t('Maximum non-delivery reports per session must be a whole number greater than zero.'));
  }
  if (!preg_match('/^\d+$/', $form_state['values']['bounce_connector_timeout']) || !$form_state['values']['bounce_connector_timeout']) {
    form_set_error('bounce_connector_timeout', t('Connection timeout must be a whole number of seconds greater than zero.'));
  }
  if (!preg_match('/^\d+$/', $form_state['values']['bounce_mail_part_size_limit_bytes']) || !$form_state['values']['bounce_mail_part_size_limit_bytes']) {
    form_set_error('bounce_mail_part_size_limit_bytes', t('Maximum mail part size must be a whole number of bytes greater than zero.'));
  }

  // A blank password means keep the password we have; the password field type
  // doesn't display its value so if the user doesn't change it, we'll see an
  // empty string rather than the existing value.
  if (empty($form_state['values']['bounce_connector_password'])) {
    $form_state['values']['bounce_connector_password'] = variable_get('bounce_connector_password', '');
  }

  if ($errors = form_get_errors()) {
    return;
  }

  $params = array(
    'server' => $form_state['values']['bounce_connector_server'],
    'protocol' => $form_state['values']['bounce_connector_protocol'],
    'port' => $form_state['values']['bounce_connector_port'],
    'login' => $form_state['values']['bounce_connector_login'],
    'password' => $form_state['values']['bounce_connector_password'],
    'timeout' => $form_state['values']['bounce_connector_timeout'],
    'mail_part_size_limit' => $form_state['values']['bounce_mail_part_size_limit_bytes'],
  );
  foreach ($params as $value) {
    if (empty($value)) {
      return;
    }
  }

  // This can be empty, so insert it after the general empty check.
  $params['encryption'] = $form_state['values']['bounce_connector_encryption'];

  $valid = bounce_connect_validate($params);
  if (!$valid) {
    form_set_error('bounce_connector_server', t('Unable to log in to the specified account and server.'));
  }
}
