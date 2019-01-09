<?php

/**
 * @file
 * Statistics Counter: Views support
 */

/**
 * Implements hook_views_data_alter().
 */
function statistics_counter_views_data_alter(&$data) {
  if (!isset($data['node_counter'])) {
    return;
  }

  // Week counts.
  $data['node_counter']['weekcount'] = array(
    'title' => t('Views this week'),
    'help' => t('The total number of times the node has been viewed this week.'),

    'field' => array(
      'handler'        => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Month counts.
  $data['node_counter']['monthcount'] = array(
    'title' => t('Views this month'),
    'help' => t('The total number of times the node has been viewed this month.'),

    'field' => array(
      'handler'        => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Year counts.
  $data['node_counter']['yearcount'] = array(
    'title' => t('Views this year'),
    'help' => t('The total number of times the node has been viewed this year.'),

    'field' => array(
      'handler'        => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
}
