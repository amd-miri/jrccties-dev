<?php

/**
 * @file
 * Set field to default value.
 */

$plugin = [
  'form'     => 'nexteuropa_newsroom_tamper_default_value_form',
  'callback' => 'nexteuropa_newsroom_tamper_default_value_callback',
  'name'     => 'Set default value if field is empty',
  'multi'    => 'direct',
  'category' => 'Other',
];

/**
 * Gets tamper form.
 *
 * @param object $importer
 *   Importer object.
 * @param string $element_key
 *   Element key.
 * @param array $settings
 *   Tamper settings.
 *
 * @return array
 *   Form array.
 */
function nexteuropa_newsroom_tamper_default_value_form($importer, $element_key, array $settings) {
  $form = [];

  $form['default_value'] = [
    '#type' => 'textarea',
    '#title' => t('Value'),
    '#default_value' => isset($settings['default_value']) ? $settings['default_value'] : '',
    '#description' => t('This field will be set to the value specified.'),
  ];

  $replace = [];

  foreach (feeds_tamper_get_unique_source_list($importer) as $source) {
    $replace[] = '[' . $source . ']';
  }

  $form['help'] = [
    '#type' => 'fieldset',
    '#title' => t('Available Replacement Patterns'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    '#value' => theme('item_list', ['items' => $replace]),
  ];

  return $form;
}

/**
 * Processes the value.
 *
 * @param FeedsParserResult $result
 *   Parsed results.
 * @param string $item_key
 *   Current item key.
 * @param string $element_key
 *   Element key.
 * @param string $field
 *   Field value.
 * @param array $settings
 *   Tamper settings.
 * @param string $source
 *   Source.
 */
function nexteuropa_newsroom_tamper_default_value_callback(FeedsParserResult $result, $item_key, $element_key, &$field, array $settings, $source) {
  // If the field is empty we set default value.
  if (!$field) {
    $trans = [];
    $item = $result->items[$item_key];
    foreach ($item as $key => $value) {
      $trans['[' . $key . ']'] = is_array($value) ? reset($value) : $value;
    }
    $field = strtr($settings['default_value'], $trans);
  }
}
