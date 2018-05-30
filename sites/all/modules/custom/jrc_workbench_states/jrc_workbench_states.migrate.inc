<?php
/**
 * @file
 * Migration of Workbench states from the Source Databse of Migrate module.
 */

/**
 * Migration class to import Workbench states from a Source Databse.
 */
class WorkbenchStateMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
  
  protected function query() {
    // Get the default query 
    $query = parent::query();
    $query->Join('workbench_moderation_node_history', 'd', 'n.nid=d.nid');
    $query->fields('d', array('state'));
    return $query;
  }

}

/**
 * Implements hook_migrate_api().
 */
function jrc_workbench_states_migrate_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}