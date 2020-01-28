<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements template_preprocess_region().
 *
 * We don't want og subscribe button in the default location.
 * Load node to preprocess og field next to the tools block.
 */
function jrccities_subtheme_preprocess_region(&$variables) {
  $item = menu_get_item();

  // Case 1 : Check for "Community" content type.
  if (!empty($item['page_arguments'][0]->type) && $item['page_arguments'][0]->type == 'community') {
    // Check if the community chose to show the subscribe button.
    if (isset($item['page_arguments'][0]->field_show_subscription_buttons) &&
        $item['page_arguments'][0]->field_show_subscription_buttons[LANGUAGE_NONE][0]['value'] == 1) {
      $gid = $item['page_arguments']['0']->nid;
      $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($gid);
    }
  }
  // Case 2 : Check for when browsing all the other nodes (content-types).
  elseif (isset($item['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]) && $item['page_arguments'][0]->entity_type == "node") {
    $gid = $item['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]['0']['target_id'];
    $node = node_load($gid);
    // Check if the community chose to show the subscribe button.
    if ($node->field_show_subscription_buttons[LANGUAGE_NONE][0]['value'] == 1) {
      $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($gid);
    }
  }
  // Case 3 : Case 3 : verify when browsing a community view.
  // Example: community/%/about.
  elseif (isset($item['page_arguments'][2]) && $item['page_callback'] == 'views_page') {
    $gid = $item['page_arguments'][2];
    $node = node_load($gid);
    // Check if the community chose to show the subscribe button.
    if ($node->field_show_subscription_buttons[LANGUAGE_NONE][0]['value'] == 1) {
      $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($gid);
    }
  }
}

/**
 * Get the og_group_subscribe output.
 *
 * @param int $nid
 *   The node id.
 *
 * @return array
 *   The output of the og_group_subscribe.
 */
function _jrccities_subtheme_get_og_group_subscribe($nid) {
  $node = node_load($nid, NULL, TRUE);
  $output = field_view_field('node', $node, 'group_group', array('type' => 'og_group_subscribe', 'label' => 'hidden'));
  return $output;
}

/**
 * Implements template_preprocess_page().
 */
function jrccities_subtheme_preprocess_page(&$variables) {
  if (isset($variables['node']->type)) {
    $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
  }

  // Hide the node_export and Track tab
  // It's breaking the theme and it's not useful for JRCCITIES website.
  // (Solution suggested by Digit).
  if (!empty($variables['tabs']['#primary'])) {
    foreach ($variables['tabs']['#primary'] as $tabnum => $tablink) {
      if ($tablink['#link']['title'] == 'Node export') {
        unset($variables['tabs']['#primary'][$tabnum]);
      }
      elseif ($tablink['#link']['title'] == 'Track') {
        unset($variables['tabs']['#primary'][$tabnum]);
      }
    }
  }

  // Add specific JS files to specific sections of the website.
  // For JRC Evidence to Inform Policy Community term and conditions.
  if (current_path() == 'group/node/76/subscribe/og_user_node') {
    drupal_add_js(libraries_get_path('jquery-ui') . '/jquery-ui.js');
    drupal_add_js(drupal_get_path('theme', 'jrccities_subtheme') . '/js/specific/jrccities_jrc_evidence_to_inform_policy.js');
  }

  // JRCCTIES-80: usage of CCK mandatody on all ec.europa pages.
  drupal_add_js('https://ec.europa.eu/wel/cookie-consent/consent.js', 'external');
}

/**
 * Implements template_preprocess_node().
 */
function jrccities_subtheme_preprocess_node(&$variables) {
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js',
    array(
      'type' => 'external',
      'scope' => 'header',
    )
  );
}

/**
 * Implements template_url_outbound_alter().
 *
 * Remove appended redirection after creating the content from URI.
 */
function jrccities_subtheme_url_outbound_alter(&$path, &$options, $original_path) {
  if (preg_match('/node.add.\+?(\S+)?/m', $path)) {
    unset($options['query']['destination']);
  }
}

/**
 * Make user role available in the body tag to filter fields from OG Porosity.
 */
function jrccities_subtheme_preprocess_html(&$variables) {
  global $user;

  $params = drupal_get_query_parameters();
  // For node/add og_group_ref queries get gid.
  if (isset($params['og_group_ref'])) {
    _jrccties_subtheme_hide_from_non_editors($params, $user, $variables);
  }
  // For node/nid/edit forms, get nid.
  if (arg(0) == 'node' && is_numeric(arg(1)) && arg(2) == 'edit') {
    _jrccties_subtheme_hide_from_non_editors($params, $user, $variables);
  }
}

/**
 * Create body class for organic group roles for crosschecking fieldgroup class.
 */
function _jrccties_subtheme_hide_from_non_editors($params, $user, &$variables) {
  if (empty($user->uid)) {
    return;
  }
  if (isset($params['og_group_ref'])) {
    $gid = $params['og_group_ref'];

    // Returns membership role.
    $role = array();
    $role = og_get_user_roles('node', $gid, $user->uid);
    $role_class = 'role-' . str_replace(' ', '-', end($role));
    $variables['classes_array'][] = $role_class;
  }
}

/**
 * Implements MODULE_preprocess_HOOK().
 *
 * Adds appropriate attributes to the list item.
 *
 * @see theme_menu_link()
 */
function jrccities_subtheme_preprocess_menu_link(&$variables) {
  $menuLinks = array(
    'Home' => array('glyph' => 'home', 'title' => 'Home'),
    'About' => array('glyph' => 'pencil', 'title' => 'About'),
    'Articles' => array('glyph' => 'file', 'title' => 'Articles'),
    'Events' => array('glyph' => 'calendar', 'title' => 'Events'),
    'Upcoming Events' => array('glyph' => 'calendar', 'title' => 'Upcoming Events'),
    'Past Events' => array('glyph' => 'calendar', 'title' => 'Past Events'),
    'News' => array('glyph' => 'transfer', 'title' => 'News'),
    'Forum' => array('glyph' => 'comment', 'title' => 'Forum'),
    'Useful Links' => array('glyph' => 'link', 'title' => 'Useful Links'),
    'Polls' => array('glyph' => 'list', 'title' => 'Polls'),
    'Library' => array('glyph' => 'calendar', 'title' => 'Library'),
    'Books' => array('glyph' => 'book', 'title' => 'Books'),
    'Documents' => array('glyph' => 'book', 'title' => 'Documents'),
    'Audios' => array('glyph' => 'volume-up', 'title' => 'Audios'),
    'Photos' => array('glyph' => 'picture', 'title' => 'Photos'),
    'Videos' => array('glyph' => 'facetime-video', 'title' => 'Videos'),
  );
  if (isset($menuLinks[$variables['element']['#title']]['title'])
      && $variables['element']['#title'] == $menuLinks[$variables['element']['#title']]['title']) {
    $variables['element']['#title'] = '<span class="glyphicon glyphicon-' . $menuLinks[$variables['element']['#title']]['glyph'] . '"> </span> ' . $menuLinks[$variables['element']['#title']]['title'];
  }
}
