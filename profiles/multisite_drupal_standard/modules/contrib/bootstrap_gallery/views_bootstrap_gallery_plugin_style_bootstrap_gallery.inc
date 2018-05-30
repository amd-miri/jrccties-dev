<?php

/**
 * @file
 * Contains the Bootstrap Gallery style plugin.
 */

/**
 * Style plugin to render each item in an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class views_bootstrap_gallery_plugin_style_bootstrap_gallery extends views_plugin_style_grid {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['image_field'] = array('default' => '');
    $options['image_title'] = array('default' => 'default');
    $options['controls'] = array('default' => false);
    $options['borderless'] = array('default' => false);
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

      // Flatten options to deal with the various hierarchy changes.
      $options = bootstrap_gallery_get_options($this->options);

      $form['bootstrap_gallery'] = array(
          '#type' => 'fieldset',
          '#title' => t('Bootstrap Gallery'),
          '#description' => t('Display options for bootstrap gallery.'),
          '#collapsible' => TRUE,
          '#weight' => -10,
      );
      $form['bootstrap_gallery']['image_field'] = array(
          '#type' => 'select',
          '#title' => t('Image Field'),
          '#default_value' => $options['image_field'],
          '#options' => $this->display->handler->get_field_labels(),
          '#description' => t('Field that contains image or thumbnail to be used with Bootstrap Gallery.'),
          '#required' => TRUE,
      );
      $form['bootstrap_gallery']['image_style'] = array(
        '#type' => 'select',
        '#title' => t('Image Style'),
        '#default_value' => $options['image_style'],
        '#options' => bootstrap_gallery_image_styles(),
        '#description' => t('Image Style preset to be used for rendering the full image.'),
        '#required' => TRUE,
      );

      $form['bootstrap_gallery']['image_title'] = array(
          '#type' => 'select',
          '#title' => t('Image Title'),
          '#default_value' => $options['image_title'],
          '#options' => array('default' => 'HTML title attribute') + $this->display->handler->get_field_labels(),
          '#description' => t('Source of headline text to be displayed as a title for the image'),
          '#required' => TRUE,
      );

      $form['bootstrap_gallery']['controls'] = array(
          '#type' => 'checkbox',
          '#title' => t('Display controls'),
          '#default_value' => $options['controls'],
          '#options' => array(TRUE, FALSE),
          '#description' => t('Display Bootstrap Carousel Controls.'),
      );

      $form['bootstrap_gallery']['borderless'] = array(
          '#type' => 'checkbox',
          '#title' => t('Borderless overlay'),
          '#default_value' => $options['borderless'],
          '#options' => array(TRUE, FALSE),
          '#description' => t('Disable Bootstrap Modal. Display a full page gallery.'),
      );

  }

    /**
     * Validate option form.
     */

    function options_validate(&$form, &$form_state) {
        // Don't run validation on style plugins without the grouping setting.
        if (isset($form_state['values']['style_options']['bootstrap_gallery'])
            && $options = $form_state['values']['style_options']['bootstrap_gallery']) {

            $image_field = $options['image_field'];
            $field_info = field_info_field($image_field);

            $allowed_field_types = array('image', 'file');

            if(!in_array($field_info['type'], $allowed_field_types)) {
                form_set_error('style_options[bootstrap_gallery][image_field]', t('Selected image field must be of type: Image'));
            }
        }
    }
}
