<?php

/**
 * @file
 * Administrative pages and functionality.
 */

/*
 -----------------------------------------------------------------------
 Admin form page for general settings and configuration.
 -----------------------------------------------------------------------
*/

/**
 * Form constructor for the Bounce module general settings.
 *
 * @see bounce_admin_settings_validate()
 * @ingroup forms
 */
function bounce_admin_settings($form, &$form_state) {

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['general']['bounce_mail_header_return_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Non-delivery report recipient'),
    '#required' => TRUE,
    '#description' => t('Enter the email address that will receive non-delivery reports, e.g. @email. It will be added as the "Return-Path" header to outgoing emails.', array('@email' => 'bounces@' . $_SERVER['SERVER_NAME'])),
    '#default_value' => variable_get('bounce_mail_header_return_path', ''),
  );
  $form['general']['bounce_mail_header_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Mail header name'),
    '#required' => TRUE,
    '#description' => t('Bounce adds a unique ID header to each outgoing mail sent via !link, and looks for that header when analyzing non-delivery reports. This is the header name, and must contain only letters, underscores, and dashes.', array('!link' => l('drupal_mail()', 'http://api.drupal.org/api/drupal/includes%21mail.inc/function/drupal_mail/7'))),
    '#default_value' => variable_get('bounce_mail_header_name', BOUNCE_DEFAULT_MAIL_HEADER_NAME),
  );

  $form['components'] = array(
    '#type' => 'fieldset',
    '#title' => t('Component settings'),
    '#description' => t('Choose the components used by this module.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['components']['bounce_connector'] = array(
    '#type' => 'select',
    '#title' => t('Mail server connector'),
    '#description' => t('The connector manages retrieval of non-delivery reports from the recipient account.'),
    '#options' => bounce_component_options('connector'),
    '#default_value' => variable_get('bounce_connector', BOUNCE_DEFAULT_CONNECTOR),
  );
  $form['components']['bounce_analyst'] = array(
    '#type' => 'select',
    '#title' => t('Non-delivery report analyst'),
    '#description' => t('The analyst parses a non-delivery report to find the recipient email address that triggered it and assigns a non-delivery code based on the report contents.'),
    '#options' => bounce_component_options('analyst'),
    '#default_value' => variable_get('bounce_analyst', BOUNCE_DEFAULT_ANALYST),
  );
  $form['components']['bounce_blocker'] = array(
    '#type' => 'select',
    '#title' => t('Mail blocker'),
    '#description' => t('The blocker decides which emails to block from further sending based on the analysis records produced by the analyst component.'),
    '#options' => bounce_component_options('blocker'),
    '#default_value' => variable_get('bounce_blocker', BOUNCE_DEFAULT_BLOCKER),
  );

  $form['data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data retention settings'),
    '#description' => t('Configure the length of time to store non-delivery report and sent mail data.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['data']['bounce_max_report_age_days'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum non-delivery report age in days'),
    '#required' => TRUE,
    '#description' => t('The age in days of the oldest non-delivery report that will be considered when calculating the current score for an email address. Older reports and records of sent mail will be deleted from the database.'),
    '#default_value' => variable_get('bounce_max_report_age_days', BOUNCE_DEFAULT_MAX_REPORT_AGE_DAYS),
  );
  $form['data']['bounce_max_sent_age_days'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum sent mail record age in days'),
    '#required' => TRUE,
    '#description' => t('Bounce adds a unique ID to the headers of ourgoing mail, and keeps a record of those headers to help identify the recipient email that caused a non-delivery report. This is the length of time in days of such records that will retained. If a non-delivery report takes longer than this to show up, then it will be harder to link it to the recipient email address.'),
    '#default_value' => variable_get('bounce_max_sent_age_days', BOUNCE_DEFAULT_MAX_SENT_AGE_DAYS),
  );

  $form['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Notices'),
    '#description' => t('Configure the notices and error messages shown to users with blocked email addresses.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['user']['bounce_notify_user_on_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify on login'),
    '#default_value' => variable_get('bounce_notify_user_on_login', TRUE),
  );
  $form['user']['bounce_notify_user_on_account_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify on the account page'),
    '#default_value' => variable_get('bounce_notify_user_on_account_page', TRUE),
  );
  $form['user']['bounce_notify_user_message'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('bounce_notify_user_message', ''),
    '#rows' => 2,
    '#required' => TRUE,
  );

  $form['user']['bounce_error_on_registration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display an error on account registration for blocked email addresses'),
    '#default_value' => variable_get('bounce_error_on_registration', TRUE),
  );
  $form['user']['bounce_error_on_registration_message'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('bounce_error_on_registration_message', ''),
    '#rows' => 2,
    '#required' => TRUE,
  );
  $form['user']['bounce_error_on_password_reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display an error on password reset for blocked email addresses'),
    '#default_value' => variable_get('bounce_error_on_registration', TRUE),
  );
  $form['user']['bounce_error_on_password_reset_message'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('bounce_error_on_password_reset_message', ''),
    '#rows' => 2,
    '#required' => TRUE,
  );

  $form = system_settings_form($form);
  $form['#validate'][] = 'bounce_admin_settings_validate';
  // We call menu_rebuild on submit because it's a valid strategy to have the
  // components (connector, analyst, blocker) add extra menu items to the
  // config here if they are enabled. The default blocker does this, and so if
  // it's swapped out the menu must be rebuilt to remove those additional menu
  // items.
  $form['#submit'][] = 'menu_rebuild';
  return $form;
}

