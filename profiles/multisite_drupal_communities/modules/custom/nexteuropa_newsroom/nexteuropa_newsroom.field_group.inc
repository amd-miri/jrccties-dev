<?php

/**
 * @file
 * nexteuropa_newsroom.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_newsroom_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_additional_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional information',
    'weight' => '3',
    'children' => array(
      0 => 'field_newsroom_author',
      1 => 'field_newsroom_ec_content',
      2 => 'field_newsroom_item_contact_mail',
      3 => 'field_newsroom_item_contact_text',
      4 => 'field_newsroom_item_venue',
      5 => 'field_newsroom_location',
      6 => 'field_newsroom_organiser',
      7 => 'group_newsroom_project_info',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-additional-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_additional_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_event_info|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_event_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Event information',
    'weight' => '42',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_item_speaker',
      2 => 'field_newsroom_item_venue',
      3 => 'field_newsroom_project',
      4 => 'field_newsroom_organiser',
      5 => 'field_newsroom_illustrative_img',
      6 => 'field_newsroom_private_img',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Event information',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-newsroom-event-info field-group-div section',
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_newsroom_event_info|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_basic_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_item_main_link',
      2 => 'field_newsroom_item_rapid_pr',
      3 => 'field_newsroom_item_short_title',
      4 => 'field_newsroom_newsletter_only',
      5 => 'field_newsroom_short_item',
      6 => 'field_newsroom_teaser',
      7 => 'field_newsroom_teaser_only',
      8 => 'title_field',
      9 => 'field_newsroom_publication_date',
      10 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_item_basic_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_contact|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '46',
    'children' => array(
      0 => 'field_newsroom_item_contact_mail',
      1 => 'field_newsroom_item_contact_text',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Contact',
      'instance_settings' => array(
        'classes' => 'group-newsroom-contact field-group-div',
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_newsroom_item_contact|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_context_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_context_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Context Information',
    'weight' => '8',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-newsroom-item-context-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_item_context_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_files|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '47',
    'children' => array(
      0 => 'field_newsroom_documents',
      1 => 'field_newsroom_docsroom_ids',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-files field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_files|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_full_content|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_full_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Full Content',
    'weight' => '2',
    'children' => array(
      0 => 'body',
      1 => 'field_newsroom_item_linked_obj',
      2 => 'field_newsroom_item_pre_title',
      3 => 'field_newsroom_item_quote_box',
      4 => 'field_newsroom_item_speaker',
      5 => 'field_newsroom_slide',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_item_full_content|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_links|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '44',
    'children' => array(
      0 => 'field_newsroom_project_website',
      1 => 'field_newsroom_registration_link',
      2 => 'field_newsroom_eur_lex_link',
      3 => 'field_newsroom_ted_link',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Event information',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-newsroom-links field-group-div section',
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_newsroom_item_links|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_main|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_main';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Main content',
    'weight' => '43',
    'children' => array(
      0 => 'field_newsroom_item_image',
      1 => 'field_newsroom_author',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-main field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_main|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_project|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_project';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project',
    'weight' => '45',
    'children' => array(
      0 => 'field_newsroom_project_acr',
      1 => 'field_newsroom_prj_coordinator',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-project field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_project|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_slide|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_slide';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Slide',
    'weight' => '49',
    'children' => array(
      0 => 'field_newsroom_slide',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-slide field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_slide|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_technical|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_technical';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical fields',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_id',
      1 => 'field_newsroom_item_type',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-item-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_item_technical|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_items_attachments|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_items_attachments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attachments',
    'weight' => '6',
    'children' => array(
      0 => 'field_newsroom_docsroom_ids',
      1 => 'field_newsroom_documents',
      2 => 'field_newsroom_files',
      3 => 'field_newsroom_illustrative_img',
      4 => 'field_newsroom_item_image',
      5 => 'field_newsroom_private_img',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-items-attachments field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_items_attachments|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_items_link|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_items_link';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '11',
    'children' => array(
      0 => 'field_newsroom_eur_lex_link',
      1 => 'field_newsroom_item_other_link',
      2 => 'field_newsroom_registration_link',
      3 => 'field_newsroom_ted_link',
      4 => 'path',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-items-link field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_items_link|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_lead|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_lead';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lead',
    'weight' => '40',
    'children' => array(
      0 => 'field_newsroom_teaser',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Lead',
      'instance_settings' => array(
        'classes' => 'group-newsroom-lead field-group-div',
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_newsroom_lead|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_type',
      1 => 'post_date',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'modifier' => '',
        'classes' => 'group-newsroom-meta field-group-meta_wrapper',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|newsroom_consultations';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'newsroom_consultations';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'newsroom_content_type_label',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'label' => 'Meta',
      'instance_settings' => array(
        'classes' => 'meta group-meta field-group-meta_wrapper',
        'modifier' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|newsroom_consultations'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|newsroom_default';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'newsroom_default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta data',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'newsroom_content_type_label',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'label' => 'Meta data',
      'instance_settings' => array(
        'classes' => 'meta group-meta field-group-meta_wrapper',
        'modifier' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|newsroom_default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|newsroom_events';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'newsroom_events';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta data',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_item_venue',
      2 => 'newsroom_content_type_label',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'label' => 'Meta data',
      'instance_settings' => array(
        'classes' => 'meta group-meta field-group-meta_wrapper',
        'modifier' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|newsroom_events'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|newsroom_fundings';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'newsroom_fundings';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'newsroom_content_type_label',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'label' => 'Meta',
      'instance_settings' => array(
        'classes' => 'meta group-meta field-group-meta_wrapper',
        'modifier' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|newsroom_fundings'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_meta|node|newsroom_item|newsroom_teaser';
  $field_group->group_name = 'group_newsroom_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'newsroom_teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Meta',
    'weight' => '0',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'newsroom_content_type_label',
    ),
    'format_type' => 'meta_wrapper',
    'format_settings' => array(
      'label' => 'Meta',
      'instance_settings' => array(
        'classes' => 'meta group-meta field-group-meta_wrapper',
        'modifier' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_meta|node|newsroom_item|newsroom_teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_project_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_project_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_additional_info';
  $field_group->data = array(
    'label' => 'Project information',
    'weight' => '21',
    'children' => array(
      0 => 'field_newsroom_prj_coordinator',
      1 => 'field_newsroom_project',
      2 => 'field_newsroom_project_acr',
      3 => 'field_newsroom_project_website',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-project-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_project_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_recommended|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_recommended';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended reading',
    'weight' => '48',
    'children' => array(
      0 => 'field_newsroom_item_rapid_pr',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Recommended reading',
      'instance_settings' => array(
        'classes' => 'group-newsroom-recommended field-group-div',
        'description' => '',
        'show_label' => 0,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_newsroom_recommended|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_relationships|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_relationships';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relationships',
    'weight' => '5',
    'children' => array(
      0 => 'field_newsroom_parent_content',
      1 => 'field_newsroom_related_content',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_relationships|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_technical|taxonomy_term|newsroom_item_type|form';
  $field_group->group_name = 'group_newsroom_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_item_type';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '3',
    'children' => array(
      0 => 'field_newsroom_import_name',
      1 => 'field_newsroom_type',
      2 => 'field_newsroom_type_id',
      3 => 'field_newsroom_highlighted',
      4 => 'field_newsroom_resp_person_label',
      5 => 'field_newsroom_read_more_text',
      6 => 'field_newsroom_display_date',
      7 => 'field_newsroom_direct_link',
      8 => 'field_newsroom_date_label',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-nt-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_technical|taxonomy_term|newsroom_item_type|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_technical|taxonomy_term|newsroom_service|form';
  $field_group->group_name = 'group_newsroom_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_service';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '2',
    'children' => array(
      0 => 'field_newsroom_service_id',
      1 => 'field_newsroom_service_active',
      2 => 'field_newsroom_service_type',
      3 => 'field_newsroom_topic',
      4 => 'field_newsroom_service_sample',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_technical|taxonomy_term|newsroom_service|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_technical|taxonomy_term|newsroom_topic|form';
  $field_group->group_name = 'group_newsroom_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '2',
    'children' => array(
      0 => 'field_newsroom_service_id',
      1 => 'field_newsroom_service_active',
      2 => 'field_newsroom_service_type',
      3 => 'field_newsroom_topic',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_technical|taxonomy_term|newsroom_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_topics|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_topics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Topics',
    'weight' => '4',
    'children' => array(
      0 => 'field_newsroom_highlighted_topic',
      1 => 'field_newsroom_primary_topic',
      2 => 'field_newsroom_topics',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-topics field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_topics|node|newsroom_item|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional information');
  t('Attachments');
  t('Basic Information');
  t('Contact');
  t('Context Information');
  t('Event information');
  t('Files');
  t('Full Content');
  t('Lead');
  t('Links');
  t('Main content');
  t('Meta');
  t('Meta data');
  t('Project');
  t('Project information');
  t('Recommended reading');
  t('Relationships');
  t('Slide');
  t('Technical Fields');
  t('Technical fields');
  t('Topics');

  return $field_groups;
}
