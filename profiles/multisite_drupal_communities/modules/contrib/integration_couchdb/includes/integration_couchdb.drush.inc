<?php

/**
 * @file
 * Contains Drush-related hook implementations.
 */

use Drupal\integration\Backend\BackendFactory;

/**
 * Implements hook_drush_command().
 */
function integration_couchdb_drush_command() {
  $items = array();
  $items['integration-couchdb-test-connection'] = array(
    'description' => 'Test CouchDB backend connection.',
    'aliases' => array('ictc'),
    'arguments' => [
      'backend' => 'The backend machine name.',
    ],
  );
  return $items;
}

/**
 * Callback for the integration-couchdb-test-connection command.
 */
function drush_integration_couchdb_test_connection($backend_name) {
  if (!$backend_name) {
    return drush_log(dt('Please specify a backend as an argument.'), 'error');
  }
  $backend = BackendFactory::getInstance($backend_name);
  $base_url = $backend->getConfiguration()->getPluginSetting('backend.base_url');
  if ($backend->isAlive()) {
    drush_log(dt('The CouchDB backend at !url is alive.',
      ['!url' => $base_url]), 'success');
  }
  else {
    drush_log(dt('The CouchDB backend at !url could not be contacted.',
      ['!url' => $base_url]), 'error');
  }
}