/**
 * Form validation handler for bounce_admin_settings().
 */
function bounce_admin_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!valid_email_address($values['bounce_mail_header_return_path'])) {
    form_set_error('bounce_mail_header_return_path', t('Please enter a valid email address.'));
  }
  if (!preg_match('/^\d+$/', $values['bounce_max_report_age_days'])) {
    form_set_error('bounce_max_report_age_days', t('Maximum report age must be a whole number of days.'));
  }
  if (!preg_match('/^\d+$/', $values['bounce_max_sent_age_days'])) {
    form_set_error('bounce_max_sent_age_days', t('Maximum sent mail record age must be a whole number of days.'));
  }
  if (!preg_match('/^[a-z_\-]+$/i', $values['bounce_mail_header_name'])) {
    form_set_error('bounce_mail_header_name', t('Mail header name must contain only letters, underscores, and dashes.'));
  }
}

/**
 * Obtain a component options array suitable for use in a form.
 *
 * @param string $component_type
 *   A component type, i.e. 'blocker', 'connector', 'analyst'.
 *
 * @return array
 *   An associative array of component titles indexed by component machine
 *   name.
 */
function bounce_component_options($component_type) {
  $components = bounce_component_definitions($component_type);
  $options = array();
  foreach ($components as $name => $definition) {
    $options[$name] = $definition['title'];
  }
  return $options;
}

/*
 -----------------------------------------------------------------------
 Admin form page for component configuration.
 -----------------------------------------------------------------------
*/

/**
 * Form constructor for component configuration forms.
 *
 * This form constructor is simply a pass-through to pick up a configuration
 * form for the currently defined component.
 */
function bounce_admin_component_configuration($form, &$form_state, $component_type, $default_component_name) {
  $component_name = variable_get('bounce_' . $component_type, $default_component_name);
  $components = bounce_component_definitions($component_type);
  bounce_component_include($components[$component_name]);
  $function = $components[$component_name]['settings_callback'];
  $params = array($form, &$form_state);
  $form = call_user_func_array($function, $params);
  return $form;
}

/*
 -----------------------------------------------------------------------
 Admin form page for blocked emails.
 -----------------------------------------------------------------------
*/

/**
 * Form constructor for the admin page displaying blocked emails.
 *
 * The form also allows the admin to filter and unblock selected emails.
 *
 * @see bounce_admin_blocked_validate()
 * @see bounce_admin_blocked_submit()
 * @ingroup forms
 */
