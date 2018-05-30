<?php

/**
 * @file
 * Functions related to the tracking the file usage of embedded media.
 */


/**
 * Implements hook_field_attach_insert().
 */
function media_embed_field_attach_insert($entity_type, $entity) {
  media_embed_file_usage_update($entity_type, $entity);
}


/**
 * Implements hook_field_attach_update().
 */
function media_embed_field_attach_update($entity_type, $entity) {
  media_embed_file_usage_update($entity_type, $entity);
}


/**
 * Implements hook_field_attach_delete_revision().
 */
function media_embed_field_attach_delete_revision($entity_type, $entity) {
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $references = media_embed_file_usage_parse($entity_type, $entity);
  foreach ($references as $id => $count) {
    $file = file_load($id);
    $file && file_usage_delete($file, 'media_embed', $entity_type, $entity_id, $count);
  }
}


/**
 * Implements hook_entity_delete().
 */
function media_embed_entity_delete($entity, $type) {
  list($entity_id) = entity_extract_ids($type, $entity);
  db_delete('file_usage')
    ->condition('module', 'media_embed')
    ->condition('type', $type)
    ->condition('id', $entity_id)
    ->execute();
}


/**
 * Add file usage from file references in an entity's text fields.
 *
 * @param string $entity_type
 *   Entity type.
 * @param object $entity
 *   Entity object.
 */
function media_embed_file_usage_update($entity_type, $entity) {
  if (!empty($entity->file_usage_processed['media_embed'])) {
    return;
  }
  $references = media_embed_file_usage_parse($entity_type, $entity);
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  if (empty($entity->revision) && empty($entity->old_vid) && empty($entity->is_new) && !empty($entity->original)) {
    $old_references = media_embed_file_usage_parse($entity_type, $entity->original);
    foreach ($old_references as $id => $old_count) {
      $count = !empty($references[$id]) ? $references[$id] : 0;
      if ($old_count > $count) {
        $deprecate = $old_count - $count;
        $file = file_load($id);
        $file && file_usage_delete($file, 'media_embed', $entity_type, $entity_id, $deprecate);
        unset($references[$id]);
      }
      elseif ($old_count == $count) {
        unset($references[$id]);
      }
      else {
        $references[$id] = $count - $old_count;
      }
    }
  }
  foreach ($references as $id => $count) {
    $file = file_load($id);
    $file && file_usage_add($file, 'media_embed', $entity_type, $entity_id, $count);
  }
  $entity->file_usage_processed['media_embed'] = TRUE;
}


/**
 * Parse file references from an entity's text fields and return them as an array.
 *
 * @param string $entity_type
 *   Entity type.
 * @param object $entity
 *   Entity object.
 *
 * @return array
 *   An associative array where keys are file IDs and values are file usage count.
 */
function media_embed_file_usage_parse($entity_type, $entity) {
  $references = array();
  $fields = media_embed_text_processing_fields($entity_type, $entity);
  foreach ($fields as $field_name) {
    $field_items = field_get_items($entity_type, $entity, $field_name);
    if ($field_items) {
      foreach ($field_items as $field_item) {
        preg_match_all('#' . MEDIA_EMBED_TOKEN_PATTERN . '#', $field_item['value'], $matches);
        foreach ($matches[1] as $id) {
          $file = file_load($id);
          if ($file) {
            isset($references[$id]) ? ++$references[$id] : $references[$id] = 1;
          }
        }
      }
    }
  }

  return $references;
}


/**
 * Returns an array containing the names of all fields that perform text filtering.
 *
 * @param string $entity_type
 *   Entity type.
 * @param object $entity
 *   Entity object.
 *
 * @return array
 */
function media_embed_text_processing_fields($entity_type, $entity) {
  list(, , $bundle) = entity_extract_ids($entity_type, $entity);
  $fields = field_info_instances($entity_type, $bundle);
  $items = array();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['settings']['text_processing'])) {
      $items[] = $field_name;
    }
  }

  return $items;
}
