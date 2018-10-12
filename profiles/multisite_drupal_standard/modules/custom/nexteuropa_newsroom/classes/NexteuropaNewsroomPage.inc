<?php

/**
 * @file
 * Code for the NexteuropaNewsroomPage class.
 */

/**
 * NexteuropaNewsroomPage class.
 */
class NexteuropaNewsroomPage {

  const DATE_FORMAT = 'd/m/Y';
  const MYSQL_DATE_FORMAT = 'd-m-Y';

  protected $type = NULL;
  protected $topic = NULL;
  protected $startDate = NULL;
  protected $endDate = NULL;

  /**
   * NexteuropaNewsroomPage constructor.
   *
   * @param object|null $type
   *   Newsroom type.
   * @param object|null $topic
   *   Newsroom topic.
   * @param Datetime|null $start_date
   *   Start date.
   * @param Datetime|null $end_date
   *   End date.
   */
  public function __construct($type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL) {
    $this->setTopic($topic);
    $this->setType($type);
    $this->setStartDate($start_date);
    $this->setEndDate($end_date);
  }

  /**
   * Gets minimal items number per agenda page.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return variable_get('nexteuropa_newsroom_page_items_number', 10);
  }

  /**
   * Gets term URL.
   *
   * @param string $value
   *   URL part.
   *
   * @return string
   *   Term url part.
   */
  public function getTermUrl($value) {
    return !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Sets type.
   *
   * @param object|null $value
   *   Type object.
   */
  public function setType($value) {
    $this->type = $value;
  }

  /**
   * Gets type.
   *
   * @return object|null
   *   Type object.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Sets start date.
   *
   * @param DateTime|null $value
   *   Start date.
   */
  public function setStartDate($value) {
    $this->startDate = $value;
  }

  /**
   * Gets start date.
   *
   * @return DateTime|null
   *   Start date.
   */
  public function getStartDate() {
    return $this->startDate;
  }

  /**
   * Sets end date.
   *
   * @param DateTime|null $value
   *   End date.
   */
  public function setEndDate($value) {
    if (!empty($value)) {
      // Include the whole day.
      $value->setTime(23, 59, 59);
    }
    $this->endDate = $value;
  }

  /**
   * Gets end date.
   *
   * @return DateTime|null
   *   End date.
   */
  public function getEndDate() {
    return $this->endDate;
  }

  /**
   * Sets topic.
   *
   * @param object|null $value
   *   Topic object.
   */
  public function setTopic($value) {
    $this->topic = $value;
  }

  /**
   * Gets topic.
   *
   * @return object|null
   *   Topic object.
   */
  public function getTopic() {
    return $this->topic;
  }

  /**
   * Gets image formatted output.
   *
   * @param object $node
   *   Node.
   * @param string $field_name
   *   Field name.
   * @param string $style_name
   *   Style name.
   *
   * @return null|string
   *   Image HTML presentation.
   */
  protected function getNodeImage($node, $field_name, $style_name = 'newsroom_style') {
    $image = NULL;
    if ($style_name == 'newsroom_style') {
      $display = [
        'type' => 'newsroom_zoomable_image',
        'settings' => _nexteuropa_newsroom_zoomable_formatter_settings('newsroom_style'),
      ];
    }
    else {
      $display = [
        'type' => 'image',
        'settings' => [
          'image_style' => 'newsroom_style',
          'image_link' => 'content',
        ],
      ];
    }

    $field_image = field_view_field('node', $node, $field_name, $display);
    if ($field_image) {
      $field_image['#label_display'] = 'hidden';
      $image = drupal_render($field_image);
    }

    return $image;
  }

  /**
   * Creates formated date string.
   *
   * @param string $timestamp
   *   Timestamp.
   *
   * @return string
   *   Formated string.
   */
  protected function getFormatedDateFromTimestamp($timestamp) {
    return $timestamp ? NexteuropaNewsroomHelper::getFormatedDate(NexteuropaNewsroomPage::DATE_FORMAT, $timestamp) : NULL;
  }

  /**
   * Gets data from DB.
   */
  protected function getData() {

    $key_hash_part = $this->getUniqueCachePart();
    $cache_key = 'page_result:' . $key_hash_part;
    $cache_total_number_key = 'page_total_number:' . $key_hash_part;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      // For cached result, we set manually params for pager.
      if ($total_number_cache = cache_get($cache_total_number_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
        pager_default_initialize($total_number_cache->data, $this->getItemsNumber());
      }
      $data = $cache->data;
    }
    else {
      $query = $this->getQueryObject();
      cache_set($cache_total_number_key, $query->extend('PagerDefault')->getCountQuery()->execute()->fetchField(), NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_page_result', 300));
      $items = $query->extend('PagerDefault')->limit($this->getItemsNumber())->execute()->fetchAll();
      $data = [];
      if ($items) {
        foreach ($items as $item) {
          $node = node_load($item->nid);
          $node->related_items = NexteuropaNewsroomRelatedItemHelper::getRelatedItems($item->nid);
          $data[$item->nid] = $node;
        }
      }

      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_page_result', 300));
    }

    return $data;
  }

  /**
   * Returns the newsroom page html.
   *
   * @return string
   *   HTML.
   */
  public function getContent() {
    drupal_set_title($this->generateTitle());
    $content = theme('newsroom_page', [
      'featured_item' => $this->getTypeFeaturedItem(),
      'items' => $this->generateItems('newsroom_page_item'),
    ]);
    $content .= theme('pager');
    return $content;
  }

  /**
   * Returns the newsroom page html.
   *
   * @return string
   *   HTML.
   */
  public function getRssContent() {
    $namespaces = [];
    if (function_exists('rdf_get_namespaces')) {
      // Merge RDF namespaces in the XML namespaces in case they are used
      // further in the RSS content.
      $xml_rdf_namespaces = [];
      foreach (rdf_get_namespaces() as $prefix => $uri) {
        $xml_rdf_namespaces['xmlns:' . $prefix] = $uri;
      }
      $namespaces += $xml_rdf_namespaces;
    }

    $content = theme('newsroom_page_rss', [
      'title' => $this->generateTitle(),
      'link' => url($this->getNavigationUrl(TRUE), ['absolute' => TRUE]),
      'namespaces' => drupal_attributes($namespaces),
      'description' => NULL,
      'items' => $this->generateItems('newsroom_page_rss_item'),
    ]);
    return $content;
  }

  /**
   * Generates title based on incoming parameters.
   *
   * @return null|string
   *   Page title.
   */
  protected function generateTitle() {
    $page_title = t('Newsroom');
    if ($this->getType()) {
      $page_title = $this->getType()->name;
    }
    if ($this->getTopic()) {
      $page_title .= ' ' . t('about !topic_title', ['!topic_title' => $this->getTopic()->name]);
    }
    return $page_title;
  }

  /**
   * Prepares page items for presenation.
   *
   * @param string $template_name
   *   Template name.
   *
   * @return string
   *   Output string.
   */
  protected function generateItems($template_name) {
    return theme($template_name, ['items' => $this->getData()]);
  }

  /**
   * Gets the unique part for cache value.
   *
   * @return string
   *   Cache key unique value.
   */
  protected function getUniqueCachePart() {
    $type_id = $this->getType() ? $this->getType()->tid : NULL;
    $topic_id = $this->getTopic() ? $this->getTopic()->tid : NULL;
    $start_date = $this->getStartDate() ? $this->getStartDate()->getTimestamp() : NULL;
    $end_date = $this->getEndDate() ? $this->getEndDate()->getTimestamp() : NULL;
    $page = !empty($_GET['page']) ? $_GET['page'] : NULL;

    return md5($type_id . $topic_id . $start_date . $end_date . $page);
  }

  /**
   * Gets query object.
   */
  public function getQueryObject() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', ['nid', 'created']);
    $query->addField('type_field', 'field_newsroom_item_type_tid', 'type_tid');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');

    $query->leftJoin('field_data_field_newsroom_item_type', 'type_field', 'type_field.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_newsletter_only', 'newsletter_item', 'newsletter_item.entity_id = n.nid');

    $query->condition('n.status', 1);
    $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);

    $db_or = db_or();
    $db_or->condition('newsletter_item.field_newsroom_newsletter_only_value', 1, '<>');
    $db_or->isNull('newsletter_item.field_newsroom_newsletter_only_value');

    $query->condition($db_or);

    $query->orderBy('start_date', 'DESC');
    $query->orderBy('end_date', 'DESC');

    if ($this->getType()) {
      $query->condition('type_field.field_newsroom_item_type_tid', NexteuropaNewsroomVocabularyHelper::getTypeChildren($this->getType()->tid));
    }

    if ($this->getTopic()) {
      $query->condition('topic_field.field_newsroom_topics_tid', $this->getTopic()->tid);
    }

    if ($this->getStartDate()) {
      $query->condition('d.field_newsroom_item_date_value', $this->getStartDate()->getTimestamp(), '>=');
    }

    if ($this->getEndDate()) {
      $db_or = db_or();

      $db_and = db_and();
      $db_and->isNotNull('d.field_newsroom_item_date_value2');
      $db_and->condition('d.field_newsroom_item_date_value2', $this->getEndDate()->getTimestamp(), '<=');
      $db_or->condition($db_and);

      $db_and = db_and();
      $db_and->isNull('d.field_newsroom_item_date_value2');
      $db_and->condition('d.field_newsroom_item_date_value', $this->getEndDate()->getTimestamp(), '<=');
      $db_or->condition($db_and);
      $query->condition($db_or);
    }

    $query->addTag('node_access');
    return $query;
  }

