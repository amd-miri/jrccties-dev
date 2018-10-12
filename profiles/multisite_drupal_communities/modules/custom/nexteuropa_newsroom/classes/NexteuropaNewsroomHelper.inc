<?php

/**
 * @file
 * Code for the NewsroomHelper class.
 */

/**
 * NexteuropaNewsroomHelper class.
 */
class NexteuropaNewsroomHelper {

  /**
   * Generates newsroom page URL.
   *
   * @param array $url_parts
   *   Url parts.
   *
   * @return string
   *   Newsroom page URL.
   */
  public static function getPageUrl(array $url_parts = []) {
    return 'newsroom/' . implode('/', $url_parts);
  }

  /**
   * Generates newsroom rss URL.
   *
   * @param array $url_parts
   *   Url parts.
   *
   * @return string
   *   Newsroom rss URL.
   */
  public static function getRssUrl(array $url_parts = []) {
    return 'newsroom-rss/' . implode('/', $url_parts);
  }

  /**
   * Gets newsroom item by original newsroom Id.
   *
   * @param string $field_name
   *   Field name.
   * @param int $newsroom_id
   *   Newsroom original ID.
   *
   * @return object
   *   Newsroom item.
   */
  public static function getNodeByFieldValue($field_name, $newsroom_id = 0) {
    $query = new EntityFieldQuery();
    $newsroom_item = $query
      ->entityCondition('entity_type', 'node')
      ->fieldCondition($field_name, 'value', $newsroom_id, '=')
      ->execute();
    return !empty($newsroom_item['node']) ? array_shift($newsroom_item['node']) : FALSE;
  }

