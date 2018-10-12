<?php

/**
 *  @file
 *  Create a Node Stream Wrapper class for the Media module.
 */

/**
 *  Create an instance like this:
 *  $youtube = new MediaNodeStreamWrapper('node://nid/7');
 */
class MediaNodeStreamWrapper extends MediaReadOnlyStreamWrapper {

  function interpolateUrl() {
    if ($nid = $this->getNid()) {
      return 'node/' . $nid;
    }
  }

  function getTarget($f) {
    return FALSE;
  }

  function getNid() {
    if ($parameters = $this->get_parameters()) {
      if ($parameters['nid'] && is_numeric($parameters['nid'])) {
        return $parameters['nid'];
      }
    }
  }

  static function getMimeType($uri, $mapping = NULL) {
    $path = explode('://', $uri);
    $parts = explode('/',  $path[1]);
    $params = array();
    $count = 0;
    $total = count($parts);
    if (!$total || ($total % 2)) {
      // If we have no parts, or an odd number of parts, it's malformed.
      return FALSE;
    }
    while ($count < $total) {
      // We iterate count for each step of the assignment to keep us honest.
      $params[$parts[$count++]] = $parts[$count++];
    }
    $node = db_select('node', 'n')
      ->fields('n', array('type'))
      ->condition('nid', $params['nid'])
      ->execute()
      ->fetchObject();
    if ($node->type) {
      return media_node_variable_get('mimetype_' . $node->type, 'image/jpeg');
    }
   }

  function getThumbnailPath() {
    $parts = $this->get_parameters();
    $node = db_select('node', 'n')
      ->fields('n', array('nid', 'type', 'vid'))
      ->condition('nid', $parts['nid'])
      ->execute()
      ->fetchObject();
    if ($node->nid) {
      $field_name = media_node_variable_get('type_' . $node->type . '_field', 'node');
      if ($field_name == 'node') {
        $node = node_load($parts['nid']);
        $view = drupal_render(node_view($node));
        return $this->parse_image_url($view, TRUE);
      }
      else {
        $field = field_info_field($field_name);
        field_attach_load('node', array($node->nid => $node), FIELD_LOAD_CURRENT, array('field_id' => $field_name));
        if ($node->{$field_name}) {
          $fields = field_info_instances('node', $node->type);
          $field_info = $fields[$field_name];
          switch ($field['type']) {
            case 'image':
            case 'file':
            case 'media':
              $file = file_load($node->{$field_name}['und'][0]['fid']);
              return $file->uri;
            case 'text':
            case 'text_long':
            case 'text_with_summary':
              return $this->parse_image_url($node->{$field_name}['und'][0]['safe_value'], $field_info['settings']['text_processing']);
          }
        }
      }
    }
  }

  /**
   * Parse an image URL directly from a string.
   *
   * @param string $text
   * The text to extract the URL from.
   * @param boolean $from_html
   * Optional, defaults to FALSE. If TRUE, then look for the path from img tags.
   */
  function parse_image_url($text, $from_html = FALSE) {
    global $base_root, $base_path;
    $file_path = variable_get('file_public_path', conf_path() . '/files');
    if ($from_html) {
      $regex = "@<img.+?src\s*?=\s*?[\"']?({$base_root})?(({$base_path}{$file_path}/)?(styles/.+?/)?(public/)?([^\"'\?]+?\.(png|jpg|gif|jpeg)))[\"']?.*?>@i";
    }
    else {
      $regex = "@^({$base_root})?({$base_path}{$file_path}/)?(styles/.+?/)?(public/)?([^\?]+?\.(png|jpg|gif|jpeg))$@i";
    }
    if (preg_match($regex, $text, $matches)) {
      return $matches[2];
    }
  }

}
