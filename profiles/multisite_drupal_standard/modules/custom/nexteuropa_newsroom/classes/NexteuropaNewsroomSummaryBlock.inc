<?php

/**
 * @file
 * Code for the NexteuropaNewsroomBlock class.
 */

/**
 * NexteuropaNexteuropaNewsroomBlock class base class.
 */
class NexteuropaNewsroomSummaryBlock {

  protected $types = [];
  protected $topics = [];
  protected $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;

  /**
   * Gets newsroom topics.
   *
   * @return array
   *   Newsroom topics.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Sets newsroom topics.
   *
   * @param array $value
   *   Newsroom topics.
   */
  public function setTopics(array $value) {
    $this->topics = $value;
  }

  /**
   * Sets newsroom types.
   *
   * @param array $value
   *   Newsroom types.
   */
  public function setTypes(array $value) {
    $this->types = $value;
  }

  /**
   * Gets newsroom types.
   *
   * @return array
   *   Newsroom types
   */
  public function getTypes() {
    return $this->types;
  }

  /**
   * Gets query operator.
   *
   * @return string
   *   Query operator: OR or AND.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Sets query operator.
   *
   * @param string $value
   *   Query operator: OR or AND.
   */
  public function setOperator($value) {
    $this->operator = $value;
  }

  /**
   * Generates RSS link based on topics.
   *
   * @return string
   *   RSS link.
   */
  protected function generateRss() {
    $topics = $this->getTopics();
    $topic_url = NULL;
    $topic_name = NULL;

    // We take only first topic if we have multiple.
    if (!empty($topics)) {
      $topic_name = $topics[0]->name;
      $topic_url = pathauto_cleanstring($topics[0]->name);
    }

    $rss_path = NexteuropaNewsroomHelper::getRssUrl([NEXTEUROPA_NEWSROOM_ALL, $topic_url]);
    $rss_title = !empty($topic_name) ? 'RSS feed : ' . $topic_name : 'RSS feed';

    $rss = '<div class="newsroom_rss">';
    $rss .= theme('feed_icon', [
      'url' => $rss_path,
      'title' => $rss_title,
    ]);
    $rss .= l($rss_title, $rss_path);
    $rss .= '</div>';

    return $rss;
  }

  /**
   * Get filters: type, topics based on the request.
   */
  protected function getFilters() {
    $path = md5(current_path());
    $cache_key = 'newsroom:summary_filter:' . $path;

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $config = $cache->data;
    }
    else {
      $topic_operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;
      $selected_topics = [];
      $selected_types = [];

      if ($entity = $this->getEntityFromRequest()) {
        if (!empty($entity->type) && $entity->type == 'newsroom_selection') {

          if (NexteuropaNewsroomHelper::getFieldValue($entity, 'field_newsroom_topic_operator')) {
            $topic_operator = NexteuropaNewsroomHelper::getFieldValue($entity, 'field_newsroom_topic_operator');
          }

          // Get topics from newsroom selection.
          if ($topic_config = field_get_items('node', $entity, 'field_newsroom_selected_topics')) {
            foreach ($topic_config as $term_ref) {
              $selected_topics[] = $term_ref['target_id'];
            }
          }

          // Get types from newsroom selection.
          $type_config = field_get_items('node', $entity, 'field_newsroom_selected_types');
          if ($type_config) {
            foreach ($type_config as $term_ref) {
              $selected_types[] = $term_ref['tid'];
            }
          }
        }
        elseif ($associated_topic_id = NexteuropaNewsroomHelper::getFieldValue($entity, 'field_newsroom_associated_topic', 'tid')) {
          // If it has the associated field, try to load topic.
          $selected_topics[] = $associated_topic_id;
        }
      }

      $types = [];
      if (!empty($selected_types)) {
        foreach ($selected_types as $type_id) {
          $types[] = NexteuropaNewsroomVocabularyHelper::getNewsroomType($type_id);
        }
      }
      else {
        $types = NexteuropaNewsroomVocabularyHelper::getNewsroomTypes();
        // We need only the first level of types.
        foreach ($types as $key => $type) {
          if ($type->depth > 0) {
            unset($types[$key]);
          }
        }
      }

      $topics = [];
      foreach ($selected_topics as $topic_id) {
        if ($topic_term = NexteuropaNewsroomVocabularyHelper::getNewsroomTopic($topic_id)) {
          $topics[] = $topic_term;
        }
      }

      $config['topic'] = $topics;
      $config['topic_operator'] = $topic_operator;
      $config['type'] = $types;

      cache_set($cache_key, $config, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_summary_filter', 3600));
    }

    $this->setTopics($config['topic']);
    $this->setTypes($config['type']);
    $this->setOperator($config['topic_operator']);
  }

