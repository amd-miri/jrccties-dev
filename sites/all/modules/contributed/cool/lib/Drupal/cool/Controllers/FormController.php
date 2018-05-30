<?php

namespace Drupal\cool\Controllers;

interface FormController {

  static public function getId();
  
  static public function getForm();

  static public function build();

  static public function afterBuild($form, &$form_state);

  static public function validate($form, &$form_state);

  static public function submit($form, &$form_state);
}
