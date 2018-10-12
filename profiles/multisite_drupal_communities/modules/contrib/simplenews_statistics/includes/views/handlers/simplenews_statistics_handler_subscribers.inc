<?php

/**
 * @file
 * Definition of simplenews_statistics_handler_subscribers.
 */

/**
 * Description.
 */
class simplenews_statistics_handler_subscribers extends views_handler_field {
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

    return $options;
  }

  /**
   * Creates the form item for the options added.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Renders the field handler.
   */
  function render($values) {
    $subscriber_count = $values->simplenews_newsletter_sent_subscriber_count;

    if ($subscriber_count == 0) {
      $subscriber_count = simplenews_statistics_count_subscribers($values->nid);
    }

    return $subscriber_count;
  }

}
