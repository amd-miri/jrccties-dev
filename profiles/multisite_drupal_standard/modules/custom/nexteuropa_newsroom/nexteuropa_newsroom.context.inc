<?php

/**
 * @file
 * nexteuropa_newsroom.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_newsroom_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_agenda_search_block';
  $context->description = 'Newsroom agenda page';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'newsroom-agenda' => 'newsroom-agenda',
        'newsroom-agenda/*' => 'newsroom-agenda/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'nexteuropa_newsroom-newsroom_agenda_search_block' => array(
          'module' => 'nexteuropa_newsroom',
          'delta' => 'newsroom_agenda_search_block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Newsroom agenda page');
  t('newsroom');
  $export['newsroom_agenda_search_block'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_item';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'newsroom_item' => 'newsroom_item',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'nexteuropa_newsroom-newsroom_admin_tools' => array(
          'module' => 'nexteuropa_newsroom',
          'delta' => 'newsroom_admin_tools',
          'region' => 'content',
          'weight' => '49',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');
  $export['newsroom_item'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_page_search_block';
  $context->description = 'Newsroom page';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'newsroom' => 'newsroom',
        'newsroom/*' => 'newsroom/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'nexteuropa_newsroom-newsroom_page_search_block' => array(
          'module' => 'nexteuropa_newsroom',
          'delta' => 'newsroom_page_search_block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Newsroom page');
  t('newsroom');
  $export['newsroom_page_search_block'] = $context;

  return $export;
}
