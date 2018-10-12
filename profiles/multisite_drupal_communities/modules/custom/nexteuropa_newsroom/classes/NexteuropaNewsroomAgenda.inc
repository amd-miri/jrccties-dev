<?php

/**
 * @file
 * Code for the NexteuropaNewsroomAgenda class.
 */

/**
 * NexteuropaNewsroomAgenda base class.
 */
class NexteuropaNewsroomAgenda {
  const DATE_FORMAT = 'Y-m-d';
  const OUTPUT_DATE_FORMAT = 'j F Y';
  const AGENDA_TYPE_CURRENT = 'current';
  const AGENDA_TYPE_UPCOMING = 'upcoming';
  const AGENDA_TYPE_PAST = 'past';

  protected $topicUrl = NEXTEUROPA_NEWSROOM_ALL;
  protected $topics = [];
  protected $typeUrl = NEXTEUROPA_NEWSROOM_ALL;
  protected $typeId = NULL;
  protected $typeName = NULL;
  protected $topicName = NULL;
  protected $currentDate = NULL;
  protected $upcomingDate = NULL;
  protected $previousDate = NULL;
  protected $currentItems = [];
  protected $upcomingItems = [];
  protected $upcomingNewsItems = [];
  protected $pastItems = [];
  protected $pastNewsItems = [];
  protected $result = [];
  protected $query = NULL;
  protected $urlParts = [];
  protected $isBlock = FALSE;

  /**
   * NexteuropaNewsroomAgenda constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param object $topics
   *   Newsroom topic.
   * @param object $current_day
   *   Current date.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setCurrentDate($current_day);
    if ($type) {
      $this->setTypeId($type->tid);
      $this->setTypeUrl($type->name);
      $this->typeName = $type->name;
    }
    if (is_object($topics)) {
      $this->topicName = $topics->name;
      $this->setTopicUrl($topics->name);
      $topics = [$topics];
    }

    $this->setTopics($topics);
  }

  /**
   * Gets the type name.
   *
   * @return string
   *   Type name.
   */
  public function getTypeName() {
    return $this->typeName;
  }

  /**
   * Gets the topic name.
   *
   * @return string
   *   Topic name.
   */
  public function getTopicName() {
    return $this->topicName;
  }

  /**
   * Gets minimal items number per agenda page.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return variable_get('nexteuropa_newsroom_agenda_page_items_number', 10);
  }

  /**
   * Gets is block.
   *
   * @return bool
   *   Is it a block or not.
   */
  public function getIsBlock() {
    return $this->isBlock;
  }

  /**
   * Sets is block.
   *
   * @param bool $value
   *   Is it a block or not.
   */
  public function setIsBlock($value) {
    $this->isBlock = $value;
  }

  /**
   * Gets url parts.
   *
   * @return array
   *   URL parts.
   */
  public function getUrlParts() {
    return $this->urlParts;
  }

  /**
   * Gets topic url.
   *
   * @return string
   *   Topic URL part.
   */
  public function getTopicUrl() {
    return $this->topicUrl;
  }

