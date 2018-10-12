<?php

/**
 * @file
 * Code relating to processing a non-delivery report to establish the original
 * recipient email address and a code for the report.
 */

/*
 -----------------------------------------------------------------------
 General analysis functions that are not a part of the default analyst
 component.
 -----------------------------------------------------------------------
*/

/**
 * Store an analysis to the database if it contains anything worth storing.
 *
 * In order to be stored, there must be both a code and mail identified.
 *
 * @param array $analysis
 *   The analysis array to be stored.
 * @param string $analyst
 *   The machine name of the analyst component that performed the analysis.
 *
 * @param array $report
 *   The non-delivery report mail as an array data structure.
 */
function bounce_record_non_delivery_report_analysis($analysis, $analyst, $report) {
  $data = array(
    'code' => $analysis['code'],
    'mail' => $analysis['mail'],
    'analyst' => $analyst,
    'report' => $report,
    'status' => BOUNCE_NDR_STATUS_UNUSED,
    'created' => time(),
  );
  drupal_write_record('bounce_non_delivery_report', $data);
}

/**
 * Determine whether an analysis is complete.
 *
 * To be valid and complete, the analysis array should at minimum contain the
 * following:
 *
 * array(
 *   'code' => non-empty string
 *   'mail' => non-empty string
 * )
 *
 * @param array $analysis
 *   The analysis array as described above.
 *
 * @return boolean
 *   TRUE if the analysis array is complete, FALSE otherwise.
 */
function bounce_is_complete_non_delivery_report_analysis($analysis) {
  return isset($analysis['code']) && $analysis['code'] && isset($analysis['mail']) && $analysis['mail'];
}

/*
 -----------------------------------------------------------------------
 Callback functions for the default analyst component.
 -----------------------------------------------------------------------
*/

/**
 * Callback function for the default analyst component.
 *
 * Process a non-delivery report email. Or at least, process an email that may
 * or may not be a non-delivery report. Half the fun is figuring out whether
 * or not this email is even useful, as all sorts of unrelated junk tends to
 * turn up out of the blue into a Return-Path address account.
 *
 * The provided $report parameter must be an indexed array of message parts.
 * Each message part is in turn an array containing at least 'charset' and
 * 'data' keys as shown below. The first part will be headers, the rest body
 * and attachment parts. Different mail servers vary greatly as to how they
 * will arrange message parts, so be prepared to look through it all - even a
 * simple text body may be split up into several parts.
 *
 * $report = array(
 *  [0] => array(
 *    ['data'] => associative array of headers
 *    ['charset'] => the default encoding of the mail, and thus the headers
 *  ),
 *  [1] => array(
 *    ['data'] => string
 *    ['charset'] => the encoding of the string
 *  ),
 *  [2] => ...
 * )
 *
 * The response is an array containing at least:
 *
 * array(
 *   'code' => $code or ''
 *   'mail' => $mail or ''
 * )
 *
 * @param array $report
 *   The non-delivery report mail as an array.
 *
 * @return array
 *   The analysis of the report.
 */
