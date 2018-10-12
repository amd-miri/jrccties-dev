<?php

/**
 * @file
 * Definition of BounceTestMailServerConnector.
 */

/**
 * A test class for faking a connection to a mail server account via the IMAP
 * package. It makes no pretensions to being comprehensive or a good test for
 * general use in connecting to a mailbox: it just fakes the small slice of
 * IMAP package functionality that is important to this module.
 */
class BounceTestMailServerConnector extends BounceMailServerConnector {

  /**
   * Stores simulated error messages for imap_last_error().
   */
  public $lastErrorMessage = FALSE;

  /**
   * Boolean switch for simulating failure of imap_close().
   */
  public $failImapClose = FALSE;
  /**
   * Boolean switch for simulating failure of imap_open().
   */
  public $failImapOpen = FALSE;
  /**
   * Boolean switch for simulating failure of imap_timeout().
   */
  public $failImapTimeout = FALSE;

  /**
   * Overrides BounceMailServerConnector::__construct().
   */
  public function __construct($params) {
    parent::__construct($params);
  }

  /*
  -----------------------------------------------------------------------
  Mail templates.
  -----------------------------------------------------------------------
  */

  /**
   * The upper level overview data for a mail.
   */
  public $mailOverviewGeneric = array(

    // Overview fields.
    'subject' => 'the messages subject - irrelevant here since it is not used for analysis',
    'from' => 'mail-daemon@example.com',
    'to' => 'bounce@mydomain.com',
    'date' => NULL,
    'deleted' => FALSE,

    // Overview fields that can or will be set later.
    /*
    'msgno'       - message sequence number in the mailbox
    */

    // Overview fields we don't use but which can exist in a real mailbox.
    /*
    'message_id' - Message-ID
    'references' - is a reference to this message id
    'in_reply_to' - is a reply to this message id
    'size' - size in bytes
    'uid' - UID the message has in the mailbox
    'recent' - this message is flagged as recent
    'flagged' - this message is flagged
    'answered' - this message is flagged as answered
    'seen' - this message is flagged as already read
    'draft' - this message is flagged as being a draft
    */

    // Fields that don't exist in a real mailbox, but are here holding data.
    'parts' => NULL,
  );

  /**
   * Generate a data structure for a non-delivery report email.
   *
   * These are stored locally. The text will be non-real, but sufficient to
   * exercise module code.
   *
   * @param string $smtp_code
   *   The code that should be extracted from the mail.
   * @param string $recipient_email_address
   *   The email address of the original recipient.
   *
   * @return array
   *   A mail data structure for the fake mailbox.
   */
  public function generateSMTPNonDeliveryReport($smtp_code, $recipient_email_address) {
    $parts = array();
    // Headers are largely irrelevant for our purposes, so use dummy values.
    $headers_part = array(
      'data' => '',
      'charset' => 'utf-8',
    );
    $headers = array(
      'header1' => 'value1',
      'header2' => 'value2',
    );
    foreach ($headers as $name => $value) {
      $headers_part['data'] .= $name . ': ' . $value . "\n";
    }
    $parts[] = $headers_part;
    // Add two sections to the body.
    $parts[] = array(
      'data' => 'blah blah ' . $smtp_code . ' blah blah',
      'charset' => 'utf-8',
    );
    $parts[] = array(
      'data' => 'blah blah ' . $recipient_email_address . ' blah blah',
      'charset' => 'utf-8',
    );

    $report = $this->mailOverviewGeneric;
    $report['parts'] = $parts;
    return $report;
  }

  /*
  -----------------------------------------------------------------------
  Methods for managing test mail data.
  -----------------------------------------------------------------------
  */

  /**
   * Return the mailbox.
   *
   * @return array
   *   The mailbox.
   */
  public function loadMailbox() {
    return variable_get('bounce_test_connector_mailbox', array());
  }

  /**
   * Store the updated mailbox.
   *
   * @param array $mailbox
   *   The mailbox.
   */
  public function storeMailbox($mailbox) {
    variable_set('bounce_test_connector_mailbox', $mailbox);
  }

  /**
   * Reset the mailbox for a new test run.
   */
  public function resetMailbox() {
    variable_set('bounce_test_connector_mailbox', array());
  }

  /**
   * Remove all messages from the fake mailbox.
   */
  public function removeMessagesFlaggedForDeletion() {
    $mailbox = $this->loadMailbox();
    foreach ($mailbox as $index => $mail) {
      if ($mail['deleted']) {
        unset($mailbox[$index]);
      }
    }

    // And reorder the numbering on the mailbox.
    $ordered_mailbox = array();
    foreach ($mailbox as $mail) {
      if (!count($ordered_mailbox)) {
        $ordered_mailbox[1] = $mail;
      }
      else {
        $ordered_mailbox[] = $mail;
      }
    }
    $this->storeMailbox($ordered_mailbox);
  }

