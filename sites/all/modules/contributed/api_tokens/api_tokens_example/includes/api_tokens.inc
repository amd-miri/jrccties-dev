<?php

/**
 * @file
 * Contains API Token handlers.
 */


/**
 * Defines "user-link" API Token handler.
 */
function api_tokens_example_handle_user_link() {
  global $user;

  $output = $user->uid ? l($user->name, 'user/' . $user->uid) : t('Anonimous');
  $output = '<strong>' . $output . '</strong>';

  return $output;
}


/**
 * Defines "node-list" API Token handler.
 */
function api_tokens_example_handle_node_list($content_type = '') {
  $query = db_select('node', 'N');
  $query->join('node_type', 'T', 'N.type = T.type');
  $query->leftJoin('users', 'U', 'U.uid = N.uid');
  $query->addField('T', 'name', 'type');
  $query->fields('N', array('nid', 'title'))
    ->fields('U', array('uid', 'name'))
    ->condition('N.status', 1)
    ->condition('U.uid', 0, '<>')
    ->orderBy('N.created', 'DESC');
  if ($content_type) {
    $query->condition('N.type', $content_type);
  }
  $data = $query->range(0, 10)
    ->execute()
    ->fetchAll();

  $rows = array();
  foreach ($data as $row) {
    $rows[] = array(
      l($row->title, 'node/' . $row->nid),
      $row->type,
      l($row->name, 'user/' . $row->uid),
    );
  }

  $vars = array(
    'header' => array(
      t('Title'),
      t('Content Type'),
      t('Author'),
    ),
    'rows' => $rows,
  );

  $content = theme('table', $vars);

  return $content;
}
