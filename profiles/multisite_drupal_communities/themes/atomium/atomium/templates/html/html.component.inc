<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 *
 * @SuppressWarnings(PHPMD.CyclomaticComplexity)
 * @SuppressWarnings(PHPMD.NPathComplexity)
 */
function atomium_preprocess_html(array &$variables, $hook) {
  // Add variables and paths needed for HTML5 and responsive support.
  $variables['base_path'] = base_path();

  // Attributes for html element.
  $variables['atomium']['attributes']['html']->merge(array(
    'lang' => $variables['language']->language,
    'dir' => $variables['language']->dir,
  ));

  // Return early, so the maintenance page does not call any of the code below.
  if ('html' !== $hook) {
    return;
  }

  // Serialize RDF Namespaces into an RDFa 1.1 prefix attribute.
  if ($variables['rdf_namespaces']) {
    $prefixes = array();
    foreach (\explode("\n  ", \ltrim($variables['rdf_namespaces'])) as $namespace) {
      // Remove xlmns: and ending quote and fix prefix formatting.
      $prefixes[] = \str_replace('="', ': ', drupal_substr($namespace, 6, -1));
    }
    $variables['rdf_namespaces'] = \implode(' ', $prefixes);
  }

  $variables['atomium']['attributes']['html']->append('prefix', $variables['rdf_namespaces']);

  // Classes for body element. Allows advanced theming based
  // on context (home page, node of certain type, etc.).
  if (!$variables['is_front']) {
    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);
    // Add unique class for each website section.
    list($section,) = \explode('/', $path, 2);
    $arg = \explode('/', $_GET['q']);
    if ('node' === $arg[0] && isset($arg[1])) {
      if ('add' === $arg[1]) {
        $section = 'node-add';
      }
      elseif (isset($arg[2]) && \is_numeric($arg[1]) && ('edit' === $arg[2] || 'delete' === $arg[2])) {
        $section = 'node-' . $arg[2];
      }
    }
    $variables['classes_array'][] = 'section-' . $section;
  }

  // Store the menu item since it has some useful information.
  $variables['menu_item'] = menu_get_item();
  if ($variables['menu_item']) {
    switch ($variables['menu_item']['page_callback']) {
      case 'views_page':
        // Is this a Views page?
        $variables['classes_array'][] = 'page-views';

        break;

      case 'page_manager_blog':
      case 'page_manager_blog_user':
      case 'page_manager_contact_site':
      case 'page_manager_contact_user':
      case 'page_manager_node_add':
      case 'page_manager_node_edit':
      case 'page_manager_node_view_page':
      case 'page_manager_page_execute':
      case 'page_manager_poll':
      case 'page_manager_search_page':
      case 'page_manager_term_view_page':
      case 'page_manager_user_edit_page':
      case 'page_manager_user_view_page':
        // Is this a Panels page?
        $variables['classes_array'][] = 'page-panels';

        break;
    }
  }

  $headers = drupal_get_http_header();
  if (isset($headers['status'])) {
    $variables['classes_array'][] = 'status-' . $headers['status'];
    if ('404 Not Found' === $headers['status']) {
      $variables['theme_hook_suggestions'][] = 'html__404';
    }
  }

  $variables['atomium']['attributes']['body']->append('class', $variables['classes_array']);
  $variables['atomium']['attributes']['body']->remove('class', atomium_get_settings('preprocess.html.classes_to_remove', TRUE));
}