function bounce_analyze_non_delivery_report($report) {
  $analysis = array(
    'header_id' => '',
    'code' => '',
    'mail' => '',
  );

  // Is this a valid and useful report?
  if (!is_array($report) || count($report) < 2) {
    return $analysis;
  }

  /*
  ---------------------------------------------------------------
  Look through the non-delivery report email headers first.
  ---------------------------------------------------------------
  */

  $header_part = array_shift($report);
  $headers = array();
  foreach ($header_part['data'] as $name => $value) {
    $headers[drupal_strtolower($name)] = $value;
  }

  // Autoreplies are surprisingly common ('out of office, contact later').
  // People need to stop doing this; it just generates clutter.
  if (bounce_analysis_is_autoreply($headers)) {
    $analysis['code'] = 'autoreply';
  }
  // Check to see whether this a standard ARF (abuse reporting format) email.
  else if (bounce_analysis_is_abuse_response_format($headers)) {
    $analysis['code'] = 'abusereport';
  }

  /*
  ---------------------------------------------------------------
  Now start in on the rest of it, and try to establish a code.

  We're looking for the identifying header from the original email that
  generated this non-delivery report, and also any SMTP codes or other
  information we can use to categorize the report.
  ---------------------------------------------------------------
  */

  // Determine a response code.
  if (!$analysis['code']) {
    foreach ($report as $part) {
      if ($analysis['code']) {
        break;
      }
      $analysis['code'] = bounce_analysis_code_from_text($part['data']);
    }
  }

  // Determine failed recipients.
  if (!$analysis['code'] && bounce_analysis_has_failed_recipients($headers)) {
    $analysis['code'] = '5.1.3';
  }

  // No code? Then give up; not much to be done here. This is expected to
  // happen: you'd be surprised at the outright strange and irrelevant email
  // that turns up in an account that is only used as a Return-Path catchall.
  if (!$analysis['code']) {
    return $analysis;
  }

  /*
  ---------------------------------------------------------------
  Now try to identify the email address for the originating email.
  ---------------------------------------------------------------
  */

  $ignored_mails = bounce_analysis_ignored_mails();

  // Try to find the original header ID that will link this non-delivery
  // report to an email address, or more than one email address if the
  // original was sent to multiple destinations.
  //
  // This may or may not work: not all non-delivery report formats include
  // the headers of the original mail.
  foreach ($report as $part) {
    $match = array();
    $matched = preg_match('/' . variable_get('bounce_mail_header_name', BOUNCE_DEFAULT_MAIL_HEADER_NAME) . '\s*:\s*([^\s\r\n]+)/', $part['data'], $match);
    if ($matched) {
      $analysis['header_id'] = $match[1];
      $mails = db_select('bounce_sent', 's')
        ->condition('s.header_id', $analysis['header_id'], '=')
        ->fields('s', array('mail'))
        ->execute()
        ->fetchCol();
      $count = count($mails);
      if ($count == 1) {
        // This matches one address, so we are done here.
        $analysis['mail'] = array_shift($mails);
        return $analysis;
      }
      elseif ($count > 1) {
        // More of a challenge: since the original email was sent to multiple
        // addresses, we have to be sure that we correctly determine which is
        // the problem child that generated this non-delivery report.
        //
        // So loop through the parts again and get counts of the various
        // addresses. Pick the one with the highest count. This isn't
        // completely foolproof, but it is the best option going short of much
        // more fiddly rules, checks, and rules within checks.
        $mail = bounce_analysis_get_most_frequent_mail($report, $ignored_mails, $mails);
        // Note that the return will be empty if the two highest counts are
        // tied - unlikely, but you never know.
        if ($mail) {
          $analysis['mail'] = $mail;
        }
        // Return in either case.
        return $analysis;
      }
    }
  }

  if ($use_vulnerable_search = variable_get('bounce_analyst_use_vulnerable_email_search')) {
    // If we don't have an email yet, then see if we can find one by more
    // direct means: find the most common email in the text and see if we
    // sent mail to it recently.
    //
    // Note that one reason for using UUIDs and a special header in the mail
    // is to make it hard for an attacker to send crafted mails to your
    // Return-Path address that will cause you to block future outgoing mails.
    // Not very likely, but why make it possible at all? When we move away from
    // UUID identifiers, we open that door.
    //
    // TODO: make this more sophisticated in an effort to avoid false positives
    // and attacks.
    //
    $mail = bounce_analysis_get_most_frequent_mail($report, $ignored_mails);
    if ($mail) {
      // Did we sent out an email within the last hour to this address? For the
      // reasons noted above, we want to ensure that this check is a short
      // timeline, to limit the opportunity for attacks using crafted emails
      // sent to the Return-Path address.
      $count = db_select('bounce_sent')
        ->condition('mail', $mail, '=')
        ->condition('created', time() - 3600, '>')
        ->countQuery()
        ->execute()
        ->fetchField();
      if ($count) {
        $analysis['mail'] = $mail;
        return $analysis;
      }
    }
  }

  return $analysis;
}

/**
 * Check to see if the email is an autoreply, based on the headers.
 *
 * @param array $headers
 *   A header associative array for a non-delivery report, values indexed by
 *   names.
 *
 * @return boolean
 *   TRUE if the headers indicate this to be an autoreply mail.
 */
function bounce_analysis_is_autoreply($headers) {
  return isset($headers['x-autoreply']);
}

/**
 * Check to see if the email provider added a header indicating one or more
 * failed recipients. Google does this, for example.
 *
 * @param array $headers
 *   A header associative array for a non-delivery report, values indexed by
 *   names.
 *
 * @return boolean
 *   TRUE if the headers contain failed recipients.
 */
function bounce_analysis_has_failed_recipients($headers) {
  return isset($headers['x-failed-recipients']);
}

