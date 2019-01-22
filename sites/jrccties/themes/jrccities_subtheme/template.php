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

  if (_jrccties_subtheme_hide_og_subscribe_button($item) === FALSE) {
    return;
  }

  // Case 0 : the main homepage.
  if ($item['path'] == "communities_directory") {
    return;
  }
  // Case 1 : Check for community content type.
  if (!empty($item['page_arguments'][0]->type)) {
    $type = $item['page_arguments'][0]->type;
    if ($type == 'community') {
      $nid = $item['page_arguments']['0']->nid;
      $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($nid);
      return;
    }
  }
  // Case 2 : Check for when browsing community/%/content-type.
  if (isset($item['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]) && $item['page_arguments'][0]->entity_type == "node") {
    $gid = $item['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]['0']['target_id'];
    $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($gid);
    return;
  }
  // Case 3 : check for when browsing a view, e.g. /community/id/about.
  if (isset($item['page_arguments'][2]) && $item['page_callback'] == 'views_page') {
    $nid = $item['page_arguments'][2];
    $variables['og_subscribe'] = _jrccities_subtheme_get_og_group_subscribe($nid);
    return;
  }
}

/**
 * Load node to see if we should show subscription widget or not.
 */
function _jrccties_subtheme_hide_og_subscribe_button($item) {
  if (isset($item['page_arguments'][0]->nid) && isset($item['page_arguments'][0]->field_show_subscription_buttons)) {
    $node = node_load($item['page_arguments'][0]->nid);
    if ($item['page_arguments'][0]->field_show_subscription_buttons[LANGUAGE_NONE][0]['value'] == 0) {
      return FALSE;
    }
  }
  if (isset($item['page_arguments'][2])) {
    $node = node_load($item['page_arguments'][2]);
    if ($node->field_show_subscription_buttons[LANGUAGE_NONE][0]['value'] == 0) {
      return FALSE;
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
}

/**
 * Implements template_preprocess_node().
 */
function jrccities_subtheme_preprocess_node(&$variables) {

  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', array(
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
  $menuLinks = [
    'Home' => ['glyph' => 'home', 'title' => 'Home'],
    'About' => ['glyph' => 'pencil', 'title' => 'About'],
    'Articles' => ['glyph' => 'file', 'title' => 'Articles'],
    'Events' => ['glyph' => 'calendar', 'title' => 'Events'],
    'Upcoming Events' => ['glyph' => 'calendar', 'title' => 'Upcoming Events'],
    'Past Events' => ['glyph' => 'calendar', 'title' => 'Past Events'],
    'News' => ['glyph' => 'transfer', 'title' => 'News'],
    'Forum' => ['glyph' => 'comment', 'title' => 'Forum'],
    'Useful Links' => ['glyph' => 'link', 'title' => 'Useful Links'],
    'Polls' => ['glyph' => 'list', 'title' => 'Polls'],
    'Library' => ['glyph' => 'calendar', 'title' => 'Library'],
    'Books' => ['glyph' => 'book', 'title' => 'Books'],
    'Documents' => ['glyph' => 'book', 'title' => 'Documents'],
    'Audios' => ['glyph' => 'volume-up', 'title' => 'Audios'],
    'Photos' => ['glyph' => 'picture', 'title' => 'Photos'],
    'Videos' => ['glyph' => 'facetime-video', 'title' => 'Videos'],
  ];
  if ($variables['element']['#title'] == $menuLinks[$variables['element']['#title']]['title']) {
    $variables['element']['#title'] = '<span class="glyphicon glyphicon-' . $menuLinks[$variables['element']['#title']]['glyph'] . '"> </span> ' . $menuLinks[$variables['element']['#title']]['title'];
  }
}
