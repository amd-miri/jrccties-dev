<?php
/**
 * @file
 * Migration of the custom file fields from The old JRC database.
 */

/**
 * Implements hook_migrate_api().
 */
function jrc_file_fields_import_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'files_fields' => array(
        'title' => t('Files Fields'),
      ),
    ),
    'migrations' => array(
      'FilesFieldsCopyright' => array(
        'class_name' => 'FilesFieldsCopyrightMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsDescription' => array(
        'class_name' => 'FilesFieldsDescriptionMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsImageAlt' => array(
        'class_name' => 'FilesFieldsImageAltMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsImageTitle' => array(
        'class_name' => 'FilesFieldsImageTitleMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsImageNormal' => array(
        'class_name' => 'FilesFieldsImageNormalMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsImageThumbnail' => array(
        'class_name' => 'FilesFieldsImageThumbnailMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsInternalNote' => array(
        'class_name' => 'FilesFieldsInternalNoteMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsPlace' => array(
        'class_name' => 'FilesFieldsPlaceMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsKeyword' => array(
        'class_name' => 'FilesFieldsKeywordMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsResearchAreas' => array(
        'class_name' => 'FilesFieldsResearchAreasMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsInstitutes' => array(
        'class_name' => 'FilesFieldsInstitutesMigration',
        'group_name' => 'files_fields',
      ),
      'FilesFieldsIdentities' => array(
        'class_name' => 'FilesFieldsIdentitiesMigration',
        'group_name' => 'files_fields',
      ),
    ),
  );
  return $api;
}

/**
 * Migration of the Copyright field content.
 */
class FilesFieldsCopyrightMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Copyright Migration');
    $table_name = 'field_data_field_file_copyright_info';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_copyright_info_value' => t('File copyright value'),
      'field_file_copyright_info_format' => t('File copyright format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_copyright_info_value', 'field_file_copyright_info_value');
    $this->addFieldMapping('field_file_copyright_info_format', 'field_file_copyright_info_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Copyright field.'));
    }
  }

}

/**
 * Migration of the Description field content.
 */
class FilesFieldsDescriptionMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Description Migration');
    $table_name = 'field_data_field_file_description';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_description_value' => t('File description value'),
      'field_file_description_summary' => t('File description summary'),
      'field_file_description_format' => t('File description format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_description_value', 'field_file_description_value');
    $this->addFieldMapping('field_file_description_summary', 'field_file_description_summary');
    $this->addFieldMapping('field_file_description_format', 'field_file_description_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Description field.'));
    }
  }

}

/**
 * Migration of the Image Alt field content.
 */
class FilesFieldsImageAltMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Image Alt Migration');
    $table_name = 'field_data_field_file_image_alt_text';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_image_alt_text_value' => t('File Image Alt value'),
      'field_file_image_alt_text_format' => t('File Image Alt format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_image_alt_text_value', 'field_file_image_alt_text_value');
    $this->addFieldMapping('field_file_image_alt_text_format', 'field_file_image_alt_text_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Image Alt field.'));
    }
  }

}

/**
 * Migration of the Image Title field content.
 */
class FilesFieldsImageTitleMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Image Title Migration');
    $table_name = 'field_data_field_file_image_title_text';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_image_title_text_value' => t('File Image Title value'),
      'field_file_image_title_text_format' => t('File Image Title format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_image_title_text_value', 'field_file_image_title_text_value');
    $this->addFieldMapping('field_file_image_title_text_format', 'field_file_image_title_text_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Image Title field.'));
    }
  }

}

/**
 * Migration of the Image Normal field content.
 */
class FilesFieldsImageNormalMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Image Normal Migration');
    $table_name = 'field_data_field_file_image_normal';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_image_normal_fid' => t('File Image Normal fid'),
      'field_file_image_normal_width' => t('File Image Normal width'),
      'field_file_image_normal_height' => t('File Image Normal height'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_image_normal_fid', 'field_file_image_normal_fid')->sourceMigration('71582fc13File');
    $this->addFieldMapping('field_file_image_normal_width', 'field_file_image_normal_width');
    $this->addFieldMapping('field_file_image_normal_height', 'field_file_image_normal_height');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}

/**
 * Migration of the Image Thumbnail field content.
 */
class FilesFieldsImageThumbnailMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Image Thumbnail Migration');
    $table_name = 'field_data_field_file_image_thumbnail';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_image_thumbnail_fid' => t('File Image Thumbnail fid'),
      'field_file_image_thumbnail_width' => t('File Image Thumbnail width'),
      'field_file_image_thumbnail_height' => t('File Image Thumbnail height'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_image_thumbnail_fid', 'field_file_image_thumbnail_fid')->sourceMigration('71582fc13File');
    $this->addFieldMapping('field_file_image_thumbnail_width', 'field_file_image_thumbnail_width');
    $this->addFieldMapping('field_file_image_thumbnail_height', 'field_file_image_thumbnail_height');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}


