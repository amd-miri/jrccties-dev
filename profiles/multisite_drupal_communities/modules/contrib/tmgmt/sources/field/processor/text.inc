<?php

/**
 * @file
 * Field processor for text.module.
 */

/**
 * Implements hook_tmgmt_source_translation_structure().
 *
 * This hook is implemented on behalf of the core text module.
 */
function text_tmgmt_source_translation_structure($entity_type, $entity, $field, $instance, $langcode, $items) {
  $structure = array();
  if (!empty($items)) {
    $structure['#label'] = check_plain($instance['label']);
    foreach ($items as $delta => $value) {
      $structure[$delta]['#label'] = t('Delta #@delta', array('@delta' => $delta));
      $structure[$delta]['value'] = array(
        '#label' => $structure['#label'],
        '#text' => $value['value'],
        '#translate' => TRUE,
      );
      // Add format.
      $structure[$delta]['format'] = array(
        '#label' => '',
        '#text' => $value['format'],
        '#translate' => FALSE,
      );
      if ($field['type'] == 'text_with_summary' && !empty($value['summary'])) {
        $structure[$delta]['summary'] = array(
          '#label' => t('Summary'),
          '#text' => $value['summary'],
          '#translate' => TRUE,
        );
      }
    }
  }
  return $structure;
}
