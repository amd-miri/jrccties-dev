<?php

/**
 * @file
 * Code for the NexteuropaNewsroomBlock class.
 */

/**
 * NexteuropaNewsroomBlock class base class.
 */
class NexteuropaNewsroomBlock extends NexteuropaNewsroomBlockBase {
  protected $items = [];

  /**
   * Contructor of NexteuropaNewsroomBlock class.
   *
   * @param object $type
   *   Newsroom type taxonomy term.
   * @param array|object $topics
   *   Newsroom topics taxonomy terms.
   * @param string $operator
   *   Operator connecting  topics.
   */
  public function __construct($type, $topics, $operator) {
    parent::__construct($type, $topics, $operator);
    $this->setIsAgenda(FALSE);
    $this->setHighlighted();
    $this->getData();
  }

  /**
   * Gets block items.
   *
   * @return array
   *   Block items.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Sets block items.
   *
   * @param array $value
   *   Block items.
   */
  public function setItems(array $value) {
    $this->items = $value;
  }

  /**
   * Gets block title.
   *
   * @return string
   *   Title.
   */
  public function getTitle() {
    return $this->getType()->name;
  }

  /**
   * Gets type URL.
   *
   * @return string
   *   Type URL.
   */
  public function getTypeUrl() {
    return pathauto_cleanstring($this->getTitle());
  }

  /**
   * Gets topic URL.
   *
   * @return string
   *   Topic URL.
   */
  public function getTopicUrl() {
    $url = NEXTEUROPA_NEWSROOM_ALL;
    $topics = $this->getTopics();
    if (count($topics) == 1) {
      $topic = reset($topics);
      $url = pathauto_cleanstring($topic->name);
    }

    return $url;
  }

  /**
   * Sets is block highlighted.
   */
  public function setHighlighted() {
    $this->highlighted = NexteuropaNewsroomHelper::getFieldValue($this->getType(), 'field_newsroom_highlighted');
  }

  /**
   * Gets block data from db.
   */
  public function getData() {
    $topic_ids = $this->getTopicsId();
    $cache_key = 'newsroom:summary_block:' . md5($this->getType()->tid . implode('', $topic_ids));

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $result = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('n', ['nid', 'title', 'created']);
      $query->fields('tt', ['name']);
      $query->addField('tt', 'tid', 'type_id');
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
      $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
      $query->leftJoin('field_data_field_newsroom_newsletter_only', 'newsletter_item', 'newsletter_item.entity_id = n.nid');

      $query->condition('n.status', 1);

      $db_or = db_or();
      $db_or->condition('newsletter_item.field_newsroom_newsletter_only_value', 1, '<>');
      $db_or->isNull('newsletter_item.field_newsroom_newsletter_only_value');

      $query->condition($db_or);
      $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);

      if (!empty($topic_ids)) {
        if ($this->getOperator() == NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
          $query->condition('topic_data.tid', $topic_ids);
        }
        elseif ($nids = NexteuropaNewsroomHelper::getNodeRelatedToTopic($topic_ids)) {
          $query->condition('nid', $nids, 'IN');
        }
      }

      $query->condition('tt.tid', NexteuropaNewsroomVocabularyHelper::getTypeChildren($this->getType()->tid));
      $query->range(0, NexteuropaNewsroomHelper::getBlockItemsNumber($this->getHighlighted()));
      $query->orderBy('n.created', 'DESC');
      $result = $query->execute()->fetchAll();

      cache_set($cache_key, $result, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_summary_block', 3600));
    }

    if ($result) {
      $this->setLatestDate($result[0]->created);
    }

    foreach ($result as $key => $item) {
      $result[$key]->new = NexteuropaNewsroomHelper::isNewItem($item->created, $item->nid);
      $result[$key]->created = NexteuropaNewsroomHelper::getFormatedDate(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT, $item->created);
    }

    $this->setItems($result);
  }

  /**
   * Generates block content.
   *
   * @return string
   *   Block content.
   */
  public function generateContent() {
    return theme('newsroom_summary_block_wrapper', [
      'content' => $this->getContent(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => $this->getTypeUrl(),
      'url' => NexteuropaNewsroomHelper::getPageUrl([$this->getTypeUrl(), $this->getTopicUrl()]),
    ]);
  }

  /**
   * Generates block items content.
   *
   * @return string
   *   Block items content.
   */
  protected function getContent() {
    return theme('newsroom_summary_block_item', [
      'items' => $this->getItems(),
    ]);
  }

}
