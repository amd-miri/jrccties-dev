<?php

/**
 * @file
 * jrccties_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function jrccties_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cop_bioeconomy_homepage_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Cop Bioeconomy Homepage Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Latest Content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '7';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'created' => 'created',
    'type' => 'type',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
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
    'jrc_com_article' => 'jrc_com_article',
    'audio' => 'audio',
    'discussion' => 'discussion',
    'document' => 'document',
    'page' => 'page',
    'photo' => 'photo',
    'useful_links' => 'useful_links',
    'video_page' => 'video_page',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'event' => 'event',
    'news' => 'news',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Link to event (field_link_to_event:url) */
  $handler->display->display_options['filters']['field_link_to_event_url']['id'] = 'field_link_to_event_url';
  $handler->display->display_options['filters']['field_link_to_event_url']['table'] = 'field_data_field_link_to_event';
  $handler->display->display_options['filters']['field_link_to_event_url']['field'] = 'field_link_to_event_url';
  $handler->display->display_options['filters']['field_link_to_event_url']['operator'] = 'not_starts';
  $handler->display->display_options['filters']['field_link_to_event_url']['value'] = 'http://ec.europa.eu/newsroom/redirection.cfm';
  $handler->display->display_options['filters']['field_link_to_event_url']['group'] = 2;
  /* Filter criterion: Content: Link to news item (field_link_to_news_item:url) */
  $handler->display->display_options['filters']['field_link_to_news_item_url']['id'] = 'field_link_to_news_item_url';
  $handler->display->display_options['filters']['field_link_to_news_item_url']['table'] = 'field_data_field_link_to_news_item';
  $handler->display->display_options['filters']['field_link_to_news_item_url']['field'] = 'field_link_to_news_item_url';
  $handler->display->display_options['filters']['field_link_to_news_item_url']['operator'] = 'not_starts';
  $handler->display->display_options['filters']['field_link_to_news_item_url']['value'] = 'http://ec.europa.eu/newsroom/redirection.cfm';
  $handler->display->display_options['filters']['field_link_to_news_item_url']['group'] = 2;
  /* Filter criterion: Content: Link to news item (field_link_to_news_item:url) */
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['id'] = 'field_link_to_news_item_url_1';
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['table'] = 'field_data_field_link_to_news_item';
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['field'] = 'field_link_to_news_item_url';
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['operator'] = 'not_starts';
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['value'] = 'https://knowledge4policy.ec.europa.eu/';
  $handler->display->display_options['filters']['field_link_to_news_item_url_1']['group'] = 2;
  /* Filter criterion: Content: Link to event (field_link_to_event:url) */
  $handler->display->display_options['filters']['field_link_to_event_url_1']['id'] = 'field_link_to_event_url_1';
  $handler->display->display_options['filters']['field_link_to_event_url_1']['table'] = 'field_data_field_link_to_event';
  $handler->display->display_options['filters']['field_link_to_event_url_1']['field'] = 'field_link_to_event_url';
  $handler->display->display_options['filters']['field_link_to_event_url_1']['operator'] = 'not_starts';
  $handler->display->display_options['filters']['field_link_to_event_url_1']['value'] = 'https://knowledge4policy.ec.europa.eu/';
  $handler->display->display_options['filters']['field_link_to_event_url_1']['group'] = 2;

  /* Display: Community Content */
  $handler = $view->new_display('block', 'Community Content', 'block_content');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = ' <i class="icon-[type]"></i>[title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['link_class'] = 'list-group-item';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'jrc_date';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $export['cop_bioeconomy_homepage_content'] = $view;

  return $export;
}
