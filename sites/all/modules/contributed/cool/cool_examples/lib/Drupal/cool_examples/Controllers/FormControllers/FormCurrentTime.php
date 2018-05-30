<?php

namespace Drupal\cool_examples\Controllers\FormControllers;

class FormCurrentTime extends \Drupal\cool\BaseForm {

  static public function getId() {
    return 'cool_examples_form_current_time';
  }

  static public function build() {
    $form = parent::build();
    $form['date_format'] = array(
      '#type' => 'textfield',
      '#default_value' => 'd/m/Y',
      '#title' => 'Date format',
      '#description' => 'The date format to use when showing the date',
    );
    return $form;
  }

  static public function validate($form, &$form_state) {
    if (empty($form_state['values']['date_format'])) {
      form_set_error('date_format', 'You need to specify the date format.');
    }
  }

  static public function submit($form, &$form_state) {
    drupal_set_message('The current time is ' . date($form_state['values']['date_format'], time()));
  }

}
