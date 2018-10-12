<?php

/**
 * @file
 * Functions for the default blocker component, which manages determination of
 * which emails to block based on analyzed non-delivery report records.
 */

/**
 * Callback for the default blocker component.
 *
 * Find emails with a summed score from non-delivery reports to put them past
 * the threshold, and return them.
 *
 * @return array
 *   An indexed array of email addresses to to be blocked.
 */
function bounce_blocked() {

  $age_in_seconds = variable_get('bounce_max_age_days', BOUNCE_DEFAULT_MAX_REPORT_AGE_DAYS) * 86400;
  $time = time() - $age_in_seconds;

  // SQL to select summed non-delivery report scores greater than the
  // threshold, but only for mails that are not already blocked, and only
  // consider non-delivery reports that have not already been used to block a
  // mail. The latter condition takes into account the case where an admin
  // unblocks a blocked mail - we only want to reblock that mail if new
  // non-delivery reports turn up.
  $query = db_select('bounce_non_delivery_report', 'ndr');
  $query->innerJoin('bounce_code_score', 'cs', 'ndr.code = cs.code');
  $query->addExpression('SUM(cs.score)', 'score');
  $query->condition('ndr.status', BOUNCE_NDR_STATUS_UNUSED, '=');
  $query->addField('ndr', 'mail');
  $query->where('NOT EXISTS (SELECT 1 FROM {bounce_blocked} b WHERE b.mail = ndr.mail)');
  $query->groupBy('ndr.mail');
  $query->orderBy('score', 'DESC');
  $result = $query->execute();

  $mails = array();
  $threshold = variable_get('bounce_blocker_threshold_score', BOUNCE_DEFAULT_BLOCKER_THRESHOLD_SCORE);
  while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
    if ($row['score'] >= $threshold) {
      $mails[] = $row['mail'];
    }
  }

  return $mails;
}

/**
 * Callback function to check on blocker configuration.
 *
 * @return boolean
 *   TRUE if configured.
 */
function bounce_blocker_is_configured() {
  // Always configured from the get-go. Defaults are sufficient.
  return TRUE;
}

/*
 -----------------------------------------------------------------------
 Settings form for the default blocker component.
 -----------------------------------------------------------------------
*/

/**
 * Form constructor for the blocker component settings form.
 *
 * @see bounce_blocker_settings_validate()
 * @ingroup forms
 */
function bounce_blocker_settings($form, &$form_state) {

  $form['blocker'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mail blocker component settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['blocker']['bounce_blocker_threshold_score'] = array(
    '#type' => 'textfield',
    '#title' => t('Threshold score'),
    '#required' => TRUE,
    '#description' => t('An email address that has accumulated at least this many points in scored non-delivery reports will be blocked. No further emails of any sort will be sent.'),
    '#default_value' => variable_get('bounce_blocker_threshold_score', BOUNCE_DEFAULT_BLOCKER_THRESHOLD_SCORE),
  );
  $form = system_settings_form($form);
  $form['#validate'][] = 'bounce_blocker_settings_validate';
  return $form;
}

/**
 * Form validation handler for bounce_blocker_settings().
 */
function bounce_blocker_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!preg_match('/^\d+$/', $values['bounce_blocker_threshold_score'])) {
    form_set_error('bounce_blocker_threshold_score', t('Threshold score must be a whole number.'));
  }
}

/*
 -----------------------------------------------------------------------
 Form page for scoring and codes used by the default blocker component.
 -----------------------------------------------------------------------
*/

/**
 * Page callback to display a table of codes and scoring.
 */
