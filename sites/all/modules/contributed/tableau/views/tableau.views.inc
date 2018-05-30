<?php

/**
 * Implements hook_views_data().
 */
function tableau_views_data() {
  $data = array();
  $data['_projects'] = _tableau_views_data_projects();
  $data['_sites'] = _tableau_views_data_sites();
  $data['_tags'] = _tableau_views_data_tags();
  $data['_users'] = _tableau_views_data_users();
  $data['_views'] = _tableau_views_data_views();
  $data['_workbooks'] = _tableau_views_data_workbooks();
  return $data;
}

function _tableau_views_data_projects() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau Project');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau Project'),
    'help' => t('Project are collections of Tableau workbooks'),
    'access query tag' => 'tableau_access',
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_workbooks' => array(
      'left_field' => 'project_id',
      'field' => 'id',
    ),
  );

  // Fields
  $data['id'] = array(
    'title' => t('Project ID'),
    'help' => t('Unique ID for the project'),
    'field' => array(
      'handler' => 'views_handler_field',
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
  $data['name'] = array(
    'title' => t('Project name'),
    'help' => t('Name of the project'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['created_at'] = array(
    'title' => t('Created at'),
    'help' => t('Date of creation'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  $data['owner_id'] = array(
    'title' => t('Owner'),
    'help' => t('Owner of the project'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_users',
      'base field' => 'id',
      'label' => t('Project owner'),
    ),
  );
  $data['site_id'] = array(
    'title' => t('Site'),
    'help' => t('Site that contains the project'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_sites',
      'base field' => 'id',
      'label' => t('Project site'),
    ),
  );

  return $data;
}

function _tableau_views_data_sites() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau Site');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau Site'),
    'help' => t('Sites are used to organize Tableau content'),
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_projects' => array(
      'left_field' => 'site_id',
      'field' => 'id',
    ),
    '_tags' => array(
      'left_field' => 'site_id',
      'field' => 'id',
    ),
    '_users' => array(
      'left_field' => 'site_id',
      'field' => 'id',
    ),
    '_views' => array(
      'left_field' => 'site_id',
      'field' => 'id',
    ),
    '_workbooks' => array(
      'left_field' => 'site_id',
      'field' => 'id',
    ),
  );

  // Fields
  $data['id'] = array(
    'title' => t('Site ID'),
    'help' => t('Unique ID for the site'),
    'field' => array(
      'handler' => 'views_handler_field',
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
  $data['name'] = array(
    'title' => t('Site name'),
    'help' => t('Site name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['url_namespace'] = array(
    'title' => t('URL Namespace'),
    'help' => t('Portion of URL specific to the site'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['status'] = array(
    'title' => t('Status'),
    'help' => t('Site status'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

function _tableau_views_data_tags() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau Tag');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau Tag'),
    'help' => t('Tags are used to categorize Tableau content'),
    'access query tag' => 'tableau_access',
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_views' => array(
      'left_field' => 'id',
      'field' => 'object_id',
      'extra' => array(array('field' => 'object_type', 'value' => 'View')),
    ),
    '_workbooks' => array(
      'left_field' => 'id',
      'field' => 'object_id',
      'extra' => array(array('field' => 'object_type', 'value' => 'Workbook')),
    ),
  );

  // Fields
  $data['tag_id'] = array(
    'title' => t('Tag ID'),
    'help' => t('ID for the tag'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['tag_name'] = array(
    'title' => t('Tag name'),
    'help' => t('Human-readable tag'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['object_type'] = array(
    'title' => t('Object type'),
    'help' => t('Type of the object being tagged'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['taggable_id'] = array(
    'title' => t('Taggable ID'),
    'help' => t('ID of the object being tagged'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['tagged_view'] = array(
    'real field' => 'object_id',
    'title' => t('Tagged view'),
    'help' => t('Tagged view'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_views',
      'base field' => 'id',
      'label' => t('Tagged view'),
    ),
  );
  $data['tagged_workbook'] = array(
    'real field' => 'object_id',
    'title' => t('Tagged workbook'),
    'help' => t('Tagged workbook'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_workbooks',
      'base field' => 'id',
      'label' => t('Tagged workbook'),
    ),
  );
  $data['user_id'] = array(
    'title' => t('User'),
    'help' => t('User that the tag belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_users',
      'base field' => 'id',
      'label' => t('Tag user'),
    ),
  );
  $data['site_id'] = array(
    'title' => t('Site'),
    'help' => t('Site that the tag belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_sites',
      'base field' => 'id',
      'label' => t('Tag site'),
    ),
  );

  return $data;
}

function _tableau_views_data_users() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau User');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau User'),
    'help' => t('Users are owners of Tableau content'),
    'access query tag' => 'tableau_access',
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_projects' => array(
      'left_field' => 'owner_id',
      'field' => 'id',
    ),
    '_tags' => array(
      'left_field' => 'user_id',
      'field' => 'id',
    ),
    '_views' => array(
      'left_field' => 'owner_id',
      'field' => 'id',
    ),
    '_workbooks' => array(
      'left_field' => 'owner_id',
      'field' => 'id',
    ),
  );

  // Fields
  $data['id'] = array(
    'title' => t('User ID'),
    'help' => t('Unique ID for the user'),
    'field' => array(
      'handler' => 'views_handler_field',
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
  $data['name'] = array(
    'title' => t('Username'),
    'help' => t('Machine-readable username'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['login_at'] = array(
    'title' => t('Login at'),
    'help' => t('Date of last login'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  $data['friendly_name'] = array(
    'title' => t('Friendly name'),
    'help' => t('Human-readable name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['licensing_role_id'] = array(
    'title' => t('Licensing role ID'),
    'help' => t('Licensing role ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['licensing_role_name'] = array(
    'title' => t('Licensing role name'),
    'help' => t('Licensing role name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['domain_id'] = array(
    'title' => t('Domain ID'),
    'help' => t('Unique ID for the domain'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['system_user_id'] = array(
    'title' => t('System user ID'),
    'help' => t('System user ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['domain_name'] = array(
    'title' => t('Domain name'),
    'help' => t('Domain name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['domain_short_name'] = array(
    'title' => t('Domain short name'),
    'help' => t('Domain short name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['site_id'] = array(
    'title' => t('Site'),
    'help' => t('Site that the user belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_sites',
      'base field' => 'id',
      'label' => t('User site'),
    ),
  );

  return $data;
}

function _tableau_views_data_views() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau View');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau View'),
    'help' => t('Views are renderable Tableau content'),
    'access query tag' => 'tableau_access',
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_tags' => array(
      'left_field' => 'object_id',
      'field' => 'id',
    ),
  );

  // Fields
  $data['id'] = array(
    'title' => t('View ID'),
    'help' => t('Unique ID for the view'),
    'field' => array(
      'handler' => 'views_handler_field',
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
  $data['name'] = array(
    'title' => t('View name'),
    'help' => t('machine-readable name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['view_url'] = array(
    'title' => t('View URL'),
    'help' => t('Portion of URL specific to the view'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['created_at'] = array(
    'title' => t('Created at'),
    'help' => t('Date of creation'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  $data['owner_id'] = array(
    'title' => t('Owner'),
    'help' => t('Owner of the view'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_users',
      'base field' => 'id',
      'label' => t('View owner'),
    ),
  );
  $data['workbook_id'] = array(
    'title' => t('Workbook'),
    'help' => t('Workbook that the view belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_workbooks',
      'base field' => 'id',
      'label' => t('View workbook'),
    ),
  );
  $data['index'] = array(
    'title' => t('Index'),
    'help' => t('View index within a workbook'),
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
  $data['title'] = array(
    'title' => t('Title'),
    'help' => t('Human-readable title'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['caption'] = array(
    'title' => t('Caption'),
    'help' => t('Human-readable caption'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['site_id'] = array(
    'title' => t('Site'),
    'help' => t('Site that the view belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_sites',
      'base field' => 'id',
      'label' => t('View site'),
    ),
  );
  $data['static'] = array(
    'title' => t('Static image'),
    'help' => t('Displays a pre-generated static image of the view.'),
    'real field' => 'id',
    'field' => array(
      'handler' => 'tableau_views_handler_field_static',
    ),
  );
  $data['thumbnail'] = array(
    'title' => t('Thumbnail'),
    'help' => t('Displays a pre-generated thumbnail of the view.'),
    'real field' => 'id',
    'field' => array(
      'handler' => 'tableau_views_handler_field_thumbnail',
    ),
  );
  $data['tags'] = array(
    'real field' => 'id',
    'title' => t('Tags on view'),
    'help' => t('Relate views to tags. This will cause duplicated records if there are multiple tags.'),
    'field' => array(
      'title' => t('All tags'),
      'help' => t('Display all tags associated with a view.'),
      'handler' => 'tableau_views_handler_field_view_tags',
      'no group by' => TRUE,
    ),
  );

  return $data;
}

function _tableau_views_data_workbooks() {
  $data = array();

  // Table
  $data['table']['group'] = t('Tableau Workbook');
  $data['table']['base'] = array(
    'field' => 'id',
    'title' => t('Tableau Workbook'),
    'help' => t('Workbooks are groups of Tableau Views'),
    'access query tag' => 'tableau_access',
    'database' => 'tableau',
  );
  $data['table']['join'] = array(
    '_views' => array(
      'left_field' => 'workbook_id',
      'field' => 'id',
    ),
    '_tags' => array(
      'left_field' => 'object_id',
      'field' => 'id',
    ),
  );

  // Fields
  $data['id'] = array(
    'title' => t('Workbook ID'),
    'help' => t('Unique ID for the workbook'),
    'field' => array(
      'handler' => 'views_handler_field',
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
  $data['name'] = array(
    'title' => t('Workbook name'),
    'help' => t('Machine-readable name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['workbook_url'] = array(
    'title' => t('Workbook URL'),
    'help' => t('Portion of URL specific to the workbook'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['created_at'] = array(
    'title' => t('Created at'),
    'help' => t('Date of creation'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  $data['updated_at'] = array(
    'title' => t('Updated at'),
    'help' => t('Date of last update'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  $data['owner_id'] = array(
    'title' => t('Owner'),
    'help' => t('Owner of the workbook'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_users',
      'base field' => 'id',
      'label' => t('Workbook owner'),
    ),
  );
  $data['project_id'] = array(
    'title' => t('Project'),
    'help' => t('Project that the workbook belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_projects',
      'base field' => 'id',
      'label' => t('Workbook project'),
    ),
  );
  $data['size'] = array(
    'title' => t('Size'),
    'help' => t('Size of the workbook in bytes'),
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
  $data['view_count'] = array(
    'title' => t('View Count'),
    'help' => t('Number of views contained in the workbook'),
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
  $data['site_id'] = array(
    'title' => t('Site'),
    'help' => t('Site that the workbook belongs to'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => '_sites',
      'base field' => 'id',
      'label' => t('Workbook site'),
    ),
  );

  return $data;
}

/**
 * Implements hook_views_handlers().
 */
function tableau_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'tableau') . '/views/handlers',
    ),
    'handlers' => array(
      'tableau_views_handler_field_static' => array(
        'parent' => 'views_handler_field',
      ),
      'tableau_views_handler_field_thumbnail' => array(
        'parent' => 'views_handler_field',
      ),
      'tableau_views_handler_field_view_tags' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
    ),
  );
}

/**
 * Implements hook_views_plugins().
 */
function tableau_views_plugins() {
  return array(
    'row' => array(
      'tableau_view' => array(
        'title' => t('Tableau View'),
        'help' => t('Renders and displays Tableau views.'),
        'handler' => 'tableau_views_plugin_row_tableau_view',
        'base' => array('_views'),
        'uses fields' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-tableau-view',
      ),
    ),
    'argument validator' => array(
      'tableau_access' => array(
        'title' => t('Tableau access'),
        'handler' => 'tableau_views_plugin_argument_validate_tableau_access',
      ),
    ),
  );
}
