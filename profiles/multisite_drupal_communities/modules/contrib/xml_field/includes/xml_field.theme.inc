<?php
/**
 * @file
 * theme functions for the module
 *
 * @ingroup xml_field
 * @{
 */

/**
 * Formats xml.
 *
 * @param array $vars
 * - xml: anything valid for xml_field_format(). If this is invalid, it will be
 * passed through check_plain and then output.
 * - attributes: array
 * - options: array
 *   - break: string: line break char
 *   - tab: string: tab char
 *   - htmlentities: bool: convert xml tags to htmlentities or not
 * - header: array or FALSE
 *   - FALSE: the xml header will not be printed
 *   - array():  Attributes to apply to the xml header
 *
 * @return string
 *
 * @ingroup themeable
 *
 * @see xml_field_format()
 */
function theme_xml($vars) {
  $vars['options'] += array(
    'colorized' => TRUE,
    'tab' => '&nbsp;&nbsp;',
  );

  $vars['attributes']['class'][] = 'xml-field-xml';
  $output = '';
  if (!empty($vars['xml'])) {
    if (xml_field_is_valid_xml_string($vars['xml'])) {
      $output .= xml_field_format($vars['xml'], $vars['options'], $vars['header']) . "\n";
    }
    else {
      $vars['attributes']['class'][] = 'invalid-xml';
      $output = check_plain($vars['xml']);
    }
  }

  // Add in the colorized spans
  if ($vars['options']['colorized']) {
    $vars['attributes']['class'][] = 'colorized';
    drupal_add_css(drupal_get_path('module', 'xml_field') . '/xml_field.css');
    $output = preg_replace('/(\S+)(=)(&quot;.*?&quot;)/s', '<span class="attribute">\1</span>\2<span class="string">\3</span>', $output);
    $output = preg_replace('/(&gt;)(.*?)(&lt;)/s', '\1<span class="value">\2</span>\3', $output);
  }

  $output = '<pre><code' . drupal_attributes($vars['attributes']) . '>' . $output . '</code></pre>';

  return $output;
}

/**
 * Formats an xml form element as it is used in forms
 *
 * @param array $vars
 *
 * @return string
 *
 * @ingroup themeable
 */
function theme_xmltext($vars) {
  $element = &$vars['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array($element['#type']));


  $wrapper_attributes = array(
    'class' => array($element['#type'] . '-wrapper'),
  );

  $build    = array();
  $build['#attached']['css'][] =  array(
    'type' => 'file', 
    'data' => drupal_get_path('module', 'xml_field') . '/xml_field.css',
  );

  $build['textarea'] = array(
    '#type' => 'textarea',
    '#value' => $element['#value'],
    '#resizable' => $element['#resizable'],
    '#attributes' => $element['#attributes'],
    '#suffix' => $element['#children'],
  );

  return drupal_render($build);
}
