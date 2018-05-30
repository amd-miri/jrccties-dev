<?php

/**
 * @file
 * Administrative interface for the API Tokens module.
 */


/**
 * Renders synopsis cell.
 */
function api_tokens_page_format_synopsis($token) {
  // Verifying token process function.
  if (api_tokens_prepare_handler($token['key'])) {
    // Collecting full handler params info.
    $param_info = api_tokens_param_info($token['key'], TRUE);
    $content = '<code>[api:' . $token['key'] . '/]</code>';
    foreach ($param_info['params'] as $i => $param) {
      $param_info['params'][$i] = '<strong><em>' . $param_info['params'][$i] . '</em></strong>';
      if ($i < $param_info['count']) {
        $param_info['params'][$i] .= '<sup>*</sup>';
      }
    }
    $param_info = implode(', ', $param_info['params']);
    $content = $param_info ? str_replace('/]', '[' . $param_info . ']/]', $content) : $content;
  }
  else {
    $content = '<em>' . t('Token handler not found') . '</em>';
  }

  return $content;
}


/**
 * Renders cache cell.
 */
function api_tokens_page_format_cache($token) {
  $cache = $token['cache'];
  $content = array();
  // Token is cacheable.
  if (DRUPAL_NO_CACHE != $cache) {
    DRUPAL_CACHE_PER_ROLE & $cache && $content[] = t('Per user role');
    DRUPAL_CACHE_PER_USER & $cache && $content[] = t('Per user');
    DRUPAL_CACHE_PER_PAGE & $cache && $content[] = t('Per page');
    DRUPAL_CACHE_GLOBAL & $cache && !$content && $content[] = t('Global');
  }
  else {
    $content[] = '<em>' . t('No caching') . '</em>';
  }

  return implode('<br/>', $content);
}


/**
 * Renders expiration cell.
 */
function api_tokens_page_format_expiration($token) {
  // Token is cacheable.
  if (DRUPAL_NO_CACHE != $token['cache']) {
    $expire = $token['cache_expire'];
    // If cache isn't set to CACHE_PERMANENT (0) or CACHE_TEMPORARY (-1)
    if (0 < $expire) {
      if (31536000 <= $expire) {
        $content = t('More then one year');
      }
      else {
        $date = new DateTime('@' . $expire, new DateTimeZone('UTC'));
        $date = array(
          'month' => $date->format('n') - 1,
          'day' => $date->format('j') - 1,
          'hour' => $date->format('G'),
          'minute' => $date->format('i'),
          'second' => $date->format('s'),
        );
        foreach ($date as $key => $value) {
          if (0 < $value) {
            $content = format_plural((int) $value, '1 ' . $key, '@count ' . $key . 's');
            break;
          }
        }
      }
    }
    elseif (CACHE_PERMANENT == $expire) {
      $content = t('Permanent');
    }
    else {
      $content = t('Temporary');
    }
  }
  else {
    $content = '-';
  }

  return $content;
}


/**
 * Renders description cell.
 */
function api_tokens_page_format_description($token) {
  return $token['description'] ? $token['description'] : '<small><i>' . t('No description.') . '</i></small>';
}


/**
 * Builds token list table row.
 */
function api_tokens_page_build_row($token) {
  $row = array(
    $token['title'],
    api_tokens_page_format_synopsis($token),
    api_tokens_page_format_cache($token),
    api_tokens_page_format_expiration($token),
    api_tokens_page_format_description($token),
  );

  return $row;
}


/**
 * Renders token list page.
 */
function api_tokens_page_list() {
  // Retrieving module info.
  $module_list = system_rebuild_module_data();
  // Receiving all registered tokens.
  $tokens = api_tokens_collect_tokens();
  $tokens_info = array();
  // Grouping tokens by provider module.
  foreach ($tokens as $token) {
    $tokens_info[$token['module']][] = $token;
  }
  $rows = array();
  $i = 0;
  foreach ($tokens_info as $module => &$tokens) {
    $token = array_shift($tokens);
    $rows[$i] = array(
      $module => array(
        'data' => $module_list[$module]->info['name'],
        'rowspan' => count($tokens) + 1,
      ),
    );
    $rows[$i++] += api_tokens_page_build_row($token);
    foreach ($tokens as $token) {
      $rows[$i++] = api_tokens_page_build_row($token);
    }
  }
  $vars = array(
    'header' => array(
      t('Provider'),
      t('Token'),
      t('Synopsis'),
      t('Cache'),
      t('Expiration'),
      t('Description'),
    ),
    'rows' => $rows,
  );
  $content = theme('table', $vars)
   . '<div class="description"><sup>*</sup> - ' . t('Required parameter.') . '</div>';

  return $content;
}
