<?php
/**
 * @file
 * Migration from Pubsy Oracle database.
 */

/**
 * Implements hook_migrate_api().
 */
function jrc_pubsy_import_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'pubsy' => array(
        'title' => t('Pubsy Publications'),
      ),
    ),
    'migrations' => array(
      'PubsyPublicationsCover' => array(
        'class_name' => 'PubsyPublicationsCoverMigration',
        'group_name' => 'pubsy',
      ),
      'PubsyPublications' => array(
        'class_name' => 'PubsyPublicationsMigration',
        'group_name' => 'pubsy',
      ),
    ),
  );
  return $api;
}

/**
 * Migration class to import Publicaion's covers.
 */
class PubsyPublicationsCoverMigration extends Migration {
  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Pubsy related Publications file Images');
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'ID' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Publication File Image ID',
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    // Source fields available from the Oracle table.
    $fields = array(
      'ID' => t('File ID'),
      'FILE_FILENAME' => t('File name'),
      'FILE_BINARY' => t('File doc'),
      'FILE_THUMBNAIL' => t('File thumbnail'),
    );

    $query = "
             SELECT 
                V_SHP_FILE.ID,
                REQUEST_ID,
                FILE_FILENAME,
                FILE_THUMBNAIL
        	  FROM 
                V_SHP_FILE 
        	  JOIN
        		V_SHP_FILE_BLOB
        	  ON
        		V_SHP_FILE.ID = V_SHP_FILE_BLOB.ID
        	  WHERE
        	    FILE_THUMBNAIL_AVAILABLE = 'Y'
        	  ORDER BY 
        	    REQUEST_ID
              ";

    $count_query = "SELECT COUNT(*) FROM V_SHP_FILE WHERE FILE_THUMBNAIL_AVAILABLE = 'Y'";

    $jrc_pubsy_db = array(
      'username' => variable_get('jrc_pubsy_db_username'),
      'password' => variable_get('jrc_pubsy_db_password'),
      'connection_string' => variable_get('jrc_pubsy_db_connection_string'),
    );

    $this->source = new MigrateSourceOracle($jrc_pubsy_db, $query, $count_query, $fields);
    $this->destination = new MigrateDestinationFile('file', 'MigrateFileBlob');

    // Map fields.
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('value', 'FILE_THUMBNAIL')->description('An image thumbnail for a Publication');
    // The destination filename must be specified for blobs.
    $this->addFieldMapping('destination_file', 'FILE_FILENAME');
    $this->addFieldMapping('destination_dir')->defaultValue('public://publications_thumbnails');
  }

  /**
   * Class prepareRow function.
   */
  public function prepareRow($row) {
    $row->FILE_FILENAME = 'publication_' . $row->REQUEST_ID . '_cover.jpg';
  }

}

/**
 * Migration class to import Publications.
 */
class PubsyPublicationsMigration extends Migration {
  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Migration of publications from the Pubsy Oracle database into Drupal Multisite nodes.');
    $this->softDependencies = array('PubsyPublicationsCover');