function bounce_admin_blocked($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'bounce') . '/css/bounce.admin.css');
  $filter = isset($_SESSION['bounce_admin_blocked_filter']) ? $_SESSION['bounce_admin_blocked_filter'] : '';

  if (isset($form_state['bounce_unblock']) && $form_state['bounce_unblock']) {
    // Confirmation form for unblocking emails.
    $result = db_select('bounce_blocked', 'b')
      ->fields('b', array('blocked_id', 'mail'))
      ->condition('b.blocked_id', $form_state['bounce_unblock'], 'IN')
      ->execute()
      ->fetchAllAssoc('blocked_id', PDO::FETCH_ASSOC);

    $form['unblocked'] = array(
      '#prefix' => '<ul>',
      '#suffix' => '</ul>',
      '#tree' => TRUE,
    );
    foreach ($result as $row) {
      $form['unblocked'][$row['blocked_id']] = array(
        '#type' => 'hidden',
        '#value' => check_plain($row['blocked_id']),
        '#prefix' => '<li>',
        '#suffix' => check_plain($row['mail']) . '</li>' . "\n",
      );
    }

    $confirm_question = format_plural(
      count($result),
      'Are you sure you want to unblock this mail?',
      'Are you sure you want to unblock these mails?'
    );
    $form = confirm_form(
      $form,
      $confirm_question,
      'admin/config/people/bounce/blocked',
      t('This action cannot be undone.'),
      t('Unblock'),
      t('Cancel')
    );

    $form['#submit'][] = 'bounce_admin_unblock_mails';
  }
  else {
    // A form to list blocked mails by page.
    $header = array(
      array('data' => t('Mail'), 'field' => 'mail', 'sort' => 'ASC'),
      array('data' => t('User'), 'field' => 'uid'),
      array('data' => t('Blocked Timestamp'), 'field' => 'created'),
      t('View Non-Delivery Reports'),
    );
    $query = db_select('bounce_blocked', 'b');
    $query->leftJoin('users', 'u', 'b.mail = u.mail');
    if ($filter) {
      $query->condition('b.mail', '%' . $filter . '%', 'LIKE');
    }
    $result = $query->fields('b', array('blocked_id', 'mail', 'created'))
      ->fields('u', array('name', 'uid'))
      ->extend('PagerDefault')
      ->limit(50)
      ->extend('TableSort')
      ->orderByHeader($header)
      ->execute()
      ->fetchAllAssoc('blocked_id', PDO::FETCH_ASSOC);
    $options = array();
    foreach ($result as $blocked_id => $row) {
      $options[$blocked_id] = array(
        check_plain($row['mail']),
        $row['uid'] ? l($row['name'], 'user/' . $row['uid']) : t('No user with this mail'),
        format_date($row['created']),
        l(t('View non-delivery reports'), 'admin/config/people/bounce/blocked/' . $blocked_id),
      );
    }

    // The ordering of form elements and their css is largely to ensure that
    // the Filter submit is the first in order in the form HTML, even though
    // it doesn't appear first in order on the page. This is so that a submit
    // on enter of the filterfield textfield will cause op=Filter rather than
    // one of the other possible op values.
    $form['top'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('bounce-blocked-form-top', 'clearfix'),
      ),
    );
    $form['top']['top-right'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('right', 'clearfix'),
      ),
    );
    $form['top']['top-right']['filterfield'] = array(
      '#type' => 'textfield',
      '#default_value' => $filter,
      '#size' => 15,
    );
    $form['top']['top-right']['filter'] = array(
      '#type' => 'submit',
      '#value' => t('Filter'),
      '#attributes' => array(
        'class' => array('left'),
      ),
    );
    $form['top']['top-right']['clear'] = array(
      '#type' => 'submit',
      '#value' => t('Clear'),
      '#attributes' => array(
        'class' => array('left'),
      ),
    );
    $form['top']['unblock'] = array(
      '#type' => 'submit',
      '#value' => t('Unblock selected mails'),
      '#attributes' => array(
        'class' => array('left'),
      ),
    );
    $form['mails'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => $filter ? t('No blocked email addresses match the filter.') : t('No email addresses are blocked.'),
    );

    $form['pager'] = array(
      '#markup' => theme('pager'),
    );

  }

  return $form;
}

/**
 * Form validation handler for bounce_admin_blocked().
 *
 * @see bounce_admin_blocked_submit()
 */
