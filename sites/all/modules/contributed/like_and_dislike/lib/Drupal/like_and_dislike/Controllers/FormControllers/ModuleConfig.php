<?php

namespace Drupal\like_and_dislike\Controllers\FormControllers;

class ModuleConfig extends \Drupal\cool\BaseForm {

  static public function getId() {
    return 'like_and_dislike_admin_page';
  }

  /**
   * Implementation of the configuration page.
   * It allows to change the vote denied message
   */
  static public function build() {
    $form = parent::build();

    $entity_types = entity_get_info();

    $form['like_and_dislike_vote_types_enabled'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#title' => t('Entity types with Like & Dislike widgets enabled:'),
      '#description' => t('If you disable any type here, already existing data will remain untouched.'),
    );
    foreach ($entity_types as $entity_type) {
      if(!in_array($entity_type['base table'], \Drupal\like_and_dislike\Model\Entity::$available_entity_types)) {
        continue;
      }
      foreach ($entity_type['bundles'] as $key => $bundle) {
        $form['like_and_dislike_vote_types_enabled']['like_and_dislike_vote_' . $key . '_available'] = array(
          '#type' => 'checkbox',
          '#title' => $bundle['label'],
          '#default_value' => variable_get('like_and_dislike_vote_' . $key . '_available', 0),
        );
      }
    }
    $form['like_and_dislike_vote_denied_messages'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Vote denied messages for each entity type'),
      '#description' => t("This is the message that the user will see if doesn't have permission to vote on the specified type:"),
    );
    foreach ($entity_types as $entity_type) {
      if(!in_array($entity_type['base table'], \Drupal\like_and_dislike\Model\Entity::$available_entity_types)) {
        continue;
      }
      foreach ($entity_type['bundles'] as $key => $bundle) {
        $form['like_and_dislike_vote_denied_messages']['like_and_dislike_vote_' . $key . '_denied_msg'] = array(
          '#type' => 'textfield',
          '#title' => $bundle['label'],
          '#default_value' => variable_get('like_and_dislike_vote_' . $key . '_denied_msg', "You don't have permission to vote"),
        );
      }
    }
    return system_settings_form($form);
  }

  static public function validate($form, &$form_state) {
    
  }

  static public function submit($form, &$form_state) {
    
  }

}