/**
 * Check to see if the email is an ARF (abuse reporting format) notice.
 *
 * For an overview of ARF, see:
 * https://en.wikipedia.org/wiki/Abuse_Reporting_Format
 * http://tools.ietf.org/html/rfc5965
 *
 * This looks at the headers only, and so cannot determine the type of the ARF,
 * but that's acceptable as they are all bad news. The type and other details
 * will be buried in the other mail parts.
 *
 * @param array $headers
 *   A header associative array for a non-delivery report, values indexed by
 *   names.
 *
 * @return boolean
 *   TRUE if the headers indicate this to be an ARF notice.
 */
function bounce_analysis_is_abuse_response_format($headers) {
  # Pretty unlikely, but paranoia never hurts.
  if (!isset($headers['content-type'])) {
    return false;
  };

  return preg_match('/report-type=feedback-report/i', $headers['content-type']);
}

/**
 * Determine a bounce code given text from a non-delivery report.
 *
 * This is a helper function to parse out an SMTP response code or other sort
 * of code from text. In the grand scheme of things this is not a very
 * sophisticated approach. For a much more sophisticated consideration, you
 * might look at something like the BounceHandler class:
 *
 * https://github.com/cfortune/PHP-Bounce-Handler
 *
 * But the contention here is that you can get by with comparatively little
 * sophistication if all you want is to avoid looking like a spam source.
 *
 * @param string $text
 *   The text that may contain a non-delivery code.
 *
 * @return string
 *   The first matched response code or an empty string if none found.
 */
function bounce_analysis_code_from_text($text) {
  $code = '';
  $matches = array();
  // RFC 1893 return code e.g. 5.1.1 or similar.
  if (preg_match('/\b([45]\.[01234567]\.[012345678])\b/', $text, $matches)) {
    $code = $matches[1];
  }
  // RFC 821 return code e.g. 550 or similar.
  if (!$code && preg_match('/\b([45][01257][012345])\b/', $text, $matches)) {
    $code = $matches[1];
  }

  // The regex below is intended to match key words from spam blocker notices
  // without matching x-spam* headers if they are fed back in the response, as
  // they are often irrelevant.
  $spam_match_regex = '/[^\B\-](spam|blocked|rejected)\b/i';

  // If this is a 5** code and it looks like a spam filter response, then put
  // it into a different bucket. Spam filter responses are often false
  // positives but may send back 550 or other permanent failure type codes.
  // Unless you are in fact sending spam, these will be false positives and
  // should not be respected - but should be noted. If you are generating a lot
  // of them, that indicates that you should be paying attention to email
  // contents.
  $matches = array();
  if ($code && preg_match('/^5/', $code) && preg_match_all($spam_match_regex, $text, $matches) > 1) {
    $code = 'spamfilter';
  }

  if ($code) {
    return $code;
  }

  // An annoyingly common greylisting case with no SMTP code. May no longer be
  // relevant, but can't hurt to keep it around.
  if (preg_match('/YOU DO NOT NEED TO RESEND YOUR MESSAGE|delivery temporarily suspended/i', $text)) {
    $code = 'greylist';
    return $code;
  }

  // Another check on the spam filter case. This will probably match more than
  // it should, but seems worth trying given the structure of most non-delivery
  // responses.
  if (preg_match_all($spam_match_regex, $text, $matches) > 1) {
    $code = 'spamfilter';
  }

  // Check for DNS Error if domain name could not be found. Some providers will
  // give an error code, but Google annoyingly does not.
  if (preg_match('/DNS Error|Domain name not found/i', $text)) {
    $code = '5.4.0';
  }

  return $code;
}

/**
 * Obtain the most frequently referenced mail from a non-delivery report.
 *
 * Check all the non-header sections of a bounce report data structure, and
 * count the instances of specific email addresses.
 *
 * @param array $report
 *   A non-delivery report data structure.
 * @param array $ignored_emails
 *   (optional) An indexed array of email addresses. These are ignored for the
 *   purpose of finding the more frequently occuring email.
 * @param array $filter_emails
 *   (optional) An indexed array of email addresses: if not empty, only count
 *   instances of these email addresses. Otherwise count them all.
 *
 * @return mixed
 *   FALSE on failure to find the most frequent, or the email address
 *   otherwise.
 */