function bounce_admin_blocked_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['op'] == t('Unblock selected mails')) {
    $block_at_least_one = FALSE;
    if ($values['mails']) {
      foreach ($values['mails'] as $blocked_id) {
        if ($blocked_id) {
          $block_at_least_one = TRUE;
          break;
        }
      }
    }
    if (!$block_at_least_one) {
      form_set_error('', t('No mails were selected to unblock.'));
    }
  }
}

/**
 * Form submission handler for bounce_admin_blocked().
 *
 * @see bounce_admin_blocked_validate()
 */
function bounce_admin_blocked_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['op'] == t('Filter')) {
    $_SESSION['bounce_admin_blocked_filter'] = $values['filterfield'];
  }
  elseif ($values['op'] == t('Clear')) {
    unset($_SESSION['bounce_admin_blocked_filter']);
  }
  elseif ($values['op'] == t('Unblock selected mails')) {
    // We have to send off to a delete confirmation page; marshal up the list
    // of things to show on that page.
    $form_state['bounce_unblock'] = array();
    foreach ($values['mails'] as $blocked_id) {
      if ($blocked_id) {
        $form_state['bounce_unblock'][] = $blocked_id;
      }
    }
    // Send back to the form page to show a confirmation.
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Form submission handler for the unblock mails confirmation form.
 *
 * This deletes the blocked mails from the database, as well as any
 * non-delivery reports that were used to block them.
 */
function bounce_admin_unblock_mails($form, &$form_state) {
  $blocked_ids = array_keys($form_state['values']['unblocked']);

  // A list of the mails we're deleting.
  $mails = db_select('bounce_blocked', 'b')
    ->fields('b', array('mail'))
    ->condition('b.blocked_id', $blocked_ids, 'IN')
    ->execute()
    ->fetchCol();

  // Delete them.
  db_delete('bounce_blocked')
    ->condition('blocked_id', $blocked_ids, 'IN')
    ->execute();

  // And delete any non-delivery reports marked used associated with them.
  db_delete('bounce_non_delivery_report')
    ->condition('mail', $mails, 'IN')
    ->condition('status', BOUNCE_NDR_STATUS_USED, '=')
    ->execute();

  drupal_set_message(format_plural(count($form_state['values']['unblocked']), 'Unblocked 1 mail.', 'Unblocked @count mails'));
  module_invoke_all('bounce_mails_unblocked', $mails);
}

/*
 -----------------------------------------------------------------------
 Admin pages for viewing non-delivery reports.
 -----------------------------------------------------------------------
*/

/**
 * A page callback for the list of all non-delivery reports.
 */
function bounce_admin_view_non_delivery_report_list() {
  $header = array(
    array('data' => t('Mail'), 'field' => 'mail', 'sort' => 'ASC'),
    array('data' => t('User'), 'field' => 'uid'),
    array('data' => t('Timestamp'), 'field' => 'created'),
    array('data' => t('Analyst'), 'field' => 'analyst'),
    array('data' => t('Code'), 'field' => 'code'),
    array('data' => t('Used to Block?'), 'field' => 'status'),
    t('View Report'),
  );
  $rows = array();
  $query = db_select('bounce_non_delivery_report', 'ndr');
  $query->leftJoin('users', 'u', 'ndr.mail = u.mail');
  $result = $query->fields('ndr', array(
    'report_id',
    'mail',
    'code',
    'analyst',
    'status',
    'created',
  ))
    ->fields('u', array('name', 'uid'))
    ->extend('PagerDefault')
    ->limit(50)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->execute()
    ->fetchAllAssoc('report_id', PDO::FETCH_ASSOC);
  $options = array();
  foreach ($result as $report_id => $row) {
    $rows[] = array(
      check_plain($row['mail']),
      $row['uid'] ? l($row['name'], 'user/' . $row['uid']) : t('No user with this mail'),
      format_date($row['created']),
      check_plain($row['analyst']),
      check_plain($row['code']),
      ($row['status'] == BOUNCE_NDR_STATUS_USED) ? t('Yes') : t('No'),
      l(t('View non-delivery report'), 'admin/config/people/bounce/ndr/nojs/' . $report_id),
    );
  }

  $page = array();
  $page['list'] = array(
    array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t(
        'No non-delivery reports have been received and successfully analyzed within the last @days.',
        array(
          '@days' => format_plural(
            variable_get('bounce_max_report_age_days', BOUNCE_DEFAULT_MAX_REPORT_AGE_DAYS),
            '1 day',
            '@count days'
          ),
        )
      ),
    ),
    array(
      '#theme' => 'pager',
    ),
  );
  return $page;
}

