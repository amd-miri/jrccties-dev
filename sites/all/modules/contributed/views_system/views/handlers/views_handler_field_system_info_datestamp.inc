<?php

/**
 * @file
 * Views field handler for the views_system module.
 */


/**
 * Renders the date stamp field of the system item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_system_info_datestamp extends views_handler_field_date {


  function render($values) {

    $info = unserialize($values->{$this->field_alias});
    $value = isset($info['datestamp']) ? $info['datestamp'] : NULL;

    $format = $this->options['date_format'];
    if (in_array($format, array('custom', 'raw time ago', 'time ago', 'raw time span', 'time span'))) {
      $custom_format = $this->options['custom_date_format'];
    }

    if (!$value) {
      return theme('views_nodate');
    }
    else {
      $time_diff = REQUEST_TIME - $value; // will be positive for a datetime in the past (ago), and negative for a datetime in the future (hence)
      switch ($format) {
        case 'raw time ago':
          return format_interval($time_diff, is_numeric($custom_format) ? $custom_format : 2);
        case 'time ago':
          return t('%time ago', array('%time' => format_interval($time_diff, is_numeric($custom_format) ? $custom_format : 2)));
        case 'raw time span':
          return ($time_diff < 0 ? '-' : '') . format_interval(abs($time_diff), is_numeric($custom_format) ? $custom_format : 2);
        case 'time span':
          return t(($time_diff < 0 ? '%time hence' : '%time ago'), array('%time' => format_interval(abs($time_diff), is_numeric($custom_format) ? $custom_format : 2)));
        case 'custom':
          if ($custom_format == 'r') {
            return format_date($value, $format, $custom_format, NULL, 'en');
          }
          return format_date($value, $format, $custom_format);
        default:
          return format_date($value, $format);
      }
    }
  }
}
