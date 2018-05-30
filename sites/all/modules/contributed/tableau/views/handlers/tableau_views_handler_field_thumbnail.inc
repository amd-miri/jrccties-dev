<?php

/**
 * @file
 * Definition of tableau_views_handler_field_thumbnail.
 */

/**
 * Displays a pre-rendered thumbnail of the view.
 *
 * @ingroup views_field_handlers
 */
class tableau_views_handler_field_thumbnail extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['width'] = array('default' => '192');
    $options['height'] = array('default' => '');
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
  }

  function render($values) {
    $entity = tableau_view_load($this->get_value($values));
    $options = array(
      'view' => $entity,
      'width' => $this->options['width'],
      'height' => $this->options['height'],
    );
    return theme('tableau_view_thumbnail', $options);
  }
}