  /**
   * Sets topic URL.
   *
   * @param string $value
   *   Topic URL part.
   */
  public function setTopicUrl($value) {
    $this->topicUrl = !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Gets type URL.
   *
   * @return string
   *   Type URL part.
   */
  public function getTypeUrl() {
    return $this->typeUrl;
  }

  /**
   * Sets type URL.
   *
   * @param string $value
   *   Type URL part.
   */
  public function setTypeUrl($value) {
    $this->typeUrl = !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Gets current items.
   *
   * @return array
   *   Current agenda items.
   */
  public function getCurrentItems() {
    return $this->currentItems;
  }

  /**
   * Sets current items.
   *
   * @param array $value
   *   Current agenda items.
   */
  public function setCurrentItems(array $value) {
    $this->currentItems = $this->prepareItemsOutput($value, NexteuropaNewsroomAgenda::AGENDA_TYPE_CURRENT);
  }

  /**
   * Gets upcoming items.
   *
   * @return array
   *   Upcoming agenda items.
   */
  public function getUpcomingItems() {
    return $this->upcomingItems;
  }

  /**
   * Sets upcoming items.
   *
   * @param array $value
   *   Upcoming agenda items.
   */
  public function setUpcomingItems(array $value) {
    $this->upcomingItems = $this->prepareItemsOutput($value, NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING);
  }

  /**
   * Gets upcoming items.
   *
   * @return array
   *   Past agenda items.
   */
  public function getPastItems() {
    return $this->pastItems;
  }

  /**
   * Sets past items.
   *
   * @param array $value
   *   Past agenda items.
   */
  public function setPastItems(array $value) {
    $this->pastItems = $this->prepareItemsOutput($value, NexteuropaNewsroomAgenda::AGENDA_TYPE_PAST);
  }

  /**
   * Gets upcoming date.
   *
   * @return object
   *   Upcoming date.
   */
  public function getUpcomingDate() {
    return $this->upcomingDate;
  }

  /**
   * Sets upcoming date.
   *
   * @param object $value
   *   Upcoming date.
   */
  public function setUpcomingDate($value) {
    $this->upcomingDate = $value;
  }

  /**
   * Gets previous date.
   *
   * @return object
   *   Previous date.
   */
  public function getPreviousDate() {
    return $this->previousDate;
  }

  /**
   * Sets previous date.
   *
   * @param object $value
   *   Previous date.
   */
  public function setPreviousDate($value) {
    $this->previousDate = $value;
  }

  /**
   * Gets current date.
   *
   * @return Datetime
   *   Current date.
   */
  public function getCurrentDate() {
    return $this->currentDate;
  }

  /**
   * Sets current date.
   *
   * @param object $value
   *   Current date.
   */
  public function setCurrentDate($value) {
    $value->setTime(0, 0, 0);
    $this->currentDate = $value;
  }

  /**
   * Gets query object.
   *
   * @return object
   *   Query object.
   */
  public function getQuery() {
    return $this->query;
  }

  /**
   * Sets query object.
   *
   * @param object $value
   *   Query object.
   */
  public function setQuery($value) {
    $this->query = $value;
  }

  /**
   * Gets results.
   *
   * @return array
   *   DB data result.
   */
  public function getResult() {
    return $this->result;
  }

  /**
   * Sets DB data results.
   */
  public function setResult() {
    $cache_key = 'result:' . $this->getUniqueCachePart();
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $this->getBaseQuery();
      $items = $this->loadResult();
      $data = $this->prepareDateObjects($items);
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_agenda_result', 3600));
    }
    $this->result = $data;
  }

  /**
   * Sets type id.
   *
   * @param int $value
   *   Type id.
   */
  public function setTypeId($value) {
    $this->typeId = $value;
  }

  /**
   * Gets type id.
   *
   * @return int
   *   Type id.
   */
  public function getTypeId() {
    return $this->typeId;
  }

  /**
   * Sets topics.
   *
   * @param object $value
   *   Newsroom topic terms array.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Gets topics.
   *
   * @return array
   *   Newsroom topic terms array.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Adds URL part.
   *
   * @param string $value
   *   URL part.
   */
  public function addUrlPart($value) {
    $this->urlParts[] = $value;
  }

  /**
   * Prepares agenda components: query, result, the dates range.
   */
  protected function prepareAgenda() {
    $this->setResult();
    $this->setupAgenda();
  }

  /**
   * Returns previous title.
   *
   * @return string
   *   Title.
   */
  public function getPreviousTitle() {
    return t('< Previous');
  }

  /**
   * Returns next title.
   *
   * @return string
   *   Title.
   */
  public function getNextTitle() {
    return t('Next >');
  }

  /**
   * Returns form rendable array by ID.
   *
   * @param string $form_id
   *   Form ID.
   *
   * @return array
   *   Form array.
   */
  protected function getForm($form_id) {
    $topics = $this->getTopics();
    $topic_id = count($topics) == 1 ? $topics[0]->tid : NULL;
    $result_topics = $form_id == 'nexteuropa_newsroom_agenda_filter_form' ? $this->getResultTopicsId() : NULL;
    return drupal_get_form($form_id, $this->getTypeId(), $topic_id, $this->getCurrentDate()
      ->format(NexteuropaNewsroomAgenda::DATE_FORMAT), $result_topics);
  }

  /**
   * Returns the agenda html.
   *
   * @return string
   *   HTML.
   */
  public function getAgenda() {
    drupal_set_title($this->generateTitle());
    $this->prepareAgenda();

    return theme('newsroom_agenda_page', [
      'is_today' => $this->getCurrentDate() == $this->getRealDate(),
      'items' => $this->getCurrentItems(),
      'next_event_items' => $this->getUpcomingItems(),
      'past_event_items' => $this->getPastItems(),
      'is_block' => $this->getIsBlock(),
      'previous_link' => !empty($this->getPreviousDate()) ? $this->getNavigationLink($this->getPreviousTitle(), $this->getPreviousDate()) : NULL,
      'next_link' => !empty($this->getUpcomingDate()) ? $this->getNavigationLink($this->getNextTitle(), $this->getUpcomingDate()) : NULL,
    ]);
  }

  /**
   * Prepares agenda items for presenation.
   *
   * @param array $grouped_items
   *   Agenda items.
   * @param string $agenda_type
   *   Agenda type : current, upcoming, past.
   *
   * @return string
   *   Output string.
   */
  protected function prepareItemsOutput(array $grouped_items, $agenda_type) {
    $output = [];
    $output['visible_items'] = NULL;
    $grouped_output = NULL;
    if (!empty($grouped_items)) {
      foreach ($grouped_items as $title => $items) {
        $item_output = [];
        foreach ($items as $item) {
          $item_output[] = [
            'output' => theme('newsroom_agenda_item', [
              'date' => theme('newsroom_agenda_date', [
                'weekDay' => $this->getFormattedDatePartBy($item->start_date_obj, $item->end_date_obj, 'D'),
                'day' => $this->getFormattedDatePartBy($item->start_date_obj, $item->end_date_obj, 'd'),
                'month' => $this->getFormattedDatePartBy($item->start_date_obj, $item->end_date_obj, 'M'),
                'year' => $this->getFormattedDatePartBy($item->start_date_obj, $item->end_date_obj, 'Y'),
                'isPast' => $item->isPast,
              ]),
              'item' => $item,
            ]),
            'visible' => $item->visible,
          ];

        }
        $grouped_output = theme('newsroom_agenda_content_items',
          [
            'item_type' => $title,
            'items' => $item_output,
            'agenda_block' => $agenda_type,
          ]);

        $output['visible_items'] .= $grouped_output;
      }
    }
    return $output;
  }

  /**
   * Returns formatted date part.
   *
   * @param object $start_date
   *   Start date.
   * @param object $end_date
   *   End date.
   * @param string $format
   *   End date.
   *
   * @return string
   *   Formatted date part string.
   */
  protected function getFormattedDatePartBy($start_date, $end_date, $format) {
    $formatted_date_part = NULL;
    $isSameDates = $start_date->format('Y-m-d') === $end_date->format('Y-m-d');
    $isSameMonth = $start_date->format('m') === $end_date->format('m') && $format == 'M';
    $isSameYear = $start_date->format('Y') === $end_date->format('Y') && $format == 'Y';
    $isSingleFormat = $isSameDates || $isSameMonth || $isSameYear;

    if ($isSingleFormat) {
      $formatted_date_part = $start_date->format($format);
    }
    else {
      $formatted_date_part = $start_date->format($format) . '-' . $end_date->format($format);
    }
    return $formatted_date_part;
  }

  /**
   * Generates content for Agenda block.
   *
   * @return string
   *   Content of the agenda block.
   */
  public function getBlockAgenda() {
    $cache_key = 'get_agenda:block:' . $this->getUniqueCachePart();
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $content = $cache->data;
    }
    else {
      $this->prepareAgenda();
      $items = $this->getCurrentItems();
      $next_items = $this->getUpcomingItems();
      $content = NULL;
      if (!empty($items) || !empty($next_items)) {
        $content = theme('newsroom_agenda_page', [
          'filter_form' => NULL,
          'date_form' => NULL,
          'items' => $items,
          'next_event_items' => $next_items,
          'is_block' => $this->getIsBlock(),
          'navigation' => [],
        ]);
      }
      cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_agenda_block', 180));
    }
    return $content;
  }

