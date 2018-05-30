<?php

namespace Drupal\cool;

abstract class BaseForm implements Controllers\FormController {

  static public function getId() {
    throw new \Exception('You need to implement the getId() method');
  }

  static public function getForm() {
    $class_name = get_called_class();
    return drupal_get_form($class_name::getId());
  }

  static public function build() {
    $form = array();
    $form['cool_class_name'] = array(
      '#type' => 'hidden',
      '#value' => get_called_class()
    );
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#weight' => 5,
    );
    $form['#validate'] = array('cool_default_form_validate');
    $form['#submit'] = array('cool_default_form_submit');
    return $form;
  }

  static public function afterBuild($form, &$form_state) {
    return $form;
  }

  static public function validate($form, &$form_state) {
    return TRUE;
  }

  static public function submit($form, &$form_state) {
    throw new \Exception('You need to implement the submit() method');
  }

}