    // Note that Oracle by default upper-cases all identifiers,
    // so use upper-case for the key name and for source fields below.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'REQUEST_ID' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Publication Request ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Source fields available from the Oracle table.
    $fields = array(
      'REQUEST_ID' => t('Request ID'),
      'DATE_ACCESSIONED' => t('Date accessioned'),
      'DATE_AVAILABLE' => t('Available date'),
      'DATE_CREATED' => t('Creation date'),
      'DATE_ISSUED' => t('Issued date'),
      'DATE_SUBMITTED' => t('Submitted number'),
      'DATE_UPDATED' => t('Date of last update'),
      'IDENTIFIER_CITATION' => t('Identifier citation'),
      'IDENTIFIER_ISBN' => t('Identifier ISBN'),
      'IDENTIFIER_ISSN' => t('Identifier ISSN'),
      'DESCRIPTION_ABSTRACT' => t('Description Abstract'),
      'DESCRIPTION_SPONSORSHIP' => t('Description sponsorship'),
      'FORMAT_MEDIUM' => t('Format medium'),
      'LANGUAGE' => t('Language'),
      'PUBLISHER' => t('Publisher'),
      'RELATION_ISPARTOFSERIES' => t('Relation is part of series'),
      'TITLE' => t('Title'),
      'ID_TYPE' => t('ID type'),
      'TYPE' => t('Type'),
      'PUBLICATION_TYPE' => t('Publication type'),
      'IDENTIFIER_DOI' => t('Identifier DOI'),
      'ID_APPEARS_COLLECTION' => t('ID appears collection'),
      'APPEARS_COLLECTION' => t('Appears collection'),
      'SCIENCE_AREAS' => t('Science areas'),
      'RESEARCH_TOPICS' => t('Research topics'),
      'KEYWORDS' => t('Keywords'),
      'IDENTITIES' => t('Identities'),
      'INSTITUTES' => t('Institutes'),
      'AUTHORS' => t('Authors'),
      'IDENTIFIER_URI' => t('Identifier URI'),
      'IDENTIFIER_OTHER' => t('Identifier other'),
      'FILE_URL' => t('File URL'),
      'FILE_THUMBNAIL_FID' => t('File thumbnail FID'),
    );

    $query = "
			  SELECT                                
               V_SHP_PUBLICATION.REQUEST_ID,
               TO_CHAR(DATE_ACCESSIONED, 'YYYY-MM-DD HH24:MI:SS') DATE_ACCESSIONED,
               TO_CHAR(DATE_AVAILABLE, 'YYYY-MM-DD HH24:MI:SS') DATE_AVAILABLE,
               TO_CHAR(DATE_CREATED, 'YYYY-MM-DD HH24:MI:SS') DATE_CREATED,
               DATE_ISSUED,
               TO_CHAR(DATE_SUBMITTED, 'YYYY-MM-DD HH24:MI:SS') DATE_SUBMITTED,
               IDENTIFIER_CITATION,
               IDENTIFIER_ISBN,
               IDENTIFIER_ISSN,
               DESCRIPTION_ABSTRACT,
               DESCRIPTION_SPONSORSHIP,
               FORMAT_MEDIUM,
               LANGUAGE,
               PUBLISHER,
               RELATION_ISPARTOFSERIES,
               TITLE,
               ID_TYPE,
               TYPE,
               IDENTIFIER_DOI,
               ID_APPEARS_COLLECTION,
               APPEARS_COLLECTION,
               SCIENCE_AREAS,
               RESEARCH_TOPICS,
               KEYWORDS,
               IDENTITIES                                        
             FROM 
               V_SHP_PUBLICATION
             ORDER BY
               REQUEST_ID
     	     ";
    $count_query = "SELECT COUNT(*) FROM V_SHP_PUBLICATION";

    $jrc_pubsy_db = array(
      'username' => variable_get('jrc_pubsy_db_username'),
      'password' => variable_get('jrc_pubsy_db_password'),
      'connection_string' => variable_get('jrc_pubsy_db_connection_string'),
    );

    $this->source = new MigrateSourceOracle($jrc_pubsy_db, $query, $count_query, $fields);
    $this->destination = new MigrateDestinationNode('publication');