  /**
   * Gets the unique part for cache value.
   *
   * @return string
   *   Cache key unique value.
   */
  protected function getUniqueCachePart() {
    return md5($this->getCurrentDate()
      ->format(NexteuropaNewsroomAgenda::DATE_FORMAT) . $this->getTypeId() . implode('', $this->getTopicsId()));
  }

  /**
   * Returns the base query for agenda presentation.
   */
  public function getBaseQuery() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', ['nid', 'title', 'created']);
    $query->fields('tt', ['name', 'weight']);
    $query->addField('tt', 'tid', 'type_id');
    $query->addField('type_order', 'field_newsroom_order_value', 'type_order');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');
    $query->addField('v', 'field_newsroom_item_venue_value', 'venue');
    $query->join('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_venue', 'v', 'v.entity_id = n.nid');
    $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
    $query->leftJoin('field_data_field_newsroom_order', 'type_order', 'type_order.entity_id = tt.tid');
    $query->leftJoin('field_data_field_newsroom_newsletter_only', 'newsletter_item', 'newsletter_item.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
    $query->condition('n.status', 1);

    $db_or = db_or();
    $db_or->condition('newsletter_item.field_newsroom_newsletter_only_value', 1, '<>');
    $db_or->isNull('newsletter_item.field_newsroom_newsletter_only_value');

    $query->condition($db_or);
    $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $query->condition('tf.field_newsroom_item_type_tid', NexteuropaNewsroomVocabularyHelper::getEventsTermsIds());

    if ($this->getTypeId()) {
      $query->condition('tt.tid', NexteuropaNewsroomVocabularyHelper::getTypeChildren($this->getTypeId()));
    }

    $query->orderBy('type_order');
    $query->orderBy('start_date', 'DESC');
    $query->orderBy('end_date', 'DESC');
    $query->orderBy('type_id', 'ASC');
    $query->addTag('node_access');

    $this->setQuery($this->processQuery($query));
  }