  /**
   * Retrieves nodes associated with topics.
   *
   * @param string $topic_ids
   *   Topic term ids.
   *
   * @return array
   *   Field data.
   */
  public static function getNodesAssociatedToTopics($topic_ids) {
    $topic_ids = is_array($topic_ids) ? $topic_ids : [$topic_ids];
    $cache_key = 'get_topic_entities' . md5(implode('', $topic_ids));
    $data = NULL;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_newsroom_associated_topic', 'f');
      $query->fields('f');
      $query->leftJoin('node', 'n', 'f.entity_id = n.nid');
      $query->condition('n.status', 1);
      $query->condition('f.field_newsroom_associated_topic_tid', $topic_ids);
      $data = $query->execute()->fetchAll();

      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_get_topic_entities', 3600));
    }
    return $data;
  }

  /**
   * Tries to resolve each taxonomy term with a corresponding ID to map.
   *
   * @param string $field_name
   *   The mapping field.
   * @param string $field_value
   *   The mapping field value.
   * @param string $bundle
   *   Bundle name.
   *
   * @return array
   *   Taxonomy ids.
   */
  public static function getTaxonomyTermFromField($field_name, $field_value, $bundle = NULL) {
    $taxonomy_items = [];

    switch ($bundle) {
      case NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY:
        $taxonomy_items = NexteuropaNewsroomVocabularyHelper::getNewsroomTypes();
        break;

      case NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY:
        $taxonomy_items = NexteuropaNewsroomVocabularyHelper::getNewsroomTopics();
        break;

      case NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY:
        $taxonomy_items = NexteuropaNewsroomVocabularyHelper::getNewsroomServices();
        break;
    }

    foreach ($taxonomy_items as $taxonomy_term_item) {
      if (NexteuropaNewsroomHelper::getFieldValue($taxonomy_term_item, $field_name) == $field_value) {
        return $taxonomy_term_item;
      }
    }

    return NULL;
  }

  /**
   * Returns universe URL.
   *
   * @return string
   *   Universe URL.
   */
  public static function getUniverseUrl() {
    return variable_get('nexteuropa_newsroom_base_url', NEXTEUROPA_NEWSROOM_BASE_URL) . self::getUniverseId() . '/';
  }

  /**
   * Gets the existing instances of fields.
   *
   * @param string $type
   *   Select or topic for the moment.
   *
   * @return array
   *   instances
   */
  public static function getFieldInstances($type) {
    // Get instances per field.
    $instances = [];
    if ($type) {
      $field_name = 'field_newsroom_associated_' . $type;
      $mappings = field_info_field_map();
      if (!empty($mappings[$field_name]['bundles']['node'])) {
        $instances = $mappings[$field_name]['bundles']['node'];
      }
    }
    return $instances;
  }

  /**
   * Tries to get taxonomy URL part (taxonomy term name).
   *
   * @param string $request_name
   *   URL request part.
   * @param string $vocabulary_name
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getTermFromRequest($request_name, $vocabulary_name) {
    $cache_key = 'newsroom:term_from_request:' . md5($request_name . $vocabulary_name);

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $taxonomy_term = $cache->data;
    }
    else {
      $taxonomy_term = NULL;
      // If it is tid load taxonomy term directly.
      if ((int) $request_name) {
        $taxonomy_term = taxonomy_term_load($request_name);
      }

      if (!$taxonomy_term) {
        $taxonomy_terms = [];

        if ($vocabulary_name == NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY) {
          $taxonomy_terms = array_merge($taxonomy_terms, NexteuropaNewsroomVocabularyHelper::getNewsroomTypes());
        }
        elseif ($vocabulary_name == NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY) {
          $taxonomy_terms = array_merge($taxonomy_terms, NexteuropaNewsroomVocabularyHelper::getNewsroomTopics());
        }
        // Compare taxonomy terms modified by pathauto with the current value
        // from the URL.
        if ($taxonomy_terms) {
          foreach ($taxonomy_terms as $term_item) {
            if (pathauto_cleanstring($term_item->name) == $request_name) {
              $taxonomy_term = $term_item;
              break;
            }
          }
        }
      }
      cache_set($cache_key, $taxonomy_term, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_term_from_request', 864000));
    }

    return $taxonomy_term;
  }

  /**
   * Defines whether the item is new or not.
   *
   * @param int $created
   *   Timestamp when item was created.
   * @param int $nid
   *   Node id.
   *
   * @return bool
   *   It is a new item or not.
   */
  public static function isNewItem($created, $nid) {
    return user_is_logged_in() && $created > time() - variable_get('nexteuropa_newsroom_days_number_for_new_user', 14) * 86400 && !node_last_viewed($nid);
  }

  /**
   * Gets dropdown options for event types.
   *
   * @param bool $events_only
   *   Display only event types.
   * @param bool $add_empty_value
   *   Add none value in the begining of array.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTypeOptions($events_only = FALSE, $add_empty_value = TRUE) {
    $type_options = self::getTaxonomyTermOptions(NexteuropaNewsroomVocabularyHelper::getNewsroomTypes());
    if ($events_only) {
      $events_types = NexteuropaNewsroomVocabularyHelper::getEventsTermsIds();
      // Filter out non events type.
      if (!empty($events_types)) {
        foreach ($type_options as $key => $type_item) {
          if (!in_array($key, $events_types)) {
            unset($type_options[$key]);
          }
        }
      }
      else {
        $type_options = [];
      }
    }
    if ($add_empty_value) {
      $type_options = [t('- None -')] + $type_options;
    }

    return $type_options;
  }

  /**
   * Gets dropdown options for newsroom topics.
   *
   * @param array $used_topics
   *   Used topics.
   * @param bool $add_empty_value
   *   Add none value in the begining of array.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTopicOptions(array $used_topics = [], $add_empty_value = TRUE) {
    $topic_options = self::getTaxonomyTermOptions(NexteuropaNewsroomVocabularyHelper::getNewsroomTopics());
    if (!empty($used_topics)) {
      foreach ($topic_options as $key => $topic) {
        if (!in_array($key, $used_topics)) {
          unset($topic_options[$key]);
        }
      }
    }
    if ($add_empty_value) {
      $topic_options = [t('- None -')] + $topic_options;
    }
    return $topic_options;
  }

  /**
   * Gets node ids associated with the topics.
   *
   * @param array $topic_ids
   *   Topics' array.
   *
   * @return array
   *   Array of nodes' ids.
   */
  public static function getNodeRelatedToTopic(array $topic_ids = []) {
    $cache_key = 'get_node_related_to_topic:' . md5(implode('', $topic_ids));
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_newsroom_topics', 'ttopic');
      $query->addField('ttopic', 'entity_id');
      $query->condition('field_newsroom_topics_tid', $topic_ids);
      $query->groupBy('ttopic.entity_id');
      $query->having('count(ttopic.entity_id) = :cnt', [':cnt' => count($topic_ids)]);

      $data = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_node_related_to_topic', 3600));
    }
    return $data;
  }

  /**
   * Gets number of items per block for the current page.
   *
   * @param bool $is_highligted
   *   Is block highligted.
   *
   * @return int
   *   Number of items.
   */
  public static function getBlockItemsNumber($is_highligted) {
    $front_page = drupal_is_front_page();
    if ($is_highligted) {
      // Highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_highlighted_items' : 'newsroom_summary_block_num_highlighted_items';
    }
    else {
      // Not highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_items' : 'newsroom_summary_block_num_items';
    }
    return variable_get($variable_name, 5);
  }

  /**
   * Gets Universe Id.
   *
   * @return string
   *   Universe Id.
   */
  public static function getUniverseId() {
    return variable_get('nexteuropa_newsroom_universe_id', FALSE);
  }

  /**
   * Returns newsroom URL.
   *
   * @param string $url_part
   *   Additional part of URL.
   *
   * @return string
   *   URL.
   */
  public static function getNewsroomUrl($url_part) {
    return self::getUniverseUrl() . $url_part;
  }

  /**
   * Returns the current formated date.
   *
   * @param string $format
   *   Format string.
   * @param int $timestamp
   *   Timestamp.
   *
   * @return string
   *   Formated date string.
   */
  public static function getFormatedDate($format = 'Y-m-d', $timestamp = NULL) {
    $timestamp = !empty($timestamp) ? $timestamp : time();
    return format_date($timestamp, 'custom', $format);
  }

  /**
   * Deletes translations.
   *
   * @param object $entity
   *   Object : taxonomy term or node.
   * @param int $entity_id
   *   Entity id.
   * @param string|null $language
   *   Language string.
   */
  public static function deleteEntityTranslations($entity, $entity_id, $language = NULL) {
    $languages = $language ? [$language] : language_list();
    $handler = entity_translation_get_handler('node', $entity);

    foreach ($languages as $language) {
      // Delete translation for the current language.
      $handler->removeTranslation($language->language);
      field_attach_presave('node', $entity);
      field_attach_update('node', $entity);
    }

    if (module_exists('entitycache')) {
      cache_clear_all($entity_id, 'cache_entity_node');
    }
  }

  /**
   * Validates if a given newsroom universe exists.
   *
   * @param string $universe_id
   *   Newsroom Universe ID.
   *
   * @return bool
   *   Newsroom Universe exists or not.
   */
  public static function validateUniverse($universe_id = NULL) {
    if ($universe_id) {
      // logout.cfm is used because it is always available if a universe exists.
      $test = drupal_http_request(self::getUniverseUrl() . 'logout.cfm');
      return $test->code == 200;
    }

    return FALSE;
  }

  /**
   * Validates if a given subsite exists.
   *
   * @param string $subsite
   *   Subsite name.
   *
   * @return bool
   *   Newsroom Universe subsite exists or not.
   */
  public static function validateSubsite($subsite = NULL) {
    // The subsite is not mandatory.
    if (empty($subsite)) {
      return TRUE;
    }
    else {
      $request = drupal_http_request(self::getUniverseUrl() . 'validation.cfm?subsite=' . $subsite);
      return !empty($request->data) && $request->data == 'True';
    }

    return FALSE;
  }

  /**
   * Gets taxonomy terms options.
   *
   * @param array $terms
   *   Taxonomy term arrays.
   *
   * @return array
   *   Dropdown options.
   */
  public static function getTaxonomyTermOptions(array $terms) {
    $options = [];
    if ($terms) {
      foreach ($terms as $term) {
        $options[$term->tid] = str_repeat('-', $term->depth) . $term->name;
      }
    }
    return $options;
  }

  /**
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  public static function getPageUsedTopicsIds() {
    $cache_key = 'result_topics';
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $tids = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('topic_field', ['tid' => 'field_newsroom_topics_tid']);
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->condition('n.status', 1);
      $tids = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $tids, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_page_result_topics', 86400));
    }
    return $tids;
  }

  /**
   * Get email hash for subscriptions.
   *
   * @param string $email
   *   E-mail.
   *
   * @return string
   *   Hash.
   */
  public static function getEmailHash($email) {
    return hash('sha256', drupal_strtolower($email) . variable_get('nexteuropa_newsroom_app_key'));
  }

  /**
   * Gets the node title without loading the whole node object.
   *
   * @param int $nid
   *   Node nid.
   *
   * @return string
   *   Node title.
   */
  public static function getNodeTitle($nid) {
    $cache_key = 'newsroom:node_title:' . $nid;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $node_title = $cache->data;
    }
    else {
      $node_title = db_query('SELECT title_field_value FROM {field_data_title_field} WHERE entity_id = :nid', [':nid' => $nid])->fetchField();
      if (empty($node_title)) {
        $node_title = db_query('SELECT title FROM {node} WHERE nid = :nid', [':nid' => $nid])->fetchField();
      }
      cache_set($cache_key, $node_title, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_node_title', 3600));
    }
    return $node_title;
  }

  /**
   * Gets entity value for non transltable fields.
   *
   * @param object $entity
   *   Entity object.
   * @param string $field_name
   *   Field name.
   * @param string $value_name
   *   Name of value field.
   *
   * @return string|int|null
   *   Field value.
   */
  public static function getFieldValue($entity, $field_name, $value_name = 'value') {
    $value = NULL;

    if ($entity) {
      if (!empty($entity->{$field_name}[LANGUAGE_NONE][0][$value_name])) {
        if (count($entity->{$field_name}[LANGUAGE_NONE]) > 1) {
          $value = [];
          foreach ($entity->{$field_name}[LANGUAGE_NONE] as $item) {
            $value[] = $item[$value_name];
          }
        }
        else {
          $value = $entity->{$field_name}[LANGUAGE_NONE][0][$value_name];
        }
      }
    }

    return $value;
  }

  /**
   * Gets main URL for a node based on the newsroom type settings.
   *
   * @param object $node
   *   Node object.
   * @param string $display_name
   *   Display name.
   *
   * @return string
   *   Main node URL.
   */
  public static function getNodeMainUrl($node, $display_name = NULL) {
    $url = 'node/' . $node->nid;
    $type = NexteuropaNewsroomVocabularyHelper::getNewsroomType(self::getFieldValue($node, 'field_newsroom_item_type', 'tid'));
    $click_through = self::getFieldValue($type, 'field_newsroom_direct_link');
    $main_link_url = self::getFieldTranslatedValue($node, 'field_newsroom_item_main_link', 'url');

    if (!empty($main_link_url)) {
      if ($click_through == NEXTEUROPA_NEWSROOM_CLICKTHROUGH_FORCE) {
        $url = $main_link_url;
      }
      elseif (self::getFieldValue($node, 'field_newsroom_teaser_only')) {
        // If item is Teaser only.
        switch ($click_through) {
          case 'always':
            $url = $main_link_url;
            break;

          case 'from_teaser':
            if ($display_name == 'teaser') {
              $url = $main_link_url;
            }
            break;
        }
      }
    }

    return $url;
  }

  /**
   * Gets translated field value.
   *
   * @param object $entity
   *   Entity object.
   * @param string $field_name
   *   Field name.
   * @param string $property_name
   *   Field property name.
   * @param string $entity_type
   *   Entity type.
   *
   * @return int|string|null
   *   Field value.
   */
  public static function getFieldTranslatedValue($entity, $field_name, $property_name = 'value', $entity_type = 'node') {
    $field = field_view_field($entity_type, $entity, $field_name);
    $value = NULL;
    if (!empty($field['#items'][0]['safe_value'])) {
      $value = $field['#items'][0]['safe_value'];
    }
    elseif (!empty($field['#items'][0][$property_name])) {
      $value = $field['#items'][0][$property_name];
    }
    return $value;
  }

  /**
   * Checks date format and if it is ok returns DateTime object.
   *
   * @param string $value
   *   Date string.
   *
   * @return \DateTime|null
   *   Datetime or NULL.
   */
  public static function checkDateFormat($value) {
    $date = NULL;
    // Format date 2017-01-01 or 01-01-2017.
    if (preg_match('/^\d{4}-\d{2}-\d{2}$/', $value) || preg_match('/^\d{2}-\d{2}-\d{4}$/', $value)) {
      $date = new DateTime();
      $date->setTimestamp(strtotime($value));
    }
    return $date;
  }

  /**
   * Gets default language.
   *
   * @return string
   *   Default language code.
   */
  public static function getDefaultLanguage() {
    return language_default()->language;
  }

  /**
   * Gets default language in uppercase.
   *
   * @return string
   *   Default language code.
   */
  public static function getDefaultLanguageUppercase() {
    return drupal_strtoupper(language_default()->language);
  }

  /**
   * Sets 404 http response.
   */
  public static function set404response() {
    drupal_not_found();
    drupal_exit();
  }

  /**
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  public static function getResultTopicsId() {
    $cache_key = 'agenda_result_topics';
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $tids = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('topic_field', ['tid' => 'field_newsroom_topics_tid']);
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->leftJoin('field_data_field_newsroom_newsletter_only', 'newsletter_item', 'newsletter_item.entity_id = n.nid');
      $query->condition('n.status', 1);

      $db_or = db_or();
      $db_or->condition('newsletter_item.field_newsroom_newsletter_only_value', 1, '<>');
      $db_or->isNull('newsletter_item.field_newsroom_newsletter_only_value');

      $query->condition($db_or);
      $query->condition('tf.field_newsroom_item_type_tid', NexteuropaNewsroomVocabularyHelper::getEventsTermsIds());
      $tids = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $tids, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_result_topics', 86400));
    }
    return $tids;
  }

}