    // Map fields.
    $this->addFieldMapping('title', 'TITLE');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('created', 'DATE_CREATED');
    $this->addFieldMapping('changed', 'DATE_ACCESSIONED');
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(1);
    $this->addFieldMapping('language')->defaultValue("und");
    $this->addFieldMapping('revision_uid')->defaultValue(1);
    $this->addFieldMapping('body:language')->defaultValue("und");
    $this->addFieldMapping('field_appears_in_collections', 'APPEARS_COLLECTION');
    $this->addFieldMapping('field_dc_contributor_author', 'AUTHORS');
    $this->addFieldMapping('field_dc_date_accessioned', 'DATE_ACCESSIONED');
    $this->addFieldMapping('field_dc_date_available', 'DATE_AVAILABLE');
    $this->addFieldMapping('field_dc_date_created', 'DATE_CREATED');
    $this->addFieldMapping('field_dc_date_issued', 'DATE_ISSUED');
    $this->addFieldMapping('field_dc_date_submitted', 'DATE_SUBMITTED');
    $this->addFieldMapping('field_dc_description_abstract', 'DESCRIPTION_ABSTRACT');
    $this->addFieldMapping('field_dc_description_abstract:format')->defaultValue("full_html");
    $this->addFieldMapping('field_dc_description_sponsorship', 'DESCRIPTION_SPONSORSHIP');
    $this->addFieldMapping('field_dc_format_medium', 'FORMAT_MEDIUM');
    $this->addFieldMapping('field_dc_identifier_citation', 'IDENTIFIER_CITATION');
    $this->addFieldMapping('field_dc_identifier_doi', 'IDENTIFIER_DOI');
    $this->addFieldMapping('field_dc_identifier_isbn', 'IDENTIFIER_ISBN');
    $this->addFieldMapping('field_dc_identifier_issn', 'IDENTIFIER_ISSN');
    $this->addFieldMapping('field_dc_identifier_uri', 'IDENTIFIER_URI');
    $this->addFieldMapping('field_dc_identifier_other', 'IDENTIFIER_OTHER');
    $this->addFieldMapping('field_dc_language', 'LANGUAGE');
    $this->addFieldMapping('field_dc_publisher', 'PUBLISHER');
    $this->addFieldMapping('field_dc_relation_ispartofseries', 'RELATION_ISPARTOFSERIES');
    $this->addFieldMapping('field_dc_title', 'TITLE');
    $this->addFieldMapping('field_dc_type', 'TYPE');
    $this->addFieldMapping('field_pubsy_doc_links', 'FILE_URL');
    $this->addFieldMapping('field_last_update', 'DATE_UPDATED');
    $this->addFieldMapping('field_old_id', 'REQUEST_ID');
    $this->addFieldMapping('field_identities', 'IDENTITIES')->sourceMigration('71582fc13Termidentities')->separator(',');
    $this->addFieldMapping('field_identities:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_research_areas', 'SCIENCE_AREAS')->sourceMigration('71582fc13Termresearch_areas')->separator(',');
    $this->addFieldMapping('field_research_areas:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_tags', 'KEYWORDS')->sourceMigration('71582fc13Termtags')->separator(',');
    $this->addFieldMapping('field_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_research_topics', 'RESEARCH_TOPICS')->sourceMigration('71582fc13Termparent_topics')->separator(',');
    $this->addFieldMapping('field_research_topics:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_institutes', 'INSTITUTES');
    $this->addFieldMapping('field_institutes:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_publication_type', 'PUBLICATION_TYPE');
    $this->addFieldMapping('field_publication_type:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_image', 'FILE_THUMBNAIL_FID');
    $this->addFieldMapping('field_image:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('workbench_moderation_state_new')->defaultValue('published');

    // Unmapped destination fields.
    $this->addUnmigratedDestinations(array('log',
                                            'is_new',
                                            'tnid',
                                            'translate',
                                            'path',
                                            'comment',
                                            'pathauto',
                                            'body',
                                            'body:format',
                                            'body:summary',
                                            'field_image:preserve_files',
                                            'field_image:alt',
                                            'field_image:title',
                                            'field_research_areas:create_term',
                                            'field_research_areas:ignore_case',
                                            'field_tags:create_term',
                                            'field_tags:ignore_case',
                                            'field_institutes:create_term',
                                            'field_institutes:ignore_case',
                                            'field_identities:create_term',
                                            'field_identities:ignore_case',
                                            'field_publication_type:create_term',
                                            'field_publication_type:ignore_case',
                                            'field_publication_files',
                                            'field_publication_files:file_class',
                                            'field_publication_files:preserve_files',
                                            'field_publication_files:destination_dir',
                                            'field_publication_files:destination_file',
                                            'field_publication_files:file_replace',
                                            'field_publication_files:source_dir',
                                            'field_publication_files:urlencode',
                                            'field_publication_files:description',
                                            'field_publication_files:display',
                                            'field_dc_description_abstract:summary',
                                            'field_file_internal_note',
                                            'field_mk',
                                            'field_meta_creator',
                                            'field_related_documents',
                                            'field_related_documents:file_class',
                                            'field_related_documents:preserve_files',
                                            'field_related_documents:destination_dir',
                                            'field_related_documents:destination_file',
                                            'field_related_documents:file_replace',
                                            'field_related_documents:source_dir',
                                            'field_related_documents:urlencode',
                                            'field_related_documents:description',
                                            'field_related_documents:display',
                                            'field_related_content',
                                            'field_related_content:summary',
                                            'field_related_content:format',
                                            'field_research_topics:create_term',
                                            'field_research_topics:ignore_case',
                                            'field_dc_date_available:timezone',
                                            'field_dc_date_available:rrule',
                                            'field_dc_date_available:to',
                                            'field_dc_date_created:timezone',
                                            'field_dc_date_created:rrule',
                                            'field_dc_date_created:to',
                                            'field_dc_date_issued:timezone',
                                            'field_dc_date_issued:rrule',
                                            'field_dc_date_issued:to',
                                            'field_dc_date_submitted:timezone',
                                            'field_dc_date_submitted:rrule',
                                            'field_dc_date_submitted:to',
                                            'field_dc_date_accessioned:timezone',
                                            'field_dc_date_accessioned:rrule',
                                            'field_dc_date_accessioned:to',
                                           ));
  }

