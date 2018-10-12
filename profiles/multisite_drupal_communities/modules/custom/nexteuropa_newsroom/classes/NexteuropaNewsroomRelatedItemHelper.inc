<?php

/**
 * @file
 * Code for the NexteuropaNewsroomRelatedItemHelper class.
 */

/**
 * NexteuropaNewsroomRelatedItemHelper class.
 */
class NexteuropaNewsroomRelatedItemHelper {

  /**
   * Gets related item block.
   *
   * @param int $nid
   *   Node id.
   *
   * @return null|string
   *   HTML output of related items.
   */
  public static function getRelatedItems($nid) {
    $output = NULL;
    $cache_key = 'related_content_items:' . $nid;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $output = $cache->data;
    }
    else {
      $output = theme('newsroom_events_related_items', [
        'related_items' => array_merge(self::getResultRelatedItems($nid), self::getEventsRelatedItems($nid)),
      ]);
      cache_set($cache_key, $output, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_related_content_items', 86400));
    }

    return $output;
  }

  /**
   * Gets related items for events type newsroom items.
   *
   * @param int $nid
   *   Node id.
   * @param int $exclude_id
   *   Node id to be excluded.
   *
   * @return array
   *   Array of related items.
   */
  public static function getEventsRelatedItems($nid, $exclude_id = NULL) {
    $related_items = [];
    $query = db_select('field_data_field_newsroom_related_content', 'n');
    $query->fields('n', ['entity_id']);
    $query->fields('tt', ['name']);
    $query->fields('cl', ['field_newsroom_content_label_value']);
    $query->join('field_data_field_newsroom_item_type', 'item_type', 'n.entity_id = item_type.entity_id');
    $query->join('taxonomy_term_data', 'tt', 'tt.tid = item_type.field_newsroom_item_type_tid');
    $query->join('field_data_field_newsroom_item_type', 'item_type1', 'n.field_newsroom_related_content_target_id = item_type1.entity_id');
    $query->leftJoin('field_data_field_newsroom_content_label', 'cl', 'cl.entity_id = tt.tid');
    $query->condition('n.field_newsroom_related_content_target_id', $nid);
    if (!empty($exclude_id)) {
      $query->condition('n.entity_id', $exclude_id, '<>');
    }
    $query->condition('n.bundle', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $query->condition('item_type1.field_newsroom_item_type_tid', NexteuropaNewsroomVocabularyHelper::getEventsTermsIds());

    if ($items = $query->execute()->fetchAll()) {
      foreach ($items as $item) {
        $related_items[] = self::buildRelatedItem($item->entity_id, empty($item->field_newsroom_content_label_value) ? $item->name : $item->field_newsroom_content_label_value);
      }
    }

    return $related_items;
  }

  /**
   * Build related item object.
   *
   * @param int $nid
   *   Node id.
   * @param string $type_label
   *   Content type label.
   *
   * @return \stdClass
   *   Related item object.
   */
  public static function buildRelatedItem($nid, $type_label) {
    $std = new stdClass();
    $std->type_name = $type_label;
    $std->link = l(NexteuropaNewsroomHelper::getNodeTitle($nid), 'node/' . $nid);
    return $std;
  }

  /**
   * Gets related items for result type newsroom items.
   *
   * @param int $nid
   *   Node id.
   *
   * @return array
   *   Array of related items.
   */
  public static function getResultRelatedItems($nid) {
    $items = [];
    $node = node_load($nid);
    $type_id = NexteuropaNewsroomHelper::getFieldValue($node, 'field_newsroom_item_type', 'tid');
    if (in_array($type_id, NexteuropaNewsroomVocabularyHelper::getResultsTermsIds())) {
      $related_items = !empty($node->field_newsroom_related_content[LANGUAGE_NONE]) ? $node->field_newsroom_related_content[LANGUAGE_NONE] : [];
      foreach ($related_items as $related_item) {
        if ($related_node = node_load($related_item['target_id'])) {
          $type = NexteuropaNewsroomVocabularyHelper::getNewsroomType(NexteuropaNewsroomHelper::getFieldValue($related_node, 'field_newsroom_item_type', 'tid'));
          $content_label = NexteuropaNewsroomHelper::getFieldValue($type, 'field_newsroom_content_label');
          $items[] = self::buildRelatedItem($related_node->nid, !empty($content_label) ? $content_label : $type->name);
          $items = array_merge($items, self::getEventsRelatedItems($related_node->nid, $nid));
        }
      }
    }

    return $items;
  }

}
