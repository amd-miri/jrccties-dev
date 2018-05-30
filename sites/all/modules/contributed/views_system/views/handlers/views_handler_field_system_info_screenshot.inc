<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Provides display options and renders the screenshot field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_screenshot extends views_handler_field {


  function option_definition() {

    $options = parent::option_definition();

    $options['system_info_screenshot_image'] = array('default' => TRUE);
    $options['system_info_screenshot_image_class'] = array('default' => 'views-system-screenshot-medium');

    return $options;
  }


  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['system_info_screenshot_image'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display as image'),
      '#default_value' => !empty($this->options['system_info_screenshot_image']),
    );
    $form['system_info_screenshot_image_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Image class'),
      '#description' => t('The CSS class to apply to the image. Default classes: views-system-screenshot-large, views-system-screenshot-medium, views-system-screenshot-small.'),
      '#default_value' => !empty($this->options['system_info_screenshot_image_class']) ? $this->options['system_info_screenshot_image_class'] : 'views-system-screenshot-medium',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-options-system-info-screenshot-image' => array(1),
      ),
    );
  }


  function render($values) {

    $info = unserialize($values->{$this->field_alias});

    if (isset($info['screenshot'])) {

      $path = _views_system_get_screenshot($info);
      if ($path) {

        if ($this->options['system_info_screenshot_image']) {

          drupal_add_css(drupal_get_path('module', 'views_system') . '/styles/views-system-screenshot.css', array('preprocess' => FALSE));

          $screenshot = array();
          $screenshot['path'] = $path;
          $screenshot['alt'] = t('Screenshot for !theme theme', array('!theme' => $info['name']));
          $screenshot['title'] = t('Screenshot for !theme theme', array('!theme' => $info['name']));
          $screenshot['attributes'] = array('class' => check_plain($this->options['system_info_screenshot_image_class']));

          $output = theme('image', $screenshot);
        }
        else {
          $output = $path;
        }
      }
      else {
        $output = '';
      }
    }
    else {
      $output = '';
    }

    return $output;
  }
}
