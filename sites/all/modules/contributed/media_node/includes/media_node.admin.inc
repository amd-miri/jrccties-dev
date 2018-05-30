<?php

/**
 * @file
 * Administrative functions for Media: Node.
 */

/**
 * The administrative settings form for Media: Node.
 */
function media_node_settings() {
  $form = array();
  $form['rebuild_media_nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rebuild media nodes'),
    '#description' => t('If you change these settings after content has already been entered, you will need to ensure that all existing nodes of these types have associated media file objects. Pressing the %rebuild button will make this happen, and also clear any unused media referencing a node of a type no longer used.', array('%rebuild' => t('Rebuild'))),
    '#weight' => -10,
  );

  $form['rebuild_media_nodes']['rebuild'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild'),
    '#submit' => array('media_node_settings_rebuild_submit'),
  );

  $options = array();
  $node_types = node_type_get_types();
  $existing = media_node_variable_get('types');
  foreach ($node_types as $node_type) {
    $fields = field_info_instances('node', $node_type->type);
    $field_options = array('node' => t('(Extract from the full display)'));
    foreach ($fields as $field_name => $bundled_field) {
      $field = field_info_field($field_name);
      if (in_array($field['type'], array('media', 'image', 'text_with_summary', 'text', 'text_long'))) {
        $field_options[$field_name] = $bundled_field['label'];
      }
    }
    $options[$node_type->type] = t('@type', array('@type' => $node_type->name));
    $form[media_node_variable_name('type_' . $node_type->type)] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => (!isset($existing[$node_type->type]) || !$existing[$node_type->type]),
      '#title' => t('@type thumbnail field', array('@type' => $node_type->name)),
      '#description' => t('Select which field to extract the thumbnail for display when selecting a node of this type from the media browser.'),
    );
    $form[media_node_variable_name('type_' . $node_type->type)][media_node_variable_name('type_' . $node_type->type . '_field')] = array(
      '#type' => 'radios',
      '#title' => t('Field to extract media'),
      '#options' => $field_options,
      '#default_value' => media_node_variable_get('type_' . $node_type->type . '_field', 'node'),
    );
    $form[media_node_variable_name('type_' . $node_type->type)][media_node_variable_name('mimetype_' . $node_type->type)] = array(
      '#type' => 'textfield',
      '#title' => t('Mimetype'),
      '#description' => t('This is the mime type to set media referencing nodes of this type to. Please do not change this setting, unless you know what you are doing.'),
      '#default_value' => media_node_variable_get('mimetype_' . $node_type->type, 'image/jpeg'),
    );
  }
  $form[media_node_variable_name('types')] = array(
    '#type' => 'checkboxes',
    '#title' => t('Media node types'),
    '#options' => $options,
    '#default_value' => media_node_variable_get('types'),
    '#description' => t('Check any node types that will be accessible as media.'),
    '#weight' => -4,
  );

  return system_settings_form($form);
}

function media_node_settings_rebuild_submit($form, &$form_state) {
  $batch = array(
    'operations' => array(array('media_node_rebuild_job', array(t('Rebuilding media nodes.')))),
    'finished' => 'media_node_rebuild_job_finished',
    // We can define custom messages instead of the default ones.
    'title' => t('Processing media nodes'),
    'error_message' => t('The Media: Node rebuilding batch job has encountered an error.'),
    'file' => drupal_get_path('module', 'media_node') . '/includes/media_node.admin.inc',
  );
  batch_set($batch);
}

function media_node_rebuild_job($operation_details, &$context) {
  // Use the $context['sandbox'] at your convenience to store the
  // information needed to track progression between successive calls.
  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;

    // Save node count for the termination message.
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT nid) FROM {node}')->fetchField();
  }

  // Process nodes by groups of 5 (arbitrary value).
  // When a group of five is processed, the batch update engine determines
  // whether it should continue processing in the same request or provide
  // progress feedback to the user and wait for the next request.
  // That way even though we're already processing at the operation level
  // the operation itself is interruptible.
  $limit = 5;

  // Retrieve the next group of nids.
  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->orderBy('n.nid', 'ASC')
    ->where('n.nid > :nid', array(':nid' => $context['sandbox']['current_node']))
    ->extend('PagerDefault')
    ->limit($limit)
    ->execute();
  foreach ($result as $row) {
    // Here we actually perform our processing on the current node.
    $node = node_load($row->nid, NULL, TRUE);

    $uri = 'node://nid/' . $node->nid;
    $file = file_uri_to_object($uri);

    if (!media_node_check_type($node->type) && $file->fid) {
      // Delete file if it's not being used.
      file_usage_delete($file, 'media_node');
      file_delete($file);
    }
    elseif (media_node_check_type($node->type) && !$file->fid) {
      // Save the file if it currently does not exist.
      $file->filename = $node->title;
      file_save($file);
      file_usage_add($file, 'media_node', 'node', $node->nid);
    }
    elseif (media_node_check_type($node->type) && $file->fid) {
      // Change the mime type if it's incorrect.
      if ($file->mimetype != media_node_variable_get('mimetype_' . $node->type, 'image/jpeg')) {
        $file->mimetype = media_node_variable_get('mimetype_' . $node->type, 'image/jpeg');
        file_save($file);
      }
    }

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $node->nid;
    $context['message'] = check_plain($node->title);
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

function media_node_rebuild_job_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Rebuilt all media referencing nodes.'));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}
