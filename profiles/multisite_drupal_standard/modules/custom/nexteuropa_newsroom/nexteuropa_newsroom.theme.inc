<?php

/**
 * @file
 * Theme hooks.
 */

/**
 * Implements hook_theme().
 */
function nexteuropa_newsroom_theme($existing, $type, $theme, $path) {
  $theme_path = $path . '/theme';
  return [
    'newsroom_services_page' => [
      'variables' => [
        'central_items' => NULL,
        'basic_items' => NULL,
        'privacy_statement' => NULL,
      ],
      'template' => 'newsroom-service-page',
      'path' => $theme_path,
    ],
    'newsroom_services_items' => [
      'variables' => [
        'items' => [],
        'css_class' => NULL,
        'title' => NULL,
        'universe_id' => NULL,
      ],
      'template' => 'newsroom-service-items',
      'path' => $theme_path,
    ],
    'newsroom_related_content' => [
      'variables' => [
        'parent_item' => NULL,
        'current_item' => NULL,
        'children_items' => [],
        'brother_items' => [],
      ],
      'template' => 'newsroom-related-content',
      'path' => $theme_path,
    ],
    'newsroom_zoomable_image' => [
      'variables' => [
        'image_output' => NULL,
        'path' => NULL,
        'image_style' => NULL,
        'title' => NULL,
        'copyright' => NULL,
        'caption' => NULL,
        'path_to_original' => NULL,
        'zoomable' => FALSE,
        'display_title' => FALSE,
      ],
      'template' => 'newsroom-zoomable-image',
      'path' => $theme_path,
    ],
    'newsroom_summary_block' => [
      'variables' => [
        'content' => NULL,
        'rss' => NULL,
      ],
      'template' => 'newsroom-summary-block',
      'path' => $theme_path,
    ],
    'newsroom_summary_block_wrapper' => [
      'variables' => [
        'items' => [],
        'title' => NULL,
        'classes' => [],
        'type_url' => NULL,
        'url' => NULL,
      ],
      'template' => 'newsroom-summary-block-wrapper',
      'path' => $theme_path,
    ],
    'newsroom_summary_block_item' => [
      'variables' => [
        'items' => [],
      ],
      'template' => 'newsroom-summary-block-item',
      'path' => $theme_path,
    ],
    'newsroom_agenda_page' => [
      'variables' => [
        'is_today' => TRUE,
        'filter_form' => NULL,
        'date_form' => NULL,
        'next_event_items' => [],
        'past_event_items' => [],
        'items' => [],
        'previous_link' => NULL,
        'next_link' => NULL,
        'is_block' => FALSE,
      ],
      'template' => 'newsroom-agenda-page',
      'path' => $theme_path,
    ],
    'newsroom_agenda_item' => [
      'variables' => [
        'date' => NULL,
        'item' => NULL,
      ],
      'template' => 'newsroom-agenda-item',
      'path' => $theme_path,
    ],
    'newsroom_agenda_content_items' => [
      'variables' => [
        'items' => [],
        'agenda_block' => NULL,
        'item_type' => NULL,
        'items_number_to_show_more_button' => 5,
      ],
      'template' => 'newsroom-agenda-content-items',
      'path' => $theme_path,
    ],
    'newsroom_agenda_date' => [
      'variables' => [
        'weekDay' => NULL,
        'day' => NULL,
        'month' => NULL,
        'year' => NULL,
        'isPast' => NULL,
      ],
      'template' => 'newsroom-agenda-date',
      'path' => $theme_path,
    ],
    'newsroom_page' => [
      'variables' => [
        'items' => NULL,
        'featured_item' => NULL,
      ],
      'template' => 'newsroom-page',
      'path' => $theme_path,
    ],
    'newsroom_page_item' => [
      'variables' => [
        'items' => NULL,
      ],
      'template' => 'newsroom-page-item',
      'path' => $theme_path,
    ],
    'newsroom_page_featured_item' => [
      'variables' => [
        'type' => NULL,
        'title' => NULL,
        'image' => NULL,
        'created' => NULL,
        'teaser' => NULL,
      ],
      'template' => 'newsroom-page-featured-item',
      'path' => $theme_path,
    ],
    'newsroom_page_rss' => [
      'variables' => [
        'title' => NULL,
        'namespaces' => NULL,
        'description' => NULL,
        'langcode' => NULL,
        'items' => NULL,
      ],
      'template' => 'newsroom-page-rss',
      'path' => $theme_path,
    ],
    'newsroom_page_rss_item' => [
      'variables' => [
        'title' => NULL,
        'link' => NULL,
        'description' => NULL,
        'url' => NULL,
      ],
      'template' => 'newsroom-page-rss-item',
      'path' => $theme_path,
    ],
    'newsroom_docsroom' => [
      'variables' => [
        'url' => NULL,
        'width' => 600,
        'height' => 200,
      ],
      'template' => 'newsroom-docsroom',
      'path' => $theme_path,
    ],
    'newsroom_events_related_items' => [
      'variables' => [
        'related_items' => NULL,
      ],
      'template' => 'newsroom-events-related-items',
      'path' => $theme_path,
    ],
  ];
}
