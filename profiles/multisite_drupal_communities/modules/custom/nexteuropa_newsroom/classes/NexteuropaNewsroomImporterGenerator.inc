<?php

/**
 * @file
 * Code for the NexteuropaNewsroomImporterGenerator class.
 */

/**
 * NexteuropaNewsroomImporterGenerator class.
 */
class NexteuropaNewsroomImporterGenerator {
  private $id = NULL;
  private $fieldMapping = NULL;
  private $title = NULL;
  private $description = NULL;
  private $rssContext = NULL;
  private $entityType = NULL;
  private $bundle = NULL;
  private $importPeriod = 3000;
  private $counter = 0;
  private $queries = [];
  private $mappers = [];
  private $fieldInfo = NULL;
  private $languages = NULL;

  /**
   * NexteuropaNewsroomImporterGenerator constructor.
   *
   * @param int $id
   *   Importer ID.
   * @param array $field_mapping
   *   Field mapping settings.
   * @param string $title
   *   Importer title.
   * @param string $description
   *   Importer description.
   * @param string $rss_context
   *   Importer feed rss context.
   * @param string $entity_type
   *   Entity type.
   * @param string $bundle
   *   Bundle name.
   * @param int $import_period
   *   Import period in seconds.
   */
  public function __construct($id, array $field_mapping, $title, $description, $rss_context, $entity_type, $bundle, $import_period) {
    $this->setId($id);
    $this->setFieldMapping($field_mapping);
    $this->setTitle($title);
    $this->setDescription($description);
    $this->setRssContext($rss_context);
    $this->setEntityType($entity_type);
    $this->setBundle($bundle);
    $this->setImportPeriod($import_period);

    // We set field info here, so we don't call it each time.
    $this->setFieldInfo(field_info_fields());
  }

  /**
   * Gets importer ID.
   *
   * @return int
   *   Importer ID.
   */
  private function getId() {
    return $this->id;
  }

  /**
   * Sets importer ID.
   *
   * @param int $id
   *   Importer ID.
   */
  private function setId($id) {
    $this->id = $id;
  }

  /**
   * Gets field mapping settings.
   *
   * @return array
   *   Field mapping settings.
   */
  private function getFieldMaping() {
    return $this->fieldMapping;
  }

  /**
   * Sets field mapping settings.
   *
   * @param array $field_mapping
   *   Field mapping settings.
   */
  private function setFieldMapping(array $field_mapping) {
    $this->fieldMapping = $field_mapping;
  }

  /**
   * Gets title.
   *
   * @return string
   *   Importer title.
   */
  private function getTitle() {
    return $this->title;
  }

  /**
   * Sets title.
   *
   * @param string $title
   *   Importer title.
   */
  private function setTitle($title) {
    $this->title = $title;
  }

  /**
   * Gets description.
   *
   * @return string
   *   Importer description.
   */
  private function getDescription() {
    return $this->description;
  }

  /**
   * Sets description.
   *
   * @param string $description
   *   Importer description.
   */
  private function setDescription($description) {
    $this->description = $description;
  }

  /**
   * Gets rss context.
   *
   * @return string
   *   Rss context.
   */
  private function getRssContext() {
    return $this->rssContext;
  }

  /**
   * Sets rss context.
   *
   * @param string $rss_context
   *   Rss context.
   */
  private function setRssContext($rss_context) {
    $this->rssContext = $rss_context;
  }

  /**
   * Gets entity type.
   *
   * @return string
   *   Entity type.
   */
  private function getEntityType() {
    return $this->entityType;
  }

  /**
   * Sets entity type.
   *
   * @param string $entity_type
   *   Entity type.
   */
  private function setEntityType($entity_type) {
    $this->entityType = $entity_type;
  }

  /**
   * Gets bundle.
   *
   * @return string
   *   Bundle.
   */
  private function getBundle() {
    return $this->bundle;
  }