  /**
   * Tries to find the entity based on request.
   *
   * @return object
   *   Drupal entity: node, taxonomy term.
   */
  protected function getEntityFromRequest() {
    $entity = NULL;
    $current_path = menu_get_item();
    // We are on a view object, it's a term argument,
    // let's use to filter results.
    if ($current_path['page_callback'] === 'views_page' && $current_path['path'] === 'taxonomy/term/%') {
      $argument_values = array_values($current_path['page_arguments']);
      $last_argument_element = end($argument_values);
      // We may have a term page, let's try to load it.
      if (is_numeric($last_argument_element)) {
        $entity = taxonomy_term_load($last_argument_element);
      }
    }
    elseif ($current_path['page_callback'] === 'node_page_view') {
      // It is a node page take node entity from request.
      $entity = $current_path['map'][1];
    }
    elseif (!empty($current_path['page_arguments'][0]->tid)) {
      // It's taxonomy term without views.
      $entity = $current_path['page_arguments'][0];
    }

    // Check if selection config is set.
    if ($newsroom_selection_id = NexteuropaNewsroomHelper::getFieldValue($entity, 'field_newsroom_associated_select', 'target_id')) {
      // If it has the selection field, try to load config.
      $entity = node_load($newsroom_selection_id);
    }

    return $entity;
  }

  /**
   * Generates the summary block.
   *
   * @return string
   *   The content of the block.
   */
  public function generateContent() {
    $this->getFilters();
    $events_terms = NexteuropaNewsroomVocabularyHelper::getEventsTermsIds();
    $blocks = [];
    $output = NULL;

    foreach ($this->getTypes() as $type) {
      // We exclude event content types, because we display them as agenda.
      if (!empty($events_terms) && in_array($type->tid, $events_terms)) {
        continue;
      }

      $blocks[] = new NexteuropaNewsroomBlock($type, $this->getTopics(), $this->getOperator());
    }

    $blocks[] = new NexteuropaNewsroomBlockAgenda(NULL, $this->getTopics(), $this->getOperator());

    usort($blocks, ['NexteuropaNewsroomSummaryBlock', 'sortBlocks']);
    foreach ($blocks as $block) {
      $output .= $block->generateContent();
    }
    return theme('newsroom_summary_block', [
      'content' => $output,
      'rss' => $this->generateRss(),
    ]);
  }

  /**
   * Callback: sorts newsroom boxes.
   */
  public function sortBlocks($a, $b) {
    $display_highlights_begin = variable_get('nexteuropa_newsroom_display_highlights_begin', 0);
    $agenda_after_highlights = variable_get('nexteuropa_newsroom_agenda_after_highlights', 0);
    $order_by_last_update = variable_get('nexteuropa_newsroom_order_by_last_update', 0);

    $type = !empty($a->getType()) && !empty($b->getType());

    if ($display_highlights_begin && $a->getHighlighted() != $b->getHighlighted()) {
      $value = $a->getHighlighted() > $b->getHighlighted() ? -1 : 1;
    }
    elseif ($agenda_after_highlights && $a->getIsAgenda() != $b->getIsAgenda()) {
      $value = ((int) $a->getIsAgenda()) > ((int) $b->getIsAgenda()) ? -1 : 1;
    }
    elseif ($order_by_last_update && $a->getLatestDate() != $b->getLatestDate()) {
      $value = $a->getLatestDate() > $b->getLatestDate() ? -1 : 1;
    }
    elseif ($type && $a->getType()->depth < $b->getType()->depth) {
      $value = 1;
    }
    elseif ($type && $a->getType()->depth > $b->getType()->depth) {
      $value = -1;
    }
    elseif ($type && $a->getType()->weight < $b->getType()->weight) {
      $value = -1;
    }
    elseif ($type && $a->getType()->weight > $b->getType()->weight) {
      $value = 1;
    }
    else {
      $value = 0;
    }

    return $value;
  }

}
