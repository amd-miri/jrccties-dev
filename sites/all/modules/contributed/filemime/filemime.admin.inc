<?php

/**
 * Form builder function for admin settings.
 */
function filemime_settings() {
  $form['filemime_file'] = array(
    '#type' => 'textfield',
    '#title' => t('Local mime.types file path'),
    '#default_value' => variable_get('filemime_file', ''),
    '#description' => t('If a mime.types file is readable, it will be parsed to extract MIME type mappings. Example: <em>/etc/mime.types</em>') . '<br />' . (is_readable(variable_get('filemime_file', '')) ? t('The configured mime.types file is readable.') : t('The configured mime.types file is not readable.')),
  );
  $form['filemime_types'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom MIME type mappings'),
    '#default_value' => variable_get('filemime_types', ''),
    '#description' => t('Types provided here will override the mime.types file. Specify the mappings using the mime.types file format. Example:<br /><em>audio/mpeg mpga mpega mp2 mp3 m4a<br />audio/mpegurl m3u<br />audio/ogg oga ogg spx</em>'),
  );
  return system_settings_form($form);
}

/**
 * Generates confirm form.
 */
function filemime_apply() {
  $form = array();
  $question = t('Apply MIME type mapping to all uploaded files?');
  $description = t('Are you sure you want to apply the configured MIME type mapping to all previously uploaded files? The MIME type for @count uploaded files will be regenerated.', array('@count' => filemime_count()));
  return confirm_form($form, $question, 'admin/config/media/filemime', $description, t('Apply'));
}

/**
 * Returns count of files in file_managed table.
 */
function filemime_count() {
  return db_query('SELECT COUNT(*) FROM {file_managed}')->fetchField();
}

/**
 * Retroactively applies MIME type mapping to all previously uploaded files.
 */
function filemime_apply_submit($form, &$form_state) {
  batch_set(array(
    'operations' => array(array('filemime_apply_process', array())),
    'finished' => 'filemime_apply_finished',
    'title' => t('Processing File MIME batch'),
    'init_message' => t('File MIME batch is starting.'),
    'progress_message' => t('Please wait...'),
    'error_message' => t('File MIME batch has encountered an error.'),
    'file' => drupal_get_path('module', 'filemime') . '/filemime.admin.inc',
  ));
  batch_process('admin/config/media/filemime');
}

/**
 * Batch process callback.
 */
function filemime_apply_process(&$context) {
  if (!isset($context['results']['processed'])) {
    $context['results']['processed'] = 0;
    $context['results']['updated'] = 0;
    $context['sandbox']['count'] = filemime_count();
    $context['sandbox']['schemes'] = file_get_stream_wrappers(STREAM_WRAPPERS_LOCAL);
  }
  $files = db_select('file_managed', 'f')->fields('f', array('fid', 'filemime', 'uri'))->range($context['results']['processed'], 1)->execute();
  foreach ($files as $file) {
    // Only operate on local stream URIs, which should represent file names.
    $scheme = file_uri_scheme($file->uri);
    if ($scheme && isset($context['sandbox']['schemes'][$scheme])) {
      $filemime = file_get_mimetype($file->uri);
      if ($file->filemime != $filemime) {
        $variables = array('%old' => $file->filemime, '%new' => $filemime, '%url' => $file->uri);
        // Fully load file object.
        $file = file_load($file->fid);
        $file->filemime = $filemime;
        file_save($file);
        $context['results']['updated']++;
        $context['message'] = t('Updated MIME type from %old to %new for %url.', $variables);
        watchdog('filemime', 'Updated MIME type from %old to %new for %url.', $variables);
      }
    }
    $context['results']['processed']++;
    $context['finished'] = $context['results']['processed'] / $context['sandbox']['count'];
  }
}

/**
 * Batch finish callback.
 */
function filemime_apply_finished($success, $results, $operations) {
  $variables = array('@processed' => $results['processed'], '@updated' => $results['updated']);
  if ($success) {
    drupal_set_message(t('Processed @processed files and updated @updated files.', $variables));
  }
  else {
    drupal_set_message(t('An error occurred after processing @processed files and updating @updated files.', $variables), 'warning');
  }
}