  /**
   * Sets bundle.
   *
   * @param string $bundle
   *   Bundle.
   */
  private function setBundle($bundle) {
    $this->bundle = $bundle;
  }

  /**
   * Gets import period.
   *
   * @return int
   *   Import period.
   */
  private function getImportPeriod() {
    return $this->importPeriod;
  }

  /**
   * Sets import period.
   *
   * @param int $import_period
   *   Import period.
   */
  private function setImportPeriod($import_period) {
    $this->importPeriod = $import_period;
  }

  /**
   * Gets counter.
   *
   * @return int
   *   Counter.
   */
  private function getCounter() {
    return $this->counter;
  }

  /**
   * Gets importer mappers.
   *
   * @return array
   *   Importer mappers.
   */
  private function getMappers() {
    return $this->mappers;
  }

  /**
   * Gets importer queries.
   *
   * @return array
   *   Importer queries.
   */
  private function getQueries() {
    return $this->queries;
  }

  /**
   * Gets field info.
   *
   * @return array
   *   Field info.
   */
  private function getFieldInfo() {
    return $this->fieldInfo;
  }

  /**
   * Sets field info.
   *
   * @param array $field_info
   *   Field info.
   */
  private function setFieldInfo(array $field_info) {
    $this->fieldInfo = $field_info;
  }

  /**
   * Increases counter.
   */
  protected function increaseCounter() {
    $this->counter++;
  }

  /**
   * Adds importer query.
   *
   * @param string $query
   *   Importer query.
   */
  protected function addQuery($query) {
    $this->queries[$this->getXpathString()] = $query;
  }

  /**
   * Adds translatable query.
   *
   * @param string $query
   *   Importer query.
   * @param string $language
   *   Language code.
   */
  protected function addTranslatableQuery($query, $language) {
    if ($this->getId() == NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER) {
      $query = ($language == NexteuropaNewsroomHelper::getDefaultLanguage()) ? $query : '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . $language . '" and @infsonewsroom:TopicId="$Temporary target 1"]/' . $query;
    }
    else {
      $query = $query . '[@lang="' . $language . '"]/text()';
    }
    $this->addQuery($query);
  }

  /**
   * Add importer mapper.
   *
   * @param array $field_mapping
   *   Field mapping settings.
   * @param string $language
   *   Language code.
   */
  protected function addMapper(array $field_mapping, $language = NULL) {

    $mapper = [
      'source' => !empty($field_mapping['source']) ? $field_mapping['source'] : $this->getXpathString(),
      'target' => $language ? $field_mapping['field'] . ':et:' . drupal_strtolower($language) : $field_mapping['field'],
      'unique' => !empty($field_mapping['unique']),
    ];

    if (!empty($field_mapping['options'])) {
      $mapper = array_merge($mapper, $field_mapping['options']);
    }

    $this->mappers[$this->getCounter()] = $mapper;
    $this->increaseCounter();
  }

  /**
   * Generates import.
   */
  public function generateImporter() {
    $config = $this->getConfig();

    // Save importer.
    $save = feeds_importer($this->getId());
    $save->setConfig($config);

    foreach (['fetcher', 'parser', 'processor'] as $type) {
      $save->setPlugin($config[$type]['plugin_key']);
      $save->$type->setConfig($config[$type]['config']);
    }

    $save->save();

    // Set default URLS for importers.
    NexteuropaNewsroomImporterHelper::setDefaultImporterUrl($this->getId());
  }

  /**
   * Checks whether field is translatable or not.
   *
   * @param array $field_mapping
   *   Field mapping settings.
   *
   * @return bool
   *   Is transltable field.
   */
  protected function isTranslatableField(array $field_mapping) {
    $is_translatable = FALSE;
    $fields = $this->getFieldInfo();
    $attribute = strrchr($field_mapping['field'], ':');
    $sanitized_name = !empty($field_mapping['original_field']) ? $field_mapping['original_field'] : str_replace($attribute, '', $field_mapping['field']);
    if (!empty($fields[$sanitized_name])) {
      $is_translatable = field_is_translatable($this->getEntityType(), $fields[$sanitized_name]);
    }

    return $is_translatable;
  }

