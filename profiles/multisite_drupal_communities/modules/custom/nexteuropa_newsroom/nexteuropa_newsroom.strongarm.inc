<?php

/**
 * @file
 * nexteuropa_newsroom.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_newsroom_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_newsroom_item';
  $strongarm->value = 'edit-menu';
  $export['additional_settings__active_tab_newsroom_item'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_newsroom_selection';
  $strongarm->value = '0';
  $export['comment_anonymous_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_newsroom_selection';
  $strongarm->value = 1;
  $export['comment_default_mode_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_newsroom_selection';
  $strongarm->value = '50';
  $export['comment_default_per_page_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_newsroom_selection';
  $strongarm->value = 1;
  $export['comment_form_location_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_newsroom_selection';
  $strongarm->value = '1';
  $export['comment_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_newsroom_selection';
  $strongarm->value = '1';
  $export['comment_preview_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_newsroom_selection';
  $strongarm->value = 1;
  $export['comment_subject_field_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_newsroom_date_only';
  $strongarm->value = 'd/m/Y';
  $export['date_format_newsroom_date_only'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short_newsroom';
  $strongarm->value = 'D, j M Y';
  $export['date_format_short_newsroom'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__newsroom_item';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'embedded' => array(
        'custom_settings' => FALSE,
      ),
      'mini_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'popup' => array(
        'custom_settings' => FALSE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'node_on_term' => array(
        'custom_settings' => FALSE,
      ),
      'self_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'title_intro_listing' => array(
        'custom_settings' => FALSE,
      ),
      'newsroom_consultations' => array(
        'custom_settings' => TRUE,
      ),
      'newsroom_events' => array(
        'custom_settings' => TRUE,
      ),
      'newsroom_fundings' => array(
        'custom_settings' => TRUE,
      ),
      'newsroom_consultaions' => array(
        'custom_settings' => FALSE,
      ),
      'newsroom_default' => array(
        'custom_settings' => TRUE,
      ),
      'dag_node_on_term' => array(
        'custom_settings' => FALSE,
      ),
      'dag_self_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'dag_title_intro_listing' => array(
        'custom_settings' => FALSE,
      ),
      'newsroom_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'dsm_biography_teaser' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '40',
        ),
        'path' => array(
          'weight' => '20',
        ),
        'redirect' => array(
          'weight' => '30',
        ),
        'xmlsitemap' => array(
          'weight' => '30',
        ),
        'language' => array(
          'weight' => '7',
        ),
      ),
      'display' => array(
        'share_buttons' => array(
          'default' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
          'newsroom_consultations' => array(
            'weight' => '43',
            'visible' => FALSE,
          ),
          'newsroom_events' => array(
            'weight' => '47',
            'visible' => FALSE,
          ),
          'newsroom_fundings' => array(
            'weight' => '42',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '9',
            'visible' => TRUE,
          ),
          'newsroom_default' => array(
            'weight' => '46',
            'visible' => FALSE,
          ),
          'teaser' => array(
            'weight' => '2',
            'visible' => TRUE,
          ),
          'newsroom_teaser' => array(
            'weight' => '36',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__newsroom_item'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__newsroom_selection';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_sync_node_type_newsroom_selection';
  $strongarm->value = array();
  $export['i18n_sync_node_type_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_newsroom_item';
  $strongarm->value = '4';
  $export['language_content_type_newsroom_item'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_newsroom_selection';
  $strongarm->value = '4';
  $export['language_content_type_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_newsroom_selection';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_newsroom_selection';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_newsroom_selection';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_newsroom_selection';
  $strongarm->value = '0';
  $export['node_preview_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_newsroom_selection';
  $strongarm->value = 0;
  $export['node_submitted_newsroom_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_newsroom_newsletter_issue_pattern';
  $strongarm->value = 'newsroom/newsletter/[node:field-newsroom-service:field-newsroom-service-id]/[node:source:title]';
  $export['pathauto_node_newsroom_newsletter_issue_pattern'] = $strongarm;

  return $export;
}