/**
 * Migration of the Internal note field content.
 */
class FilesFieldsInternalNoteMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Internal Note Migration');
    $table_name = 'field_data_field_file_internal_note';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_internal_note_value' => t('File Internal Note value'),
      'field_file_internal_note_format' => t('File Internal Note format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_internal_note_value', 'field_file_internal_note_value');
    $this->addFieldMapping('field_file_internal_note_format', 'field_file_internal_note_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Internal Note field.'));
    }
  }

}

/**
 * Migration of the Place field content.
 */
class FilesFieldsPlaceMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Place Migration');
    $table_name = 'field_data_field_file_place';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_file_place_value' => t('File Place value'),
      'field_file_place_format' => t('File Place format'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_file_place_value', 'field_file_place_value');
    $this->addFieldMapping('field_file_place_format', 'field_file_place_format');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}

/**
 * Migration of the keyword field content.
 */
class FilesFieldsKeywordMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Keyword Migration');
    $table_name = 'field_data_field_tags';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
        'field_tags_tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'null' => TRUE,
          'description' => 'JRC Keyword TID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_tags_tid' => t('File Keyword tid'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
              ->condition(db_or()->condition('bundle', 'image', '=')
                               ->condition('bundle', 'video', '=')
                               ->condition('bundle', 'audio', '=')
                               ->condition('bundle', 'document', '=')
                               ->condition('bundle', 'archive', '=')
                        )
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_tags_tid', 'field_tags_tid')->sourceMigration('71582fc13Termtags');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}

/**
 * Migration of the Research Areas field content.
 */
class FilesFieldsResearchAreasMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Research Areas Migration');
    $table_name = 'field_data_field_research_areas';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
        'field_research_areas_tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'null' => TRUE,
          'description' => 'JRC Research Areas TID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_research_areas_tid' => t('File Keyword tid'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
              ->condition(db_or()->condition('bundle', 'image', '=')
                               ->condition('bundle', 'video', '=')
                               ->condition('bundle', 'audio', '=')
                               ->condition('bundle', 'document', '=')
                               ->condition('bundle', 'archive', '=')
                        )
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_research_areas_tid', 'field_research_areas_tid')->sourceMigration('71582fc13Termresearch_areas');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}

/**
 * Migration of the Institutes field content.
 */
class FilesFieldsInstitutesMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Institutes Migration');
    $table_name = 'field_data_field_institutes';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
        'field_institutes_tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'null' => TRUE,
          'description' => 'JRC Institutes TID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_institutes_tid' => t('File Keyword tid'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
              ->condition(db_or()->condition('bundle', 'image', '=')
                               ->condition('bundle', 'video', '=')
                               ->condition('bundle', 'audio', '=')
                               ->condition('bundle', 'document', '=')
                               ->condition('bundle', 'archive', '=')
                        )
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_institutes_tid', 'field_institutes_tid')->sourceMigration('71582fc13Terminstitutes');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}

/**
 * Migration of the Identities field content.
 */
class FilesFieldsIdentitiesMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Files Fields Identities Migration');
    $table_name = 'field_data_field_identities';
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'entity_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'JRC File ID',
        ),
        'field_identities_tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'null' => TRUE,
          'description' => 'JRC Identities TID',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name),
      'jrc_legacy_db'
    );

    // Source fields available.
    $fields = array(
      'entity_type' => t('Entity type'),
      'bundle' => t('Bundle'),
      'deleted' => t('Deleted'),
      'entity_id' => t('Entity ID'),
      'revision_id' => t('Revision ID'),
      'language' => t('Language'),
      'delta' => t('Delta'),
      'field_identities_tid' => t('File Keyword tid'),
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select($table_name, 'ci')
              ->fields('ci')
              ->condition(db_or()->condition('bundle', 'image', '=')
                               ->condition('bundle', 'video', '=')
                               ->condition('bundle', 'audio', '=')
                               ->condition('bundle', 'document', '=')
                               ->condition('bundle', 'archive', '=')
                        )
      ->groupBy('entity_id')
      ->groupBy('field_identities_tid')
            ->orderBy('entity_id', 'ASC');

    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('entity_type')->defaultValue('file');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('71582fc13File');
    $this->addFieldMapping('revision_id')->defaultValue('NULL');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('field_identities_tid', 'field_identities_tid')->sourceMigration('71582fc13Termidentities');
  }

  /**
   * Migrate prepare function.
   */
  public function prepare($node, stdClass $row) {
    if ($node->entity_id == NULL) {
      throw new MigrateException(t('One record has not a related content in the destination for the Place field.'));
    }
  }

}