  /**
   * Gets xpath source string.
   *
   * @return string
   *   Xpath source string.
   */
  protected function getXpathString() {
    return 'xpathparser:' . $this->getCounter();
  }

  /**
   * Adds newsroom default value tamper.
   *
   * @param string $default_source
   *   Default language source.
   */
  protected function addNewsroomDefaultValueTamper($default_source) {
    if ($default_source) {
      $tamper['tamper']['plugins'] = [
        'newsroom_default_value' => [
          'default_value' => '[' . $default_source . ']',
        ],
      ];

      $this->addTampers($tamper);
    }
  }

  /**
   * Prepares dynamic mapping for the current import based o field mapping.
   */
  private function prepareDynamicMapping() {
    foreach ($this->getFieldMaping() as $field_mapping) {
      if ($this->isTranslatableField($field_mapping)) {

        $default_language_source = NULL;
        foreach ($this->getLanguages() as $language) {
          if ($language == NexteuropaNewsroomHelper::getDefaultLanguageUppercase()) {
            $default_language_source = $this->getXpathString();
          }
          else {
            $this->addNewsroomDefaultValueTamper($default_language_source);
          }

          if (!empty($field_mapping['query'])) {
            $this->addTranslatableQuery($field_mapping['query'], $language);
          }

          $this->addMapper($field_mapping, $language);
        }

      }
      else {
        $this->addTampers($field_mapping);
        if (!empty($field_mapping['query'])) {
          $this->addQuery($field_mapping['query']);
        }

        $this->addMapper($field_mapping);
      }
    }

  }

  /**
   * Gets enabled languages.
   *
   * @return array
   *   Enabled languages.
   */
  private function getLanguages() {
    if (!$this->languages) {
      $languages = locale_language_list();
      $language_keys = array_map('drupal_strtoupper', array_keys($languages));

      // We need to put the default language on top. Like this we can create
      // tampers easily.
      $default_language = array_search(NexteuropaNewsroomHelper::getDefaultLanguageUppercase(), $language_keys);
      if ($default_language) {
        unset($language_keys[$default_language]);
        array_unshift($language_keys, NexteuropaNewsroomHelper::getDefaultLanguageUppercase());
      }

      $this->languages = $language_keys;
    }
    return $this->languages;
  }

  /**
   * Generates import debug values array with empty values.
   *
   * @return array
   *   Debug values array.
   */
  protected function generateDebugArray() {
    // We don't need debug and raw values, we set 0 for these xpath mappings.
    $debug_array = [];
    foreach (array_keys($this->getQueries()) as $xpath) {
      $debug_array[$xpath] = 0;
    }
    return $debug_array;
  }

