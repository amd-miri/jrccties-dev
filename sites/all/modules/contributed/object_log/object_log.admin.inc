<?php
/**
 * Menu callback function for admin/reports/object_log.
 */
function object_log_overview_page() {
  $build = array();
  $build['object_log_clear'] = drupal_get_form('object_log_clear_form');
  $build['object_log'] = object_log_build_log();
  return $build;
}

/**
 * Build a render array showing objects stored in the object log.
 *
 * @param $label
 *   If set, create links for viewing the new object alongside the current one.
 * @return
 *   A render array for a table of links to stored objects.
 */
function object_log_build_log($label = NULL) {
  $rows = array();
  $header = array(
    array(
      'data' => t('Label'),
      'field' => 'ol.label',
    ),
    array(
      'data' => t('Date'),
      'field' => 'ol.created',
      'sort' => 'desc',
    ),
  );
  $query = db_select('object_log', 'ol')->extend('PagerDefault')->extend('TableSort');
  $query->fields('ol', array('label', 'created'));
  $result = $query
    ->limit(25)
    ->orderByHeader($header)
    ->execute();
  
  foreach ($result as $item) {
    if ($label) {
      $link = l($item->label, 'admin/reports/object_log/' . $label . '/' . $item->label);
    }
    else {
      $link = l($item->label, 'admin/reports/object_log/' . $item->label);
    }
    $rows[] = array(
      $link,
      format_date($item->created, 'short'),
    );
  }
  
  $build = array(
    'object_log' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array('id' => 'object_log'),
      '#empty' => t('No objects stored.'),
    ),
    'object_log_pager' => array(
      '#theme' => 'pager',
    ),
  );
  
  return $build;
}

/**
 * Menu callback function for "admin/reports/object_log/$label".
 *
 * This function will also look at the given query path to find any additional
 * objects that may have been requested.
 *
 * @param $label
 *   The label of an object to inspect.
 */
function object_log_object_page($label) {
  // Determine all of the requested objects.
  if (strpos($_GET['q'], 'admin/reports/object_log') === 0) {
    $labels = explode('/', str_replace('admin/reports/object_log/', '', $_GET['q']));
  }
  else {
    $labels = array($label);
  }
  $build = object_log_build_objects($labels);
  
  // Display the log table so the user can select another object to compare to
  // the given object.
  $build['object_log'] = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => t('Select an object to compare with @label', array('@label' => $label)),
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
    ),
  );
  $build['object_log'] += object_log_build_log($label);

  return $build;
}

/**
 * Display stored objects for inspection.
 *
 * @param $labels
 *   An array of labels representing objects to be displayed.
 * @return
 *   A render array of objects ready for inspection.
 */
function object_log_build_objects($labels = array()) {
  $build = array();
  $build['objects'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'object_log_objects',
      'class' => array('object-log', 'object-count-' . count($labels), 'clearfix'),
    ),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'object_log') . '/object_log.admin.css'),
    ),
  );

  foreach ($labels as $delta => $label) {
    if ($object = object_log_build_object($label)) {
      $build['objects'][$delta] = $object;
    }
    else {
      $markup = '<div class="object"><h4 class="object-label">' . check_plain($label) . '</h3><p>' . t('Not in log.') . '</p></div>';
      $build['objects'][$delta] = array('#type' => 'markup', '#markup' => $markup);
    }
  }
  return $build;
}

/**
 * Build a render array for a stored object.
 *
 * @param $label
 *   The label of the object to display.
 * @return
 *   A render array for the object.
 */
function object_log_build_object($label) {
  $log = object_log_retrieve($label);
  if (!$log) {
    return FALSE;
  }
  $object = $log->data;
  $build = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('object_wrapper'),
    ),
  );
  $build['title'] = array(
    '#type' => 'markup',
    '#markup' => check_plain($label),
    '#prefix' => '<h4 class="object-label">',
    '#suffix' => '</h4>',
  );
  $build['object'] = array(
    '#type' => 'markup',
    '#markup' => kprint_r($object, TRUE, NULL),
    '#prefix' => '<div class="object">',
    '#suffix' => '</div>',
  );
  return $build;
}

/**
 * Form for clearing the object log.
 */
function object_log_clear_form($form, &$form_state) {
  $form = array();
  $form['clear'] = array(
    '#type' => 'submit', 
    '#value' => t('Clear object log'), 
    '#submit' => array('object_log_clear_form_submit'),
  );
  return $form;
}

/**
 * Submit callback for object_log_clear_form().
 */
function object_log_clear_form_submit($form, &$form_state) {
  object_log_clear_log();
  drupal_set_message(t('Object log cleared.'));
  $form_state['redirect'] = 'admin/reports';
}
