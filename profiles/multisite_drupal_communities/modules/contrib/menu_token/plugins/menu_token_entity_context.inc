<?php

class menu_token_entity_context implements menu_token_handler {
  function form_options($options) {
    // Nothing to do here.
  }

  function form_submit($form, &$form_state) {
    // Nothing to do here.
  }

  function form_validate($form, &$form_state) {
    // Nothing to do here.
  }

  function form_alter(&$form, &$form_state) {
    // Nothing to do here.
  }

  function object_load($options) {
    $entity_type = $options['_type'];
    $entity_info = entity_get_info($entity_type);

    $original_map = arg();
    $parts = array_slice($original_map, 0, MENU_MAX_PARTS);
    $ancestors = menu_get_ancestors($parts);
    $router_item = db_query_range('SELECT * FROM {menu_router} WHERE path IN (:ancestors) ORDER BY fit DESC', 0, 1, array(':ancestors' => $ancestors))->fetchAssoc();

    // Check for views argument.
    // Warning: only returns the first entity even if there are multiple arguments
    // of the same entity type in the url. The module as is doesn't allow for
    // argument selection.
    if ($router_item['page_callback'] == 'views_page' && module_exists('views')) {
      $view = views_get_page_view();
      $entity_key = $entity_info['entity keys']['id'];
      if (isset($view->argument) && array_key_exists($entity_key, $view->argument)) {
        return entity_load_single($entity_type, $view->argument[$entity_key]->argument);
      }
    }

    // Check for load function.
    // Warning: only returns the first entity even if there are multiple load
    // functions of the same type. The module as is doesn't allow for argument
    // selection.
    if (!empty($entity_info['load hook']) && !empty($router_item['load_functions'])) {
      $load_functions = unserialize($router_item['load_functions']);
      if ($key = array_search($entity_info['load hook'], $load_functions)) {
        return entity_load_single($entity_type, $parts[$key]);
      }
    }
  }
}
