<?php

/**
 * @file
 * Nexteuropa Newsroom administration page.
 */

/**
 * Nexteuropa newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Form array.
 */
function nexteuropa_newsroom_admin_settings(array $form, array &$form_state) {
  // Be aware about the selected content types in the fields fieldset.
  $sel_ct = NexteuropaNewsroomHelper::getFieldInstances('select');
  $top_ct = NexteuropaNewsroomHelper::getFieldInstances('topic');
  $newsroom_universe_id = NexteuropaNewsroomHelper::getUniverseId();
  // Get some information basing on the activation of the universe id.
  if (!empty($newsroom_universe_id)) {
    $universe_id_info['disabled'] = TRUE;
    $universe_id_info['description'] = t('To change the Newsroom Universe ID contact the site administrator.');
    $universe_id_info['class'] = 'selected';
  }
  else {
    $universe_id_info['disabled'] = FALSE;
    $universe_id_info['description'] = t('After setting the Newsroom Universe ID for the first time content will be imported from the Newsroom service. This might take a few minutes.');
    $universe_id_info['class'] = 'not-selected';
  }

  // This is special, made just to hold the universe_id field.
  $form['universe_id'] = [
    '#type' => 'container',
    '#title' => t('Newsroom Universe ID'),
    '#attributes' => ['class' => [$universe_id_info['class']]],
  ];

  $form['universe_id']['nexteuropa_newsroom_universe_id'] = [
    '#type' => 'textfield',
    '#title' => t('Universe ID value'),
    '#required' => TRUE,
    '#disabled' => $universe_id_info['disabled'],
    '#description' => $universe_id_info['description'],
    '#default_value' => $newsroom_universe_id,
    '#element_validate' => ['_nexteuropa_newsroom_admin_universe_id_validate'],
  ];

  // Other settings for the newsroom.
  $form['newsroom_others'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom client settings'),
    '#description' => t("These settings will determine newsroom behavior in your website.
      In particular you can choose here whether to import multilingual content from the newsroom or not.
      Mind the fact that we rely on the enabled languages in your website, so you will not be able to import items in a language that doesn't exist yet."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
  ];

  $form['newsroom_others']['importers_link'] = [
    '#type' => 'item',
    '#markup' => l(t('Feed importers'), 'import'),
  ];

  $form['newsroom_others']['nexteuropa_newsroom_subsite'] = [
    '#type' => 'textfield',
    '#title' => t('Name of the subsite, if any.'),
    '#description' => t('The value you enter here will be used to filter the items belonging to this website.'),
    '#default_value' => variable_get('nexteuropa_newsroom_subsite'),
    '#element_validate' => ['_nexteuropa_newsroom_admin_subsite_validate'],
  ];

  $form['newsroom_others']['nexteuropa_newsroom_use_css'] = [
    '#type' => 'checkbox',
    '#title' => t('Use the stylesheets provided by this feature'),
    '#default_value' => variable_get('nexteuropa_newsroom_use_css', 1),
  ];

  $form['newsroom_others']['nexteuropa_newsroom_legacy'] = [
    '#type' => 'checkbox',
    '#title' => t('If you have custom css code related to the newsroom maintain the legacy html code.'),
    '#default_value' => variable_get('nexteuropa_newsroom_legacy', 1),
  ];

  $types = NexteuropaNewsroomVocabularyHelper::getNewsroomTypes();

  if (!empty($types)) {
    $form['newsroom_paths'] = [
      '#type' => 'fieldset',
      '#title' => t('Newsroom content path settings'),
      '#prefix' => '<div id="newsroom_reset">',
      '#suffix' => '</div>',
      '#description' => t("You can define here a root path for your items basing on the item type. The default behavior is to have sections correponding to the types, so if you have two types like
            news and events you will get pattern like news/[node:title], events/[node:title], you can override the root path for your elements here. Do not use leading or trailing slashes"),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
    ];

    $form['newsroom_paths']['nexteuropa_newsroom_patterns'] = [
      '#type' => 'checkbox',
      '#title' => t('Do you want to take over the configuration of pattern for node aliases?'),
      '#description' => t('if this is unchecked the newsroom will not alter the aliases for its nodes.'),
      '#default_value' => variable_get('nexteuropa_newsroom_patterns', FALSE),
    ];

    foreach ($types as $type) {
      $type_name = pathauto_cleanstring($type->name);
      $parents = taxonomy_get_parents($type->tid);
      $parent = '';

      if (!empty($parents)) {
        $parent = reset($parents);
        $parent = pathauto_cleanstring($parent->name) . '/';
      }

      $path_var_name = 'nexteuropa_newsroom_' . $type_name . '_root';
      $form['newsroom_paths'][$path_var_name] = [
        '#type' => 'textfield',
        '#title' => t('Pattern for %type', ['%type' => $type_name]),
        '#required' => FALSE,
        '#description' => t('Aliases pattern for the %type_name topic.', ['%type_name' => $type_name]),
        '#default_value' => variable_get($path_var_name, $parent . $type_name),
        '#element_validate' => ['_nexteuropa_newsroom_admin_type_root_validate'],
      ];
    }

    $form['newsroom_paths']['reset'] = [
      '#type' => 'submit',
      '#value' => 'Reset to the defaults',
      '#ajax' => [
        'callback' => '_nexteuropa_newsroom_admin_reset_paths',
        'event' => 'click',
        'wrapper' => 'newsroom_reset',
        'effect' => 'fade',
        'method' => 'replace',
      ],
    ];
  }
  // Settings about the newsroom fields.
  $form['newsroom_fields'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom fields settings'),
    '#description' => t('Here you can easily manage the addition or the removal of the newsroom fields from your content types. Refer to the <a href="@documentation">documentation</a> for having detailed information about the usage of the newsroom fields.  They are meant to give you the chance to associate topics to you contents so that matching news coming from the newsroom can be shown or mentioned contextually.', ['@documentation' => 'https://webgate.ec.europa.eu/fpfis/wikis/pages/viewpage.action?spaceKey=MULTISITE&title=%5BFPFIS%5D+Nexteuropa+Newsroom+-+Documentation']),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
  ];

  $form['newsroom_fields']['nexteuropa_newsroom_content_types_topic'] = [
    '#type' => 'checkboxes',
    '#title' => t('Direct topic relation field in your content types'),
    '#description' => t('Choose the content types in which you want to activate a relationship with a newsroom topic.'),
    '#options' => _nexteuropa_newsroom_prepare_options('ct'),
    '#multiple' => TRUE,
    '#default_value' => $top_ct,
  ];

  $form['newsroom_fields']['nexteuropa_newsroom_content_types_delete_topic'] = [
    '#type' => 'checkbox',
    '#title' => t('Delete all the topic relation fields in your content types.'),
    '#description' => t('If you want to delete all the instance of the topic field together check this.'),
    '#default_value' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];

  $form['newsroom_fields']['nexteuropa_newsroom_content_types_select'] = [
    '#type' => 'checkboxes',
    '#title' => t('Advanced and configurable reference with newsroom items.'),
    '#description' => t('Choose the content types in which you want to activate a complex relationship with the newsroom items.'),
    '#options' => _nexteuropa_newsroom_prepare_options('ct'),
    '#multiple' => TRUE,
    '#default_value' => $sel_ct,
  ];

  $form['newsroom_fields']['nexteuropa_newsroom_content_types_delete_select'] = [
    '#type' => 'checkbox',
    '#title' => t('Delete all the newsroom select fields in your content types.'),
    '#description' => t('If you want to delete all the instance of the select field together check this.'),
    '#default_value' => 0,
  ];

  // Settings about the universe.
  $form['newsroom_universe'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom universe settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_app'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom app'),
    '#default_value' => variable_get('nexteuropa_newsroom_app'),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_app_key'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom key'),
    '#default_value' => variable_get('nexteuropa_newsroom_app_key'),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_subscription_url'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom subscription URL'),
    '#default_value' => variable_get('nexteuropa_newsroom_subscription_url'),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_base_url'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom universe base URL'),
    '#default_value' => variable_get('nexteuropa_newsroom_base_url', NEXTEUROPA_NEWSROOM_BASE_URL),
    '#description' => t('The base url of newsroom feeds.'),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_allowed_ips'] = [
    '#type' => 'textfield',
    '#title' => t('IP addresses allowed for import'),
    '#default_value' => variable_get('nexteuropa_newsroom_allowed_ips', '127.0.0.1,158.167.165.192,158.167.165.191,158.167.209.222,158.167.240.147,158.167.209.223,158.167.210.159,158.167.210.158'),
    '#description' => t('Comma separated list of IP addresses where the importer can be launched from.'),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_item_import_script'] = [
    '#type' => 'textfield',
    '#title' => t('Item import script name'),
    '#default_value' => variable_get('nexteuropa_newsroom_item_import_script', NEXTEUROPA_NEWSROOM_ITEM_SCRIPT),
  ];
  $form['newsroom_universe']['nexteuropa_newsroom_single_item_import_segment'] = [
    '#type' => 'textfield',
    '#title' => t('URL chunk for single item import'),
    '#default_value' => variable_get('nexteuropa_newsroom_single_item_import_segment', NEXTEUROPA_NEWSROOM_ITEM_SEGMENT),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_topic_import_script'] = [
    '#type' => 'textfield',
    '#title' => t('Topic import script name'),
    '#default_value' => variable_get('nexteuropa_newsroom_topic_import_script', NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT),
  ];
  $form['newsroom_universe']['nexteuropa_newsroom_single_topic_import_segment'] = [
    '#type' => 'textfield',
    '#title' => t('URL chunk for single topic import'),
    '#default_value' => variable_get('nexteuropa_newsroom_single_topic_import_segment', NEXTEUROPA_NEWSROOM_TOPIC_SEGMENT),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_type_import_script'] = [
    '#type' => 'textfield',
    '#title' => t('Type import script name'),
    '#default_value' => variable_get('nexteuropa_newsroom_type_import_script', NEXTEUROPA_NEWSROOM_TYPE_SCRIPT),
  ];
  $form['newsroom_universe']['nexteuropa_newsroom_single_type_import_segment'] = [
    '#type' => 'textfield',
    '#title' => t('URL chunk for single type import'),
    '#default_value' => variable_get('nexteuropa_newsroom_single_type_import_segment', NEXTEUROPA_NEWSROOM_TYPE_SEGMENT),
  ];

  // For topics and services we use the same script name.
  $form['newsroom_universe']['nexteuropa_newsroom_service_import_script'] = [
    '#type' => 'textfield',
    '#title' => t('Service import script name'),
    '#default_value' => variable_get('nexteuropa_newsroom_service_import_script', NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT),
  ];
  $form['newsroom_universe']['nexteuropa_newsroom_single_service_import_segment'] = [
    '#type' => 'textfield',
    '#title' => t('URL chunk for single service import'),
    '#default_value' => variable_get('nexteuropa_newsroom_single_service_import_segment', NEXTEUROPA_NEWSROOM_SERVICE_SEGMENT),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_single_item_edit_segment'] = [
    '#type' => 'textfield',
    '#title' => t('URL chunk to edit an item in the Newsroom'),
    '#default_value' => variable_get('nexteuropa_newsroom_single_item_edit_segment', NEXTEUROPA_NEWSROOM_ITEM_EDIT_SEGMENT),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_proposal_script'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom proposal script'),
    '#default_value' => variable_get('nexteuropa_newsroom_proposal_script', NEXTEUROPA_NEWSROOM_PROPOSAL_SCRIPT),
  ];

  $form['newsroom_universe']['nexteuropa_newsroom_docsroom_url'] = [
    '#type' => 'textfield',
    '#title' => t('Newsroom Docsroom URL'),
    '#default_value' => variable_get('nexteuropa_newsroom_docsroom_url'),
  ];

  // Page settings.
  $form['newsroom_pages'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom page settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];
  $form['newsroom_pages']['nexteuropa_newsroom_newsletter_privacy'] = [
    '#type' => 'textarea',
    '#title' => t('Privacy statement'),
    '#default_value' => variable_get('nexteuropa_newsroom_newsletter_privacy'),
  ];
  $form['newsroom_pages']['nexteuropa_newsroom_featured_type'] = [
    '#type' => 'select',
    '#title' => t('Featured newsroom type'),
    '#options' => NexteuropaNewsroomHelper::getNewsroomTypeOptions(FALSE),
    '#default_value' => variable_get('nexteuropa_newsroom_featured_type'),
  ];

  // Settings about the newsroom blocks.
  $form['newsroom_blocks'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom blocks settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];

  $form['newsroom_blocks']['nexteuropa_newsroom_order_by_last_update'] = [
    '#type' => 'checkbox',
    '#title' => t('Sort newsroom boxes chronologically in the summary blocks.'),
    '#default_value' => variable_get('nexteuropa_newsroom_order_by_last_update', 0),
  ];

  $form['newsroom_blocks']['nexteuropa_newsroom_display_highlights_begin'] = [
    '#type' => 'checkbox',
    '#title' => t('Highlighted topics are displayed at the begining of the list.'),
    '#default_value' => variable_get('nexteuropa_newsroom_display_highlights_begin', 1),
  ];

  $form['newsroom_blocks']['nexteuropa_newsroom_agenda_after_highlights'] = [
    '#type' => 'checkbox',
    '#title' => t('Display Agenda after the highlights.'),
    '#default_value' => variable_get('nexteuropa_newsroom_agenda_after_highlights', 1),
  ];

  $form['newsroom_blocks']['nexteuropa_newsroom_summary_block_num_items'] = [
    '#type' => 'select',
    '#title' => t('Number of items in boxes in the summary blocks'),
    '#options' => _nexteuropa_newsroom_prepare_options(5),
    '#default_value' => variable_get('nexteuropa_newsroom_summary_block_num_items', 3),
  ];

  $form['newsroom_blocks']['nexteuropa_newsroom_summary_block_num_highlighted_items'] = [
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary blocks'),
    '#options' => _nexteuropa_newsroom_prepare_options(6),
    '#default_value' => variable_get('nexteuropa_newsroom_summary_block_num_highlighted_items', 3),
  ];

  $form['newsroom_blocks']['home_blocks'] = [
    '#type' => 'fieldset',
    '#title' => t('Newsroom home blocks settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];
  // Settings about newsroom blocks in the home page.
  $form['newsroom_blocks']['home_blocks']['nexteuropa_newsroom_summary_home_block_num_items'] = [
    '#type' => 'select',
    '#title' => t('Number of items in boxes in the summary block on the homepage'),
    '#options' => _nexteuropa_newsroom_prepare_options(5),
    '#default_value' => variable_get('nexteuropa_newsroom_summary_home_block_num_items', 3),
  ];

  $form['newsroom_blocks']['home_blocks']['nexteuropa_newsroom_summary_home_block_num_highlighted_items'] = [
    '#type' => 'select',
    '#title' => t('Number of items in boxes of highlighted types in the summary block on the homepage'),
    '#options' => _nexteuropa_newsroom_prepare_options(6),
    '#default_value' => variable_get('nexteuropa_newsroom_summary_home_block_num_highlighted_items', 3),
  ];

  $form['newsroom_blocks']['home_blocks']['nexteuropa_newsroom_days_number_for_new_user'] = [
    '#type' => 'textfield',
    '#title' => t('Number of days from now where we check new newsroom items'),
    '#default_value' => variable_get('nexteuropa_newsroom_days_number_for_new_user', 14),
  ];

  $form['viewmodes'] = [
    '#type' => 'fieldset',
    '#title' => 'Newsroom View Modes',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];

  $form['viewmodes']['nexteuropa_newsroom_events_type_id'] = [
    '#type' => 'textfield',
    '#title' => t('Event type ID'),
    '#description' => t('Newsroom event type ID'),
    '#default_value' => variable_get('nexteuropa_newsroom_events_type_id'),
    '#size' => 10,
  ];

  $form['viewmodes']['nexteuropa_newsroom_fundings_type_id'] = [
    '#type' => 'textfield',
    '#title' => t('Fundings type ID'),
    '#description' => t('Newsroom fundings type ID'),
    '#default_value' => variable_get('nexteuropa_newsroom_fundings_type_id'),
    '#size' => 10,
  ];

  $form['viewmodes']['nexteuropa_newsroom_consultations_type_id'] = [
    '#type' => 'textfield',
    '#title' => t('Consultations type ID'),
    '#description' => t('Newsroom consultations type ID'),
    '#default_value' => variable_get('nexteuropa_newsroom_consultations_type_id'),
    '#size' => 10,
  ];

  $form['viewmodes']['nexteuropa_newsroom_use_default_view_mode'] = [
    '#type' => 'checkbox',
    '#title' => t('Use the newsroom default view mode'),
    '#default_value' => variable_get('nexteuropa_newsroom_use_default_view_mode', 1),
  ];

  $form['viewmodes']['nexteuropa_newsroom_redirect_short_items'] = [
    '#type' => 'checkbox',
    '#title' => t('Redirect short items'),
    '#default_value' => variable_get('nexteuropa_newsroom_redirect_short_items', 0),
  ];

  // Attach a css to the admin settings form.
  $form['#attached']['css'] = [
    drupal_get_path('module', 'nexteuropa_newsroom') . '/styles/nexteuropa_newsroom_admin_setting.css',
  ];
  // Validate function.
  $form['#validate'][] = '_nexteuropa_newsroom_admin_settings_form_validate';
  // Submit handler.
  $form['#submit'][] = '_nexteuropa_newsroom_admin_settings_form_submit';

  if ($newsroom_universe_id) {
    $form['actions']['run'] = [
      '#type' => 'submit',
      '#value' => t('Run importers'),
      '#submit' => ['_nexteuropa_newsroom_import_importers'],
      '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
      '#weight' => 9,
    ];
    $form['actions']['delete_items'] = [
      '#type' => 'submit',
      '#value' => t('Delete existing items'),
      '#submit' => ['_nexteuropa_newsroom_delete_items'],
      '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
      '#weight' => 10,
    ];
    $form['actions']['rebuild'] = [
      '#type' => 'submit',
      '#value' => t('Rebuild importers'),
      '#submit' => ['_nexteuropa_newsroom_admin_rebuild_importers'],
      '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
      '#weight' => 11,
    ];
    $form['actions']['clean_cache'] = [
      '#type' => 'submit',
      '#value' => 'Clean cache',
      '#submit' => ['_nexteuropa_newsroom_admin_clean_cache'],
      '#access' => user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS),
      '#weight' => 12,
    ];
  }

  // Define the fields_form array.
  $form_state['fields_form'] = [];
  $form_state['fields_form']['topic'] = $top_ct;
  $form_state['fields_form']['select'] = $sel_ct;

  // Confirmation step_needed.
  if (!empty($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    return _nexteuropa_newsroom_admin_delete_confirm($form, $form_state);
  }
  // Normal form.
  else {
    return system_settings_form($form);
  }
}

/**
 * Validation step for the the newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_admin_settings_form_validate(array $form, array &$form_state) {
  // If we are not during a confirm or this has happened right before.
  if (empty($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $check_values = _nexteuropa_newsroom_admin_prepare_check($form_state['fields_form'], $form_state['values']);

    // Check every topic and select instance if requested.
    foreach (['topic', 'select'] as $field_item) {
      if ($check_values['delete'][$field_item] == 1) {
        $test = _nexteuropa_newsroom_admin_check_deletion($field_item, NEXTEUROPA_NEWSROOM_ALL);
      }
      // If there are less values than before, check instances.
      elseif (!empty($check_values['check'][$field_item][0])) {
        $test = _nexteuropa_newsroom_admin_check_deletion($field_item, $check_values['check'][$field_item][0]);
      }
    }

    if (!empty($test)) {
      $form_state['storage']['confirm'] = TRUE;
      $form_state['confirm']['values'] = $test;
    }
  }
}

/**
 * Submit handler for the newsroom admin form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_admin_settings_form_submit(array $form, array &$form_state) {
  $universe_id = NexteuropaNewsroomHelper::getUniverseId();
  if (empty($universe_id) && $form_state['values']['nexteuropa_newsroom_universe_id']) {
    variable_set('nexteuropa_newsroom_universe_id', $form_state['values']['nexteuropa_newsroom_universe_id']);
    _nexteuropa_newsroom_admin_rebuild_importers();
  }

  $patterns = !empty($form_state['values']['patterns']) && $form_state['values']['patterns'] == 1 ? TRUE : FALSE;
  $keys = array_keys($form_state['values']);
  $rootpaths = preg_grep('/rootpath/', $keys);
  // Shouldn't be needed, it is a setting form.
  if (!empty($rootpaths)) {
    foreach ($rootpaths as $type) {
      $typename = str_replace('_rootpath', '', $type);
      variable_set('newsroom_' . $typename . '_root', $form_state['values'][$type]);
    }
  }

  $patterns ? variable_set('nexteuropa_newsroom_patterns', 1) : variable_set('nexteuropa_newsroom_patterns', 0);

  // If the validation returns the confirm request.
  if (!empty($form_state['storage']['confirm']) && empty($form_state['confirm']['processed'])) {
    $form_state['rebuild'] = TRUE;
  }
  else {
    $check_values = _nexteuropa_newsroom_admin_prepare_check($form_state['fields_form'], $form_state['values']);

    // Remove every topic or select instance if requested.
    foreach (['topic', 'select'] as $field_item) {
      if ($check_values['delete'][$field_item] == 1) {
        _nexteuropa_newsroom_admin_remove_fields($field_item, NEXTEUROPA_NEWSROOM_ALL);
      }
      elseif (!empty($check_values['selected'][$field_item]) && !empty($check_values['check'][$field_item][1])) {
        // Add new instances.
        _nexteuropa_newsroom_admin_add_fields($field_item, $check_values['check'][$field_item][1]);
      }
      elseif (!empty($check_values['check'][$field_item][0])) {
        // Remove instances.
        _nexteuropa_newsroom_admin_remove_fields($field_item, $check_values['check'][$field_item][0]);
      }
    }

    cache_clear_all('newsroom:', 'cache', TRUE);
  }
}

/**
 * Add a confirmation step if needed.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Confirmation form array.
 */
function _nexteuropa_newsroom_admin_delete_confirm(array $form, array &$form_state) {
  $form_state['confirm']['processed'] = TRUE;
  $values = $form_state['confirm']['values'];
  $desc = '<div class="messages error"><h3>' . t('Part of the form has not been submitted yet. You have:') . '</h3></br><i>';
  foreach ($values as $field => $nodes) {
    for ($i = 0; $i < count($values[$field]); $i++) {
      $desc .= t('@num nodes containing values for the field @field in the content type @ct.',
          [
            '@num' => $values[$field][$i]['nodes'],
            '@field' => $field,
            '@ct' => $values[$field][$i]['ct'],
          ]
        ) . '<br/>';
    }
  }
  $desc .= '</i>' . t('If you continue these information could be lost.') . '</p>';
  $form['process'] = ['#type' => 'hidden', '#value' => 'true'];
  return confirm_form($form, 'Confirmation needed for removing field instances with values in the current database', 'admin/config/content/newsroom', check_markup($desc, 'full_html'), 'Continue', 'Restart');
}

/**
 * Checks universe ID for valid value.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_universe_id_validate(array $element, array &$form_state) {
  if (!NexteuropaNewsroomHelper::validateUniverse($form_state['values']['nexteuropa_newsroom_universe_id'])) {
    form_error($element, t('You must enter a valid Newsroom Universe ID.'));
  }
}

/**
 * Checks subsite for valid value.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_subsite_validate(array $element, array &$form_state) {
  if (!NexteuropaNewsroomHelper::validateSubsite($form_state['values']['nexteuropa_newsroom_subsite'])) {
    form_error($element, t("This subsite doesn't seem to exist, please check the value you entered."));
  }
}

/**
 * Validates newsroom URL patterns.
 *
 * @param array $element
 *   Form element.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_admin_type_root_validate(array $element, array &$form_state) {
  $value = preg_replace('@^/|/$@', '', $element['#value']);
  $value_array = explode('/', $value);
  $pattern = '';

  for ($i = 1; $i <= count($value_array); $i++) {
    $segment = pathauto_cleanstring($value_array[$i - 1]);
    $pattern .= $segment;
    if ($i < count($value_array) && $segment != '') {
      $pattern .= '/';
    }
  }

  if ($form_state['values'][$element['#name']] != $pattern) {
    drupal_set_message(
      t('The value for the %el has been modified. BEFORE: %or ::: AFTER: %mod',
        [
          '%el' => $element['#name'],
          '%or' => $form_state['values'][$element['#name']],
          '%mod' => $pattern,
        ]),
      'warning'
    );
    $form_state['values'][$element['#name']] = $pattern;
  }
}

/**
 * Callback: Resets values in the path patterns field for the newsroom items.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Pathes.
 */
function _nexteuropa_newsroom_admin_reset_paths(array $form, array &$form_state) {
  foreach (NexteuropaNewsroomVocabularyHelper::getNewsroomTypes() as $type) {
    $type_name = pathauto_cleanstring($type->name);
    $parents = taxonomy_get_parents($type->tid);
    $parent = '';
    if (!empty($parents)) {
      $parent = reset($parents);
      $parent = pathauto_cleanstring($parent->name) . '/';
    }
    $form['newsroom_paths'][$type_name . '_rootpath']['#value'] = $parent . $type_name;
  }
  return $form['newsroom_paths'];
}

/**
 * Cleans newsroom cache - Ajax callback.
 */
function _nexteuropa_newsroom_admin_clean_cache() {
  cache_clear_all('*', NEXTEUROPA_NEWSROOM_CACHE_TABLE, TRUE);
  drupal_set_message(t('Cache has been cleaned.'));
}

/**
 * Adds fields to selected content types.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $sel_ct
 *   Array of content types machine names.
 */
function _nexteuropa_newsroom_admin_add_fields($type = 'topic', array $sel_ct = []) {
  $field_name = 'field_newsroom_associated_' . $type;
  if (!empty($sel_ct)) {

    foreach ($sel_ct as $machine_name => $content_type) {
      $exist = field_info_instance('node', $field_name, $machine_name);
      // Check for existing instances.
      if ($exist === NULL) {
        $instance = [
          'field_name' => $field_name,
          'entity_type' => 'node',
          'bundle' => $machine_name,
          'label' => 'Newsroom ' . $type,
          'description' => '',
          'required' => 0,
        ];
        field_create_instance($instance);
        // Call the field_group helper function, we surely have to update it.
        _nexteuropa_newsroom_admin_field_group($machine_name);
        // Set a message to inform the user about the field instance creation.
        drupal_set_message(t('Created instance of @field in the @bundle content type.', ['@field' => $field_name, '@bundle' => $machine_name]));
      }
    }
  }
}

/**
 * Creates a field_group to hold the newsroom fields in a vertical tab.
 *
 * @param string $machine_name
 *   Content type machine name.
 */
function _nexteuropa_newsroom_admin_field_group($machine_name) {
  // Get info about the group, it's likely to be already in the database.
  $groups = field_group_info_groups('node', $machine_name, 'form', TRUE);
  $fields = ['topic', 'select'];
  $group_name = 'group_newsroom_fields';
  $instances = FALSE;

  // Check for instances of the newsroom fields inside the given content type.
  foreach ($fields as $field) {
    $field_name = 'field_newsroom_associated_' . $field;
    if (field_info_instance('node', $field_name, $machine_name) != NULL) {
      $instances[] = field_info_instance('node', $field_name, $machine_name);
    }
  }

  // If the group is already there, remove it.
  if (!empty($groups[$group_name])) {
    db_delete('field_group')
      ->condition('bundle', $machine_name, '=')
      ->condition('group_name', $group_name, '=')
      ->execute();
  }

  // Create the group with the right children.
  if ($instances) {
    $field_group = (object) [
      'identifier' => $group_name . '|node|' . $machine_name . '|form',
      'group_name' => $group_name,
      'entity_type' => 'node',
      'bundle' => $machine_name,
      'mode' => 'form',
      'children' => [],
      'parent_name' => '',
      'weight' => 5,
      'label' => 'Newsroom fields',
      'format_type' => 'tab',
      'disabled' => FALSE,
      'format_settings' => [
        'instance_settings' => [
          'required_fields' => 0,
          'classes' => 'group-newsroom field-group-tab',
          'description' => '',
        ],
        'formatter' => 'closed',
      ],
    ];

    foreach ($instances as $instance) {
      $field_group->children[] = $instance['field_name'];
    }

    field_group_group_save($field_group);
  }
  else {
    drupal_set_message(t('Removed the fieldgroup @name from the @content_type content type.', ['@name' => $group_name, '@content_type' => $machine_name]), 'status');
  }
}

/**
 * Removes all the instances of a fields.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $sel_ct
 *   Array of content types machine names.
 */
function _nexteuropa_newsroom_admin_remove_fields($type = 'topic', array $sel_ct = []) {
  // This function runs after checking for existing field values in the databas.
  $field_name = 'field_newsroom_associated_' . $type;
  // All is the parameter we get when an user want to delete all the instances.
  if ($sel_ct == NEXTEUROPA_NEWSROOM_ALL) {
    $instances = NexteuropaNewsroomHelper::getFieldInstances($type);
  }
  // Limit the search to the selected content types.
  elseif (!empty($sel_ct)) {
    foreach ($sel_ct as $content_type) {
      $instances[] = $content_type;
    }
  }

  if (!empty($instances)) {
    // Loop through the instances to delete them.
    foreach ($instances as $instance) {
      $instance = field_info_instance('node', $field_name, $instance);
      field_delete_instance($instance, FALSE);
      // Call the field_group helper function, we could have to delete it.
      _nexteuropa_newsroom_admin_field_group($instance['bundle'], $field_name);
      // Add the message to queue.
      drupal_set_message(t('Deleted instance of @field in the @bundle content type.', ['@field' => $field_name, '@bundle' => $instance['bundle']]));
    }
  }
}

/**
 * Checks if it safe to delete field instances.
 *
 * @param string $type
 *   Select or topic fo the moment.
 * @param array $checks
 *   Array of items to check.
 *
 * @return array
 *   Information about the field name and nodes found.
 */
function _nexteuropa_newsroom_admin_check_deletion($type, array $checks = []) {
  $nodes = [];
  // "All" is the parameter we get to delete all the instances.
  if ($checks == NEXTEUROPA_NEWSROOM_ALL) {
    $instances = NexteuropaNewsroomHelper::getFieldInstances($type);
  }
  elseif (!empty($checks)) {
    // Get the instances to check for.
    foreach ($checks as $check) {
      $instances[] = $check;
    }
  }

  if (!empty($instances)) {
    foreach ($instances as $instance) {
      // Check in the database for values of the selected field.
      $query = db_select('field_data_field_newsroom_associated_' . $type, 'ch');
      $query->condition('bundle', $instance, '=');
      $num_rows = $query->countQuery()->execute()->fetchField();
      // There are values, we store the number of nodes to show it to the user.
      if ($num_rows > 0) {
        $nodes['field_data_field_newsroom_associated_' . $type][] = [
          'ct' => $instance,
          'nodes' => $num_rows,
        ];
      }
    }
  }
  return $nodes;
}

/**
 * Prepares check for instances deletion.
 *
 * @param array $previous
 *   Old values.
 * @param array $input
 *   New values.
 *
 * @return array
 *   Variables to pass.
 */
function _nexteuropa_newsroom_admin_prepare_check(array $previous, array $input) {
  // Set some values.
  $selected['topic'] = array_filter($input['nexteuropa_newsroom_content_types_topic']);
  $selected['select'] = array_filter($input['nexteuropa_newsroom_content_types_select']);
  $check_topic = [];
  $check_select = [];
  // Check the two array for differences. we need to catch also a deselection.
  if ($selected != $previous) {
    $check_topic[] = array_diff($previous['topic'], $selected['topic']);
    $check_topic[] = array_diff($selected['topic'], $previous['topic']);
    $check_select[] = array_diff($previous['select'], $selected['select']);
    $check_select[] = array_diff($selected['select'], $previous['select']);
  }
  // Prepare all the relevant data formatted into an [).
  $infos = [
    'selected' => [
      'topic' => $selected['topic'],
      'select' => $selected['select'],
    ],
    'delete' => [
      'topic' => $input['nexteuropa_newsroom_content_types_delete_topic'],
      'select' => $input['nexteuropa_newsroom_content_types_delete_select'],
    ],
    'check' => [
      'topic' => $check_topic,
      'select' => $check_select,
    ],
  ];

  return $infos;
}

/**
 * Rebuilds multilingual importers.
 */
function _nexteuropa_newsroom_admin_rebuild_importers() {
  NexteuropaNewsroomImporterHelper::rebuildImporters();
  drupal_set_message(t('Newsroom importers have been successfully generated.'));
}

/**
 * Runs all importers.
 */
function _nexteuropa_newsroom_import_importers() {
  // Run the multilingual imports if required.
  $importers = NexteuropaNewsroomImporterHelper::returnImporters();
  foreach ($importers as $importer) {
    NexteuropaNewsroomImporterHelper::runFeedImporter($importer);
  }
}

/**
 * Submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_delete_items_confirm_submit(array $form, array &$form_state) {
  if ($form_state['values']['confirm']) {
    // Delete the imported items.
    $importers = NexteuropaNewsroomImporterHelper::returnImporters();

    foreach ($importers as $importer) {
      NexteuropaNewsroomImporterHelper::deleteItems($importer);
    }

    drupal_set_message(t('Newsroom data has been removed.'));
  }

  $form_state['redirect'] = 'admin/config/content/newsroom';
}

/**
 * Confirmation form page callback.
 *
 * @param array $form
 *   Form array.
 *
 * @return array
 *   Confirmatio form.
 */
function _nexteuropa_newsroom_delete_items_confirm(array $form) {
  return confirm_form($form,
    t('Are you sure you want to clear newsroom items?'),
    'admin/config/content/newsroom',
    t('This will remove all data imported by Newsroom connector.'),
    t('Remove imported data')
  );
}

/**
 * Submit handler, delete items.
 */
function _nexteuropa_newsroom_delete_items(array $form, array &$form_state) {
  drupal_goto('admin/config/content/newsroom/delete');
  drupal_exit();
}

/**
 * Prepares options for the content type select.
 *
 * @param string $type
 *   Type of the options to generate.
 *
 * @return array
 *   Array of options.
 */
function _nexteuropa_newsroom_prepare_options($type) {
  $options = [];
  if (is_numeric($type)) {
    for ($i = 1; $i <= $type; $i++) {
      $options[$i] = $i;
    }
  }
  else {
    // Get a list of the existing content type.
    $content_types = node_type_get_types();
    // Exclude the ct used for the import.
    unset($content_types[NEXTEUROPA_NEWSROOM_CONTENT_TYPE]);
    unset($content_types['newsroom_selection']);
    // Build options for selecting content types.
    foreach ($content_types as $name => $content_type) {
      if ($content_type->disabled !== 1) {
        $options[$name] = $content_type->name;
      }
    }
  }
  return $options;
}