  /**
   * Add a mail message to the fake mailbox.
   *
   * @param array $mail
   *   A mail array as built by generateSMTPNonDeliveryReport().
   */
  public function deliverMail($mail) {
    $mailbox = $this->loadMailbox();
    // Machinations to ensure the index is 1-based.
    if (empty($mailbox)) {
      $index = 1;
    }
    else {
      $index = max(array_keys($mailbox)) + 1;
    }
    $mail['msgno'] = $index;
    $mail['deleted'] = FALSE;
    $mailbox[$index] = $mail;
    $this->storeMailbox($mailbox);
  }

  /*
  -----------------------------------------------------------------------
  Redeclarations to make properties public and thus accessible for testing.
  -----------------------------------------------------------------------
  */

  public $server = NULL;
  public $port = NULL;
  public $protocol = NULL;
  public $encryption = '';
  public $login = NULL;
  public $password = NULL;
  public $folder = NULL;

  /**
   * Overrides BounceMailServerConnector::parseMailHeadersIntoArray().
   */
  public function parseMailHeadersIntoArray($headers) {
    return parent::parseMailHeadersIntoArray($headers);
  }

  /**
   * Overrides BounceMailServerConnector::mailGetParts().
   */
  public function mailGetParts($message_number, $part, $prefix) {
    return parent::mailGetParts($message_number, $part, $prefix);
  }

  /**
   * Overrides BounceMailServerConnector::mailDecodePart().
   */
  public function mailDecodePart($message_number, $part, $prefix) {
    return parent::mailDecodePart($message_number, $part, $prefix);
  }

  /*
  -----------------------------------------------------------------------
  Wrapper methods to generate responses as though from IMAP package
  functions.
  -----------------------------------------------------------------------
  */

  /**
   * Overrides BounceMailServerConnector::imapBody().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_body()
   */
  public function imapBody($message_number, $options = NULL) {
    // Munge the message sections together; not terribly realistic, but fine
    // for testing here.
    //
    // this fake behavior is probably very different from what happens in
    // reality when you try imap_body on a multipart message. But since we only
    // try imap_body on non-multipart messages that shouldn't matter all that
    // much.
    $mailbox = $this->loadMailbox();
    if (isset($mailbox[$message_number])) {
      $body = array();
      foreach ($mailbox[$message_number]['parts'] as $part) {
        if (is_string($part['data'])) {
          $body[] = $part['data'];
        }
      }
      return implode("\n\n", $body);
    }
    return NULL;
  }

  /**
   * Overrides BounceMailServerConnector::imapCheck().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_check()
   */
  public function imapCheck() {
    $mailbox = $this->loadMailbox();
    return (object) array(
      'Date' => date(DateTime::RFC2822),
      'Driver' => drupal_strtoupper($this->protocol),
      'Mailbox' => $this->folder,
      'Nmsgs' => count($mailbox),
      'Recent' => count($mailbox),
    );
  }

  /**
   * Overrides BounceMailServerConnector::imapClose().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   *  of a real server.
   *
   * @see imap_close()
   */
  public function imapClose($flag) {
    if ($this->failImapClose) {
      $this->lastErrorMessage = 'imap_close() set to fail';
      return FALSE;
    }
    else {
      if ($flag == CL_EXPUNGE) {
        $this->removeMessagesFlaggedForDeletion();
      }
      return TRUE;
    }
  }

  /**
   * Overrides BounceMailServerConnector::imapDelete().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_delete()
   */
  public function imapDelete($message_number) {
    $mailbox = $this->loadMailbox();
    if (isset($mailbox[$message_number])) {
      $mailbox[$message_number]['deleted'] = TRUE;
    }
    $this->storeMailbox($mailbox);
  }

  /**
   * Overrides BounceMailServerConnector::imapFetchOverview().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_fetch_overview()
   */
  public function imapFetchOverview($range) {
    $mailbox = $this->loadMailbox();
    if (preg_match('/:/', $range)) {
      list($start, $end) = explode(':', $range);
      $mails = array();
      foreach ($mailbox as $message_number => $mail) {
        if ($message_number >= $start && $message_number <= $end) {
          $mails[$message_number] = $mail;
        }
      }
    }
    else {
      $message_numbers = explode(',', $range);
      $message_numbers = array_flip($message_numbers);
      $mails = array_intersect_key($mailbox, $message_numbers);
    }

    foreach ($mails as &$mail) {
      unset($mail['parts']);
      $mail = (object) $mail;
    }
    return array_values($mails);
  }

