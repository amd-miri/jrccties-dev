<?php

/**
 * @file
 * Simplenews Statistics default views file.
 */

/**
 * Implements hook_views_default_views().
 */
function simplenews_statistics_views_default_views() {
  /**
   * Simplenews Statistics Overview view.
   */
  $view = new view();
  $view->name = 'simplenews_statistics_overview';
  $view->description = 'Shows the statistical overview for a newsletter.';
  $view->tag = 'simplenews_statistics';
  $view->base_table = 'node';
  $view->human_name = 'Simplenews Statistics Overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Simplenews Statistics Overview';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view newsletter statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'subscriber_count' => 'subscriber_count',
    'sent_subscriber_count' => 'sent_subscriber_count',
    'open_count' => 'open_count',
    'open_count_1' => 'open_count_1',
    'open_count_2' => 'open_count_2',
    'click_count' => 'click_count',
    'click_count_1' => 'click_count_1',
    'click_count_2' => 'click_count_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'subscriber_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sent_subscriber_count' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'open_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'open_count_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'open_count_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'click_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'click_count_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'click_count_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Simplenews Statistics: Subscriber count */
  $handler->display->display_options['fields']['subscriber_count']['id'] = 'subscriber_count';
  $handler->display->display_options['fields']['subscriber_count']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['subscriber_count']['field'] = 'subscriber_count';
  $handler->display->display_options['fields']['subscriber_count']['label'] = 'Subscribers';
  /* Field: Simplenews issue: Sent count */
  $handler->display->display_options['fields']['sent_subscriber_count']['id'] = 'sent_subscriber_count';
  $handler->display->display_options['fields']['sent_subscriber_count']['table'] = 'simplenews_newsletter';
  $handler->display->display_options['fields']['sent_subscriber_count']['field'] = 'sent_subscriber_count';
  $handler->display->display_options['fields']['sent_subscriber_count']['label'] = 'Emails sent';
  /* Field: Simplenews Statistics: Total opens */
  $handler->display->display_options['fields']['total_opens']['id'] = 'total_opens';
  $handler->display->display_options['fields']['total_opens']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['total_opens']['field'] = 'total_opens';
  /* Field: Simplenews Statistics: Unique opens */
  $handler->display->display_options['fields']['unique_opens']['id'] = 'unique_opens';
  $handler->display->display_options['fields']['unique_opens']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['unique_opens']['field'] = 'unique_opens';
  /* Field: Simplenews Statistics: Open rate */
  $handler->display->display_options['fields']['open_rate']['id'] = 'open_rate';
  $handler->display->display_options['fields']['open_rate']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['open_rate']['field'] = 'open_rate';
  /* Field: Simplenews Statistics: Unique clicks */
  $handler->display->display_options['fields']['unique_clicks']['id'] = 'unique_clicks';
  $handler->display->display_options['fields']['unique_clicks']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['unique_clicks']['field'] = 'unique_clicks';
  /* Field: Simplenews Statistics: Click-through rate */
  $handler->display->display_options['fields']['ctr']['id'] = 'ctr';
  $handler->display->display_options['fields']['ctr']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['ctr']['field'] = 'ctr';
  $handler->display->display_options['fields']['ctr']['alter']['text'] = '[ctr] ([unique_clicks])';
  /* Field: Simplenews Statistics: Bounce rate */
  $handler->display->display_options['fields']['bounce_rate']['id'] = 'bounce_rate';
  $handler->display->display_options['fields']['bounce_rate']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['bounce_rate']['field'] = 'bounce_rate';
  $handler->display->display_options['fields']['bounce_rate']['number'] = 1;
  $handler->display->display_options['fields']['bounce_rate']['percentage'] = 1;
  $handler->display->display_options['fields']['bounce_rate']['precision'] = '2';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'simplenews' => 'simplenews',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'access denied';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'simplenews' => 'simplenews',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/simplenews_statistics/summary';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Newsletter Overview';
  $handler->display->display_options['menu']['description'] = 'Simplenews Statistics overview';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'devel';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  // Add to default views return array.
  $views[$view->name] = $view;

  /**
   * Simplenews Statistics Clicks view.
   */
  $view = new view();
  $view->name = 'simplenews_statistics_clicks';
  $view->description = 'Shows all click records for a newsletter.';
  $view->tag = 'simplenews_statistics';
  $view->base_table = 'simplenews_statistics_click';
  $view->human_name = 'Simplenews Statistics Clicks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view newsletter statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 500, 1000';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'cid' => 'cid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'cid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['label'] = 'Intro';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  $handler->display->display_options['header']['result']['content'] = 'Links in this newsletter have been clicked @total times.';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no click statistics available for this newsletter.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Simplenews Statistics: URL */
  $handler->display->display_options['relationships']['urlid']['id'] = 'urlid';
  $handler->display->display_options['relationships']['urlid']['table'] = 'simplenews_statistics_click';
  $handler->display->display_options['relationships']['urlid']['field'] = 'urlid';
  $handler->display->display_options['relationships']['urlid']['required'] = TRUE;
  /* Relationship: Simplenews Statistics: Subscriber */
  $handler->display->display_options['relationships']['snid']['id'] = 'snid';
  $handler->display->display_options['relationships']['snid']['table'] = 'simplenews_statistics_click';
  $handler->display->display_options['relationships']['snid']['field'] = 'snid';
  $handler->display->display_options['relationships']['snid']['required'] = TRUE;
  /* Field: Simplenews Statistics: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'simplenews_statistics_url';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['relationship'] = 'urlid';
  $handler->display->display_options['fields']['url']['display_as_link'] = FALSE;
  /* Field: Simplenews subscriber: Subscriber */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'simplenews_subscriber';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'snid';
  $handler->display->display_options['fields']['mail']['label'] = 'E-mail';
  /* Field: Simplenews Statistics: Timestamp » Click */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'simplenews_statistics_click';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date clicked';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'medium';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Sort criterion: Simplenews Statistics: Timestamp » Click */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'simplenews_statistics_click';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Simplenews Statistics: Node ID */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'simplenews_statistics_url';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'urlid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'simplenews' => 'simplenews',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'access denied';

  /* Display: Simplenews Statistics Clicks */
  $handler = $view->new_display('page', 'Simplenews Statistics Clicks', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/simplenews_statistics/clicks';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Newsletter Clicks';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Simplenews Statistics';
  $handler->display->display_options['tab_options']['weight'] = '0';

  // Add to default views return array.
  $views[$view->name] = $view;

  /**
   * Simplenews Statistics Opens view.
   */
  $view = new view();
  $view->name = 'simplenews_statistics_opens';
  $view->description = 'Shows all open records for a newsletter.';
  $view->tag = 'simplenews_statistics';
  $view->base_table = 'simplenews_statistics_open';
  $view->human_name = 'Simplenews Statistics Opens';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view newsletter statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 500, 1000';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  $handler->display->display_options['header']['result']['content'] = 'This newsletter has been opened @total times.';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no open statistics available for this newsletter.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Simplenews Statistics: Subscriber */
  $handler->display->display_options['relationships']['snid']['id'] = 'snid';
  $handler->display->display_options['relationships']['snid']['table'] = 'simplenews_statistics_open';
  $handler->display->display_options['relationships']['snid']['field'] = 'snid';
  /* Field: Simplenews subscriber: Subscriber */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'simplenews_subscriber';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'snid';
  $handler->display->display_options['fields']['mail']['label'] = 'E-mail';
  /* Field: Simplenews Statistics: Timestamp » Open */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'simplenews_statistics_open';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Sort criterion: Simplenews Statistics: Timestamp » Open */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'simplenews_statistics_open';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Simplenews Statistics: Node ID */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'simplenews_statistics_open';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'simplenews' => 'simplenews',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'empty';

  /* Display: Simplenews Statistics Opens */
  $handler = $view->new_display('page', 'Simplenews Statistics Opens', 'page');
  $handler->display->display_options['path'] = 'node/%/simplenews_statistics/opens';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Newsletter Opens';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Simplenews Statistics';
  $handler->display->display_options['tab_options']['weight'] = '0';

  // Add to default views return array.
  $views[$view->name] = $view;

  /**
   * Simplenews Statistics Summary view.
   */
  $view = new view();
  $view->name = 'simplenews_statistics_summary';
  $view->description = 'Shows a statistical summary for all newsletters.';
  $view->tag = 'simplenews_statistics';
  $view->base_table = 'node';
  $view->human_name = 'Simplenews Statistics Summary';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Simplenews Statistics Summary';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view newsletter statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_simplenews_term' => 'field_simplenews_term',
    'subscriber_count' => 'subscriber_count',
    'sent_subscriber_count' => 'sent_subscriber_count',
    'status' => 'status',
    'send_start_timestamp' => 'send_start_timestamp',
    'open_count_1' => 'open_count_1',
    'open_count' => 'open_count',
    'click_count_1' => 'click_count_1',
    'click_count' => 'click_count',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_simplenews_term' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subscriber_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sent_subscriber_count' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'send_start_timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'open_count_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'open_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'click_count_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'click_count' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Intro';
  $handler->display->display_options['header']['area']['content'] = 'Visit the "Statistics" tab on the individual node pages for more details.';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Newsletter category */
  $handler->display->display_options['fields']['field_simplenews_term']['id'] = 'field_simplenews_term';
  $handler->display->display_options['fields']['field_simplenews_term']['table'] = 'field_data_field_simplenews_term';
  $handler->display->display_options['fields']['field_simplenews_term']['field'] = 'field_simplenews_term';
  $handler->display->display_options['fields']['field_simplenews_term']['label'] = 'Newsletter Category';
  $handler->display->display_options['fields']['field_simplenews_term']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Simplenews Statistics: Subscriber count */
  $handler->display->display_options['fields']['subscriber_count']['id'] = 'subscriber_count';
  $handler->display->display_options['fields']['subscriber_count']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['subscriber_count']['field'] = 'subscriber_count';
  $handler->display->display_options['fields']['subscriber_count']['label'] = '';
  $handler->display->display_options['fields']['subscriber_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['subscriber_count']['element_label_colon'] = FALSE;
  /* Field: Simplenews issue: Sent count */
  $handler->display->display_options['fields']['sent_subscriber_count']['id'] = 'sent_subscriber_count';
  $handler->display->display_options['fields']['sent_subscriber_count']['table'] = 'simplenews_newsletter';
  $handler->display->display_options['fields']['sent_subscriber_count']['field'] = 'sent_subscriber_count';
  $handler->display->display_options['fields']['sent_subscriber_count']['label'] = '';
  $handler->display->display_options['fields']['sent_subscriber_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sent_subscriber_count']['element_label_colon'] = FALSE;
  /* Field: Simplenews issue: Sent status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'simplenews_newsletter';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['text'] = '[status] ([sent_subscriber_count]/[subscriber_count])';
  /* Field: Simplenews Statistics: Timestamp » Sending started */
  $handler->display->display_options['fields']['send_start_timestamp']['id'] = 'send_start_timestamp';
  $handler->display->display_options['fields']['send_start_timestamp']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['send_start_timestamp']['field'] = 'send_start_timestamp';
  $handler->display->display_options['fields']['send_start_timestamp']['label'] = 'Sent Date';
  $handler->display->display_options['fields']['send_start_timestamp']['date_format'] = 'medium';
  $handler->display->display_options['fields']['send_start_timestamp']['second_date_format'] = 'long';
  /* Field: Simplenews Statistics: Unique opens */
  $handler->display->display_options['fields']['unique_opens']['id'] = 'unique_opens';
  $handler->display->display_options['fields']['unique_opens']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['unique_opens']['field'] = 'unique_opens';
  $handler->display->display_options['fields']['unique_opens']['label'] = '';
  $handler->display->display_options['fields']['unique_opens']['exclude'] = TRUE;
  $handler->display->display_options['fields']['unique_opens']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['unique_opens']['open_rate_precision'] = 0;
  /* Field: Simplenews Statistics: Open rate */
  $handler->display->display_options['fields']['open_rate']['id'] = 'open_rate';
  $handler->display->display_options['fields']['open_rate']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['open_rate']['field'] = 'open_rate';
  $handler->display->display_options['fields']['open_rate']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['open_rate']['alter']['text'] = '[open_rate] ([unique_opens])';
  /* Field: Simplenews Statistics: Unique clicks */
  $handler->display->display_options['fields']['unique_clicks']['id'] = 'unique_clicks';
  $handler->display->display_options['fields']['unique_clicks']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['unique_clicks']['field'] = 'unique_clicks';
  $handler->display->display_options['fields']['unique_clicks']['label'] = '';
  $handler->display->display_options['fields']['unique_clicks']['exclude'] = TRUE;
  $handler->display->display_options['fields']['unique_clicks']['element_label_colon'] = FALSE;
  /* Field: Simplenews Statistics: Click-through rate */
  $handler->display->display_options['fields']['ctr']['id'] = 'ctr';
  $handler->display->display_options['fields']['ctr']['table'] = 'simplenews_statistics';
  $handler->display->display_options['fields']['ctr']['field'] = 'ctr';
  $handler->display->display_options['fields']['ctr']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['ctr']['alter']['text'] = '[ctr] ([unique_clicks])';
  /* Sort criterion: Simplenews issue: Sent status */
  $handler->display->display_options['sorts']['status']['id'] = 'status';
  $handler->display->display_options['sorts']['status']['table'] = 'simplenews_newsletter';
  $handler->display->display_options['sorts']['status']['field'] = 'status';
  /* Sort criterion: Simplenews Statistics: Timestamp » Sending started */
  $handler->display->display_options['sorts']['send_start_timestamp']['id'] = 'send_start_timestamp';
  $handler->display->display_options['sorts']['send_start_timestamp']['table'] = 'simplenews_statistics';
  $handler->display->display_options['sorts']['send_start_timestamp']['field'] = 'send_start_timestamp';
  $handler->display->display_options['sorts']['send_start_timestamp']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'simplenews' => 'simplenews',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/simplenews/statistics';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Statistics';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add to default views return array.
  $views[$view->name] = $view;

  return $views;
}