  /**
   * Processes query before execution.
   *
   * @param object $query
   *   Query object.
   *
   * @return object
   *   Query object.
   */
  protected function processQuery($query) {
    if (!empty($this->getTopics())) {
      $query->condition('topic_data.tid', $this->getTopicsId());
    }
    return $query;
  }

  /**
   * Creates agenda items based on blocks and specific date criteria.
   *
   * @param string $blockName
   *   Block name.
   *
   * @return array
   *   Array of items.
   */
  protected function createAgendaItemsFor($blockName) {
    // Filter in the present by default.
    $isShowCurrentBlock = TRUE;
    $isShowUpcomingBlock = TRUE;
    $isShowPastBlock = TRUE;
    $current_date = $this->getCurrentDate();
    $upcoming_date_start = clone $current_date;
    $upcoming_date_start = clone $upcoming_date_start->modify('+1 day');
    $past_date_start = clone $current_date;
    $past_date_start = $past_date_start->modify('-1 day');

    $real_current_date = $this->getRealDate();

    // Filter in the future.
    if ($in_future = $current_date > $real_current_date) {
      $upcoming_date_start = $current_date;
      $isShowPastBlock = FALSE;
      $isShowCurrentBlock = FALSE;
    }

    // Filter in the past.
    if ($in_past = $current_date < $real_current_date) {
      $past_date_start = $current_date;
      $isShowUpcomingBlock = FALSE;
      $isShowCurrentBlock = FALSE;
    }

    $query_results = $this->getResult();
    $items_by_types = $this->getDistinctItemTypesArray($query_results);
    $total = 30;
    $show_items_total = variable_get('nexteuropa_newsroom_agenda_list_items', 5);

    if (NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING == $blockName) {
      // We need to sort the items in ascending order for Upcoming events.
      usort($query_results, array($this, "sortByDate"));
    }

    foreach ($query_results as $item) {
      $temp_item = NULL;
      // Reduce the page loading time by breaking/continuing for each item type.
      if (count($items_by_types[$item->name]) >= $total) {
        continue;
      }
      switch ($blockName) {
        case NexteuropaNewsroomAgenda::AGENDA_TYPE_CURRENT:
          if ($isShowCurrentBlock && $item->start_date_obj->format('Ymd') <= $current_date->format('Ymd') &&
            $item->end_date_obj->format('Ymd') >= $current_date->format('Ymd')
          ) {
            $temp_item = $this->getCacheAgendaItem($item);
          }
          break;

        case NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING:
          // If filter set to current date.
          $condition_future = $item->start_date_obj->format('Ymd') >= $upcoming_date_start->format('Ymd');
          // If filter set to future date.
          if ($in_future) {
            $condition_future = ($item->start_date_obj->format('Ymd') >= $upcoming_date_start->format('Ymd') &&
              $item->end_date_obj->format('Ymd') >= $upcoming_date_start->format('Ymd'));
          }
          if ($isShowUpcomingBlock && $condition_future) {
            $temp_item = $this->getCacheAgendaItem($item);
          }
          break;

        case NexteuropaNewsroomAgenda::AGENDA_TYPE_PAST:
          // If filter set to current date.
          $condition_past = $item->end_date_obj->format('Ymd') <= $past_date_start->format('Ymd');
          // If filter set to past date.
          if ($in_past) {
            $condition_past = ($item->start_date_obj->format('Ymd') <= $past_date_start->format('Ymd') ||
              $item->end_date_obj->format('Ymd') <= $past_date_start->format('Ymd'));
          }
          if ($isShowPastBlock && $condition_past) {
            $item->isPast = TRUE;
            $temp_item = $this->getCacheAgendaItem($item);
          }
          break;
      }

      if ($temp_item) {
        $temp_item->visible = count($items_by_types[$temp_item->name]) < $show_items_total;
        // No more than $total number of items per item type (for hiding).
        if (count($items_by_types[$temp_item->name]) < $total) {
          $items_by_types[$temp_item->name][] = $temp_item;
        }
      }
    }

    return $items_by_types;
  }

