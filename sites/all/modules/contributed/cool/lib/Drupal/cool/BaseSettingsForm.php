<?php

namespace Drupal\cool;

abstract class BaseSettingsForm extends BaseForm {

  static public function getForm() {
    $class_name = get_called_class();
    return drupal_get_form($class_name::getId());
  }

  static public function build() {
    $form = parent::build();
    return system_settings_form($form);
  }

  static public function afterBuild($form, &$form_state) {
    return $form;
  }

  static public function validate($form, &$form_state) {
    return TRUE;
  }

  static public function submit($form, &$form_state) {
    
  }

}
