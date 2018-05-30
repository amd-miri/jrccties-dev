<?php

/**
 * @file
 * Contains the tableau view row style plugin.
 */

/**
 * Plugin which performs a tableau_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 *
 * @ingroup views_row_plugins
 */
class tableau_views_plugin_row_tableau_view extends views_plugin_row {
  // Basic properties that let the row style follow relationships.
  var $base_table = '_views';
  var $base_field = 'id';

  // Stores the nodes loaded with pre_render.
  var $views = array();

  function option_definition() {
    $options = parent::option_definition();

    $options['width'] = array('default' => '960px');
    $options['height'] = array('default' => '960px');
    $options['format'] = array('default' => 'static');
    $options['tabs'] = array('default' => 'no');
    $options['toolbar'] = array('default' => 'no');
    $options['render'] = array('default' => 'default');
    $options['render_threshold'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('View width'),
      '#default_value' => $this->options['width'],
      '#description' => t('Width of the Tableau view.'),
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('View height'),
      '#default_value' => $this->options['height'],
      '#description' => t('Height of the Tableau view. <em>Leave empty to retain aspect ratio.</em>'),
    );
    $form['format'] = array(
      '#type' => 'radios',
      '#title' => t('Display format'),
      '#options' => array(
        'static' => t('Static image'),
        'interactive' => t('Interactive'),
        'thumbnail' => t('Thumbnail'),
      ),
      '#default_value' => $this->options['format'],
      '#description' => t('Whether the Tableau view should be interactive or just a thumbnail.'),
    );
    $form['tabs'] = array(
      '#type' => 'radios',
      '#title' => t('View tabs'),
      '#options' => array(
        'yes' => t('Enabled'),
        'no' => t('Disabled'),
      ),
      '#default_value' => $this->options['tabs'],
      '#description' => t('Whether the Tableau view should display tabs. <em>Ignored when using <strong>Static</strong> format.</em>'),
    );
    $form['toolbar'] = array(
      '#type' => 'radios',
      '#title' => t('View toolbar'),
      '#options' => array(
        'yes' => t('Enabled'),
        'no' => t('Disabled'),
      ),
      '#default_value' => $this->options['toolbar'],
      '#description' => t('Whether the Tableau view should display a toolbar. <em>Ignored when using <strong>Static</strong> format.</em>'),
    );
    $form['render'] = array(
      '#type' => 'radios',
      '#title' => t('Browser rendering'),
      '#options' => array(
        'default' => t('Default (based on Tableau server configuration)'),
        'true' => t('Force client-side'),
        'false' => t('Force server-side'),
        'threshold' => t('Custom threshold'),
      ),
      '#default_value' => $this->options['render'],
      '#description' => t('Determine what type of rendering methodology to use, or set a custom threshold for automatic switching.<br /><em>Refer to !link for more information on browser rendering.</em>', array('!link' => l('this link', 'http://onlinehelp.tableausoftware.com/current/server/en-us/browser_rendering.htm'))),
    );
    $form['render_threshold'] = array(
      '#type' => 'textfield',
      '#title' => t('Browser rendering threshold'),
      '#default_value' => $this->options['render_threshold'],
      '#description' => t('Determine the threshold at which a Tableau view will render on the client versus the server.<br /><em>Only applies to the <strong>custom threshold</strong> above.'),
    );
  }

  function pre_render($values) {
    $ids = array();
    foreach ($values as $row) {
      $ids[] = $row->{$this->field_alias};
    }
    $this->views = tableau_view_load_multiple($ids);
  }

  function render($row) {
    if (isset($this->views[$row->{$this->field_alias}])) {
      $entity = $this->views[$row->{$this->field_alias}];
      $options = array(
        'format' => $this->options['format'],
        'width' => $this->options['width'],
        'height' => $this->options['height'],
        'view' => $entity,
        'tabs' => $this->options['tabs'],
        'toolbar' => $this->options['toolbar'],
        'render' => $this->options['render'],
        'render_threshold' => $this->options['render_threshold'],
      );
      return theme('tableau_view', $options);
    }
  }
}