  /**
   * Returns navigation link based on URL.
   *
   * @param bool $is_rss
   *   Is url for RSS feed or not.
   *
   * @return string|null
   *   HTML link.
   */
  public function getNavigationUrl($is_rss = FALSE) {
    $url_parts = [];
    $url_parts[] = $this->getTermUrl($this->getType() ? $this->getType()->name : NULL);
    $url_parts[] = $this->getTermUrl($this->getTopic() ? $this->getTopic()->name : NULL);
    $url_parts[] = $this->getStartDate() ? $this->getStartDate()->format(NexteuropaNewsroomPage::MYSQL_DATE_FORMAT) : NEXTEUROPA_NEWSROOM_ALL;
    $url_parts[] = $this->getEndDate() ? $this->getEndDate()->format(NexteuropaNewsroomPage::MYSQL_DATE_FORMAT) : NEXTEUROPA_NEWSROOM_ALL;

    return $is_rss ? NexteuropaNewsroomHelper::getRssUrl($url_parts) : NexteuropaNewsroomHelper::getPageUrl($url_parts);
  }

  /**
   * Gets type featured item.
   *
   * @return null|string
   *   Featured item content.
   */
  protected function getTypeFeaturedItem() {
    $content = NULL;
    $featured_item_id = NexteuropaNewsroomHelper::getFieldValue($this->getType(), 'field_newsroom_featured_item', 'target_id');
    if (empty($featured_item_id)) {
      // If featured item is not set we try to take from feature newsroom type.
      if ($featured_type = NexteuropaNewsroomVocabularyHelper::getNewsroomType(variable_get('nexteuropa_newsroom_featured_type'))) {
        $featured_item_id = NexteuropaNewsroomHelper::getFieldValue($featured_type, 'field_newsroom_featured_item', 'target_id');
      }
    }

    if ($featured_item_id) {
      $cache_key = 'type_featured_item:' . $this->getType()->tid;

      if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
        $content = $cache->data;
      }
      else {

        if ($featured_node = node_load($featured_item_id)) {

          $type = NexteuropaNewsroomVocabularyHelper::getNewsroomType(NexteuropaNewsroomHelper::getFieldValue($featured_node, 'field_newsroom_item_type', 'tid'));

          $image_style = 'large';
          $image = $this->getNodeImage($featured_node, 'field_newsroom_illustrative_img', $image_style);
          if (empty($image)) {
            $image = $this->getNodeImage($featured_node, 'field_newsroom_private_img', $image_style);
          }

          $topic_url = $this->getTermUrl($this->getTopic() ? $this->getTopic()->name : NULL);

          $content = theme('newsroom_page_featured_item', [
            'type' => $type ? l($type->name, NexteuropaNewsroomHelper::getPageUrl([$this->getTermUrl($type->name), $topic_url])) : NULL,
            'title' => l($featured_node->title, 'node/' . $featured_node->nid),
            'image' => $image,
            'created' => NexteuropaNewsroomHelper::getFormatedDate(NexteuropaNewsroomPage::DATE_FORMAT, $featured_node->created),
            'teaser' => NexteuropaNewsroomHelper::getFieldTranslatedValue($featured_node, 'field_newsroom_teaser'),
          ]);
        }

        cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_type_featured_item', 300));

      }
    }

    return $content;
  }

}
