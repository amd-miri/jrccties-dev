<?php

/**
 * @file
 * Definition of BounceTestMailServerConnector.
 */

/**
 * A class for connecting to a mail server account via POP3 or IMAP protocols.
 *
 * The class needs the php-imap package installed. This manages both POP and
 * IMAP protocols:
 * http://www.php.net/manual/en/book.imap.php
 *
 * The innards of this class are adapted from code in a comment by Wil Barath:
 * http://www.php.net/manual/en/book.imap.php#96414
 *
 * This uses much of that material as a starting point, while adding comments,
 * additional functionality, and fixing a number of issues discovered in the
 * course of testing.
 */
class BounceMailServerConnector {

  /**
   * A copy of the imap connection.
   */
  protected $connection = NULL;

  /**
   * Hostname for the mailserver.
   */
  protected $server = NULL;

  /**
   * Port used to connect to the mailserver.
   */
  protected $port = NULL;

  /**
   * Protocol used: 'pop3' or 'imap'. The latter two use SSL.
   */
  protected $protocol = NULL;

  /**
   * String for encryption used: '', 'tls', or 'ssl'.
   */
  protected $encryption = '';

  /**
   * The login used to connect to the mailserver.
   */
  protected $login = NULL;

  /**
   * The password used to connect to the mailserver.
   */
  protected $password = NULL;

  /**
   * The mail folder to read. For our purposes, this is almost always 'INBOX'.
   */
  protected $folder = NULL;

  /**
   * Don't retrieve a message part larger than this size in bytes, as it's
   * unlikely to be text, and we're only interested in text.
   */
  protected $maxMailPartSizeBytes = NULL;

  /**
   * The class constructor.
   *
   * The provided parameter array must be of the following form:
   *
   * array(
   *   'server' => 'mail.mydomain.com',
   *   'protocol' => 'pop3',
   *   'encryption' => 'ssl',
   *   'port' => 993,
   *   'login' => 'me@mydomain.com',
   *   'password' => 'some string',
   *   'folder' => 'INBOX',
   *   'timeout' => 5,
   * )
   *
   * Available values for the protocol parameter are ['pop3','imap'].
   *
   * Available values for the encryption parameter are ['', 'tls', 'ssl'].
   *
   * The folder parameter should almost always be 'INBOX'.
   *
   * @param array $params
   *   An associative array of the parameters for connecting to a mail server.
   */
  public function __construct($params) {
    $this->server = $params['server'];
    $this->protocol = $params['protocol'];
    $this->encryption = $params['encryption'];
    $this->port = $params['port'];
    $this->login = $params['login'];
    $this->password = $params['password'];
    $this->folder = $params['folder'];
    $this->maxMailPartSizeBytes = $params['mail_part_size_limit'];

    // Set the connection timeouts.
    $result = $this->imapTimeout(IMAP_OPENTIMEOUT, $params['timeout']);
    if (!$result) {
      $this->watchdogLastImapError('Failed to set open timeout');
    }
    $result = $this->imapTimeout(IMAP_READTIMEOUT, $params['timeout']);
    if (!$result) {
      $this->watchdogLastImapError('Failed to set read timeout');
    }
    $result = $this->imapTimeout(IMAP_WRITETIMEOUT, $params['timeout']);
    if (!$result) {
      $this->watchdogLastImapError('Failed to set write timeout');
    }
    $result = $this->imapTimeout(IMAP_CLOSETIMEOUT, $params['timeout']);
    if (!$result) {
      $this->watchdogLastImapError('Failed to set close timeout');
    }
  }

