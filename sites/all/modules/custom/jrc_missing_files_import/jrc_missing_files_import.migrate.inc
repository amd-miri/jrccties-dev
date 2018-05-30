<?php
/**
 * @file
 * Migration of the custom file fields from The old JRC database.
 */

/**
 * Implements hook_migrate_api().
 */
function jrc_missing_files_import_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'missing_files' => array(
        'title' => t('Missing Files'),
      ),
    ),
    'migrations' => array(
      'MissingFiles' => array(
        'class_name' => 'MissingFilesMigration',
        'group_name' => 'missing_files',
      ),
    ),
  );
  return $api;
}

/**
 * Migration of the missing files.
 */

/**
 * Migration for files.
 */
class MissingFilesMigration extends Migration {

  protected $baseDir;

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import files.');
    $this->baseDir = 'https://ec.europa.eu/jrc/sites/default/files';

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sourceid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => t('Source ID'),
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $directories = array(
      $this->baseDir,
    );

    // Edit to include the desired extensions.
    $allowed = 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm';
    if (module_exists('file_entity')) {
      $allowed = variable_get('file_entity_default_allowed_extensions', $allowed);
    }
    $file_mask = '/^.*\.(' . str_replace(array(',', ' '), '|', $allowed) . ')$/i';
    $list = new MigrateListFiles($directories, $this->baseDir, $file_mask);
    // Send FALSE as second argument to prevent loading of file data, which we
    // don't need.
    $item = new MigrateItemFile($this->baseDir, FALSE);
    $fields = array('sourceid' => t('File name with path'));
    $this->source = new MigrateSourceList($list, $item, $fields);
    $this->destination = new MigrateDestinationFile('file', 'MigrateFileUri');

    // Save to the default file scheme.
    $this->addFieldMapping('destination_dir')
      ->defaultValue(variable_get('file_default_scheme', 'public') . '://');
    // Use the full file path in the file name so that we retain the directory
    // structure.
    $this->addFieldMapping('destination_file', 'destination_file');
    // Set the value to the file name, including path.
    $this->addFieldMapping('value', 'file_uri');
  }

  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $row->file_uri = $this->baseDir . $row->sourceid;

    // Remove the leading forward slash.
    $row->destination_file = substr($row->sourceid, 1);
  }
}
