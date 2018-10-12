<?php

/**
 * @file
 * Simplenews Statistics views integration file.
 */

/**
 * Implements hook_views_data().
 */
function simplenews_statistics_views_data() {
  /**
   * Views definitions for the 'urls' table.
   */
  $data['simplenews_statistics_url']['table'] = array(
    'base' => array(
      'field' => 'urlid',
      'title' => t('Simplenews Statistics URLs'),
    ),
    'group' => t('Simplenews Statistics'),
    'join' => array(
      'simplenews_newsletter' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
  );

  $data['simplenews_statistics_url']['urlid'] = array(
    'title' => t('URL ID'),
    'help' => t('The URL ID for a URL in a newsletter.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics_url']['nid'] = array(
    'title' => t('Node ID'),
    'help' => t('The simplenews node ID in which the URL is stored.'),
    'relationship' => array(
      'title' => t('Newsletter'),
      'help' => t('The simplenews node in which the URL is stored.'),
      'base' => 'simplenews_newsletter',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Newsletter'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics_url']['url'] = array(
    'title' => t('URL'),
    'help' => t('The original URL.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['simplenews_statistics_url']['click_count'] = array(
    'title' => t('Click count'),
    'help' => t('The number of times this URL has been clicked.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  /**
   * Views definitions for the 'clicks' table.
   */
  $data['simplenews_statistics_click']['table'] = array(
    'base' => array(
      'field' => 'clid',
      'title' => t('Simplenews Statistics clicks'),
    ),
    'group' => t('Simplenews Statistics'),
    'join' => array(
      'simplenews_newsletter' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'simplenews_subscriber' => array(
        'left_field' => 'snid',
        'field' => 'snid',
      ),
    ),
  );

  $data['simplenews_statistics_click']['clid'] = array(
    'title' => t('Click ID'),
    'help' => t('The click ID for this record.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics_click']['urlid'] = array(
    'title' => t('URL ID'),
    'help' => t('The URL ID for this click.'),
    'relationship' => array(
      'title' => t('URL'),
      'help' => t('The URL for this click.'),
      'base' => 'simplenews_statistics_url',
      'base field' => 'urlid',
      'handler' => 'views_handler_relationship',
      'label' => t('URL'),
    ),
  );

  $data['simplenews_statistics_click']['snid'] = array(
    'title' => t('Simplenews subscriber'),
    'help' => t('The simplenews subscriber.'),
    'relationship' => array(
      'title' => t('Subscriber'),
      'help' => t('The subscriber tied to this URL record.'),
      'base' => 'simplenews_subscriber',
      'base field' => 'snid',
      'handler' => 'views_handler_relationship',
      'label' => t('Simplenews subscriber'),
    ),
  );

  $data['simplenews_statistics_click']['timestamp'] = array(
    'title' => t('Timestamp') . ' » ' . t('Click'),
    'help' => t('The UNIX timestamp when the user clicked this link.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  /**
   * Views integration definitions for the 'opens' table.
   */
  $data['simplenews_statistics_open']['table'] = array(
    'base' => array(
      'field' => 'opid',
      'title' => t('Simplenews Statistics opens'),
    ),
    'group' => t('Simplenews Statistics'),
    'join' => array(
      'simplenews_newsletter' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'simplenews_subscriber' => array(
        'left_field' => 'snid',
        'field' => 'snid',
      ),
    ),
  );

  $data['simplenews_statistics_open']['opid'] = array(
    'title' => t('Open ID'),
    'help' => t('The open ID for this record.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics_open']['snid'] = array(
    'title' => t('Simplenews subscriber'),
    'help' => t('The simplenews subscriber.'),
    'relationship' => array(
      'title' => t('Subscriber'),
      'help' => t('The subscriber for which the email was opened.'),
      'base' => 'simplenews_subscriber',
      'base field' => 'snid',
      'handler' => 'views_handler_relationship',
      'label' => t('Simplenews subscriber'),
    ),
  );

  $data['simplenews_statistics_open']['nid'] = array(
    'title' => t('Node ID'),
    'help' => t('The simplenews node ID for which the email was opened.'),
    'relationship' => array(
      'title' => t('Newsletter'),
      'help' => t('The simplenews node for which the email was opened.'),
      'base' => 'simplenews_newsletter',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Newsletter'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics_open']['timestamp'] = array(
    'title' => t('Timestamp') . ' » ' . t('Open'),
    'help' => t('The UNIX timestamp at which the user opened the email.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  /**
   * Views integration definitions for the 'simplenews_statistics' table.
   */
  $data['simplenews_statistics']['table'] = array(
    'group' => t('Simplenews Statistics'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
  );

  $data['simplenews_statistics']['send_start_timestamp'] = array(
    'title' => t('Timestamp') . ' » ' . t('Sending started'),
    'help' => t('The time the sending of the newsletter started.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  $data['simplenews_statistics']['send_end_timestamp'] = array(
    'title' => t('Timestamp') . ' » ' . t('Sending finished'),
    'help' => t('The time the sending of the newsletter ended.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  $data['simplenews_statistics']['archived'] = array(
    'title' => t('Archived'),
    'help' => t('Whether this newsletter has been archived or not.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_boolean',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_boolean',
    ),
  );

  $data['simplenews_statistics']['unique_opens'] = array(
    'title' => t('Unique opens'),
    'help' => t('Count unique opens for a newsletter.'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_opens',
      'click sortable' => TRUE,
    ),
    // @todo: Filter, sort, and argument will not work if not archived.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics']['total_opens'] = array(
    'title' => t('Total opens'),
    'help' => t('Count total opens for a newsletter.'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_opens',
      'click sortable' => TRUE,
    ),
    // @todo: Filter, sort, and argument will not work if not archived.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics']['unique_clicks'] = array(
    'title' => t('Unique clicks'),
    'help' => t('Unique clicks (archived only).'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_clicks',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  /**
   * Views integration for calculations with custom handlers.
   */
  $data['simplenews_statistics']['subscriber_count'] = array(
    'title' => t('Subscriber count'),
    'help' => t('Shows current number of subscribers if not yet sent and number of subscribers at time of sending if sent. More accurate than the number provided by <em>Simplenews issue: Subscriber count</em>.'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_subscribers',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['simplenews_statistics']['open_rate'] = array(
    'title' => t('Open rate'),
    'help' => t('Calculate open rate for a newsletter.'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_opens',
    ),
  );

  $data['simplenews_statistics']['ctr'] = array(
    'title' => t('Click-through rate'),
    'help' => t('CTR (click-through rate).'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_clicks',
    ),
  );

  $data['simplenews_statistics']['bounce_rate'] = array(
    'title' => t('Bounce rate'),
    'help' => t('Unsubscribe and bounce rates. Only unsubscribes or bounces that result in a user being unsubscribed by a third-party module will be counted.'),
    'field' => array(
      'handler' => 'simplenews_statistics_handler_unsubscribes',
    ),
  );


  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function simplenews_statistics_views_data_alter(&$data) {
  // Modify the title and description to more accurately represent the data
  // stored in this field. @todo: Submit a patch to simplenews for this.
  $data['simplenews_newsletter']['sent_subscriber_count']['title'] = t('Sent count');
  $data['simplenews_newsletter']['sent_subscriber_count']['help'] = t('The number of newsletter copies that have been sent to subscribers.');
}