  /**
   * Connect and log in to a mail server.
   *
   * @return bool
   *   TRUE on success, FALSE on error.
   */
  public function login() {
    try {
      $this->connection = $this->imapOpen(
        $this->getMailboxString(),
        $this->login,
        $this->password,
        // Why this? See https://bugs.php.net/bug.php?id=33039 and
        // http://www.php.net/manual/en/function.imap-open.php#73514 for
        // details.
        OP_SILENT
      );
      if (!$this->connection) {
        $this->watchdogLastImapError(t('Login failure'));
        return FALSE;
      }
      else {
        return TRUE;
      }
    } catch (Exception $e) {
      // Plausible to see exceptions if very bad values have been passed in,
      // such as an empty hostname string.
      $this->watchdogLastImapError($e->getMessage());
      return FALSE;
    }
  }

  /**
   * Log out of the currently active POP3 server connection.
   *
   * @return bool
   *   TRUE on success, FALSE on error.
   */
  public function logout() {
    if ($this->connection) {
      // Close connection and delete all messages flagged for deletion.
      $result = $this->imapClose(CL_EXPUNGE);
      $this->connection = NULL;
      if (!$result) {
        $this->watchdogLastImapError(t('Logout failure'));
      }
      return $result;
    }
  }

  /**
   * Obtain information on the POP3 folder you are presently logged in to.
   *
   * The function returns a result of this form:
   *
   * Array (
   *   [Unread] => 0
   *   [Deleted] => 0
   *   [Nmsgs] => 0
   *   [Size] => 0
   *   [Date] => Mon, 7 Feb 2011 22:28:23 -0500 (EST)
   *   [Driver] => pop3
   *   [Mailbox] => {m.host.com:995/pop3/ssl/user="us@host.com"}INBOX
   *   [Recent] => 0
   * )
   *
   * Where Nmsgs is the total number of messages in the folder, and the other
   * parameters should be fairly self-explanatory.
   *
   * @return array
   *   An array of information.
   */
  public function getMailboxInfo() {
    $check = $this->imapMailboxmsginfo();
    if ($check) {
      return ((array) $check);
    }
    else {
      $this->watchdogLastImapError(t('Failed to get mailbox info'));
    }
  }

  /**
   * List messages in the presently active POP3 mail folder.
   *
   * The function produces results of this form: a list of message information:
   *
   * Array (
   *   [1] => Array (
   *     [subject] => test w/ attachment
   *     [from] => name
   *     [to] => mail@domain.com
   *     [date] => Mon, 7 Feb 2011 19:37:07 -0800
   *     [message_id] =>
   *     [size] => 962
   *     [uid] => 1
   *     [msgno] => 1
   *     [recent] => 1
   *     [flagged] => 0
   *     [answered] => 0
   *     [deleted] => 0
   *     [seen] => 0
   *     [draft] => 0
   *     [udate] => 1297136227
   *   )
   *   [2] => ...
   * )
   *
   * @param string $range
   *   In the form x:y e.g. 1:3 obtains messages 1, 2, and 3.
   *
   * @return array
   *   The messages.
   */
  public function listMessages($range = '') {
    $result = array();
    if (!$range) {
      $mc = $this->imapCheck();
      if (!$mc) {
        $this->watchdogLastImapError(t('Failed to check the mailbox for the number of messages'));
        return $result;
      }
      $range = '1:' . $mc->Nmsgs;
    }
    $response = $this->imapFetchOverview($range);
    if (!is_array($response)) {
      $this->watchdogLastImapError(t('Failed to obtain an overview of messages'));
      return $result;
    }
    foreach ($response as $message) {
      $result[$message->msgno] = (array) $message;
    }
    return $result;
  }

  /**
   * Return the headers of a message.
   *
   * Headers are returned either as raw text or an array indexed by header
   * name.
   *
   * @param integer $message_number
   *   An integer index key from the array returned by listMessages().
   * @param bool $headers_as_array
   *   If true, return an array rather than the raw header string.
   *
   * @return mixed
   *   Either a header string or the headers formed up as an array.
   */
  public function getMessageHeaders($message_number, $headers_as_array = FALSE) {
    $headers = $this->imapFetchheader($message_number, FT_PREFETCHTEXT);
    if (!is_string($headers)) {
      $headers = '';
      $this->watchdogLastImapError(t('Failed to retrieve the header for message number = %id', array('%id' => $message_number)));
    }
    if ($headers_as_array) {
      $headers = $this->parseMailHeadersIntoArray($headers);
    }
    return $headers;
  }

