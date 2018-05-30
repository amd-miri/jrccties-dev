<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements template_preprocess_page().
 */
function jrccities_subtheme_preprocess_page(&$variables) {
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
