<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the project field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_project extends views_handler_field {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_project_link'] = array('default' => FALSE);
    $options['system_info_project_link_path'] = array('default' => 'http://drupal.org/project/[project]');

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_project_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link this field to its drupal.org project page'),
      '#description' => t('This will override any other link you have set.'),
      '#default_value' => !empty($this->options['system_info_project_link']),
    );
    $form['system_info_project_link_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Link path'),
      '#description' => t('URL of the drupal.org project page. Replacement patterns: [project]'),
      '#default_value' => !empty($this->options['system_info_project_link_path']) ? $this->options['system_info_project_link_path'] : 'http://drupal.org/project/[project]',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-options-system-info-project-link' => array(1),
      ),
    );
  }


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    return isset($info['project']) ? $this->render_link($info, $values) : '';
  }


  function render_link($data, $values) {

    if (!empty($this->options['system_info_project_link']) && $data !== NULL && $data !== '') {

      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = strtr($this->options['system_info_project_link_path'], array('[project]' => $data['project']));
    }

    return $data['project'];
  }
}
