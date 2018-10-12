<?php

/**
 * @file
 * Install helper functions.
 */

/**
 * Renames and migrates the data to a new field.
 *
 * @param string $old_name
 *   Old field name.
 * @param string $new_name
 *   New field name.
 */
function _nexteuropa_newsroom_rename_field($old_name, $new_name) {
  $old_field = field_info_field($old_name);

  if ($old_field) {
    // Create new field.
    $new_field = $old_field;
    $new_field['field_name'] = $new_name;
    $new_field_info = field_info_field($new_name);
    if (empty($new_field_info)) {
      field_create_field($new_field);
    }
  }

  if (!empty($old_field['bundles'])) {
    foreach ($old_field['bundles'] as $entity_type => $bundles) {
      foreach ($bundles as $bundle) {
        $old_instance = field_info_instance($entity_type, $old_name, $bundle);

        if ($old_instance) {
          $new_instance = $old_instance;
          $new_instance['field_name'] = $new_name;
          $new_instance_info = field_info_instance($entity_type, $new_name, $bundle);
          if (empty($new_instance_info)) {
            field_create_instance($new_instance);
          }

          // Migrate old fields' data to the new ones.
          $field_data = db_select('field_data_' . $old_name, 'old')
            ->fields('old')
            ->condition('entity_type', $entity_type)
            ->condition('bundle', $bundle)
            ->execute();

          while ($data = $field_data->fetchAssoc()) {
            $data_new = [];
            foreach ($data as $column => $value) {
              $column = str_replace($old_name, $new_name, $column);
              $data_new[$column] = $value;
            }

            db_insert('field_data_' . $new_name)
              ->fields($data_new)
              ->execute();
          }

          db_truncate('field_data_' . $old_name);

          // Migrate old fields' revision data to the new ones.
          $field_revision = db_select('field_revision_' . $old_name, 'old')
            ->fields('old')
            ->condition('entity_type', $entity_type)
            ->condition('bundle', $bundle)
            ->execute();

          while ($revision = $field_revision->fetchAssoc()) {
            $revision_new = [];
            foreach ($revision as $column => $value) {
              $column = str_replace($old_name, $new_name, $column);
              $revision_new[$column] = $value;
            }

            db_insert('field_revision_' . $new_name)
              ->fields($revision_new)
              ->execute();
          }

          db_truncate('field_revision_' . $old_name);
        }
      }
    }
  }
}

/**
 * Removes field group.
 *
 * @param array $groups
 *   Groups identifiers.
 */
function _nexteuropa_newsroom_remove_group(array $groups = []) {
  foreach ($groups as $group_id) {
    $query = db_delete('field_group');
    $query->condition('identifier', $group_id);
    $query->execute();
    cache_clear_all('field_groups', 'cache_field');
  }
}
