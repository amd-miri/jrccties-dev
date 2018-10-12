<?php
/**
 * @file
 * Declares the Views plugin for paging.
 */

/**
 * Declares the pager block display.
 * @return type 
 */
function freepager_views_plugins() {
  return array(
    'display' => array(
      'freepager' => array(
        'title' => t('Pager block'),
        'help' => t('Uses the available fields to build a pager.'),
        'handler' => 'freepager_plugin_display_pagerblock',
        'theme' => 'views_freepager',
        'uses hook block' => TRUE,
        'contextual links locations' => array('block'),
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'use more' => FALSE,
        'accept attachments' => TRUE,
        'admin' => t('Free Pager block'),
      ),
    ),
  );
}
