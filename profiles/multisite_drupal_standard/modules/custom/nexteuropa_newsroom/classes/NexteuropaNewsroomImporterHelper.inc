<?php

/**
 * @file
 * Code for the NewsroomHelper class.
 */

/**
 * NexteuropaNewsroomImporterHelper class.
 */
class NexteuropaNewsroomImporterHelper {

  /**
   * Calls feed importer with the certain URL.
   *
   * @param string $importer_id
   *   Importer ID.
   * @param string $url
   *   RSS feed URL to call.
   */
  public static function runFeedImporter($importer_id, $url = NULL) {
    $source = feeds_source($importer_id);
    if (!empty($url)) {
      $config['FeedsHTTPFetcher']['source'] = $url;
      $source->addConfig($config);
      $source->save();
      $source->import();
    }
    else {
      // For normal import we need batch, so we call startImport.
      $source->startImport();
    }
  }

  /**
   * Delete items.
   *
   * @param string $importer_id
   *   Importer ID.
   */
  public static function deleteItems($importer_id) {
    $source = feeds_source($importer_id);
    $source->startClear();
    $source->progressClearing();
  }

  /**
   * Gets default URL of importer.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return string
   *   URL.
   */
  public static function getImporterUrl($importer_id) {
    $url = '';

    switch ($importer_id) {

      case NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER:
      case NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER:
        $url = NexteuropaNewsroomHelper::getNewsroomUrl(variable_get('nexteuropa_newsroom_topic_import_script', NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT));
        break;

      case NEXTEUROPA_NEWSROOM_TYPE_IMPORTER:
        $url = NexteuropaNewsroomHelper::getNewsroomUrl(variable_get('nexteuropa_newsroom_type_import_script', NEXTEUROPA_NEWSROOM_TYPE_SCRIPT));
        break;

      case NEXTEUROPA_NEWSROOM_ITEM_IMPORTER:
        $subsite = variable_get('nexteuropa_newsroom_subsite', FALSE);
        $subsite_url_part = '?';

        if ($subsite) {
          $subsite_url_part = '?subsite=' . $subsite;
        }

        $url = NexteuropaNewsroomHelper::getNewsroomUrl(variable_get('nexteuropa_newsroom_item_import_script', NEXTEUROPA_NEWSROOM_ITEM_SCRIPT)) . $subsite_url_part;
        break;

      case NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER:
        $url = NexteuropaNewsroomHelper::getNewsroomUrl(variable_get('nexteuropa_newsroom_issue_import_script', NEXTEUROPA_NEWSROOM_NEWSLETTER_SCRIPT));
        break;
    }

    return $url;
  }

  /**
   * Sets default importer URL.
   *
   * @param string $importer_id
   *   Importer id.
   */
  public static function setDefaultImporterUrl($importer_id) {
    $url = self::getImporterUrl($importer_id);
    if (!empty($url)) {
      $source = feeds_source($importer_id);
      $config = $source->getConfig();
      $config['FeedsHTTPFetcher']['source'] = $url;
      $source->setConfig($config);
      $source->save();
    }
  }

  /**
   * Newsroom importer for single items.
   *
   * @param string $type
   *   Entity type: topic, type or service.
   * @param int $newsroom_id
   *   Original newsroom ID.
   * @param string $importer_id
   *   Importer ID.
   *
   * @return string
   *   Taxonomy term redirect URL.
   */
  public static function getTaxonomyTermImportPath($type, $newsroom_id, $importer_id) {
    $url = self::getImporterUrl($importer_id) . variable_get('nexteuropa_newsroom_single_' . $type . '_import_segment') . $newsroom_id;
    self::runFeedImporter($importer_id, $url);
    return 'newsroom-redirect/' . $type . '/' . $newsroom_id;
  }

  /**
   * Imports a single newsroom item by the original newsroom ID.
   *
   * @param int $newsroom_id
   *   Original newsroom id.
   */
  public static function getNewsroomItemImportPath($newsroom_id = 0) {
    $path = NULL;
    if ($newsroom_id) {
      // Prepare URLs for importers and get feed importer ID.
      $url = self::getImporterUrl(NEXTEUROPA_NEWSROOM_ITEM_IMPORTER) . variable_get('nexteuropa_newsroom_single_item_import_segment', NEXTEUROPA_NEWSROOM_ITEM_SEGMENT) . $newsroom_id;
      self::runFeedImporter(NEXTEUROPA_NEWSROOM_ITEM_IMPORTER, $url);
      $path = 'news-redirect/' . $newsroom_id;
    }

    return $path;
  }

