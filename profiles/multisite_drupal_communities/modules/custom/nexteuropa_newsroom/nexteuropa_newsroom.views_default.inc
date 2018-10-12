<?php

/**
 * @file
 * nexteuropa_newsroom.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function nexteuropa_newsroom_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'newsletter_subscription';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsletter subscription';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Newsletter subscription';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Newsroom Service ID */
  $handler->display->display_options['fields']['field_newsroom_service_id']['id'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['table'] = 'field_data_field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['field'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_id']['element_label_colon'] = FALSE;
  /* Contextual filter: Taxonomy term: Newsroom Topic (field_newsroom_topic) */
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['id'] = 'field_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['table'] = 'field_data_field_newsroom_topic';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['field'] = 'field_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['node'] = TRUE;
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['anyall'] = '+';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['limit'] = TRUE;
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['validate_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service type (field_newsroom_service_type) */
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['id'] = 'field_newsroom_service_type_value';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['table'] = 'field_data_field_newsroom_service_type';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['field'] = 'field_newsroom_service_type_value';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['value'] = 'Newsletter';
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['newsletter_subscription'] = $view;

  $view = new view();
  $view->name = 'newsroom_related_documents';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom related documents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'nexteuropa_bem_listing';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: URL */
  $handler->display->display_options['fields']['field_newsroom_documents']['id'] = 'field_newsroom_documents';
  $handler->display->display_options['fields']['field_newsroom_documents']['table'] = 'field_data_field_newsroom_documents';
  $handler->display->display_options['fields']['field_newsroom_documents']['field'] = 'field_newsroom_documents';
  $handler->display->display_options['fields']['field_newsroom_documents']['ui_name'] = 'URL';
  $handler->display->display_options['fields']['field_newsroom_documents']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_documents']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_documents']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_documents']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_newsroom_documents']['type'] = 'link_plain';
  $handler->display->display_options['fields']['field_newsroom_documents']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_documents']['delta_offset'] = '0';
  /* Field: Text */
  $handler->display->display_options['fields']['field_newsroom_documents_1']['id'] = 'field_newsroom_documents_1';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['table'] = 'field_data_field_newsroom_documents';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['field'] = 'field_newsroom_documents';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['ui_name'] = 'Text';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_documents_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_documents_1']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['type'] = 'link_title_plain';
  $handler->display->display_options['fields']['field_newsroom_documents_1']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_documents_1']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
  <span class="icon icon--file file__icon"></span>
  <div class="file__metadata">
     <a href="[field_newsroom_documents]">[field_newsroom_documents_1]</a>
  </div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
    'newsroom_item' => 'newsroom_item',
  );
  /* Filter criterion: Content: Related Documents (field_newsroom_documents:url) */
  $handler->display->display_options['filters']['field_newsroom_documents_url']['id'] = 'field_newsroom_documents_url';
  $handler->display->display_options['filters']['field_newsroom_documents_url']['table'] = 'field_data_field_newsroom_documents';
  $handler->display->display_options['filters']['field_newsroom_documents_url']['field'] = 'field_newsroom_documents_url';
  $handler->display->display_options['filters']['field_newsroom_documents_url']['operator'] = 'not empty';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['newsroom_related_documents'] = $view;

  $view = new view();
  $view->name = 'newsroom_services';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsroom services';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Central Newsletters';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '86400';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '86400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Image */
  $handler->display->display_options['fields']['field_newsroom_service_image']['id'] = 'field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['table'] = 'field_data_field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['field'] = 'field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_service_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_newsroom_service_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Newsroom Service ID */
  $handler->display->display_options['fields']['field_newsroom_service_id']['id'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['table'] = 'field_data_field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['field'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_id']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: Entity translation: Sample: translated */
  $handler->display->display_options['fields']['field_newsroom_service_sample_et']['id'] = 'field_newsroom_service_sample_et';
  $handler->display->display_options['fields']['field_newsroom_service_sample_et']['table'] = 'field_data_field_newsroom_service_sample';
  $handler->display->display_options['fields']['field_newsroom_service_sample_et']['field'] = 'field_newsroom_service_sample_et';
  $handler->display->display_options['fields']['field_newsroom_service_sample_et']['label'] = 'Sample';
  $handler->display->display_options['fields']['field_newsroom_service_sample_et']['click_sort_column'] = 'url';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';
  /* Filter criterion: Taxonomy term: Basic mailing (field_newsroom_basic_mailing) */
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['id'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['table'] = 'field_data_field_newsroom_basic_mailing';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['field'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['value'] = array(
    1 => '1',
  );

  /* Display: Central newsletters */
  $handler = $view->new_display('block', 'Central newsletters', 'central');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';
  /* Filter criterion: Taxonomy term: Basic mailing (field_newsroom_basic_mailing) */
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['id'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['table'] = 'field_data_field_newsroom_basic_mailing';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['field'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Taxonomy term: Mailing exists (field_newsroom_mailing_exists) */
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['id'] = 'field_newsroom_mailing_exists_value';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['table'] = 'field_data_field_newsroom_mailing_exists';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['field'] = 'field_newsroom_mailing_exists_value';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['block_caching'] = '8';

  /* Display: Basic newsletters */
  $handler = $view->new_display('block', 'Basic newsletters', 'basic');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Other newsletters';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';
  /* Filter criterion: Taxonomy term: Basic mailing (field_newsroom_basic_mailing) */
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['id'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['table'] = 'field_data_field_newsroom_basic_mailing';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['field'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['value'] = array(
    0 => '0',
  );
  /* Filter criterion: Taxonomy term: Mailing exists (field_newsroom_mailing_exists) */
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['id'] = 'field_newsroom_mailing_exists_value';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['table'] = 'field_data_field_newsroom_mailing_exists';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['field'] = 'field_newsroom_mailing_exists_value';
  $handler->display->display_options['filters']['field_newsroom_mailing_exists_value']['value'] = array(
    1 => '1',
  );
  $export['newsroom_services'] = $view;

  return $export;
}
