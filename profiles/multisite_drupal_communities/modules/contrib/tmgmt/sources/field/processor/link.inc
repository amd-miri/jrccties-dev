<?php
/**
 * @file
 * Field processor for link.module.
 */

/**
 * Implements hook_tmgmt_source_translation_structure().
 *
 * This hook is implemented on behalf of the link.module.
 */
function link_tmgmt_source_translation_structure($entity_type, $entity, $field, $instance, $langcode, $items) {
  $structure = array();
  if (!empty($items)) {
    $structure['#label'] = check_plain($instance['label']);
    foreach ($items as $delta => $value) {
      $structure[$delta]['#label'] = t('Delta #@delta', array('@delta' => $delta));
      // Translatable columns.
      foreach (array('url', 'title') as $column) {
        if (isset($value[$column])) {
          $structure[$delta][$column] = array(
            '#label' => t('@field (@column)', array('@field' => $structure['#label'], '@column' => $column)),
            '#text' => $value[$column],
            '#translate' => TRUE,
          );
        }
      }

      // The 'attributes' columns might contain translatable strings.
      if (!empty($value['attributes']['title'])) {
        $structure[$delta]['attributes:title'] = array(
          '#label' => t('@field (@column)', array('@field' => $structure['#label'], '@column' => 'title attribute')),
          '#text' => $value['attributes']['title'],
          '#translate' => TRUE,
        );
      }

      // Non-translatable columns.
      $structure[$delta]['attributes'] = array(
        '#label' => '',
        '#text' => $value['attributes'],
        '#translate' => FALSE,
      );
    }
  }
  return $structure;
}

/**
 * Implements hook_field_type_tmgmt_populate_entity().
 *
 * This hook is implemented on behalf of the link.module.
 */
function link_field_type_tmgmt_populate_entity($entity_type, $entity, $field, $instance, $langcode, $data, $use_field_translation) {
  $field_name = $field['field_name'];
  $field_langcode = $field['translatable'] ? $langcode : LANGUAGE_NONE;
  // When not using field translation, make sure we're not storing multiple
  // languages.
  if (!$use_field_translation) {
    $entity->{$field_name} = array($field_langcode => array());
  }

  foreach (element_children($data[$field_name]) as $delta) {
    $columns = array();
    // Prepare first the 'attributes' column, if contains a translated 'title'.
    if (!empty($data[$field_name][$delta]['attributes:title']['#translation']['#text'])) {
      $data[$field_name][$delta]['attributes']['#text']['title'] = $data[$field_name][$delta]['attributes:title']['#translation']['#text'];
    }
    // This value has been packed in $data[$field_name][$delta]['attributes'].
    unset($data[$field_name][$delta]['attributes:title']);

    foreach (element_children($data[$field_name][$delta]) as $column) {
      if (isset($data[$field_name][$delta][$column]['#translation']['#text'])) {
        $columns[$column] = $data[$field_name][$delta][$column]['#translation']['#text'];
      }
      // For elements which are not translatable, keep using the original value.
      elseif (isset($data[$field_name][$delta][$column]['#translate']) && $data[$field_name][$delta][$column]['#translate'] == FALSE) {
        $columns[$column] = $data[$field_name][$delta][$column]['#text'];
      }
    }
    // Make sure the array_merge() gets an array as a first parameter.
    if (!isset($entity->{$field_name}[$field_langcode][$delta])) {
      $entity->{$field_name}[$field_langcode][$delta] = array();
    }
    $entity->{$field_name}[$field_langcode][$delta] = array_merge($entity->{$field_name}[$field_langcode][$delta], $columns);
  }
}