  /**
   * Adds tamper for the current source (field).
   *
   * @param array $field_mapping
   *   Field mapping settings.
   */
  private function addTampers(array $field_mapping) {
    if (empty($field_mapping['tamper'])) {
      return;
    }

    $settings = $field_mapping['tamper'];

    $source = !empty($field_mapping['source']) ? $field_mapping['source'] : $this->getXpathString();
    $source_prepared_string = drupal_strtolower(str_replace(['-', ' '], [
      '_',
      '_',
    ], $source));
    $weight = 0;
    foreach ($settings['plugins'] as $plugin_id => $plugin) {

      $feeds_tamper = new stdClass();
      $feeds_tamper->id = $this->getId() . '-' . $source_prepared_string . '-' . $plugin_id;
      $feeds_tamper->importer = $this->getId();
      $feeds_tamper->source = $source;
      $feeds_tamper->plugin_id = $plugin_id;
      $feeds_tamper->disabled = FALSE;
      $feeds_tamper->api_version = 2;
      $feeds_tamper->export_type = 0;
      $feeds_tamper->weight = $weight;

      if ($plugin_id == 'efq_finder') {

        // Prepare setting for Entity Field Query finder.
        $feeds_tamper->settings = [
          'entity_type' => $plugin['entity_type'],
          'bundle' => $plugin['bundle'],
          'column' => 'value',
          'property' => FALSE,
          'update' => 'Update',
          'field' => $plugin['field'],
        ];
        $feeds_tamper->description = 'Entity Field Query finder';

      }
      elseif ($plugin_id == 'rewrite') {

        // Prepare setting for Rewrite plugin.
        $feeds_tamper->settings = [
          'text' => $plugin['prefix'] . '[' . $source . ']',
        ];
        $feeds_tamper->description = 'Rewrite';

      }
      elseif ($plugin_id == 'strtotime') {

        // String to timestamp plugin.
        $feeds_tamper->description = 'String to Unix timestamp';

      }
      elseif ($plugin_id == 'default_value') {

        $feeds_tamper->settings = [
          'default_value' => $plugin['default_value'],
        ];
        $feeds_tamper->description = 'Set default language';

      }
      elseif ($plugin_id == 'newsroom_default_value') {

        $feeds_tamper->settings = [
          'default_value' => $plugin['default_value'],
        ];
        $feeds_tamper->description = 'Set default value if empty';

      }
      elseif ($plugin_id == 'find_replace') {

        $feeds_tamper->settings = [
          'find' => $plugin['replacement'],
          'replace' => '',
          'case_sensitive' => 1,
          'word_boundaries' => 0,
          'whole' => 0,
          'regex' => FALSE,
          'func' => 'str_replace',
        ];
        $feeds_tamper->description = 'Find replace';

      }

      feeds_tamper_save_instance($feeds_tamper);
      $weight++;
    }
  }

  /**
   * Gets importer config.
   *
   * @return array
   *   Importer config.
   */
  private function getConfig() {
    $this->prepareDynamicMapping();
    $config = [
      'name' => $this->getTitle(),
      'description' => $this->getDescription(),
      'fetcher' => [
        'plugin_key' => 'FeedsHTTPFetcher',
        'config' => [
          'auto_detect_feeds' => FALSE,
          'use_pubsubhubbub' => FALSE,
          'designated_hub' => '',
          'request_timeout' => NULL,
        ],
      ],
      'parser' => [
        'plugin_key' => 'FeedsXPathParserXML',
        'config' => [
          'sources' => $this->getQueries(),
          'rawXML' => $this->generateDebugArray(),
          'context' => $this->getRssContext(),
          'exp' => [
            'errors' => 0,
            'debug' => $this->generateDebugArray(),
          ],
          'allow_override' => 0,
        ],
      ],
      'content_type' => '',
      'update' => 0,
      'import_period' => $this->getImportPeriod(),
      'expire_period' => 1800,
      'import_on_create' => 1,
      'process_in_background' => 0,
    ];

    if ($this->getEntityType() == 'node') {
      $config['processor'] = [
        'plugin_key' => 'FeedsNodeProcessor',
        'config' => [
          'expire' => '-1',
          'author' => '0',
          'authorize' => 0,
          'mappings' => $this->getMappers(),
          'update_existing' => '2',
          'input_format' => 'full_html',
          'skip_hash_check' => 1,
          'bundle' => $this->getBundle(),
        ],
      ];
      return $config;
    }
    else {
      $config['processor'] = [
        'plugin_key' => 'FeedsTermProcessor',
        'config' => [
          'vocabulary' => $this->getBundle(),
          'mappings' => $this->getMappers(),
          'update_existing' => '2',
          'input_format' => 'plain_text',
          'skip_hash_check' => 0,
          'bundle' => $this->getBundle(),
        ],
      ];
      return $config;
    }
  }

}
