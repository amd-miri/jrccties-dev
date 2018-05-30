<?php

/**
 * Implements hook_views_plugins().
 */
function bootstrap_gallery_views_plugins() {
    $plugins = array();

    $plugins['style']['bootstrap_gallery'] = array(
        'title' => t('Bootstrap Gallery'),
        'help' => t('Renders the full views output in a responsive grid'),
        'handler' => 'views_bootstrap_gallery_plugin_style_bootstrap_gallery',
        'theme' => 'views_view_bootstrap_gallery',
        'uses fields' => FALSE,
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
    );

    return $plugins;
}