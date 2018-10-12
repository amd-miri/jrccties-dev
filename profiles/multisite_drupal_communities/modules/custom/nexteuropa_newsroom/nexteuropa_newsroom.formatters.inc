<?php

/**
 * @file
 * Nexteuropa Newsroom formatter hooks.
 */

/**
 * Implements hook_field_formatter_info().
 */
function nexteuropa_newsroom_field_formatter_info() {
  return [
    'newsroom_main_link' => [
      'label' => t('Newsroom Main Link'),
      'field types' => ['link_field'],
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    ],
    'newsroom_pathauto' => [
      'label' => t('Newsroom Path Auto'),
      'field types' => ['text'],
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    ],
    'newsroom_zoomable_image' => [
      'label' => t('Newsroom image'),
      'field types' => ['image'],
      'settings' => _nexteuropa_newsroom_zoomable_formatter_settings(),
    ],
    'newsroom_docsroom' => [
      'label' => t('Newsroom Docsroom Documents'),
      'field types' => ['number_integer'],
      'settings' => [
        'display_type' => 'default',
        'width' => 600,
        'height' => 200,
      ],
    ],
  ];
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function nexteuropa_newsroom_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = [];

  switch ($display['type']) {

    case 'newsroom_zoomable_image':
      $image_styles = image_style_options(FALSE, PASS_THROUGH);
      $element['image_style'] = [
        '#title' => t('Image style'),
        '#type' => 'select',
        '#default_value' => $settings['image_style'],
        '#empty_option' => t('None (original image)'),
        '#options' => $image_styles,
      ];
      $element['zoomable'] = [
        '#title' => t('Allow zoom (to original in fancybox)'),
        '#type' => 'checkbox',
        '#default_value' => $settings['zoomable'],
      ];
      $element['display_title'] = [
        '#title' => t('Display title.'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_title'],
      ];
      $element['display_copyright'] = [
        '#title' => t('Display copyright'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_copyright'],
      ];
      $element['display_caption'] = [
        '#title' => t('Display caption'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_caption'],
      ];
      break;

    case 'newsroom_main_link':
      $element['display_type'] = [
        '#title' => t('Type of display context'),
        '#type' => 'select',
        '#options' => [
          'default' => t('Default'),
          'title' => t('Title only'),
          'teaser' => t('Teaser also displayed'),
        ],
        '#default_value' => $settings['display_type'],
      ];

      break;

    case 'newsroom_docsroom':
      $element['display_type'] = [
        '#title' => t('Type of display context'),
        '#type' => 'select',
        '#options' => [
          'default' => t('Default iframe presentation'),
          'link' => t('Link'),
        ],
        '#default_value' => $settings['display_type'],
      ];
      $element['width'] = [
        '#title' => t('Iframe width.'),
        '#type' => 'textfield',
        '#default_value' => $settings['width'],
      ];
      $element['height'] = [
        '#title' => t('Iframe height.'),
        '#type' => 'textfield',
        '#default_value' => $settings['height'],
      ];

      break;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function nexteuropa_newsroom_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  if ($display['type'] == 'newsroom_main_link') {
    if (!empty($display['settings']['display_type'])) {
      $options = [
        'default' => t('Default'),
        'title' => t('Title only'),
        'teaser' => t('Teaser also displayed'),
      ];
      return $options[$display['settings']['display_type']];
    }
    else {
      return t('Default');
    }
  }
  elseif ($display['type'] == 'newsroom_docsroom') {
    if (!empty($display['settings']['display_type'])) {
      $options = [
        'default' => t('Default iframe presentation'),
        'link' => t('Link'),
      ];

      return $options[$display['settings']['display_type']];
    }
    else {
      return t('Default');
    }
  }
  elseif ($display['type'] == 'newsroom_zoomable_image') {
    $settings = $display['settings'];
    $summary = [];
    $image_styles = image_style_options(FALSE, PASS_THROUGH);
    unset($image_styles['']);
    if (!empty($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', ['@style' => $image_styles[$settings['image_style']]]);
    }
    else {
      $summary[] = t('Original image');
    }
    if (!empty($settings['zoomable'])) {
      $summary[] = t('Is zoomable');
    }
    if (!empty($settings['display_title'])) {
      $summary[] = t('Displays title');
    }
    if (!empty($settings['display_copyright'])) {
      $summary[] = t('Displays copyright');
    }
    return implode(',', $summary);
  }

  return '';
}

/**
 * Implements hook_field_formatter_view().
 */
function nexteuropa_newsroom_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = [];

  switch ($display['type']) {
    case 'newsroom_pathauto':
      foreach ($items as $delta => $item) {
        $elements[$delta] = ['#markup' => pathauto_cleanstring($item['safe_value'])];
      }
      break;

    case 'newsroom_main_link':
      foreach ($items as $delta => $item) {
        if (!empty($item['url'])) {
          $item['url'] = NexteuropaNewsroomHelper::getNodeMainUrl($entity, $display['settings']['display_type']);
        }

        $elements[$delta] = [
          '#theme' => 'link_formatter_link_absolute',
          '#element' => $item,
          '#field' => $instance,
          '#display' => $display,
        ];
      }

      break;

    case 'newsroom_zoomable_image':
      global $language;
      foreach ($items as $delta => $item) {
        $image = ['path' => $item['uri']];
        $path_to_original = file_create_url($item['uri']);

        // Sets alt text.
        if (!empty($item['field_file_image_alt_text'][$language->language][0])) {
          $image['alt'] = $item['field_file_image_alt_text'][$language->language][0]['safe_value'];
        }
        elseif (is_array($item) && array_key_exists('alt', $item)) {
          $image['alt'] = $item['alt'];
        }

        // Sets zoomability.
        $zoomable = !empty($display['settings']['zoomable']) ? TRUE : FALSE;

        // Sets title.
        $title = NULL;
        if (!empty($item['field_file_image_title_text'][$language->language][0])) {
          $image['title'] = $item['field_file_image_title_text'][$language->language][0]['safe_value'];
          if ($display['settings']['display_title']) {
            $title = $item['field_file_image_title_text'][$language->language][0]['safe_value'];
          }
        }
        elseif (!empty($item['title'])) {
          $image['title'] = $item['title'];
        }

        $copyright = NULL;

        // Sets copyright.
        if (!empty($display['settings']['display_copyright']) && !empty($item['field_newsroom_copyrights'][$language->language][0])) {
          $copyright = $item['field_newsroom_copyrights'][$language->language][0]['safe_value'];
        }

        // Sets caption.
        $caption = '';
        if (!empty($display['settings']['display_caption']) && !empty($item['field_caption'][$language->language][0])) {
          $caption = $item['field_caption'][$language->language][0]['safe_value'];
        }

        if (!empty($item['attributes'])) {
          $image['attributes'] = $item['attributes'];
        }

        if (!empty($item['width']) && !empty($item['height'])) {
          $image['width'] = $item['width'];
          $image['height'] = $item['height'];
        }

        $image['title'] = $title;

        if (!empty($display['settings']['image_style'])) {
          $image['style_name'] = $display['settings']['image_style'];
          $image_output = theme('image_style', $image);
        }
        else {
          $image_output = theme('image', $image);
        }

        $elements[$delta] = [
          '#theme' => 'newsroom_zoomable_image',
          '#copyright' => $copyright,
          '#caption' => $caption,
          '#image_output' => $image_output,
          '#path_to_original' => $path_to_original,
          '#zoomable' => $zoomable,
        ];
      }

      break;

    case 'newsroom_docsroom':
      $docsroom_ids = [];
      foreach ($items as $item) {
        $docsroom_ids[] = $item['value'];
      }

      if (!empty($docsroom_ids)) {
        $display_type = !empty($display['settings']['display_type']) ? $display['settings']['display_type'] : 'default';
        $url = url(
          variable_get('nexteuropa_newsroom_docsroom_url'),
          [
            'external' => TRUE,
            'query' => [
              'documentsIds' => implode(',', $docsroom_ids),
              'iframe' => 'true',
              'autoHeight' => 'true',
            ],
          ]
        );
        if ($display_type == 'default') {
          $elements[0] = [
            '#theme' => 'newsroom_docsroom',
            '#url' => $url,
            '#width' => !empty($display['settings']['width']) ? $display['settings']['width'] : NULL,
            '#height' => !empty($display['settings']['height']) ? $display['settings']['height'] : NULL,
          ];
        }
        elseif ($display_type == 'link') {
          $elements[0] = [
            '#theme' => 'link',
            '#text' => 'Docsroom documents',
            '#path' => $url,
            '#options' => [
              'attributes' => ['class' => ['docsroom-link']],
              'html' => FALSE,
            ],
          ];
        }
      }

      break;
  }

  return $elements;
}

/**
 * Returns zoomable formatter settings array.
 *
 * @param string $image_style
 *   Image style.
 * @param int $display_title
 *   Display title or not.
 * @param int $display_copyright
 *   Display copyright or not.
 * @param int $display_caption
 *   Display caption or not.
 * @param int $zoomable
 *   Is image zoomable or not.
 *
 * @return array
 *   Settings array.
 */
function _nexteuropa_newsroom_zoomable_formatter_settings($image_style = 'newsroom_style', $display_title = 1, $display_copyright = 1, $display_caption = 1, $zoomable = 1) {
  return [
    'image_style' => $image_style,
    'display_title' => $display_title,
    'display_copyright' => $display_copyright,
    'display_caption' => $display_caption,
    'zoomable' => $zoomable,
  ];
}
