<?php
/**
 * @file
 * Contains the block display plugin.
 */

/**
 * The plugin that handles a block.
 *
 * @ingroup views_display_plugins
 */
class freepager_plugin_display_pagerblock extends views_plugin_display_block {
  function option_definition() {
    $options = parent::option_definition();

    foreach (array_keys(freepager_settings()) as $setting_name) {
      $options[$setting_name] = array('default' => FALSE);
    }

    return $options;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    // Remove the category set by the parent class before adding our own.
    unset($categories['block']);
    $categories['freepager_block'] = array(
      'title' => t('Pager block settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    $options['block_description']['category'] = 'freepager_block';

    // Get all the fields present in this view, to use as setting summaries.
    $field_labels = $this->get_field_labels();
    foreach (freepager_settings() as $name => $setting) {
      $options[$name] = array(
        'category' => 'freepager_block',
        'title' => $setting['label'],
        'value' => isset($field_labels[$this->get_option($name)]) ? $field_labels[$this->get_option($name)] : t('(none)'),
      );
    }

    // The 'loop' option is treated differently. It isn't a field select list.
    $yesno = array(0 => t('no'), 1 => t('yes'));
    $options['loop']['value'] = $yesno[$this->get_option($name)];
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    // Set some variables to increase code readability.
    $freepager_settings = freepager_settings();
    $section = &$form_state['section'];

    // If one of Free pager's settings are built, populate the form.
    if (isset($freepager_settings[$section])) {
      $form['#title'] .= $freepager_settings[$section]['label'];
      $form[$section] = array(
        '#type' => 'select',
        '#description' => $freepager_settings[$section]['description'],
        '#options' => array(FALSE => t('(none)')) + $this->get_field_labels(),
        '#default_value' => $this->get_option($section),
      );

      // The 'loop' setting should be treated differently. It's a check box.
      if ($section == 'loop') {
        $form[$section] = array(
          '#type' => 'checkbox',
          '#title' => $freepager_settings['loop']['label'],
          '#description' => $freepager_settings[$section]['description'],
          '#default_value' => $this->get_option($section),
        );
      }
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);

    // Set some variables to increase code readability.
    $freepager_settings = freepager_settings();
    $section = &$form_state['section'];

    // If one of Free pager's settings are submitted, make sure to save them.
    if (isset($freepager_settings[$section])) {
      $this->set_option($section, $form_state['values'][$section]);
    }
  }
}