  /**
   * Overrides BounceMailServerConnector::imapFetchbody().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_fetchbody()
   */
  public function imapFetchbody($message_number, $prefix) {
    $mailbox = $this->loadMailbox();
    if (isset($mailbox[$message_number])) {
      $parts = $mailbox[$message_number]['parts'];
      $headers = array_shift($parts);

      if ($prefix === '0') {
        return $headers['data'];
      }
      else {
        // Assuming only one level in the prefix (e.g. it might be 0, 1, 2,
        // etc and not 1.1, 2.3, etc) - which is not the case in reality,
        // but is fine for these fake mails.
        if (isset($parts[((int) $prefix) - 1])) {
          return $parts[((int) $prefix) - 1]['data'];
        }
        else {
          return NULL;
        }
      }
    }
    else {
      return NULL;
    }
  }

  /**
   * Overrides BounceMailServerConnector::imapFetchheader().
   *
   * Wrapper method that (incompletely, probably badly) simulates the
   * response of a real server.
   *
   * @see imap_fetchheader()
   */
  public function imapFetchheader($message_number, $options = 0) {
    $mailbox = $this->loadMailbox();
    if (isset($mailbox[$message_number]['parts'][0]['data'])) {
      return $mailbox[$message_number]['parts'][0]['data'];
    }
    else {
      return NULL;
    }
  }

  /**
   * Overrides BounceMailServerConnector::imapFetchstructure().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server. Of all these wrapper functions, this is probably the one
   * that most butchers and oversimplifies what a real response can look like.
   *
   * @see imap_fetchstructure()
   */
  public function imapFetchstructure($message_number, $options = NULL) {
    $mailbox = $this->loadMailbox();
    if (isset($mailbox[$message_number])) {
      // Turning a one-level array (the parts of the mail message data) into a
      // two-level structure of objects. For the purposes of this test harness,
      // we'll treat a one-section-after-header mail as having primary body
      // type = 0 (text) and two-or-more-sections-after-header mails as having
      // primary body type = 1 (multipart).
      //
      // Body type 0 is a single object with no children, not even the remaining
      // body part Body type 1 is an object with a child object for each part
      // following the headers.
      $parts = $mailbox[$message_number]['parts'];
      $headers = array_shift($parts);
      $structure = (object) array(
        // Type 0 = text.
        'type' => 0,
      );
      if (count($parts) > 1) {
        // Multipart (very fake, broken, lacking-vital-params multipart
        // in this case).
        $structure->type = 1;
        foreach ($parts as $index => $part) {
          $structure->parts[] = (object) array(
            // Text.
            'type' => 0,
            // This should absolutely NOT be drupal_strlen - we're counting
            // bytes, not characters.
            'bytes' => mb_strlen($part['data'], 'latin1'),
          );
        }
      }
      return $structure;
    }
    else {
      return NULL;
    }
  }

  /**
   * Overrides BounceMailServerConnector::imapLastError().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_last_error()
   */
  public function imapLastError() {
    return $this->lastErrorMessage;
  }

  /**
   * Overrides BounceMailServerConnector::imapMailboxmsginfo().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_mailboxmsginfo()
   */
  public function imapMailboxmsginfo() {
    $mailbox = $this->loadMailbox();
    $deleted = 0;
    foreach ($mailbox as $mail) {
      if ($mail['deleted']) {
        $deleted++;
      }
    }
    return (object) array(
      'Unread' => count($mailbox),
      'Deleted' => $deleted,
      'Nmsgs' => count($mailbox),
      // Size is not important for this use, so leave it as 0.
      'Size' => 0,
      'Date' => date(DateTime::RFC2822),
      'Driver' => $this->protocol,
      'Mailbox' => $this->getMailboxString(TRUE),
      'Recent' => count($mailbox),
    );
  }

  /**
   * Overrides BounceMailServerConnector::imapOpen().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_open()
   */
  public function imapOpen($mailbox, $username, $password, $options = NULL, $n_retries = NULL) {
    if ($this->failImapOpen) {
      $this->lastErrorMessage = 'imap_open() set to fail';
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Overrides BounceMailServerConnector::imapTimeout().
   *
   * Wrapper method that (incompletely, probably badly) simulates the response
   * of a real server.
   *
   * @see imap_timeout()
   */
  public function imapTimeout($timeout_type, $timeout) {
    if ($this->failImapOpen) {
      $this->lastErrorMessage = 'imap_timeout() set to fail';
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

}