  /**
   * Class prepareRow function.
   */
  public function prepareRow($row) {
    global $conf;

    // Always include this fragment at the beginning of every prepareRow()
    // so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Connect to Oracle database.
    $jrc_pubsy_db_username = variable_get('jrc_pubsy_db_username');
    $jrc_pubsy_db_password = variable_get('jrc_pubsy_db_password');
    $jrc_pubsy_db_connection_string = variable_get('jrc_pubsy_db_connection_string');
    $connect = oci_connect($jrc_pubsy_db_username, $jrc_pubsy_db_password, $jrc_pubsy_db_connection_string, 'UTF8');

    // Check the connection.
    if (!$connect) {
      $e = oci_error();
      throw new Exception($e['message']);
    }

    // Title should be maximum 255 chars.
    $row->TITLE = drupal_substr($row->TITLE, 0, 255);

    // Change year format to complete date format
    // otherwise it is recognised as a timestamp and replaced by the year 1970
    $row->DATE_ISSUED = strtotime($row->DATE_ISSUED . "-1-1 00:00:00");
    $row->DATE_ISSUED = format_date($row->DATE_ISSUED, 'jrc_pubsy_date');

    // Add the actual time for update date.
    $row->DATE_UPDATED = format_date(time(), 'jrc_pubsy_date');

    // Description Abstract & Description Abstract summary
    // Remove special characters and get Description Abstract summary.
    $row->DESCRIPTION_ABSTRACT = check_plain(preg_replace("/[^\x{0000}-\x{FFFF}]/iu", " ", $row->DESCRIPTION_ABSTRACT));

    // Publications collections ID of Pubsy.
    $pub_collection = array(
      'Joint Research Centre Corporate Activities' => array(
        692,
        3275,
        17839,
        63076,
      ),
      'Institute for Reference Materials and Measurements' => array(3342, 3343),
      'Institute for Transuranium Elements' => array(3379),
      'Institute for Energy and Transport' => array(3415),
      'Institute for the Protection and Security of the Citizen' => array(3460),
      'Institute for Environment and Sustainability' => array(3511),
      'Institute for Health and Consumer Protection' => array(18002),
      'Institute for Prospective Technological Studies' => array(3582),
    );
    foreach ($pub_collection as $key => $c) {
      if (in_array($row->ID_APPEARS_COLLECTION, $c)) {
        $row->APPEARS_COLLECTION = $key;
      }
    }

    // Each Publication has several authors to fetch in authors table.
    $query = "
              SELECT 
                AUTHOR
              FROM 
                V_SHP_AUTHOR 
              WHERE 
                REQUEST_ID = " . $row->REQUEST_ID . "
              ORDER BY AUTHOR_ORDER
              ";
    $res = oci_parse($connect, $query);
    if (!oci_execute($res)) {
      _jrc_pubsy_import_notify_error(print_r(oci_error(), TRUE), $category = "Query execution error");
      return FALSE;
    }

    $row->AUTHORS = array();
    while ($author = _jrc_pubsy_import_lowercase(oci_fetch_object($res))) {
      $row->AUTHORS[] = $author->author;
    }

    // Get the identifiers for of each Publication.
    $query = "
              SELECT 
                IDENTIFIER_TYPE,
                IDENTIFIER_OTHER
              FROM 
                V_SHP_IDENTIFIER 
              WHERE 
                REQUEST_ID = " . $row->REQUEST_ID . "
              ";
    $res = oci_parse($connect, $query);
    if (!oci_execute($res)) {
      _jrc_pubsy_import_notify_error(print_r(oci_error(), TRUE), $category = "Query execution error");
      return FALSE;
    }
    $row->IDENTIFIER_URI = array();
    $row->IDENTIFIER_OTHER = array();
    while ($identifier = _jrc_pubsy_import_lowercase(oci_fetch_object($res))) {
      if ($identifier->identifier_type == 'URI') {
        $row->IDENTIFIER_URI[] = $identifier->identifier_other;
      }
      elseif ($identifier->identifier_type == 'EUR' || $identifier->identifier_type == 'OPOCE') {
        $row->IDENTIFIER_OTHER[] = $identifier->identifier_type . " " . $identifier->identifier_other;
      }
    }

    // Get Publication's files for each Publication.
    $query = "
              SELECT
                FILE_FILENAME,
                FILE_URL
        	  FROM 
                V_SHP_FILE 
        	  WHERE 
                REQUEST_ID = " . $row->REQUEST_ID . "
              ";
    $res = oci_parse($connect, $query);
    if (!oci_execute($res)) {
      _jrc_pubsy_import_notify_error(print_r(oci_error(), TRUE), $category = "Query execution error");
      return FALSE;
    }

    $row->FILE_URL = array();
    while ($file = _jrc_pubsy_import_lowercase(oci_fetch_object($res))) {
      $row->FILE_URL[] = urldecode($file->file_url);
    }
    $row->FILE_IMAGE = 'publication_' . $row->REQUEST_ID . '_cover.jpg';
    $row->FILE_THUMBNAIL_FID = _jrc_pubsy_import_get_row_file_fid($row->FILE_IMAGE);

    // Get publication institutes.
    // Notice: These are not tids!
    // These IDs are defined by Pubsy and should be always the same.
    $pub_institutes = array(
      'Horizontal services' => array(692, 3275, 17839, 63076),
      'IRMM' => array(3342, 3343),
      'ITU' => array(3379),
      'IET' => array(3415),
      'IPSC' => array(3460),
      'IES' => array(3511),
      'IHCP' => array(18002),
      'IPTS' => array(3582),
    );

    foreach ($pub_institutes as $key => $i) {
      if (in_array($row->ID_APPEARS_COLLECTION, $i)) {
        $terms = taxonomy_get_term_by_name($key, 'institutes');
        if (!empty($terms)) {
          foreach ($terms as $term) {
            $row->INSTITUTES[] = $term->tid;
          }
        }
      }
    }

    // Get Publication's type
    // Notice: These are not tids!
    // These IDs are defined by Pubsy and should be always the same.
    $pub_types = array(
      'Articles in books' => array(3),
      'Articles in Journals' => array(4, 5, 26, 28),
      'Books' => array(1, 2),
      'Contributions to Conferences' => array(10, 11, 12, 32, 33),
      'EUR - Scientific and Technical Research Reports'
      => array(8, 9, 20, 21, 22, 23, 24, 25),
      'Reference reports' => array(7),
      'PhD Theses' => array(15),
    );

    // Publication type.
    foreach ($pub_types as $key => $t) {
      if (in_array($row->ID_TYPE, $t)) {
        $terms = taxonomy_get_term_by_name($key, 'publication_types');
        if (!empty($terms)) {
          foreach ($terms as $term) {
            $row->PUBLICATION_TYPE = $term->tid;
          }
        }
      }
    }

    // Disconnect from Oracle darabase.
    oci_close($connect);
  }

}