  /**
   * Gets an array of distinct item types.
   *
   * @param array $items
   *   Array of newsroom items.
   *
   * @return array
   *   Array of types filled with items.
   */
  protected function getDistinctItemTypesArray(array $items) {
    $type_id = 0;
    $types_array = [];
    foreach ($items as $item) {
      if ($type_id != $item->type_id) {
        $type_id = $item->type_id;
        $types_array[$item->name] = [];
      }
    }
    return $types_array;
  }

  /**
   * Adds additional info and caches agenda item.
   *
   * @param object $item
   *   Current data object.
   *
   * @return object
   *   Agenda item.
   */
  protected function getCacheAgendaItem(&$item) {
    $agenda_item = NULL;
    $cache_key = 'get_agenda:create_agenda:' . $this->getUniqueCachePart() . $item->nid;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $agenda_item = $cache->data;
    }
    else {
      $node = node_load($item->nid);
      $item->title = $node->title;
      $item->related_items = NexteuropaNewsroomRelatedItemHelper::getRelatedItems($item->nid);
      $item->url = NexteuropaNewsroomHelper::getNodeMainUrl($node);
      $item->prepared_start_date = $item->start_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
      $item->prepared_end_date = $item->end_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
      $agenda_item = $item;
      cache_set($cache_key, $item, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_agenda_build', 3600));
    }
    return $agenda_item;
  }

  /**
   * Converts string to date object and fills empty dates.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return array
   *   Prepared agenda items.
   */
  protected function prepareDateObjects(array $items) {
    if (!empty($items)) {
      foreach ($items as $key => $item) {
        $items[$key]->new = NexteuropaNewsroomHelper::isNewItem($item->created, $item->nid);
        $items[$key]->isPast = FALSE;
        $items[$key]->visible = TRUE;
        $start_date = new DateTime();
        $start_date->setTimestamp($item->start_date);
        $start_date->setTime(0, 0, 0);
        $items[$key]->start_date_obj = $start_date;

        // If the end date is empty, it means it is one day event and we set the
        // end date to start date.
        $end_date = clone $start_date;
        if (!empty($item->end_date)) {
          $end_date->setTimestamp($item->end_date);
        }
        $items[$key]->end_date_obj = $end_date;
      }
    }
    return $items;
  }

