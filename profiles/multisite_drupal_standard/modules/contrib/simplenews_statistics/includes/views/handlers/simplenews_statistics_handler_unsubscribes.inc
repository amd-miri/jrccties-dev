<?php

/**
 * @file
 * Definition of simplenews_statistics_handler_unsubscribes.
 */

/**
 * Description.
 */
class simplenews_statistics_handler_unsubscribes extends views_handler_field {
  /**
   * Add some required fields needed on render().
   */
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = array(
      'table' => 'node',
      'field' => 'nid',
    );
    $this->additional_fields['send_start_timestamp'] = array(
      'table' => 'simplenews_statistics',
      'field' => 'send_start_timestamp',
    );
    $this->additional_fields['tid'] = array(
      'table' => 'simplenews_newsletter',
      'field' => 'tid',
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

    $options['number'] = array('default' => TRUE);
    $options['percentage'] = array('default' => TRUE);
    $options['precision'] = array('default' => '0');
    $options['source'] = array('default' => '');

    return $options;
  }

  /**
   * Creates the form item for the options added.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);


    $form['number'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show count'),
      '#default_value' => $this->options['number'],
      '#description' => t('Show the number of bounces for this newsletter.'),
    );

    $form['percentage'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show percentage'),
      '#default_value' => $this->options['percentage'],
      '#description' => t('Show the bounce rate as a percentage.'),
    );

    $form['precision'] = array(
      '#type' => 'textfield',
      '#title' => t('Precision'),
      '#default_value' => $this->options['precision'],
      '#description' => t('Number of decimal places to which the bounce rate should be calculated.'),
      '#states' => array(
        'invisible' => array(
          ':input[name="options[percentage]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['source'] = array(
      '#type' => 'textfield',
      '#title' => t('Source'),
      '#default_value' => $this->options['source'],
      '#description' => t('Specify the source from which to count unsubscribes. E.g. <em>unknown</em>, <em>website</em>, <em>mass unsubscribe</em>, <em>bounce</em>. Sources are defined by the module that cause the user to be unsubscribed. Leave this blank unless you know specifically what you are looking for.'),
    );
  }

  /**
   * Renders the field handler.
   */
  function render($values) {
    $subscribers = $values->simplenews_newsletter_sent_subscriber_count;
    $start = $values->simplenews_statistics_send_start_timestamp;
    $tid = $values->simplenews_newsletter_tid;
    $number = $this->options['number'];
    $percentage = $this->options['percentage'];
    $precision = intval($this->options['precision']);
    $source = $this->options['source'];

    if ($start == 0) {
      return 'N/A'; // Newsletter has not been sent yet.
    }

    // If exists, get next newsletter since sent date.
    $query = db_select('simplenews_statistics', 'ss')
      ->fields('ss', array('send_start_timestamp'))
      ->condition('ss.send_start_timestamp', $start, '>');
    $end = $query->execute()->fetchField();

    if ($end == FALSE) {
      // Count unsubs since newsletter started sending.
      $unsubs = simplenews_statistics_count_unsubscribes($tid, $start, REQUEST_TIME, $source);
    }
    else {
      // Count unsubs between sending of this newsletter and the next.
      $unsubs = simplenews_statistics_count_unsubscribes($tid, $start, $end, $source);
    }

    // Formatting.
    if ($percentage && $subscribers > 0) {
      // Percentage.
      $unsub_percent = round($unsubs / $subscribers * 100, $precision) . '%';
      if ($number) {
        // Percentage and number.
        return $unsub_percent . ' (' . $unsubs . ')';
      }
      return $unsub_percent;
    }

    return $unsubs;
  }

}