function bounce_analysis_get_most_frequent_mail($report, $ignored_emails = array(), $filter_emails = array()) {
  $filter_emails = array_flip(array_unique($filter_emails));
  $ignored_emails = array_flip(array_unique($ignored_emails));
  $counts = array();
  foreach ($report as $part) {
    if (is_string($part['data'])) {
      $part_counts = array_count_values(bounce_mails_from_text($part['data']));
      if ($filter_emails) {
        $part_counts = array_intersect_key($part_counts, $filter_emails);
      }
      foreach ($part_counts as $email => $count) {
        if (!isset($counts[$email])) {
          $counts[$email] = $count;
        }
        else {
          $counts[$email] += $count;
        }
      }
    }
  }

  // Strip out the ignored emails.
  $counts = array_diff_key($counts, $ignored_emails);

  if (empty($counts)) {
    return FALSE;
  }
  elseif (count($counts) == 1) {
    return key($counts);
  }
  else {
    // Sort the array so that the largest count is at the end, and look at the
    // two largest counts.
    asort($counts);
    $max_count = end($counts);
    $max_email = key($counts);
    $second_max_count = prev($counts);
    if ($max_count == $second_max_count) {
      // If the two largest counts are equal, then we can't declare a most
      // frequent email.
      return FALSE;
    }
    else {
      // Otherwise return the final email in the array.
      return $max_email;
    }
  }
}

/**
 * Return an indexed array of ignored email addresses.
 *
 * These email addresses should be discarded and ignored while digging through
 * non-delivery reports.
 *
 * @return array
 *   An indexed array of email addresses.
 */
function bounce_analysis_ignored_mails() {
  $mails = array();
  $site_mail = variable_get('site_mail', ini_get('sendmail_from'));
  if ($site_mail) {
    $mails[] = $site_mail;
  }
  $admin = user_load(1);
  if (isset($admin->mail) && $admin->mail) {
    $mails[] = $admin->mail;
  }
  $configured_mails = explode(',', variable_get('bounce_analyst_ignored_mails', ''));
  foreach ($configured_mails as &$mail) {
    $mail = preg_replace('/^\s+|\s+$/', '', $mail);
  }
  $mails += $configured_mails;
  return array_unique($mails);
}

/**
 * Callback function to check on analyst configuration.
 *
 * @return boolean
 *   TRUE if configured.
 */
function bounce_analyst_is_configured() {
  // Always configured from the get-go. Defaults are sufficient.
  return TRUE;
}

/*
 -----------------------------------------------------------------------
 Settings form for the default analyst component.
 -----------------------------------------------------------------------
*/

/**
 * Form constructor for the default analyst component settings form.
 *
 * @see bounce_analyst_settings_validate()
 * @ingroup forms
 */
function bounce_analyst_settings($form, &$form_state) {
  $form['analyst'] = array(
    '#type' => 'fieldset',
    '#title' => t('Non-delivery report analysis settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['analyst']['bounce_analyst_use_vulnerable_email_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attempt to identify the recipient email address when the original header identifier is missing'),
    '#description' => t('Bounce assigns a unique ID to a header field in each piece of outgoing mail. Not all mail servers will send back those headers, however, which makes it harder to reliably identify the original recipient. One reason for using a header and unique ID in outgoing mails is to make it hard for an attacker to send crafted mails to your Return-Path address that will cause you to block future outgoing mails. Enabling this checkbox will allow more non-delivery reports to be processed successfully, but it will also enable this form of attack.'),
    '#default_value' => variable_get('bounce_analyst_use_vulnerable_email_search', FALSE),
  );
  $form['analyst']['bounce_analyst_ignored_emails'] = array(
    '#type' => 'textarea',
    '#title' => t('Ignored email addresses'),
    '#description' => t('Enter a comma-delimited list of email addresses. These will be ignored in any attempt to establish which email address out of many in a non-delivery report is the original recipient. This can be useful if your site uses mail templates that include one or more email addresses, for example.'),
    '#default_value' => variable_get('bounce_analyst_ignored_emails', implode(', ', bounce_analysis_ignored_mails())),
    '#rows' => 3,
  );
  $form = system_settings_form($form);
  $form['#validate'][] = 'bounce_analyst_settings_validate';
  return $form;
}

/**
 * Form validation handler for bounce_analyst_settings().
 */
function bounce_analyst_settings_validate($form, &$form_state) {
  if ($form_state['values']['bounce_analyst_ignored_emails']) {
    $mails = explode(',', $form_state['values']['bounce_analyst_ignored_emails']);
    foreach ($mails as $mail) {
      $mail = preg_replace('/^\s+|\s+$/', '', $mail);
      if (!valid_email_address($mail)) {
        form_set_error($mail, t('%mail is not a valid email address.', array('%mail' => $mail)));
      }
    }
  }
}