  /**
   * Mark the the indicated message for deletion.
   *
   * The message will be deleted when logout() is called.
   *
   * @param integer $message_number
   *   An integer index key from the array returned by listMessages().
   *
   * @return bool
   *   TRUE on success, FALSE otherwise.
   */
  public function markMessageForDeletion($message_number) {
    $result = $this->imapDelete($message_number);
    if (!$result) {
      $this->watchdogLastImapError(t('Failed to delete message number = %id', array('%id' => $message_number)));
    }
    return $result;
  }


  /**
   * Return an array containing data from the various message parts.
   *
   * The results look much like this for a single part email, with the
   * message headers in raw and parsed form contained in the first array field.
   *
   * Array (
   *   [0] => Array (
   *     [charset] => us-ascii
   *     [raw] => Return-Path:
   *               Delivered-To: account@domain.com
   *               Reply-To:
   *               From: "That Guy"
   *               To:
   *               Subject: test 1
   *               Date: Mon, 7 Feb 2011 19:37:07 -0800
   *               Message-ID:
   *               MIME-Version: 1.0
   *               Content-Type: text/plain;
   *               charset="us-ascii"
   *               Content-Transfer-Encoding: 7bit
   *               Content-Language: en-us
   *     [data] => Array(
   *       [Return-Path] =>
   *       [Delivered-To] => account@domain.com
   *       [Reply-To] =>
   *       [From] => "That Guy"
   *       [To] =>
   *       [Subject] => test 1
   *       [Date] => Mon, 7 Feb 2011 19:37:07 -0800
   *       [Message-ID] =>
   *       [MIME-Version] => 1.0
   *       [Content-Type] => text/plain;charset="us-ascii"
   *       [Content-Transfer-Encoding] => 7bit
   *     )
   *   )
   *   [1] => Array (
   *     [charset] => us-ascii
   *     [data] => example mail body, probably much longer in reality
   *   )
   * )
   *
   * Multi-part mails will contain more array entries of data, one for each
   * part or file attachment.
   *
   * @param integer $message_number
   *   The message identifier.
   *
   * @return array
   *   The email.
   */
  public function getMessage($message_number) {
    $mail = $this->imapFetchstructure($message_number);
    if (!is_object($mail)) {
      $this->watchdogLastImapError(t('Failed to retrieve message structure for message number = %id', array('%id' => $message_number)));
      return array();
    }

    // $this->mailGetParts() will chase down all the components of a
    // multi-part mail, but only return the headers of a single part mail.
    $mail = $this->mailGetParts($message_number, $mail, '0');
    $mail[0]['raw'] = $mail[0]['data'];
    $mail[0]['data'] = $this->parseMailHeadersIntoArray($mail[0]['raw']);
    if (!isset($mail[0]['charset'])) {
      // Probably wrong, but better than nothing.
      $mail[0]['charset'] = 'utf-8';
    };

    // So if it is only a single part mail, we have to go and fetch the body.
    if (count($mail) == 1) {
      $body = $this->imapBody($message_number);
      if (!is_string($body)) {
        $this->watchdogLastImapError(t('Failed to retrieve message body for message number = %id', array('%id' => $message_number)));
      }
      $mail[] = array(
        'data' => $body,
        'charset' => $mail[0]['charset'],
      );
    }

    return $mail;
  }

  /*
  -----------------------------------------------------------------------
  Utility functions from here on down.
  -----------------------------------------------------------------------
  */

