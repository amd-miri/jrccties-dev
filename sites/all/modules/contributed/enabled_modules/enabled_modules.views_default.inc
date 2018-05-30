<?php
/**
 * @file
 * Views hook implementations for enabled_modules.
 */

/**
 * Implements hook_views_default_views().
 */
function enabled_modules_views_default_views() {
  /*
   * View 'enabled_modules_list'
   */
  $view = new view();
  $view->name = 'enabled_modules';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'system';
  $view->human_name = 'Enabled Modules';
  $view->core = 7;
  $view->api_version = 3;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Enabled Modules';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view enabled modules';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['grouping'] = 'info_project';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: System: Display name */
  $handler->display->display_options['fields']['info_name']['id'] = 'info_name';
  $handler->display->display_options['fields']['info_name']['table'] = 'system';
  $handler->display->display_options['fields']['info_name']['field'] = 'info_name';
  $handler->display->display_options['fields']['info_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['info_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_name']['hide_alter_empty'] = 0;
  /* Field: System: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'system';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['name']['alter']['text'] = '[info_name] ([name])';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  /* Field: System: Project */
  $handler->display->display_options['fields']['info_project']['id'] = 'info_project';
  $handler->display->display_options['fields']['info_project']['table'] = 'system';
  $handler->display->display_options['fields']['info_project']['field'] = 'info_project';
  $handler->display->display_options['fields']['info_project']['exclude'] = TRUE;
  $handler->display->display_options['fields']['info_project']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['path'] = 'http://drupal.org/[info_project]';
  $handler->display->display_options['fields']['info_project']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['external'] = 1;
  $handler->display->display_options['fields']['info_project']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_project']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_project']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_project']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_project']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_project']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_project']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_project']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_project']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['info_project']['system_info_project_link'] = 1;
  /* Filter criterion: System: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'system';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'module' => 'module',
  );
  /* Filter criterion: System: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'system';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'enabled-modules';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Enabled Modules';
  $handler->display->display_options['menu']['weight'] = '0';

  $views[$view->name] = $view;

  /*
   * View 'enabled_modules_admin'
   */
  $view = new view();
  $view->name = 'enabled_modules_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'system';
  $view->human_name = 'Enabled Modules_admin';
  $view->core = 7;
  $view->api_version = 3;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Enabled Modules';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access site reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'filename' => 'filename',
    'info_configure' => 'info_configure',
    'info_description' => 'info_description',
    'info_name' => 'info_name',
    'info_package' => 'info_package',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'filename' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'info_configure' => array(
      'align' => '',
      'separator' => '',
    ),
    'info_description' => array(
      'align' => '',
      'separator' => '',
    ),
    'info_name' => array(
      'align' => '',
      'separator' => '',
    ),
    'info_package' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: System: Filename */
  $handler->display->display_options['fields']['filename']['id'] = 'filename';
  $handler->display->display_options['fields']['filename']['table'] = 'system';
  $handler->display->display_options['fields']['filename']['field'] = 'filename';
  $handler->display->display_options['fields']['filename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['filename']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['external'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['filename']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['filename']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['filename']['alter']['html'] = 0;
  $handler->display->display_options['fields']['filename']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['filename']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['filename']['hide_empty'] = 0;
  $handler->display->display_options['fields']['filename']['empty_zero'] = 0;
  $handler->display->display_options['fields']['filename']['hide_alter_empty'] = 0;
  /* Field: System: Package */
  $handler->display->display_options['fields']['info_package']['id'] = 'info_package';
  $handler->display->display_options['fields']['info_package']['table'] = 'system';
  $handler->display->display_options['fields']['info_package']['field'] = 'info_package';
  $handler->display->display_options['fields']['info_package']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['external'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_package']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_package']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_package']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_package']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_package']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_package']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_package']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_package']['hide_alter_empty'] = 0;
  /* Field: System: Display name */
  $handler->display->display_options['fields']['info_name']['id'] = 'info_name';
  $handler->display->display_options['fields']['info_name']['table'] = 'system';
  $handler->display->display_options['fields']['info_name']['field'] = 'info_name';
  $handler->display->display_options['fields']['info_name']['label'] = 'Name';
  $handler->display->display_options['fields']['info_name']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['info_name']['alter']['text'] = '<strong>[info_name]</strong> ([filename])';
  $handler->display->display_options['fields']['info_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_name']['hide_alter_empty'] = 0;
  /* Field: System: Description */
  $handler->display->display_options['fields']['info_description']['id'] = 'info_description';
  $handler->display->display_options['fields']['info_description']['table'] = 'system';
  $handler->display->display_options['fields']['info_description']['field'] = 'info_description';
  $handler->display->display_options['fields']['info_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_description']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_description']['hide_alter_empty'] = 0;
  /* Field: System: Configure */
  $handler->display->display_options['fields']['info_configure']['id'] = 'info_configure';
  $handler->display->display_options['fields']['info_configure']['table'] = 'system';
  $handler->display->display_options['fields']['info_configure']['field'] = 'info_configure';
  $handler->display->display_options['fields']['info_configure']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['external'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['info_configure']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['info_configure']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['info_configure']['alter']['html'] = 0;
  $handler->display->display_options['fields']['info_configure']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['info_configure']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['info_configure']['hide_empty'] = 0;
  $handler->display->display_options['fields']['info_configure']['empty_zero'] = 0;
  $handler->display->display_options['fields']['info_configure']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['info_configure']['system_info_configure_link'] = 1;
  /* Filter criterion: System: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'system';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: System: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'system';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'module' => 'module',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/enabled-modules/enabled';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Enabled';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Enabled Modules';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Disabled Modules';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: System: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'system';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  /* Filter criterion: System: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'system';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'module' => 'module',
  );
  /* Filter criterion: System: Schema version */
  $handler->display->display_options['filters']['schema_version']['id'] = 'schema_version';
  $handler->display->display_options['filters']['schema_version']['table'] = 'system';
  $handler->display->display_options['filters']['schema_version']['field'] = 'schema_version';
  $handler->display->display_options['filters']['schema_version']['operator'] = '!=';
  $handler->display->display_options['filters']['schema_version']['value']['value'] = '-1';
  $handler->display->display_options['path'] = 'admin/reports/enabled-modules/disabled';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Disabled';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Page 2 */
  $handler = $view->new_display('page', 'Page 2', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Not Installed Modules';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: System: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'system';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  /* Filter criterion: System: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'system';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'module' => 'module',
  );
  /* Filter criterion: System: Schema version */
  $handler->display->display_options['filters']['schema_version']['id'] = 'schema_version';
  $handler->display->display_options['filters']['schema_version']['table'] = 'system';
  $handler->display->display_options['filters']['schema_version']['field'] = 'schema_version';
  $handler->display->display_options['filters']['schema_version']['value']['value'] = '-1';
  $handler->display->display_options['path'] = 'admin/reports/enabled-modules/not-installed';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Not installed';
  $handler->display->display_options['menu']['weight'] = '10';
  $views[$view->name] = $view;

  return $views;
}
