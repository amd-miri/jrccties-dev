<?php

/**
 * @file
 * Contains page function for simplenews statistics.
 */

/**
 * Check and log newsletter opens.
 */
function simplenews_statistics_open_page($nid, $snid, $terminate = TRUE) {
  // Call possible decoders for nid & snid in modules implementing the hook.
  // Modules implementing this hook should validate this input themself because
  // we can not know what kind of string they will generate.
  $hook = 'simplenews_statistics_decode';
  foreach (module_implements($hook) as $module) {
    $function = $module . '_' . $hook;
    if (function_exists($function)) {
      $nid = $function($nid, 'nid');
      $snid = $function($snid, 'snid');
    }
  }

  // Once decoded properly we can know for sure that nid & snid are numeric.
  if (!is_numeric($nid) || !is_numeric($snid)) {
    watchdog('simplenews_statistics', 'Simplenews statistics open called with illegal parameter(s).');
  }
  else {
    $subscriber = simplenews_subscriber_load($snid);
    if (!empty($subscriber) && $subscriber->snid == $snid) {
      $record = new stdClass();
      $record->snid = $subscriber->snid;
      $record->nid = $nid;
      $record->timestamp = time();
      drupal_write_record('simplenews_statistics_open', $record);
    }
  }

  if ($terminate == FALSE) {
    return; // Allow PHP execution to continue.
  }

  // Render a transparent image and stop PHP execution.
  $type = 'image/png; utf-8';
  $file = drupal_get_path('module', 'simplenews_statistics') . '/images/count.png';

  // Default headers are set by drupal_page_header(), just set content type.
  drupal_add_http_header('Content-Type', $type);
  drupal_add_http_header('Content-Length', filesize($file));

  readfile($file);
  drupal_exit();
}

/**
 * Check and log newsletter URL clicks.
 */
function simplenews_statistics_click_page($urlid, $snid) {
  // Call possible decoders for urlid & snid in modules implementing the hook.
  $hook = 'simplenews_statistics_decode';
  foreach (module_implements($hook) as $module) {
    $function = $module . '_' . $hook;
    if (function_exists($function)) {
      $urlid = $function($urlid, 'urlid');
      $snid = $function($snid, 'snid');
    }
  }

  // Once decoded properly we can know for sure that the $urlid and $snid are
  // numeric. Fallback on any error is to go to the homepage.
  if (!is_numeric($urlid) || !is_numeric($snid)) {
    watchdog('simplenews_statistics', 'Simplenews statistics click called with illegal parameter(s).');
    drupal_goto();
  }

  // Track click if there is an url and a valid subscriber. For test mails the
  // snid can be 0, so no valid subscriber will be loaded and the click won't
  // be counted. But the clicked link will still redirect properly.
  $query = db_select('simplenews_statistics_url', 'ssu')
    ->fields('ssu')
    ->condition('urlid', $urlid);
  $url_record = $query->execute()->fetchObject();

  $subscriber = simplenews_subscriber_load($snid);
  if (!empty($subscriber) && $subscriber->snid == $snid && isset($url_record)) {
    $click_record = new stdClass();
    $click_record->urlid = $urlid;
    $click_record->snid = $snid;
    $click_record->timestamp = time();
    drupal_write_record('simplenews_statistics_click', $click_record);

    // Check if the open action was registered for this subscriber. If not we
    // can track the open here to improve statistics accuracy.
    $query = db_select('simplenews_statistics_open', 'sso');
    $query->condition('snid', $snid);
    $num_rows = $query->countQuery()->execute()->fetchField();
    if ($num_rows == 0) {
      simplenews_statistics_open_page($url_record->nid, $snid, FALSE);
    }
  }

  // Redirect to the right URL.
  if (!empty($url_record) && !empty($url_record->url)) {
    // Split the URL into it's parts for easier handling.
    $path = $url_record->url;
    $options = array(
      'fragment' => '',
      'query' => array(),
    );

    // The fragment should always be after the query, so we get that first.
    // We format it for the options array for drupal_goto().
    $fragment_position = strpos($path, '#');
    if (FALSE !== $fragment_position) {
      $fragment = substr($path, $fragment_position + 1);
      $path = str_replace('#' . $fragment, '', $path);
      $options['fragment'] = $fragment;
    }
    // Determine the position of the query string, get it, delete it from the
    // original path and then we explode the parts and the key-value pairs to
    // get a clean output that we can use in drupal_goto().
    $query_position = strpos($path, '?');
    if (FALSE !== $query_position) {
      $query = substr($path, $query_position + 1);
      $path = str_replace('?' . $query, '', $path);
      $element = explode('&', $query);
      foreach ($element as $pair) {
        $pair = explode('=', $pair);
        if (!isset($pair[1])) {
          $pair[1] = '';
        }
        $options['query'][$pair[0]] = $pair[1];
      }
    }

    // Call possible rewriters for the url.
    $hook = 'simplenews_statistics_rewrite_goto_url';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        $function($path, $options, $snid, $url_record->nid);
      }
    }
    // Fragment behaviour can get out of spec here.
    drupal_goto($path, $options);
  }

  // Fallback on any error is to go to the homepage.
  // @todo: Give some feedback to user and perhaps watchdog.
  drupal_goto();
}

/**
 * Page callback to render a view with contextual links.
 */
function simplenews_statistics_embed_view($view_name, $display_id) {
  $view = views_embed_view($view_name);
  return render($view);
}