  /**
   * Return the connection string for the mailbox.
   *
   * The connection string has this form:
   *
   * {mail.host.com:995/pop3/ssl/novalidate-cert}INBOX
   * {mail.host.com:995/pop3/ssl/novalidate-cert/user="us@host.com"}INBOX
   *
   * @param boolean $with_user
   *   If TRUE, include the user="userlogin" segment.
   *
   * @return string
   *   The connection string.
   */
  protected function getMailboxString($with_user = FALSE) {
    $inner = "{$this->server}:{$this->port}/{$this->protocol}";
    if ($this->encryption) {
      $inner .= "/{$this->encryption}/novalidate-cert";
    }
    if ($with_user) {
      $inner .= '/"user=' . $this->login . '"';
    }
    return '{' . $inner . '}' . $this->folder;
  }

  /**
   * Record the last error generated from the underlying IMAP functionality.
   *
   * @param string $message
   *   The error message.
   */
  protected function watchdogLastImapError($message) {
    $error = $this->imapLastError();
    if ($error) {
      watchdog('bounce', '%message : %error', array('%message' => $message, '%error' => $error), WATCHDOG_ERROR);
    }
    else {
      watchdog('bounce', '%message : No IMAP package error found.', array('%message' => $message), WATCHDOG_ERROR);
    }
  }

  /**
   * Parse a message header into an associative array of name-value pairs.
   *
   * @param string $headers
   *   The email headers as a string.
   *
   * @return array
   *   An associated array of name-value pairs.
   */
  protected function parseMailHeadersIntoArray($headers) {
    $headers = preg_replace('/\r\n\s+/m', '', $headers);
    preg_match_all('/([^: ]+): (.+?(?:\r\n\s(?:.+?))*)?\r\n/m', $headers, $matches);
    $result = array();
    foreach ($matches[1] as $key => $value) {
      $result[$value] = $matches[2][$key];
    }
    return $result;
  }

  /**
   * Return the parts of a multi-part mail.
   *
   * Recursively walk through the parts, obtaining the content for each part,
   * and return the whole as nested arrays.
   *
   * @param integer $message_number
   *   The identifier for the message.
   * @param object $part
   *   A message part.
   * @param string $prefix
   *   Describing the position in the structure.
   *
   * @return array
   *   The parts of the mail as an array.
   */
  protected function mailGetParts($message_number, $part, $prefix) {
    $attachments = array();
    $attachments[$prefix] = $this->mailDecodePart($message_number, $part, $prefix);
    if (isset($part->parts)) {
      // This is multipart.
      $prefix = ($prefix == '0') ? '' : $prefix . '.';
      foreach ($part->parts as $index => $subpart) {
        $attachments = array_merge(
          $attachments,
          // The $index below should be 0-based, but what needs to be passed
          // into the server is 1-based, hence the + 1.
          $this->mailGetParts($message_number, $subpart, $prefix . ($index + 1))
        );
      }
    }
    return $attachments;
  }

  /**
   * Retrieve and decode the content for a single part.
   *
   * Return the content, or a message if the part is larger than the size limit
   * for mail parts set in the configuration.
   *
   * @param integer $message_number
   *   The identifier for the message.
   * @param object $part
   *   A message part.
   * @param string $prefix
   *   Describing the position in the structure.
   *
   * @return array
   *   The part data.
   */
  protected function mailDecodePart($message_number, $part, $prefix) {
    $attachment = array();

    if (isset($part->ifdparameters) && $part->ifdparameters) {
      foreach ($part->dparameters as $object) {
        $attachment[drupal_strtolower($object->attribute)] = $object->value;
        if (drupal_strtolower($object->attribute) == 'filename') {
          $attachment['is_attachment'] = TRUE;
          $attachment['filename'] = $object->value;
        }
      }
    }

    if (isset($part->ifparameters) && $part->ifparameters) {
      foreach ($part->parameters as $object) {
        $attachment[drupal_strtolower($object->attribute)] = $object->value;
        if (drupal_strtolower($object->attribute) == 'name') {
          $attachment['is_attachment'] = TRUE;
          $attachment['name'] = $object->value;
        }
      }
    }

    // If this thing is large, just return a string saying it is large. Large
    // items are generally not what we are looking for when searching for
    // bounce-related information.
    //
    // Note that if it has sub-parts, the byte count should be a sum of subpart
    // byte counts, so ignore it.
    if (!isset($part->parts) && isset($part->bytes) && $part->bytes > $this->maxMailPartSizeBytes) {
      $attachment['data'] = t('Mail part too large to consider: @bytes bytes', array('@bytes' => $part->bytes));
      return $attachment;
    }

    $data = $this->imapFetchbody($message_number, $prefix);
    if (!is_string($data)) {
      $this->watchdogLastImapError(t('Failed to retrieve message structure for message number = %id', array('%id' => $message_number)));
      $attachment['data'] = '';
    }
    else {
      if (isset($part->encoding)) {
        // 3 = BASE64.
        if ($part->encoding == 3) {
          $data = base64_decode($data);
        }
        // 4 = QUOTED-PRINTABLE.
        elseif ($part->encoding == 4) {
          $data = quoted_printable_decode($data);
        }
      }
      $attachment['data'] = $data;
    }
    return $attachment;
  }

