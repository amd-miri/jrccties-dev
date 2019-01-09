<?php

/**
 * @file
 * Code for the NewsroomHelper class.
 */

/**
 * NexteuropaNewsroomVocabularyHelper class.
 */
class NexteuropaNewsroomVocabularyHelper {

  /**
   * Merges a term_tid and it's children into one array.
   *
   * @param int $term_tid
   *   Term id.
   *
   * @return array
   *   Tidss
   */
  public static function getTypeChildren($term_tid) {
    $children_items = self::findChildrenById(NexteuropaNewsroomVocabularyHelper::getNewsroomTypes(), $term_tid);
    // We need parent ID also in the output array to use it in query.
    $parent_children_tids = [$term_tid];
    $children_tids = array_keys($children_items);
    if (!empty($children_tids)) {
      $parent_children_tids = array_merge($parent_children_tids, $children_tids);
    }

    return $parent_children_tids;
  }

  /**
   * Gets events Terms ids.
   *
   * @return array
   *   Newsroom type taxonomy terms array.
   */
  public static function getEventsTermsIds() {
    $event_type_ids = &drupal_static(__FUNCTION__);
    if (empty($event_type_ids)) {
      $event_type_ids = self::findBehaviorType([
        'consultation_funding',
        'events',
        'agenda',
        'call',
      ]);
    }
    return $event_type_ids;
  }

  /**
   * Gets results Terms ids.
   *
   * @return array
   *   Newsroom type taxonomy terms array.
   */
  public static function getResultsTermsIds() {
    $event_type_ids = &drupal_static(__FUNCTION__);
    if (empty($event_type_ids)) {
      $event_type_ids = self::findBehaviorType([
        'result',
      ]);
    }
    return $event_type_ids;
  }

  /**
   * Finds types by behavior.
   *
   * @param array $behavior_types
   *   Behaviors.
   */
  private static function findBehaviorType(array $behavior_types) {
    $event_type_ids = [];
    $types = NexteuropaNewsroomVocabularyHelper::getNewsroomTypes();
    foreach ($types as $type) {
      if (in_array(NexteuropaNewsroomHelper::getFieldValue($type, 'field_newsroom_type'), $behavior_types)) {
        $event_type_ids[] = $type->tid;
      }
    }
    return $event_type_ids;
  }

  /**
   * Gets newsroom type vocabulary.
   *
   * @return object
   *   Newsroom type vocabulary.
   */
  public static function getNewsroomTypeVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets Newsroom types.
   *
   * @return array
   *   Newsroom types.
   */
  public static function getNewsroomTypes() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $vocabulary = self::getNewsroomTypeVocabulary();
      $data = self::getNewsroomTaxonomyTerms($vocabulary->vid);
    }
    return $data;
  }

  /**
   * Finds children by id.
   *
   * @param array $taxonomy_terms
   *   Taxonomy terms array.
   * @param int $parent_tid
   *   Parent taxonomy term ID.
   *
   * @return array
   *   Taxonomy terms.
   */
  public static function findChildrenById(array $taxonomy_terms, $parent_tid) {
    $children = [];
    if ($taxonomy_terms) {
      foreach ($taxonomy_terms as $item) {
        if (in_array($parent_tid, $item->parents)) {
          $children[$item->tid] = $item;
        }
      }
    }
    return $children;
  }

  /**
   * Gets newsroom type by id.
   *
   * @param int|null $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomType($tid = NULL) {
    return $tid ? self::findTermById(NexteuropaNewsroomVocabularyHelper::getNewsroomTypes(), $tid) : NULL;
  }

  /**
   * Gets newsroom type by id.
   *
   * @param int|null $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomTopic($tid = NULL) {
    return $tid ? self::findTermById(self::getNewsroomTopics(), $tid) : NULL;
  }

  /**
   * Gets newsroom topic vocabulary.
   *
   * @return object
   *   Newsroom topic vocabulary.
   */
  public static function getNewsroomTopicVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets newsroom service vocabulary.
   *
   * @return object
   *   Newsroom service vocabulary.
   */
  public static function getNewsroomServiceVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets newsroom topics.
   *
   * @return array
   *   Newsroom topics.
   */
  public static function getNewsroomTopics() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $vocabulary = self::getNewsroomTopicVocabulary();
      $data = self::getNewsroomTaxonomyTerms($vocabulary->vid);
    }
    return $data;
  }

  /**
   * Gets newsroom services.
   *
   * @return array
   *   Newsroom services.
   */
  public static function getNewsroomServices() {
    $data = &drupal_static(__FUNCTION__);
    if (empty($data)) {
      $vocabulary = self::getNewsroomServiceVocabulary();
      $data = self::getNewsroomTaxonomyTerms($vocabulary->vid);
    }
    return $data;
  }

  /**
   * Gets translated taxonomy items from vocabulary.
   *
   * @param int $vocabulary_id
   *   Vocabulary ID.
   *
   * @return array
   *   Array of taxonomy terms.
   */
  protected static function getNewsroomTaxonomyTerms($vocabulary_id) {
    global $language;
    $cache_key = 'terms_' . $vocabulary_id . $language->language;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $data = i18n_taxonomy_get_tree($vocabulary_id, NexteuropaNewsroomHelper::getDefaultLanguage(), 0, NULL, TRUE);
      foreach ($data as $key => $taxonomy_term) {
        $i18n_object = i18n_get_object('taxonomy_term', $taxonomy_term->tid);
        $data[$key] = $i18n_object->localize($language->language);
      }
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }

    return $data;
  }

  /**
   * Finds term by id.
   *
   * @param array $taxonomy_terms
   *   Taxonomy terms array.
   * @param int $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function findTermById(array $taxonomy_terms, $tid) {
    $taxonomy_term = NULL;
    if ($taxonomy_terms) {
      foreach ($taxonomy_terms as $item) {
        if ($item->tid == $tid) {
          $taxonomy_term = $item;
        }
      }
    }
    return $taxonomy_term;
  }

  /**
   * Returns item type in plural.
   *
   * @param int $item_type_id
   *   Taxonomy term ID.
   *
   * @return string
   *   Taxonomy term in plural.
   */
  public static function getItemTypeInPlural($item_type_id) {
    $the_type = self::getNewsroomType($item_type_id);

    $plurals = [
      250 => t('Events'),
      520 => t('Consultations'),
      253 => t('Funding opportunities'),
      826 => t('Calls for proposals'),
      825 => t('Calls for tenders'),
    ];

    return $plurals[$the_type->field_newsroom_type_id[LANGUAGE_NONE][0]['value']];
  }

}
