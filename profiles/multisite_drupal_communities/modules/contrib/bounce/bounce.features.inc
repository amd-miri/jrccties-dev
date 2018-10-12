<?php

/**
 * @file
 * Enable the default blocker component's codes and scoring to be exported via
 * the Features module.
 *
 * Note that most of the hook functions here begin "bounce_code_" rather
 * than "bounce_". This is necessary.
 */

/**
 * Implements hook_features_api().
 *
 * We have to tell features that we are defining a new entity for export: rows
 * from the bounce_code_score table.
 */
function bounce_features_api() {
  return array(
    'bounce_code' => array(
      'name' => t('Email non-delivery report codes'),
      'feature_source' => TRUE,
      'default_hook' => 'bounce_default_bounce_codes',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
      'file' => drupal_get_path('module', 'bounce') . '/bounce.features.inc',
    ),
  );
}

/**
 * Implements hook_features_export_options().
 *
 * This returns an options array for checkboxes shown in the form
 * for creating or recreating a features module. Here that just means
 * all of the non-delivery report codes from the database.
 */
function bounce_code_features_export_options() {
  $codes = array();
  $result = db_select('bounce_code_score', 'cs')
    ->fields('cs')
    ->execute();
  foreach ($result as $row) {
    $codes[$row->code] = $row->code;
  }
  return $codes;
}

/**
 * Implements hook_features_export_render().
 *
 * Produce the PHP code that will be saved out into the generated features
 * module produced by Features.
 *
 * @param array $module
 *   A module name.
 * @param array $data
 *   An array of non-delivery report codes.
 */
function bounce_code_features_export_render($module, $data) {

  /*
  This code is basically copied from hook_features_export() implementations
  found in the /include/*.inc files in the features module. Look through
  those files for further examples of how to do this.
  */

  $output = array();
  $output[] = '$codes = array();';
  $result = db_select('bounce_code_score', 'cs')
    ->fields('cs')
    ->condition('code', array_values($data), 'IN')
    ->orderBy('code', 'ASC')
    ->execute()
    ->fetchAllAssoc('code', PDO::FETCH_ASSOC);
  foreach ($result as $code => $row) {
    $output[] = "\$codes['{$code}'] = " . var_export($row, TRUE) . ';';
  }
  $output[] = 'return $codes;';
  $output = implode("\n", $output);
  return array('bounce_default_bounce_codes' => $output);
}

/**
 * Implements hook_features_rebuild().
 *
 * Fairly straightforward: load all the non-delivery report code defaults from
 * features and update the database.
 */
function bounce_code_features_rebuild($module) {
  if ($defaults = features_get_default('bounce_code', $module)) {
    $existing_codes = db_select('bounce_code_score', 'cs')
      ->fields('cs', array('code'))
      ->condition('code', array_keys($defaults), 'IN')
      ->execute()
      ->fetchCol();
    foreach ($defaults as $code => $data) {
      if (in_array($code, $existing_codes)) {
        drupal_write_record('bounce_code_score', $data, 'code');
      }
      else {
        drupal_write_record('bounce_code_score', $data);
      }
    }
  }
}

/**
 * Implements hook_features_revert().
 *
 * Reverting is the same as rebuilding in this case.
 */
function bounce_code_features_revert($module) {
  return bounce_code_features_rebuild($module);
}

/**
 * Implements hook_features_export().
 *
 * Used to add dependencies in this case, though other forms of features
 * export do more complex things.
 *
 * @param array $data
 *   An array of variable names in this case.
 * @param array $export
 *   The export definition.
 */
function bounce_code_features_export($data, &$export, $module_name = '') {

  /*
  This code is basically copied from hook_features_export() implementations
  found in the /include/*.inc files in the features module. Look through
  those files for further examples of how to do this.
  */

  $export['dependencies']['features'] = 'features';

  $map = features_get_default_map('bounce_code', '_bounce_code_identifier');
  foreach ($data as $varname) {
    // If this variable is provided by a different module, add it as a
    // dependency.
    if (isset($map[$varname]) && $map[$varname] != $module_name) {
      $export['dependencies'][$map[$varname]] = $map[$varname];
    }
    else {
      $export['features']['bounce_code'][$varname] = $varname;
    }
  }

  // Add the necessary dependency on this module.
  $export['dependencies']['bounce'] = 'bounce';

  $pipe = array();
  return $pipe;
}

/**
 * A trivial callback function that is passed to features_get_default_map.
 */
function _bounce_code_identifier($bounce_code) {
  return $bounce_code;
}
