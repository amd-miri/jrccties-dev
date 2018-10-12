<?php

/**
 * @file
 * Constants defined for the Bounce module, all here to keep them out of
 * the way.
 */

/**
 * The default maximum number of email non-delivery reports to pull from a
 * server in a single connection session.
 */
define('BOUNCE_DEFAULT_MAX_REPORTS_PER_SESSION', 50);

/**
 * A short default timeout in seconds for the mail server connector.
 */
define('BOUNCE_DEFAULT_CONNECTION_TIMEOUT', 5);

/**
 * Default value for the largest attachment size to consider when retrieving
 * mail parts.
 */
define('BOUNCE_DEFAULT_MAIL_PART_SIZE_LIMIT_BYTES', 20480);

/**
 * The score needed to stop sending emails to an address.
 */
define('BOUNCE_DEFAULT_BLOCKER_THRESHOLD_SCORE', 50);

/**
 * The default age at which non-delivery report records are cleared out from
 * the database.
 */
define('BOUNCE_DEFAULT_MAX_REPORT_AGE_DAYS', 100);

/**
 * The default age at which sent mail records are cleared out from the
 * database. (i.e. how long a non-delivery report has to show up to be
 * considered).
 */
define('BOUNCE_DEFAULT_MAX_SENT_AGE_DAYS', 10);

/**
 * The default connector definition used to connect to mail servers.
 */
define('BOUNCE_DEFAULT_CONNECTOR', 'default');

/**
 * The default analyst definition used to process non-delivery reports.
 */
define('BOUNCE_DEFAULT_ANALYST', 'default');

/**
 * The default blocker definition used to determine which mails to block.
 */
define('BOUNCE_DEFAULT_BLOCKER', 'default');

/**
 * The default key for the ID inserted into the headers of outgoing mail.
 */
define('BOUNCE_DEFAULT_MAIL_HEADER_NAME', 'x-bounce-identifier');

/**
 * Indicates that a non-delivery report has not been used to block an email
 * address. It can therefore be used as a part of considering whether to
 * block an email or deleted if too old.
 */
define('BOUNCE_NDR_STATUS_UNUSED', 0);

/**
 * Indicates that a non-delivery report has been used to block an email
 * address. It should not be used as a part of considering whether to
 * (re)block an email and only deleted if the email address is no longer
 * blocked.
 */
define('BOUNCE_NDR_STATUS_USED', 1);
