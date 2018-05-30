<?php

/**
 * @file
 * Views data and handlers for the views_system module.
 */


/**
 * @defgroup views_system_module views_system.module handlers
 *
 * @{
 */


/**
 * Implements hook_views_data_alter().
 */
function views_system_views_data_alter(&$data) {

  // Table field: system.filename
  $data['system']['filename']['title'] = t('Filename');
  // Table field: system.name
  $data['system']['name']['title'] = t('Name');
  // Table field: system.type
  $data['system']['type']['field']['handler'] = 'views_handler_field_system_type';
  $data['system']['type']['filter']['handler'] = 'views_handler_filter_in_operator';
  $data['system']['type']['filter']['options callback'] = '_views_system_get_type';
  // Table field: system.owner
  $data['system']['owner'] = array(
    'title' => t('Owner'),
    'help' => t("A theme's 'parent'. Can be either a theme or an engine."),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'owner',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Table field: system.status
  $data['system']['status']['filter']['handler'] = 'views_handler_filter_system_status';
  $data['system']['status']['filter']['label'] = t('Status');
  // Table field: system.bootstrap
  $data['system']['bootstrap'] = array(
    'title' => t('Bootstrap'),
    'help' => t("Boolean indicating whether this module is loaded during Drupal's early bootstrapping phase (e.g. even before the page cache is consulted)."),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'bootstrap',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Bootstrap'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Table field: system.weight
  $data['system']['weight'] = array(
    'title' => t('Weight'),
    'help' => t("The order in which this module's hooks should be invoked relative to other modules. Equal-weighted modules are ordered by name."),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'weight',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Table field: system.info
  $data['system']['info'] = array(
    'title' => t('Info'),
    'help' => t('A serialized array containing information from the .info file.'),
    'field' => array(
      'handler' => 'views_handler_field_serialized',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'info',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['system']['info_basetheme'] = array(
    'real field' => 'info',
    'title' => t('Base theme'),
    'help' => t('The name of the base theme.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_basetheme',
    ),
  );
  $data['system']['info_configure'] = array(
    'real field' => 'info',
    'title' => t('Configure'),
    'help' => t('The configure line of the module.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_configure',
    ),
  );
  $data['system']['info_core'] = array(
    'real field' => 'info',
    'title' => t('Core'),
    'help' => t('The Drupal core version of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_core',
    ),
  );
  $data['system']['info_datestamp'] = array(
    'real field' => 'info',
    'title' => t('Date stamp'),
    'help' => t('The date stamp of the project this item belongs to.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_datestamp',
    ),
  );
  $data['system']['info_dependencies'] = array(
    'real field' => 'info',
    'title' => t('Dependencies'),
    'help' => t('Required modules.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_dependencies',
      'label' => t('Depends on'),
    ),
  );
  $data['system']['info_description'] = array(
    'real field' => 'info',
    'title' => t('Description'),
    'help' => t('The brief description of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_description',
    ),
  );
  $data['system']['info_engine'] = array(
    'real field' => 'info',
    'title' => t('Engine'),
    'help' => t('The name of the theme engine; typically: engine = phptemplate.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_engine',
    ),
  );
  $data['system']['info_features'] = array(
    'real field' => 'info',
    'title' => t('Features'),
    'help' => t('The features of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_features',
    ),
  );
  $data['system']['info_files'] = array(
    'real field' => 'info',
    'title' => t('Files'),
    'help' => t('The declared files of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_files',
    ),
  );
  $data['system']['info_hidden'] = array(
    'real field' => 'info',
    'title' => t('Hidden'),
    'help' => t('Boolean indicating whether this item is hidden.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_hidden',
      'type' => 'yes-no',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_system_info_hidden',
      'label' => t('Hidden'),
      'type' => 'yes-no',
    ),
  );
  $data['system']['info_name'] = array(
    'real field' => 'info',
    'title' => t('Display name'),
    'help' => t('The real name of the item for display purposes; e.g. Node.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_name',
    ),
  );
  $data['system']['info_package'] = array(
    'real field' => 'info',
    'title' => t('Package'),
    'help' => t('The name of the package this item belongs to.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_package',
    ),
  );
  $data['system']['info_php'] = array(
    'real field' => 'info',
    'title' => t('PHP'),
    'help' => t('The minimum PHP version of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_php',
    ),
  );
  $data['system']['info_project'] = array(
    'real field' => 'info',
    'title' => t('Project'),
    'help' => t('The name of the project this item belongs to.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_project',
    ),
  );
  $data['system']['info_regions'] = array(
    'real field' => 'info',
    'title' => t('Regions'),
    'help' => t('The regions of the theme.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_regions',
    ),
  );
  $data['system']['info_regions_hidden'] = array(
    'real field' => 'info',
    'title' => t('Regions hidden'),
    'help' => t('The hidden regions of the theme.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_regions_hidden',
    ),
  );
  $data['system']['info_screenshot'] = array(
    'real field' => 'info',
    'title' => t('Screenshot'),
    'help' => t('The screenshot of the theme.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_screenshot',
    ),
  );
  $data['system']['info_scripts'] = array(
    'real field' => 'info',
    'title' => t('Scripts'),
    'help' => t('The declared Javascript files of the system item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_scripts',
    ),
  );
  $data['system']['info_settings'] = array(
    'real field' => 'info',
    'title' => t('Settings'),
    'help' => t('The default settings of the theme.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_settings',
    ),
  );
  $data['system']['info_stylesheets'] = array(
    'real field' => 'info',
    'title' => t('Stylesheets'),
    'help' => t('The declared CSS files of the system item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_stylesheets',
    ),
  );
  $data['system']['info_version'] = array(
    'real field' => 'info',
    'title' => t('Version'),
    'help' => t('The version of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_system_info_version',
    ),
  );
  // Additional field: Drupal core
  $data['system']['drupal_core'] = array(
    'real field' => 'filename',
    'title' => t('Drupal core'),
    'help' => t('Boolean indicating whether this item is part of Drupal core.'),
    'field' => array(
      'handler' => 'views_handler_field_system_drupal_core',
      'type' => 'yes-no',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_system_drupal_core',
      'label' => t('Drupal core'),
      'type' => 'yes-no',
    ),
  );
}


/**
 * @}
 */
