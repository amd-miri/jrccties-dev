<?php

/**
 * @file
 * Definition of simplenews_statistics_handler_clicks.
 */

/**
 * Description.
 */
class simplenews_statistics_handler_clicks extends views_handler_field {
  /**
   * Add some required fields needed on render().
   */
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = array(
      'table' => 'node',
      'field' => 'nid',
    );
  }

  /**
   * Loads additional fields.
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Default options form.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['ctr_precision'] = array('default' => '0');

    return $options;
  }

  /**
   * Creates the form item for the options added.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if ($this->real_field == 'ctr') {
      $form['ctr_precision'] = array(
        '#type' => 'textfield',
        '#title' => t('Precision'),
        '#default_value' => $this->options['ctr_precision'],
        '#description' => t('Number of decimal places to which the click-through rate should be calculated.'),
      );
    }
  }

  /**
   * Renders the field handler.
   */
  function render($values) {
    $field = $this->real_field;
    $precision = intval($this->options['ctr_precision']);
    $unique_opens = simplenews_statistics_count_opens($values->nid, TRUE);

    if ($field == 'click_count') {
      $click_count =  simplenews_statistics_count_clicks($values->nid);
    }
    else {
      $click_count = simplenews_statistics_count_clicks($values->nid, TRUE);
    }

    if ($field == 'ctr' && $unique_opens > 0) {
      return round($click_count / $unique_opens * 100, $precision) . '%';
    }
    elseif ($field == 'ctr' && $unique_opens == 0) {
      return t('N/A');
    }

    return $click_count;
  }

}
