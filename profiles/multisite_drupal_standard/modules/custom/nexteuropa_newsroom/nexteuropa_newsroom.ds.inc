<?php

/**
 * @file
 * nexteuropa_newsroom.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function nexteuropa_newsroom_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_consultations';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_consultations';
  $ds_fieldsetting->settings = array(
    'dsm_newsroom_related_policies' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'dsm_content_types_of_information' => array(
      'weight' => '16',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '8',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'newsroom_share_block' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'newsroom_content_type_label' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'hidden',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => '',
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_illustrative_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'p',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
    'field_newsroom_private_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_consultations'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_default';
  $ds_fieldsetting->settings = array(
    'dsm_newsroom_related_policies' => array(
      'weight' => '22',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '17',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'dsm_content_types_of_information' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '7',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'newsroom_share_block' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'newsroom_content_type_label' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'hidden',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => '',
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_illustrative_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'p',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
    'field_newsroom_private_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_events';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_events';
  $ds_fieldsetting->settings = array(
    'dsm_newsroom_related_policies' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'dsm_content_types_of_information' => array(
      'weight' => '20',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'newsroom_share_block' => array(
      'weight' => '20',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_content_type_label' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'hidden',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_contact_mail' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Contact information',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => '',
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-col' => TRUE,
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
        ),
      ),
    ),
    'field_newsroom_item_speaker' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_venue' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_location' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Location / Map',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_illustrative_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'p',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
    'field_newsroom_private_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_events'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_fundings';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_fundings';
  $ds_fieldsetting->settings = array(
    'dsm_newsroom_related_policies' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'dsm_content_types_of_information' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '8',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'newsroom_share_block' => array(
      'weight' => '16',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_content_type_label' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'hidden',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => '',
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-col' => TRUE,
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_illustrative_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'p',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
    'field_newsroom_private_img' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_fundings'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h3',
        'class' => 'listing__title',
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_content_type_label' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'hidden',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => '',
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'p',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
          'fi-first-last' => FALSE,
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function nexteuropa_newsroom_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'newsroom_related_documents';
  $ds_field->label = 'Newsroom page : Related documents';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|39e10d54fad34071dca96fe7d7133f38',
    'block_render' => '1',
  );
  $export['newsroom_related_documents'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'newsroom_share_block';
  $ds_field->label = 'Newsroom share block';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'nexteuropa_newsroom|newsroom_share_block',
    'block_render' => '1',
  );
  $export['newsroom_share_block'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function nexteuropa_newsroom_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_consultations';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_consultations';
  $ds_layout->layout = 'ne_entity_three_col';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'dsm_newsroom_related_policies',
        18 => 'dsm_content_types_of_information',
        19 => 'group_related_policies',
      ),
      'left_header' => array(
        1 => 'newsroom_content_type_label',
        2 => 'group_newsroom_meta',
        3 => 'title',
        4 => 'field_newsroom_item_date',
      ),
      'central' => array(
        5 => 'field_newsroom_teaser',
        6 => 'field_newsroom_illustrative_img',
        7 => 'field_newsroom_private_img',
        8 => 'field_newsroom_item_quote_box',
        9 => 'body',
        10 => 'newsroom_related_documents',
        11 => 'field_newsroom_docsroom_ids',
        12 => 'field_newsroom_item_linked_obj',
        13 => 'field_newsroom_item_other_link',
        14 => 'field_newsroom_ted_link',
        15 => 'field_newsroom_item_main_link',
        16 => 'ds_nr_related_content',
        17 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'dsm_newsroom_related_policies' => 'right',
      'newsroom_content_type_label' => 'left_header',
      'group_newsroom_meta' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_ted_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'newsroom_share_block' => 'central',
      'dsm_content_types_of_information' => 'right',
      'group_related_policies' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'bottom_header' => 'div',
      'top' => 'div',
      'left' => 'div',
      'central' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|newsroom_item|newsroom_consultations'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_default';
  $ds_layout->layout = 'ne_entity_three_col';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'group_newsroom_meta',
        1 => 'newsroom_content_type_label',
        2 => 'title',
        3 => 'field_newsroom_item_date',
      ),
      'central' => array(
        4 => 'field_newsroom_teaser',
        5 => 'field_newsroom_illustrative_img',
        6 => 'field_newsroom_private_img',
        7 => 'field_newsroom_item_quote_box',
        8 => 'body',
        9 => 'newsroom_related_documents',
        10 => 'field_newsroom_docsroom_ids',
        11 => 'field_newsroom_item_linked_obj',
        12 => 'field_newsroom_item_other_link',
        13 => 'field_newsroom_project',
        14 => 'field_newsroom_prj_coordinator',
        15 => 'field_newsroom_project_acr',
        16 => 'field_newsroom_project_website',
        17 => 'field_newsroom_ted_link',
        18 => 'field_newsroom_item_main_link',
        19 => 'ds_nr_related_content',
        20 => 'newsroom_share_block',
        24 => 'field_newsroom_item_contact_mail',
      ),
      'right' => array(
        21 => 'dsm_content_types_of_information',
        22 => 'group_related_policies',
        23 => 'dsm_newsroom_related_policies',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'left_header',
      'newsroom_content_type_label' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_project' => 'central',
      'field_newsroom_prj_coordinator' => 'central',
      'field_newsroom_project_acr' => 'central',
      'field_newsroom_project_website' => 'central',
      'field_newsroom_ted_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'newsroom_share_block' => 'central',
      'dsm_content_types_of_information' => 'right',
      'group_related_policies' => 'right',
      'dsm_newsroom_related_policies' => 'right',
      'field_newsroom_item_contact_mail' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'bottom_header' => 'div',
      'top' => 'div',
      'left' => 'div',
      'central' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|newsroom_item|newsroom_default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_event';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_event';
  $ds_layout->layout = 'ne_entity_three_col';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'field_newsroom_item_date',
        1 => 'field_newsroom_item_type',
        2 => 'field_newsroom_item_quote_box',
        3 => 'field_newsroom_item_venue',
        4 => 'body',
        5 => 'field_newsroom_organiser',
        6 => 'field_newsroom_item_contact_mail',
        7 => 'field_newsroom_location',
        8 => 'field_newsroom_registration_link',
        9 => 'field_newsroom_item_linked_obj',
        10 => 'field_newsroom_documents',
        11 => 'share_buttons',
        12 => 'field_newsroom_docsroom_ids',
        13 => 'field_newsroom_item_other_link',
        14 => 'field_newsroom_item_main_link',
        15 => 'field_newsroom_item_contact_text',
        16 => 'field_newsroom_files',
        17 => 'field_newsroom_teaser',
        18 => 'field_newsroom_illustrative_img',
        19 => 'field_newsroom_private_img',
        20 => 'title_field',
        21 => 'field_newsroom_related_content',
        22 => 'field_newsroom_author',
        23 => 'field_newsroom_parent_content',
        24 => 'field_newsroom_primary_topic',
        25 => 'field_newsroom_teaser_only',
        26 => 'field_newsroom_topics',
        27 => 'field_newsroom_short_item',
        28 => 'field_newsroom_newsletter_only',
        29 => 'field_newsroom_project',
        30 => 'field_newsroom_project_acr',
        31 => 'field_newsroom_ec_content',
        32 => 'field_newsroom_eur_lex_link',
        33 => 'field_newsroom_ted_link',
        34 => 'field_newsroom_project_website',
        35 => 'field_newsroom_slide',
        36 => 'field_newsroom_prj_coordinator',
        37 => 'field_newsroom_highlighted_topic',
        38 => 'field_newsroom_item_pre_title',
        39 => 'field_newsroom_item_image',
        40 => 'field_newsroom_item_id',
        41 => 'field_newsroom_item_rapid_pr',
        43 => 'field_newsroom_item_short_title',
        44 => 'field_newsroom_item_speaker',
      ),
    ),
    'fields' => array(
      'field_newsroom_item_date' => 'left_header',
      'field_newsroom_item_type' => 'left_header',
      'field_newsroom_item_quote_box' => 'left_header',
      'field_newsroom_item_venue' => 'left_header',
      'body' => 'left_header',
      'field_newsroom_organiser' => 'left_header',
      'field_newsroom_item_contact_mail' => 'left_header',
      'field_newsroom_location' => 'left_header',
      'field_newsroom_registration_link' => 'left_header',
      'field_newsroom_item_linked_obj' => 'left_header',
      'field_newsroom_documents' => 'left_header',
      'share_buttons' => 'left_header',
      'field_newsroom_docsroom_ids' => 'left_header',
      'field_newsroom_item_other_link' => 'left_header',
      'field_newsroom_item_main_link' => 'left_header',
      'field_newsroom_item_contact_text' => 'left_header',
      'field_newsroom_files' => 'left_header',
      'field_newsroom_teaser' => 'left_header',
      'field_newsroom_illustrative_img' => 'left_header',
      'field_newsroom_private_img' => 'left_header',
      'title_field' => 'left_header',
      'field_newsroom_related_content' => 'left_header',
      'field_newsroom_author' => 'left_header',
      'field_newsroom_parent_content' => 'left_header',
      'field_newsroom_primary_topic' => 'left_header',
      'field_newsroom_teaser_only' => 'left_header',
      'field_newsroom_topics' => 'left_header',
      'field_newsroom_short_item' => 'left_header',
      'field_newsroom_newsletter_only' => 'left_header',
      'field_newsroom_project' => 'left_header',
      'field_newsroom_project_acr' => 'left_header',
      'field_newsroom_ec_content' => 'left_header',
      'field_newsroom_eur_lex_link' => 'left_header',
      'field_newsroom_ted_link' => 'left_header',
      'field_newsroom_project_website' => 'left_header',
      'field_newsroom_slide' => 'left_header',
      'field_newsroom_prj_coordinator' => 'left_header',
      'field_newsroom_highlighted_topic' => 'left_header',
      'field_newsroom_item_pre_title' => 'left_header',
      'field_newsroom_item_image' => 'left_header',
      'field_newsroom_item_id' => 'left_header',
      'field_newsroom_item_rapid_pr' => 'left_header',
      'field_newsroom_item_short_title' => 'left_header',
      'field_newsroom_item_speaker' => 'left_header',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
    'layout_link_attribute' => FALSE,
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|newsroom_event'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_events';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_events';
  $ds_layout->layout = 'ne_entity_three_col';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'dsm_newsroom_related_policies',
        23 => 'dsm_content_types_of_information',
        25 => 'group_related_policies',
      ),
      'left_header' => array(
        1 => 'group_newsroom_meta',
        2 => 'newsroom_content_type_label',
        3 => 'title',
        4 => 'field_newsroom_item_venue',
        6 => 'field_newsroom_item_date',
      ),
      'central' => array(
        5 => 'field_newsroom_teaser',
        7 => 'field_newsroom_illustrative_img',
        8 => 'field_newsroom_private_img',
        9 => 'field_newsroom_item_quote_box',
        10 => 'body',
        11 => 'field_newsroom_item_speaker',
        12 => 'field_newsroom_organiser',
        13 => 'field_newsroom_item_contact_mail',
        14 => 'newsroom_related_documents',
        15 => 'field_newsroom_docsroom_ids',
        16 => 'field_newsroom_item_linked_obj',
        17 => 'field_newsroom_item_other_link',
        18 => 'field_newsroom_location',
        19 => 'field_newsroom_ted_link',
        20 => 'field_newsroom_registration_link',
        21 => 'field_newsroom_item_main_link',
        22 => 'ds_nr_related_content',
        24 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'dsm_newsroom_related_policies' => 'right',
      'group_newsroom_meta' => 'left_header',
      'newsroom_content_type_label' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_venue' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_item_date' => 'left_header',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'field_newsroom_item_speaker' => 'central',
      'field_newsroom_organiser' => 'central',
      'field_newsroom_item_contact_mail' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_location' => 'central',
      'field_newsroom_ted_link' => 'central',
      'field_newsroom_registration_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'dsm_content_types_of_information' => 'right',
      'newsroom_share_block' => 'central',
      'group_related_policies' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'bottom_header' => 'div',
      'top' => 'div',
      'left' => 'div',
      'central' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|newsroom_item|newsroom_events'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_fundings';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_fundings';
  $ds_layout->layout = 'ne_entity_three_col';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'dsm_newsroom_related_policies',
        18 => 'dsm_content_types_of_information',
        19 => 'group_related_policies',
      ),
      'left_header' => array(
        1 => 'newsroom_content_type_label',
        2 => 'group_newsroom_meta',
        3 => 'title',
        4 => 'field_newsroom_item_date',
      ),
      'central' => array(
        5 => 'field_newsroom_teaser',
        6 => 'field_newsroom_private_img',
        7 => 'field_newsroom_illustrative_img',
        8 => 'field_newsroom_item_quote_box',
        9 => 'body',
        10 => 'newsroom_related_documents',
        11 => 'field_newsroom_docsroom_ids',
        12 => 'field_newsroom_item_linked_obj',
        13 => 'field_newsroom_ted_link',
        14 => 'field_newsroom_item_other_link',
        15 => 'field_newsroom_item_main_link',
        16 => 'field_newsroom_item_contact_mail',
        17 => 'ds_nr_related_content',
        20 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'dsm_newsroom_related_policies' => 'right',
      'newsroom_content_type_label' => 'left_header',
      'group_newsroom_meta' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_ted_link' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'field_newsroom_item_contact_mail' => 'central',
      'ds_nr_related_content' => 'central',
      'dsm_content_types_of_information' => 'right',
      'group_related_policies' => 'right',
      'newsroom_share_block' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'bottom_header' => 'div',
      'top' => 'div',
      'left' => 'div',
      'central' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|newsroom_item|newsroom_fundings'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_teaser';
  $ds_layout->layout = 'ne_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'group_newsroom_meta',
        1 => 'newsroom_content_type_label',
        2 => 'field_newsroom_item_date',
        3 => 'title',
        4 => 'field_newsroom_teaser',
        5 => 'node_link',
      ),
      'second' => array(
        6 => 'field_newsroom_illustrative_img',
        7 => 'field_newsroom_private_img',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'main',
      'newsroom_content_type_label' => 'main',
      'field_newsroom_item_date' => 'main',
      'title' => 'main',
      'field_newsroom_teaser' => 'main',
      'node_link' => 'main',
      'field_newsroom_illustrative_img' => 'second',
      'field_newsroom_private_img' => 'second',
    ),
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'second' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|newsroom_item|newsroom_teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ne_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'main' => array(
        0 => 'share_buttons',
      ),
    ),
    'fields' => array(
      'share_buttons' => 'main',
    ),
    'classes' => array(),
    'wrappers' => array(
      'main' => 'div',
      'second' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|teaser'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function nexteuropa_newsroom_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_consultations';
  $ds_view_mode->label = 'Newsroom consultations';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_consultations'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_default';
  $ds_view_mode->label = 'Newsroom default';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_default'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_events';
  $ds_view_mode->label = 'Newsroom events';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_events'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_fundings';
  $ds_view_mode->label = 'Newsroom fundings';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_fundings'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_teaser';
  $ds_view_mode->label = 'Newsroom teaser';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_teaser'] = $ds_view_mode;

  return $export;
}