  /*
  -----------------------------------------------------------------------
  Wrapper methods for IMAP functions.

  These functions are wrapped to allow overriding in child classes, e.g. for
  testing without the need for a mailserver.
  -----------------------------------------------------------------------
  */

  /**
   * Wrapper method for imap_body().
   *
   * @see imap_body()
   */
  protected function imapBody($message_number, $options = NULL) {
    return imap_body($this->connection, $message_number, $options);
  }

  /**
   * Wrapper method for imap_check().
   *
   * @see imap_check()
   */
  protected function imapCheck() {
    return imap_check($this->connection);
  }

  /**
   * Wrapper method for imap_close().
   *
   * @see imap_close()
   */
  protected function imapClose($flag) {
    return imap_close($this->connection, $flag);
  }

  /**
   * Wrapper method for imap_delete().
   *
   * @see imap_delete()
   */
  protected function imapDelete($message_number) {
    return imap_delete($this->connection, $message_number);
  }

  /**
   * Wrapper method for imap_fetch_overview().
   *
   * @see imap_fetch_overview()
   */
  protected function imapFetchOverview($range) {
    return imap_fetch_overview($this->connection, $range);
  }

  /**
   * Wrapper method for imap_fetchbody().
   *
   * @see imap_fetchbody()
   */
  protected function imapFetchbody($message_number, $prefix) {
    return imap_fetchbody($this->connection, $message_number, $prefix);
  }

  /**
   * Wrapper method for imap_fetchheader().
   *
   * @see imap_fetchheader()
   */
  protected function imapFetchheader($message_number, $options = 0) {
    return imap_fetchheader($this->connection, $message_number, $options);
  }

  /**
   * Wrapper method for imap_fetchstructure().
   *
   * @see imap_fetchstructure()
   */
  protected function imapFetchstructure($message_number, $options = NULL) {
    return imap_fetchstructure($this->connection, $message_number, $options);
  }

  /**
   * Wrapper method for imap_last_error().
   *
   * @see imap_last_error()
   */
  protected function imapLastError() {
    return imap_last_error();
  }

  /**
   * Wrapper method for imap_mailboxmsginfo().
   *
   * @see imap_mailboxmsginfo()
   */
  protected function imapMailboxmsginfo() {
    return imap_mailboxmsginfo($this->connection);
  }

  /**
   * Wrapper method for imap_open().
   *
   * @see imap_open()
   */
  protected function imapOpen($mailbox, $username, $password, $options = NULL, $n_retries = NULL) {
    return imap_open($mailbox, $username, $password, $options, $n_retries);
  }

  /**
   * Wrapper method for imap_timeout().
   *
   * @see imap_timeout()
   */
  protected function imapTimeout($timeout_type, $timeout) {
    return imap_timeout($timeout_type, $timeout);
  }
}
