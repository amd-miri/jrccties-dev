<?php

/**
 * Implements hook_migrate_api().
 */
function table_migration_migrate_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}

class DrupalTableMigration extends DrupalMigration {
  /**
   * The schema of the current table.
   *
   * @var array
   */
  protected $schema = NULL;

  /**
   * The name of the current table.
   *
   * @var string
   */
  protected $tableName = NULL;
  
  public function __construct(array $arguments) {
    parent::__construct($arguments);
	$this->description = $arguments['description'];
	$this->tableName = $arguments['table_name'];
    $this->schema = drupal_get_schema($this->tableName);
	
    $this->map = new MigrateSQLMap($this->machineName,
        MigrateDestinationTable::getKeySchema($this->tableName),
        MigrateDestinationTable::getKeySchema($this->tableName)
      );
    $query =  $query = $this->query();
	$source_fields = $this->sourceFields();
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationTable($this->tableName);
	
    $colums = $this->columns();
    // Setup common mappings
    $this->addSimpleMappings($colums);      
  
  }

  /**
   * Query for basic node fields from Drupal 6.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = Database::getConnection('default', $this->sourceConnection)
	   ->select($this->tableName)
      ->fields($this->tableName);

    return $query;
  } 
  
  /**
   * Returns a list of fields available to be mapped.
   *
   * @return array
   *  Keys: machine names of the fields (to be passed to addFieldMapping)
   *  Values: Human-friendly descriptions of the fields.
   */
  public function sourceFields() {
    $fields = array();
    foreach ($this->schema['fields'] as $column => $schema) {
      $fields[$column] = t('!type', array('!type' => $schema['type']));
    }
    return $fields;
  }  
  
  /**
   * Returns columns of table.
   *
   * @return array
   */
  public function columns() {
    $columns = array();
    foreach ($this->schema['fields'] as $column => $schema) {
      $columns[] = $column;
    }
    return $columns;
  }  

}

