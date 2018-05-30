<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the configure field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_configure extends views_handler_field {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_configure_link'] = array('default' => FALSE);

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_configure_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link this field to the main configuration page of the module'),
      '#description' => t('This will override any other link you have set.'),
      '#default_value' => !empty($this->options['system_info_configure_link']),
    );
  }


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    return isset($info['configure']) ? $this->render_link($info, $values) : '';
  }


  function render_link($data, $values) {

    if (!empty($this->options['system_info_configure_link']) && $data !== NULL && $data !== '') {

      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $data['configure'];
    }

    return $data['configure'];
  }
}
