<?php

/**
 * @file
 * Nexteuropa Newsroom blocks hooks and helpers.
 */

/**
 * Implements hook_block_info().
 */
function nexteuropa_newsroom_block_info() {
  $blocks = [];
  $blocks['newsroom_summary_blocks'] = [
    'info' => t('Newsroom summary blocks'),
    'cache' => DRUPAL_CACHE_CUSTOM,
  ];
  $blocks['newsroom_related_content'] = [
    'info' => t('Newsroom related Content'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  ];
  $blocks['newsroom_admin_tools'] = [
    'info' => t('Newsroom administration buttons'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  $blocks['newsroom_newsletter_subscription'] = [
    'info' => t('Newsroom newsletter subscription'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  $blocks['newsroom_proposal'] = [
    'info' => t('Newsroom items proposal'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  ];
  $blocks['newsroom_agenda_block'] = [
    'info' => t('Newsroom agenda block'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  $blocks['newsroom_share_block'] = [
    'info' => t('Newsroom share block'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  $blocks['newsroom_page_search_block'] = [
    'info' => t('Newsroom page search block'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  $blocks['newsroom_agenda_search_block'] = [
    'info' => t('Newsroom agenda search block'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  ];
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function nexteuropa_newsroom_block_view($delta = '') {
  switch ($delta) {
    case 'newsroom_summary_blocks':
      $block['subject'] = l(t('Newsroom'), NexteuropaNewsroomHelper::getPageUrl([NEXTEUROPA_NEWSROOM_ALL]));
      $block['content'] = _nexteuropa_newsroom_get_summary_blocks();
      break;

    case 'newsroom_related_content':
      $block['subject'] = t('Related content');
      $block['content'] = _nexteuropa_newsroom_related_content();
      break;

    case 'newsroom_admin_tools':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_tools();
      break;

    case 'newsroom_newsletter_subscription':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_newsletter_subscription();
      break;

    case 'newsroom_proposal':
      $block['subject'] = t('Newsroom item proposal');
      $block['content'] = _nexteuropa_newsroom_block_news_proposal();
      break;

    case 'newsroom_agenda_block':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_agenda_block();
      break;

    case 'newsroom_share_block':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_share_block();
      break;

    case 'newsroom_page_search_block':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_page_search_block();
      break;

    case 'newsroom_agenda_search_block':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_agenda_search_block();
      break;
  }
  return $block;
}

/**
 * Gets agenda search block.
 *
 * @return string
 *   Form content.
 */
function _nexteuropa_newsroom_agenda_search_block() {
  $type = NexteuropaNewsroomBuilder::getType(arg(1, drupal_get_path_alias()));
  $topic = NexteuropaNewsroomBuilder::getTopic(arg(2, drupal_get_path_alias()));
  $day = NexteuropaNewsroomBuilder::getDay(arg(3, drupal_get_path_alias()));
  $month = NexteuropaNewsroomBuilder::getMonth(arg(4, drupal_get_path_alias()));
  $year = NexteuropaNewsroomBuilder::getYear(arg(5, drupal_get_path_alias()));
  $current_date = new DateTime();
  $current_date->setDate($year, $month, $day);

  return drupal_get_form(
    'nexteuropa_newsroom_agenda_filter_form',
    $type ? $type->tid : NULL,
    $topic ? $topic->tid : NULL,
    $current_date->format(NexteuropaNewsroomAgenda::DATE_FORMAT),
    NexteuropaNewsroomHelper::getResultTopicsId()
  );
}

/**
 * Gets page search block.
 *
 * @return string
 *   Form content.
 */
function _nexteuropa_newsroom_page_search_block() {
  $type = NexteuropaNewsroomBuilder::getType(arg(1, drupal_get_path_alias()));
  $topic = NexteuropaNewsroomBuilder::getTopic(arg(2, drupal_get_path_alias()));
  $start_date = NexteuropaNewsroomBuilder::getDate(arg(3, drupal_get_path_alias()));
  $end_date = NexteuropaNewsroomBuilder::getDate(arg(4, drupal_get_path_alias()));
  $filter_form = drupal_get_form('nexteuropa_newsroom_page_filter_form', $type, $topic, $start_date, $end_date);
  return drupal_render($filter_form);
}

/**
 * Gets newsroom agenda block content.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_agenda_block() {
  $content = '';
  if ($type = _nexteuropa_newsroom_get_type_from_agenda_block_context()) {
    $agenda_block = new NexteuropaNewsroomBlockAgenda($type, [], NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR);
    $content = $agenda_block->generateContent();
  }

  return $content;

}

/**
 * Gets newsroom share block content.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_share_block() {
  drupal_add_js('//europa.eu/webtools/load.js', 'file');
  $output = '<div class="social-media-links--webtool-horizontal">';
  $output .= '<span class="social-media-links__label">' . t('Share this page') . '</span>';
  $output .= '<div class="shareThis hideWhenSmall">';
  $output .= '<script type="application/json">{';
  $output .= '"service": "sbkm",';
  $output .= '"popup": false,';
  $output .= '"counter": false,';
  $output .= '"to": ["facebook","twitter","googleplus","linkedin","e-mail","more"]';
  $output .= '}</script></div>';
  $output .= '</div>';
  return $output;
}

/**
 * Detects type in agenda block context.
 *
 * @return object
 *   Taxonomy term.
 */
function _nexteuropa_newsroom_get_type_from_agenda_block_context() {
  $type = NULL;
  $active_contexts = context_active_contexts();
  foreach ($active_contexts as $active_context) {
    if (is_array($active_context->reactions) && count($active_context->reactions) > 0) {
      foreach ($active_context->reactions as $reaction_type => $current_reaction) {
        if ($reaction_type == 'newsroom_agenda_block') {
          if (!empty($current_reaction['type_id'])) {
            $type = NexteuropaNewsroomVocabularyHelper::getNewsroomType($current_reaction['type_id']);
          }
        }
      }
    }
  }
  return $type;
}

/**
 * Gets summary of the blocks.
 *
 * @return string
 *   Summary block content.
 */
function _nexteuropa_newsroom_get_summary_blocks() {
  $summary_block = new NexteuropaNewsroomSummaryBlock();
  return $summary_block->generateContent();
}

/**
 * Gets related content tree.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_related_content() {
  $content = '';
  if ($node = menu_get_object()) {
    $children_related_items = _nexteuropa_newsroom_get_related_content('field_newsroom_related_content', $node);
    $parent_related_items = _nexteuropa_newsroom_get_related_content('field_newsroom_parent_content', $node);
    $brother_items = [];
    $parent_item = NULL;
    if (count($parent_related_items) > 0) {
      $parent_item = $parent_related_items[0];
      $brother_items = _nexteuropa_newsroom_get_related_children('field_newsroom_parent_content', $parent_item->id, $node->nid);
    }

    if ($parent_item || count($brother_items) > 0 || count($children_related_items) > 0) {
      $content = theme('newsroom_related_content', [
        'parent_item' => $parent_item,
        'current_item' => $node,
        'brother_items' => $brother_items,
        'children_items' => $children_related_items,
      ]);
    }
  }
  return $content;
}

/**
 * Tries to resolve each taxonomy term with a corresponding ID to map.
 *
 * @param string $field_name
 *   The mapping field.
 * @param int $parent_nid
 *   The parent node id.
 * @param int $current_nid
 *   The curent node id.
 *
 * @return array
 *   Taxonomy ids.
 */
function _nexteuropa_newsroom_get_related_children($field_name, $parent_nid, $current_nid) {
  $items = [];
  if ($parent_nid) {
    $cache_key = 'node_relative_items';
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $items = $cache->data;
    }
    else {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->fieldCondition($field_name, 'target_id', $parent_nid)
        ->execute();
      $result = $query->execute();
      if (!empty($result['node'])) {
        // Exclude the current item ID from array.
        $ids = array_diff(array_keys($result['node']), [$current_nid]);
        $items = _nexteuropa_newsroom_prepare_related_content_array($ids);
      }
      cache_set($cache_key, $items, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('nexteuropa_newsroom_ct_node_relative_items', 86400));
    }
  }

  return $items;
}

/**
 * Gets related content from node.
 *
 * @param string $field_name
 *   Field name.
 * @param object $node
 *   Current node.
 *
 * @return array
 *   Related nodes.
 */
function _nexteuropa_newsroom_get_related_content($field_name, $node) {
  $items = [];
  $node_ids = NexteuropaNewsroomHelper::getFieldValue($node, $field_name, 'target_id');
  if ($node_ids) {
    $node_ids = is_array($node_ids) ? $node_ids : [$node_ids];
    $items = _nexteuropa_newsroom_prepare_related_content_array($node_ids);
  }
  return $items;
}

/**
 * Prepares related content array.
 *
 * @param array $ids
 *   Array of newsroom item ids.
 *
 * @return array
 *   Array of objects to display.
 */
function _nexteuropa_newsroom_prepare_related_content_array(array $ids) {
  $items = [];
  if (!empty($ids)) {
    foreach ($ids as $id) {
      $std = new stdClass();
      $std->id = $id;
      $std->title = NexteuropaNewsroomHelper::getNodeTitle($id);
      $items[] = $std;
    }
  }
  return $items;
}

/**
 * Returns buttons to manage newsroom items. Edit in newsroom, re-import etc.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_tools() {
  $content = '';
  $newsroom_item = menu_get_object();
  if ($newsroom_item->type == NEXTEUROPA_NEWSROOM_CONTENT_TYPE) {
    $newsroom_id_field = field_get_items('node', $newsroom_item, 'field_newsroom_item_id');
    $newsroom_id = $newsroom_id_field[0]['value'];
    $links = [];
    if (user_access(NEXTEUROPA_NEWSROOM_EDIT_ACCESS)) {
      $links['edit'] = [
        'text' => '<span class="glyphicon glyphicon-edit"></span> Edit item in the Newsroom',
        'path' => NexteuropaNewsroomHelper::getNewsroomUrl(variable_get('nexteuropa_newsroom_single_item_edit_segment', NEXTEUROPA_NEWSROOM_ITEM_EDIT_SEGMENT) . $newsroom_id),
        'options' => [
          'external' => TRUE,
          'html' => TRUE,
          'attributes' => ['class' => 'btn btn-success'],
        ],
      ];
    }
    if (user_access(NEXTEUROPA_NEWSROOM_IMPORT_ACCESS)) {
      $links['reimport'] = [
        'text' => '<span class="glyphicon glyphicon-refresh"></span> Re-import from the Newsroom',
        'path' => 'newsroom-import/item/' . $newsroom_id,
        'options' => [
          'html' => TRUE,
          'attributes' => ['class' => 'btn btn-danger'],
        ],
      ];
    }

    foreach ($links as $link) {
      $content .= '<div class="btn-group-sm btn-group">' . l($link['text'], $link['path'], $link['options']) . '</div>';
    }

    if (!empty($content)) {
      $content = '<div class="btn-toolbar">' . $content . '</div>';
    }
  }
  return $content;
}

/**
 * Newsletter subscription block.
 *
 * @return array
 *   Form array.
 */
function _nexteuropa_newsroom_newsletter_subscription() {
  $content = [];
  if ($view = views_get_view('newsletter_subscription')) {
    $view->set_display('block');
    $view->pre_execute();
    $view->execute();

    if (!empty($view->result)) {
      $service = array_shift($view->result);
      $content = drupal_get_form('nexteuropa_newsroom_newsletter_subscription_form', [
        'tid' => $service->field_field_newsroom_service_id[0]['raw']['safe_value'],
        'name' => $service->taxonomy_term_data_name,
      ]);
    }
  }
  return $content;
}

/**
 * Returns block with the link to newsroom proposal form.
 *
 * @return string
 *   Block content.
 */
function _nexteuropa_newsroom_block_news_proposal() {

  if (!user_access(NEXTEUROPA_NEWSROOM_PROPOSAL_ACCESS)) {
    return NULL;
  }

  $topic_id = NULL;
  $output = NULL;
  // Try to get Topic ID from the entity.
  if ($node = menu_get_object()) {
    // First try to get topic from the current node.
    if ($associated_topic_id = NexteuropaNewsroomHelper::getFieldValue($node, 'field_newsroom_associated_topic', 'tid')) {
      $topic_id = $associated_topic_id;
    }
    elseif ($group_id = NexteuropaNewsroomHelper::getFieldValue($node, 'og_group_ref', 'target_id')) {
      // Try get topic from Organic group, if it exists.
      $group_id = is_array($group_id) ? $group_id[0] : $group_id;
      $group = node_load($group_id);

      if ($group && $group_associated_topic_id = NexteuropaNewsroomHelper::getFieldValue($group, 'field_newsroom_associated_topic', 'tid')) {
        $topic_id = $group_associated_topic_id;
      }
    }
  }
  else {
    // Taxonomy term override.
    $taxonomy_term = NULL;
    $current_page_path = current_path();

    if (strpos($current_page_path, 'taxonomy/term') !== FALSE) {
      // Never sure what menu_callback will get you with.
      // A view overridding a taxo page.
      $url_tokens = explode('/', $current_page_path);
      if (!empty($url_tokens[2]) && is_numeric($url_tokens[2])) {
        $taxonomy_term = taxonomy_term_load($url_tokens[2]);
        // First try to get topic from the current taxonomy term.
        if ($taxonomy_term && $associated_topic_id = NexteuropaNewsroomHelper::getFieldValue($taxonomy_term, 'field_newsroom_associated_topic', 'tid')) {
          $topic_id = $associated_topic_id;
        }
      }
    }
  }

  if (!empty($topic_id)) {
    $output = '<div class="communityTools">';
    $output .= '<div class="RSSButton">' . l(t('Propose newsroom item'), '/news-proposal', ['query' => ['topic_id' => $topic_id]]) . '</div>';
    $output .= '</div>';
  }
  return $output;
}