  /**
   * Importers list.
   *
   * @return array
   *   Returns an array of Importers IDs.
   */
  public static function returnImporters() {
    $importers = [
      NEXTEUROPA_NEWSROOM_TYPE_IMPORTER,
      NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER,
      NEXTEUROPA_NEWSROOM_ITEM_IMPORTER,
      NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER,
      NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER,
    ];
    return $importers;
  }

  /**
   * Gets issue importer field mapping settings.
   *
   * @return array
   *   Issue importer field mapping settings.
   */
  private static function getIssueImporterMappings() {
    $field_mapping = [
      [
        'field' => 'title',
        'query' => 'title[@lang="' . NexteuropaNewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'title_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_nl_issue_date:start',
        'query' => 'pubDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_newsletter_id',
        'query' => 'infsonewsroom:BasicIssueId/text()',
      ],
      [
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'link',
      ],
      [
        'field' => 'field_newsroom_newsletter_items:etid',
        'query' => 'infsonewsroom:BasicSvItemId/text()',
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'node',
              'bundle' => 'newsroom_item',
              'field' => 'field_newsroom_item_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_service',
        'query' => 'infsonewsroom:BasicSvId/text()',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'taxonomy_term',
              'bundle' => NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY,
              'field' => 'field_newsroom_service_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'guid',
        'query' => '$field_newsroom_newsletter_id',
        'unique' => 1,
      ],
      [
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => [
          'plugins' => [
            'default_value' => [
              'default_value' => NexteuropaNewsroomHelper::getDefaultLanguage(),
            ],
          ],
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets item importer field mapping settings.
   *
   * @return array
   *   Item importer field mapping settings.
   */
  private static function getItemImporterMappings() {

    $field_mapping = [
      [
        'field' => 'title',
        'query' => 'title[@lang="' . NexteuropaNewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'title_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_item_date:start',
        'query' => 'infsonewsroom:BasicDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_item_date:end',
        'query' => 'infsonewsroom:BasictoDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_publication_date:start',
        'query' => 'pubDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_private_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Private"]/@url',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ],
      [
        'field' => 'field_newsroom_private_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ],
      [
        'field' => 'field_newsroom_private_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ],
      [
        'field' => 'field_newsroom_private_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ],
      [
        'field' => 'field_newsroom_private_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ],
      [
        'field' => 'field_newsroom_item_rapid_pr',
        'query' => 'infsonewsroom:BasicRapidPressRelease/text()',
      ],
      [
        'field' => 'field_newsroom_item_type',
        'query' => 'infsonewsroom:NewsType/@id',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'taxonomy_term',
              'bundle' => NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY,
              'field' => 'field_newsroom_type_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_item_id',
        'query' => 'infsonewsroom:BasicId',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_item_other_link:title',
        'query' => 'infsonewsroom:ContextOtherLinkText',
      ],
      [
        'field' => 'field_newsroom_item_other_link:url',
        'query' => 'infsonewsroom:ContextOtherLinkUrl',
      ],
      [
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'infsonewsroom:BasicUrl',
      ],
      [
        'field' => 'field_newsroom_documents:url',
        'query' => 'enclosure[not(@type="image/jpeg") and not(@external_app="DocsRoom")]/@url',
      ],
      [
        'field' => 'field_newsroom_documents:title',
        'query' => 'enclosure[not(@type="image/jpeg") and not(@external_app="DocsRoom")]/@title',
      ],
      [
        'field' => 'promote',
        'query' => 'infsonewsroom:pubHighlight/text()',
      ],
      [
        'field' => 'field_newsroom_topics',
        'query' => 'category[@domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'taxonomy_term',
              'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
              'field' => 'field_newsroom_topic_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_primary_topic',
        'query' => 'category[@infsonewsroom:TopicPrimary="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'taxonomy_term',
              'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
              'field' => 'field_newsroom_topic_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'created',
        'query' => 'infsonewsroom:BasicReferenceDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'sticky',
        'query' => 'infsonewsroom:pubIsCentral/text()',
      ],
      [
        'field' => 'field_newsroom_short_item',
        'query' => 'infsonewsroom:pubIsLong/text()',
      ],
      [
        'field' => 'field_newsroom_teaser_only',
        'query' => 'infsonewsroom:pubTeaserOnly/text()',
      ],
      [
        'field' => 'field_newsroom_related_content',
        'query' => 'infsonewsroom:slave/@id',
      ],
      [
        'field' => 'field_newsroom_parent_content',
        'query' => 'infsonewsroom:master/@id',
      ],
      [
        'field' => 'field_newsroom_project_acr',
        'query' => 'infsonewsroom:ContextProjectAcronym/text()',
      ],
      [
        'field' => 'field_newsroom_prj_coordinator',
        'query' => 'infsonewsroom:ContextProjectCoordinator/text()',
      ],
      [
        'field' => 'field_newsroom_project',
        'query' => 'infsonewsroom:ContextProjectName',
      ],
      [
        'field' => 'field_newsroom_project_website:url',
        'query' => 'infsonewsroom:ContextProjectURL',
      ],
      [
        'field' => 'field_newsroom_project_website:title',
        'query' => 'infsonewsroom:ContextProjectURLDisplay',
      ],
      [
        'field' => 'field_newsroom_location:wkt',
        'query' => 'infsonewsroom:ContextWellknowntext/text()',
      ],
      [
        'field' => 'field_newsroom_highlighted_topic',
        'query' => 'category[@infsonewsroom:TopicHighlight="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugins' => [
            'efq_finder' => [
              'entity_type' => 'taxonomy_term',
              'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
              'field' => 'field_newsroom_topic_id',
            ],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_ec_content',
        'query' => 'infsonewsroom:ContextECContent/text()',
      ],
      [
        'field' => 'field_newsroom_item_venue',
        'query' => 'infsonewsroom:ContextVenue',
      ],
      [
        'field' => 'field_newsroom_organiser',
        'query' => 'infsonewsroom:ContextOrganiser',
      ],
      [
        'field' => 'field_newsroom_author',
        'query' => 'infsonewsroom:ContextAuthor',
      ],
      [
        'field' => 'field_newsroom_eur_lex_link:url',
        'query' => 'infsonewsroom:ContextEurlex',
      ],
      [
        'field' => 'field_newsroom_ted_link:url',
        'query' => 'infsonewsroom:ContextTed',
      ],
      [
        'field' => 'field_newsroom_registration_link:url',
        'query' => 'infsonewsroom:ContextRegistrationLink',
      ],
      [
        'field' => 'field_newsroom_registration_link:title',
        'query' => 'infsonewsroom:ContextRegistrationLinkText',
      ],
      [
        'field' => 'body',
        'query' => 'infsonewsroom:FullContent',
      ],
      [
        'field' => 'field_newsroom_item_contact_text',
        'query' => 'infsonewsroom:ContextContactText',
      ],
      [
        'field' => 'field_newsroom_item_contact_mail',
        'query' => 'infsonewsroom:ContextContactEmail',
      ],
      [
        'field' => 'field_newsroom_item_linked_obj',
        'query' => 'infsonewsroom:FullLinkedObject',
      ],
      [
        'field' => 'field_newsroom_item_pre_title',
        'query' => 'infsonewsroom:FullPreTitle',
      ],
      [
        'field' => 'field_newsroom_item_quote_box',
        'query' => 'infsonewsroom:FullQuoteBox',
      ],
      [
        'field' => 'field_newsroom_item_short_title',
        'query' => 'infsonewsroom:BasicShortTitle',
      ],
      [
        'field' => 'field_newsroom_item_speaker',
        'query' => 'infsonewsroom:ContextSpeaker',
      ],
      [
        'field' => 'field_newsroom_teaser',
        'query' => 'infsonewsroom:BasicTeaser',
      ],
      [
        'field' => 'guid',
        'query' => '$field_newsroom_item_id',
      ],
      [
        'field' => '_feed_changed',
        'query' => 'infsonewsroom:pubUpdateDate/text()',
        'tamper' => [
          'plugins' => [
            'find_replace' => [
              'replacement' => 'GMT',
            ],
            'strtotime' => [],
          ],
        ],
      ],
      [
        'field' => 'field_newsroom_newsletter_only',
        'query' => 'infsonewsroom:itemDisplay/text()',
      ],
      [
        'field' => 'field_newsroom_docsroom_ids',
        'query' => 'enclosure[@external_app="DocsRoom"]/@external_id',
      ],
      [
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => [
          'plugins' => [
            'default_value' => [
              'default_value' => NexteuropaNewsroomHelper::getDefaultLanguage(),
            ],
          ],
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Builds newsroom importer generator.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return \NewsroomImporterGenerator
   *   Newsroom importer generator.
   */
  public static function buildImporter($importer_id) {
    $import_period = -1;
    $rss_context = '//channel/item';
    switch ($importer_id) {
      case NEXTEUROPA_NEWSROOM_ITEM_IMPORTER:
        $title = 'Newsroom Items Multilingual';
        $description = 'Imports Newsroom Items from the Newsroom service.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_CONTENT_TYPE;
        $import_period = 0;
        $field_mapping = self::getItemImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER:
        $title = 'Newsroom Newsletter issues';
        $description = 'Imports newsletter issues.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_NEWSLETTER_CONTENT_TYPE;
        $import_period = 3600;
        $field_mapping = self::getIssueImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TYPE_IMPORTER:
        $title = 'Newsroom Type Multilingual';
        $description = 'Imports Item Types from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY;
        $field_mapping = self::getTypeImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER:
        $title = 'Newsroom Topics Multilingual';
        $description = 'Imports Topics from the Newsroom service';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY;
        $rss_context = '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . NexteuropaNewsroomHelper::getDefaultLanguageUppercase() . '"]';
        $field_mapping = self::getTopicImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER:
        $title = 'Newsroom Services Multilingual';
        $description = 'Imports Services from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY;
        $field_mapping = self::getServiceImporterMappings();
        break;
    }

    return new NexteuropaNewsroomImporterGenerator($importer_id, $field_mapping, $title, $description, $rss_context, $entity_type, $bundle, $import_period);
  }

  /**
   * Gets type importer field mapping settings.
   *
   * @return array
   *   Type importer field mapping settings.
   */
  private static function getTypeImporterMappings() {
    // Define the needed infos to build the importer dinamically.
    $field_mapping = [
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_type_id',
        'query' => 'infsonewsroom:BasicTypeId/text()',
      ],
      [
        'field' => 'name',
        'query' => 'title[@lang="' . NexteuropaNewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'title',
      ],
      [
        'field' => 'parentguid',
        'query' => 'infsonewsroom:BasicTypeParent/text()',
        'tamper' => [
          'plugins' => [
            'rewrite' => [
              'prefix' => 'type-',
            ],
          ],
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets topic importer field mapping settings.
   *
   * @return array
   *   Topic importer field mapping settings.
   */
  private static function getTopicImporterMappings() {
    $field_mapping = [
      [
        'field' => 'Temporary target 1',
        'query' => '@infsonewsroom:TopicId',
        'target' => 'Temporary target 1',
      ],
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_topic_id',
        'query' => '@infsonewsroom:TopicId',
      ],
      [
        'field' => 'name',
        'query' => 'text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'text()',
      ],
      [
        'field' => 'field_newsroom_category_domain',
        'query' => '@domain',
      ],
      [
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => [
          'plugins' => [
            'rewrite' => [
              'prefix' => 'topic-',
            ],
          ],
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets service importer field mapping settings.
   *
   * @return array
   *   Service importer field mapping settings.
   */
  private static function getServiceImporterMappings() {
    $field_mapping = [
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_service_id',
        'query' => 'infsonewsroom:BasicSvId/text()',
      ],
      [
        'field' => 'name',
        'query' => 'title[@lang="' . NexteuropaNewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_service_active',
        'query' => 'infsonewsroom:BasicSvStatus/text()',
      ],
      [
        'field' => 'field_newsroom_service_sample:url',
        'query' => 'infsonewsroom:archivesLink',
      ],
      [
        'field' => 'field_newsroom_service_type',
        'query' => 'infsonewsroom:BasicSvType',
      ],
      [
        'field' => 'description',
        'query' => 'description/text()',
      ],
      [
        'field' => 'field_newsroom_basic_mailing',
        'query' => 'infsonewsroom:BasicSvMailing/text()',
      ],
      [
        'field' => 'field_newsroom_mailing_exists',
        'query' => 'infsonewsroom:mailingExists/text()',
      ],
      [
        'field' => 'field_newsroom_service_image:uri',
        'query' => 'infsonewsroom:BasicSvVisuUrl/text()',
      ],
      [
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => [
          'plugins' => [
            'rewrite' => [
              'prefix' => 'service-',
            ],
          ],
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Rebuild importers.
   */
  public static function rebuildImporters() {
    $importers = self::returnImporters();

    foreach ($importers as $importer) {
      // WE drop all tampers for the current importer.
      db_delete('feeds_tamper')
        ->condition('importer', $importer)
        ->execute();
      feeds_importer($importer)->delete();
      // Recreate them.
      $importer = self::buildImporter($importer);
      $importer->generateImporter();
    }
  }

}