  /**
   * Returns navigation link based on URL.
   *
   * @param string $title
   *   Link title.
   * @param object $date
   *   Datetime object.
   *
   * @return string|null
   *   HTML link.
   */
  protected function getNavigationLink($title, $date) {
    return $date ? l($title, $this->getNavigationUrl($date), [
      'attributes' => ['class' => ['btn btn-default']],
    ]) : NULL;
  }

  /**
   * Returns agenda navigation URL.
   *
   * @param object $date
   *   Datetime object.
   *
   * @return string
   *   URL string.
   */
  public function getNavigationUrl($date) {
    $this->urlParts = [];
    $this->addUrlPart($this->getTypeUrl());
    $this->addUrlPart($this->getTopicUrl());
    $this->setUrlItems($date);
    return 'newsroom-agenda/' . implode('/', $this->getUrlParts());
  }

  /**
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of topic IDs.
   */
  protected function getTopicsId() {
    $topic_ids = [];
    if (!empty($this->getTopics())) {
      foreach ($this->getTopics() as $topic) {
        $topic_ids[] = $topic->tid;
      }
    }
    return $topic_ids;
  }

  /**
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  protected function getResultTopicsId() {
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

  /**
   * Get real date.
   */
  protected function getRealDate() {
    $real_date = new DateTime();
    $real_date->setTime(0, 0, 0);
    return $real_date;
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $this->findCurrentItems();
    $this->findUpcomingItems();
    $this->findPastItems();
  }

  /**
   * Adds date url parts.
   *
   * @param object $date
   *   The current date.
   */
  protected function setUrlItems($date) {
    if ($date) {
      $this->addUrlPart($date->format('j'));
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

  /**
   * Finds and sets current items.
   */
  protected function findCurrentItems() {
    $current_items = NULL;
    $current_items = $this->createAgendaItemsFor(NexteuropaNewsroomAgenda::AGENDA_TYPE_CURRENT);
    $this->setCurrentItems($current_items);
  }

  /**
   * Finds and sets upcoming items.
   */
  protected function findUpcomingItems() {
    $upcoming_items = NULL;
    $upcoming_items = $this->createAgendaItemsFor(NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING);
    $this->setUpcomingItems($upcoming_items);
  }

  /**
   * Finds and sets past items.
   */
  protected function findPastItems() {
    $past_items = NULL;
    $past_items = $this->createAgendaItemsFor(NexteuropaNewsroomAgenda::AGENDA_TYPE_PAST);
    $this->setPastItems($past_items);
  }

  /**
   * Groups agenda items by item type.
   *
   * @param array $grouped_items
   *   Array of grouped agenda items.
   *
   * @return bool
   *   flag to determine if we need to add more button.
   */
  protected function checkItemsToAddMoreButton(array $grouped_items) {
    foreach ($grouped_items as $items) {
      foreach ($items as $item) {
        if (!$item->visible) {
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    return $this->getQuery()->execute()->fetchAll();
  }

  /**
   * Gets utmost date.
   *
   * @param bool $first
   *   Return the first or last utmost date in the result.
   *
   * @return object
   *   Utmost date.
   */
  protected function getUtmostDate($first = TRUE) {
    $utmost_date = NULL;
    if ($result = $this->getResult()) {
      if ($first) {
        $utmost_item = array_pop($result);
        $utmost_date = clone $utmost_item->start_date_obj;
      }
      else {
        $utmost_item = reset($result);
        $utmost_date = clone $utmost_item->end_date_obj;
      }
    }
    return $utmost_date;
  }

  /**
   * Generates title based on incoming parameters.
   *
   * @return null|string
   *   Page title.
   */
  protected function generateTitle() {
    $page_title = t('Agenda');
    if ($this->getTypeName()) {
      $page_title = $this->getTypeName();
    }
    if ($this->getTopicName()) {
      $page_title .= ' ' . t('about !topic_title', ['!topic_title' => $this->getTopicName()]);
    }
    return $page_title;
  }

  /**
   * Sorts objects by start_date_obj.
   *
   * @param object $item1
   *   First object to compare.
   * @param object $item2
   *   Second object to compare.
   *
   * @return bool
   *   Flag for sorting.
   */
  protected function sortByDate($item1, $item2) {
    return $item1->start_date_obj > $item2->start_date_obj;
  }

}
