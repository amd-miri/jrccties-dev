<?php

function context_menu_parent_options($menus, $item, $type = '') {
  // The menu_links table can be practically any size and we need a way to
  // allow contrib modules to provide more scalable pattern choosers.
  // hook_form_alter is too late in itself because all the possible parents are
  // retrieved here, unless menu_override_parent_selector is set to TRUE.
  if (variable_get('menu_override_parent_selector', FALSE)) {
    return array();
  }

  $available_menus = array();
  if (!is_array($item)) {
    // If $item is not an array then it is a node type.
    // Use it as $type and prepare a dummy menu item for _menu_get_options().
    $type = $item;
    $item = array('mlid' => 0);
  }
  if (empty($type)) {
    // If no node type is set, use all menus given to this function.
    $available_menus = $menus;
  }
  else {
    // If a node type is set, use all available menus for this type.
    $type_menus = variable_get('menu_options_' . $type, array('main-menu' => 'main-menu'));
    foreach ($type_menus as $menu) {
      $available_menus[$menu] = $menu;
    }
  }

  return _context_menu_get_options($menus, $available_menus, $item);
}

function _context_menu_get_options($menus, $available_menus, $item) {
  // If the item has children, there is an added limit to the depth of valid parents.
  if (isset($item['parent_depth_limit'])) {
    $limit = $item['parent_depth_limit'];
  }
  else {
    $limit = _menu_parent_depth_limit($item);
  }

  $options = array();
  foreach ($menus as $menu_name => $title) {
    if (isset($available_menus[$menu_name])) {
      $tree = menu_tree_all_data($menu_name, NULL);
      $options[$menu_name . ':0'] = '<' . $title . '>';
      _context_menu_parents_recurse($tree, $menu_name, '--', $options, $item['mlid'], $limit);
    }
  }
  return $options;
}

function _context_menu_parents_recurse($tree, $menu_name, $indent, &$options, $exclude, $depth_limit) {
  foreach ($tree as $data) {
    if ($data['link']['depth'] > $depth_limit) {
      // Don't iterate through any links on this level.
      break;
    }
    if ($data['link']['mlid'] != $exclude && $data['link']['hidden'] >= 0) {
      $title = $indent . ' ' . truncate_utf8($data['link']['title'], 30, TRUE, FALSE);
      if ($data['link']['hidden']) {
        $title .= ' (' . t('disabled') . ')';
      }
      $data['title'] = $title;
      $options[$menu_name . ':' . $data['link']['mlid']] = $data['link'];
      if ($data['below']) {
        _context_menu_parents_recurse($data['below'], $menu_name, $indent . '--', $options, $exclude, $depth_limit);
      }
    }
  }
}