/**
 * Present a table of non-delivery reports associated with a blocked mail.
 *
 * Text of the report emails is loaded via ajax.
 *
 * @param array $blocked_mail
 *   A associative array containing the column names and values for a single
 *   row from the bounce_blocked table.
 */
function bounce_admin_view_blocked_mail($blocked_mail) {
  drupal_set_title(t('View non-delivery reports for @mail', array('@mail' => $blocked_mail['mail'])));
  drupal_add_css(drupal_get_path('module', 'bounce') . '/css/bounce.admin.css');
  $page = array();

  $header = array(
    t('Code'),
    t('Analyst'),
    t('Timestamp'),
    t('View'),
  );
  $rows = array();

  $reports = db_select('bounce_non_delivery_report', 'ndr')
    ->fields('ndr', array('report_id', 'code', 'analyst', 'created'))
    ->condition('ndr.mail', $blocked_mail['mail'], '=')
    ->condition('ndr.status', BOUNCE_NDR_STATUS_USED, '=')
    ->execute()
    ->fetchAllAssoc('report_id', PDO::FETCH_ASSOC);

  foreach ($reports as $report_id => $report) {
    $ajax_link = array(
      'data' => array(
        '#type' => 'link',
        '#title' => t('View'),
        '#href' => 'admin/config/people/bounce/ndr/nojs/' . $report_id,
        '#ajax' => array(
          'wrapper' => 'bounce-report-wrapper',
          'method' => 'replace',
          'effect' => 'fade',
          'progress' => array(
            // Suppress the throbber/message rather than try to figure out how
            // to accomodate it in the table.
            'message' => '',
          ),
        ),
      ),
    );

    $rows[] = array(
      check_plain($report['code']),
      check_plain($report['analyst']),
      format_date($report['created']),
      $ajax_link,
    );
  }

  $page['summary']['table'] = array(
    '#prefix' => '<div id="bounce-reports-table-wrapper">',
    '#suffix' => '</div>',
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  $page['report'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'id' => 'bounce-report-wrapper',
    ),
  );

  return $page;
}

/**
 * Page callback to view a specific non-delivery report.
 *
 * The page can be returned as AJAX or a normal page render array.
 *
 * @param string $call_type
 *   Values 'ajax' or 'nojs' to show whether this an ajax call or not.
 * @param array $report_row
 *   An associative array representation of a row from the report table.
 */
function bounce_admin_view_non_delivery_report($call_type, $report_row) {
  $page = array();
  $report = $report_row['report'];

  // Mail headers first.
  $header_part = array_shift($report);
  $header = array(
    t('Mail Header'),
    t('Value'),
  );
  $rows = array();
  foreach ($header_part['data'] as $name => $value) {
    $rows[] = array(check_plain($name), check_plain($value));
  }
  $page['headers'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  // Now the rest of the mail parts.
  foreach ($report as $index => $part) {
    $header = array(
      t('Mail Part @part', array('@part' => $index + 1)),
    );
    $rows = array(
      array(preg_replace('/\r?\n/', '<br/>', check_plain($part['data']))),
    );
    $page['part' . $index] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    );
  }

  // What we return depends on whether this is an ajax call or not.
  if ($call_type == 'ajax') {
    // Wrap the report with the div the resulting HTML will be replacing.
    $page['#prefix'] = '<div id="bounce-report-wrapper">';
    $page['#suffix'] = '</div>';
    $commands = array(
      ajax_command_replace('#bounce-report-wrapper', drupal_render($page)),
    );
    ajax_deliver(array(
      '#type' => 'ajax',
      '#commands' => $commands,
    ));
  }
  else {
    // Set an appropriate title.
    drupal_set_title(t('Non-delivery report @id for @mail', array('@mail' => $report_row['mail'], '@id' => $report_row['report_id'])));
    return $page;
  }
}