function bounce_admin_scoring() {
  $page = array();

  // Build a table to show the existing scoring, with links to edit/delete.
  $codes = db_select('bounce_code_score', 'cs')
    ->fields('cs')
    ->orderBy('type', 'ASC')
    ->orderBy('code', 'ASC')
    ->execute()
    ->fetchAllAssoc('code', PDO::FETCH_ASSOC);
  $code_type_options = _bounce_admin_code_type_options();

  $header = array(
    t('Code'),
    t('Type'),
    t('Score'),
    t('Description'),
    t('Edit'),
    t('Delete'),
  );
  $rows = array();
  foreach ($codes as $code) {
    $rows[] = array(
      check_plain($code['code']),
      isset($code_type_options[$code['type']]) ? $code_type_options[$code['type']] : t('Unknown'),
      check_plain($code['score']),
      check_plain($code['description']),
      l(t('Edit'), 'admin/config/people/bounce/scoring/' . $code['code'] . '/edit'),
      l(t('Delete'), 'admin/config/people/bounce/scoring/' . $code['code'] . '/delete'),
    );
  }

  $item_list = array(
    'items' => array(
      l(t('Add new code'), 'admin/config/people/bounce/scoring/add'),
    ),
    'attributes' => array(
      'class' => array('action-links'),
    ),
  );

  $page['add_link'] = array(
    '#prefix' => '<ul class="action-links"><li>',
    '#markup' => l(t('Add new code'), 'admin/config/people/bounce/scoring/add'),
    '#suffix' => '</li></ul>',
  );
  $page['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $page;
}

/**
 * Form constructor for the code scoring editing form.
 *
 * @see bounce_admin_edit_code_validate()
 * @see bounce_admin_edit_code_submit()
 * @ingroup forms
 */
function bounce_admin_edit_code($form, &$form_state, $data = NULL) {
  if ($data) {
    $form['code_is_new'] = array(
      '#type' => 'value',
      '#value' => FALSE,
    );
    $form['code'] = array(
      '#type' => 'value',
      '#value' => $data['code'],
    );
    $form['code_item'] = array(
      '#type' => 'item',
      '#title' => t('Code'),
      '#markup' => check_plain($data['code']),
    );
  }
  else {
    $form['code_is_new'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
    $form['code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code'),
      '#required' => TRUE,
      '#description' => t('The identifying name for this code.'),
    );
  }

  $form['score'] = array(
    '#type' => 'textfield',
    '#title' => t('Score'),
    '#required' => TRUE,
    '#description' => t('The score for each instance of a non-delivery report associated with this code.'),
    '#default_value' => isset($data['score']) ? $data['score'] : '',
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => _bounce_admin_code_type_options(),
    '#default_value' => isset($data['type']) ? $data['type'] : '',
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Enter a short description for the non-delivery report code.'),
    '#default_value' => isset($data['description']) ? $data['description'] : '',
  );

  $form['op'] = array(
    '#type' => 'submit',
    '#value' => $data ? t('Update') : t('Create'),
  );

  return $form;
}

/**
 * Form validation handler for bounce_admin_edit_code().
 *
 * @see bounce_admin_edit_code_submit()
 */
function bounce_admin_edit_code_validate($form, &$form_state) {
  if (!preg_match('/^\d+$/', $form_state['values']['score'])) {
    form_set_error('score', t('Score must be a whole number.'));
  }
  if ($form_state['values']['code_is_new']) {
    $code = bounce_admin_code_machine_name($form_state['values']['code']);
    $count = db_select('bounce_code_score')
      ->condition('code', $code, '=')
      ->countQuery()
      ->execute()
      ->fetchField();
    if ($count) {
      form_set_error('code', t('The code %code already exists.', array('%code' => $form_state['values']['code'])));
    }
  }
}

/**
 * Form submission handler for bounce_admin_edit_code().
 *
 * @see bounce_admin_edit_code_validate()
 */
function bounce_admin_edit_code_submit($form, &$form_state) {
  $values = $form_state['values'];
  $data = array(
    'code' => $values['code'],
    'score' => $values['score'],
    'type' => $values['type'],
    'description' => $values['description'],
  );
  if ($values['code_is_new']) {
    // Turn user input into something we can put into a path.
    $data['code'] = bounce_admin_code_machine_name($data['code']);
    drupal_write_record('bounce_code_score', $data);
    drupal_set_message(t('The code %code has been created.', array('%code' => $data['code'])));
  }
  else {
    drupal_write_record('bounce_code_score', $data, 'code');
    drupal_set_message(t('The code %code has been updated.', array('%code' => $data['code'])));
  }
  $form_state['redirect'] = 'admin/config/people/bounce/scoring';
}

/**
 * Create a machine name from a user-entered name for a code.
 *
 * @param string $code
 *   The user enterend code.
 *
 * @return string
 *   A machine name version of the code.
 */
function bounce_admin_code_machine_name($code) {
  return preg_replace('/[^a-z0-9_\.]+/', '_', drupal_strtolower($code));
}

/**
 * Form constructor for the code deletion confirmation.
 *
 * @param array $data
 *   An associative array containing the code to delete.
 *
 * @see bounce_admin_delete_code_submit()
 * @ingroup forms
 */
function bounce_admin_delete_code($form, &$form_state, $data) {
  $form['code'] = array(
    '#type' => 'value',
    '#value' => $data['code'],
  );
  return confirm_form($form,
    t('Are you sure you want to delete the code %code?', array('%code' => $data['code'])),
    'admin/config/people/bounce/scoring',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for bounce_admin_delete_code().
 */
function bounce_admin_delete_code_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $code = $form_state['values']['code'];
    db_delete('bounce_code_score')
      ->condition('code', $code, '=')
      ->execute();
    drupal_set_message(t('The code %code has been deleted.', array('%code' => $code)));
  }
  $form_state['redirect'] = 'admin/config/people/bounce/scoring';
}

/**
 * Return an array of code types suitable for use in a select.
 *
 * @return array
 *   An associative array of $type_id => $type_title.
 */
function _bounce_admin_code_type_options() {
  $options = &drupal_static(__FUNCTION__);
  if (!isset($options)) {
    $types = module_invoke_all('bounce_code_type');
    drupal_alter('bounce_code_type', $types);
    $options = array();
    foreach ($types as $type_id => $type) {
      $options[$type_id] = $type['title'];
    }
  }
  return $options;
}
