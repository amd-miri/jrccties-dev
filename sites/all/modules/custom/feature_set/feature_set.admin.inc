<?php
/**
 * @file
 * Administration forms for feature_sets.
 */

/**
 * Define the administration form.
 */
function feature_set_admin_form($form, &$form_state, $install_state = NULL) {
  $featuresets = feature_set_get_featuresets($install_state);

  $form = array();

  if (!empty($install_state)) {
    // Indicate we are in an install.
    $form['install'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }

  // Really too bad tableselect has no easy way to disable a single checkbox...
  if (!empty($featuresets)) {
    foreach ($featuresets as $featureset => $details) {
      if (!$details['meta']) {
        $elementname = 'featureset-' . $featureset;
        $form[$elementname] = array(
          '#type' => 'checkbox',
          '#disabled' => empty($details['status']) ? TRUE : FALSE,
          // Disabled the widget if its in an inconsistent.
          '#default_value' => (FEATURE_SET_ENABLED & $details['status']) ? 1 : 0,
          '#featuresetinfo' => array(
            'featureset' => $details['title'],
            'description' => $details['description'],
            'icon' => empty($details['icon']) ? '' : $details['icon'],
          ),
        );

        if (empty($details['status'])) {
          $info = t('This feature set is in an inconsistent state. Please use the following links to correct the feature set.');
          $variables = array(
            'links' => array(
              'feature-set-enable-link' => array(
                'title' => t('Enable'),
                'href' => 'admin/structure/feature-set/enable/' . $featureset,
              ),
              'feature-set-disable-link' => array(
                'title' => t('Disable'),
                'href' => 'admin/structure/feature-set/disable/' . $featureset,
              ),
            ),
          );
          $form[$elementname]['#featuresetinfo']['status'] = $info . theme('links', $variables);
          $form[$elementname]['#featuresetinfo']['class'] = 'warning';
        }
        else {
          if ($form[$elementname]['#default_value']) {
            $form[$elementname]['#featuresetinfo']['status'] = t('OK');
            $form[$elementname]['#featuresetinfo']['class'] = 'status';
          }
          else {
            $form[$elementname]['#featuresetinfo']['status'] = t('Disabled');
            $form[$elementname]['#featuresetinfo']['class'] = 'disabled';
          }
        }
      }
    }
  }

  $form['#theme'] = 'feature_set_admin_form';

  $form['submit'] = array('#type' => 'submit', '#value' => t('Update Feature Sets'));

  $form['#submit'][] = 'feature_set_admin_form_submit';
  $form['#submit'][] = 'feature_set_adjust_meta_feature_sets';

  return $form;
}

/**
 * Theme the administration form.
 *
 * Tableselect does not have a method to easily disable a single checkbox.
 */
function theme_feature_set_admin_form($vars) {
  $form = $vars['form'];
  drupal_add_css(drupal_get_path('module', 'feature_set') . '/feature-set.css');
  $header = array('', 'Feature Set', 'status');

  $rows = array();
  foreach (element_children($form) as $key) {
    if (strpos($key, 'featureset-') === 0) {
      // Set the icon if available.
      if (!empty($form[$key]['#featuresetinfo']['icon'])) {
        $variables = array(
          'path' => $form[$key]['#featuresetinfo']['icon'],
          'alt' => t('@feature-set icon', array('@feature-set' => $form[$key]['#featuresetinfo']['featureset'])),
          'attributes' => array(),
        );
        $icon = '<div class="feature-set-image">' . theme_image($variables) . '</div>';
      }
      else {
        $icon = '';
      }
      $featureset = '<div class="feature-set">';
      $featureset .= '<span class="name">' . $form[$key]['#featuresetinfo']['featureset'] . '</span>';
      if (!empty($form[$key]['#featuresetinfo']['description'])) {
        $featureset .= '<span class="description">' . $form[$key]['#featuresetinfo']['description'] . '</span>';
      }
      $featureset .= '</div>';

      $row = array(
        'data' => array(
          drupal_render($form[$key]),
          $icon . $featureset,
          array(
            'data' => $form[$key]['#featuresetinfo']['status'],
            'class' => array($form[$key]['#featuresetinfo']['class'], 'messages'),
          ),
        ),
      );
      $rows[] = $row;

    }
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Submit handler for our form.
 *
 * This only processes feature sets that are in a known state.
 */
function feature_set_admin_form_submit($form, &$form_state) {
  $featuresets = feature_set_get_featuresets();
  $operations = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'featureset-') === 0) {
      $featureset = str_replace('featureset-', '', $key);
      // Only operate if its in an 'OK' status.
      if (isset($featuresets[$featureset]) && $featuresets[$featureset]['status'] != 0) {
        if ($form_state['values'][$key]) {
          $operations[] = array('feature_set_enable_feature_set', array($featuresets[$featureset]));
        }
        else {
          $operations[] = array('feature_set_disable_feature_set', array($featuresets[$featureset]));
        }
      }
    }
  }

  if (!empty($operations)) {
    // We might be in an install profile an thus have another batch active.
    $batch['operations'] = $operations;
    $batch['title'] = t('Adjusting feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // Store the feature sets to enable in session to get them back later.
      $_SESSION['feature_set_batch'] = $batch;
    }
  }
}

function feature_set_adjust_meta_feature_sets($form, &$form_state) {
  $featuresets = feature_set_get_featuresets();
  $metasets = feature_set_get_meta_feature_sets($form_state);

  if (!empty($metasets['enable'])) {
    foreach ($metasets['enable'] as $enable) {
      $operations[] = array('feature_set_enable_feature_set', array($featuresets[$enable]));
    }
  }
  if (!empty($metasets['disable'])) {
    foreach ($metasets['disable'] as $disable) {
      $operations[] = array('feature_set_disable_feature_set', array($featuresets[$disable]));
    }
  }

  if (!empty($operations)) {
    // We might be in an install profile an thus have another batch active.
    $batch['operations'] = $operations;
    $batch['title'] = t('Adjusting meta feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    watchdog('debug', '<pre>' . var_export($batch, 1) . '</pre>');
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // Store the feature sets to enable in session so we can get them back later.
      $_SESSION['feature_set_meta_batch'] = $batch;
    }
  }

}

function feature_set_install_enable() {
  if (!empty($_SESSION['feature_set_batch'])) {
    return $_SESSION['feature_set_batch'];
  }
}

function feature_set_meta_install_enable() {
  if (!empty($_SESSION['feature_set_meta_batch'])) {
    return $_SESSION['feature_set_meta_batch'];
  }
}

/**
 * Return install time tasks.
 */
function feature_set_install_tasks() {
  $tasks = array(
    'feature_set_admin_form' => array(
      'display_name' => st('Feature Set Options'),
      'type' => 'form',
    ),
    'freature_set_install_modules' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => 'feature_set_install_enable',
    ),
    'feature_set_install_meta_feature_sets' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => 'feature_set_meta_install_enable',
    ),
  );
  return $tasks;
}

/**
 * Disable a feature set, intended to disable an inconsistent feature set.
 */
function feature_set_disable_url($form, $form_state, $featureset) {
  $form['featureset'] = array('#type' => 'value', '#value' => $featureset);
  return confirm_form(
    $form,
    t('Are you sure you want to disable %title?', array('%title' => $featureset)),
    'admin/structure/feature-set'
  );
}

/**
 * Submit Handler to disable a feature set.
 */
function feature_set_disable_url_submit($form, &$form_state) {
  $featuresets = $featuresets = feature_set_get_featuresets();
  if (isset($featuresets[$form_state['values']['featureset']])) {
    feature_set_disable_feature_set($featuresets[$form_state['values']['featureset']]);
  }
  else {
    drupal_set_message(t('The feature set "%featureset" could not be found. Please check the link and try again', array('%featureset' => $form_state['values']['featureset'])), 'error');
  }

  $form_state['redirect'] = 'admin/structure/feature-set';
}

/**
 * Enable a feature set intended to enable an inconsistent feature set.
 */
function feature_set_enable_url($form, $form_state, $featureset) {
  $form['featureset'] = array('#type' => 'value', '#value' => $featureset);
  return confirm_form(
    $form,
    t('Are you sure you want to enable %title?', array('%title' => $featureset)),
    'admin/structure/feature-set'
  );
}

/**
 * Submit Handler to intended to enable an inconsistent feature set.
 */
function feature_set_enable_url_submit($form, &$form_state) {
  $featuresets = $featuresets = feature_set_get_featuresets();
  if (isset($featuresets[$form_state['values']['featureset']])) {
    feature_set_enable_feature_set($featuresets[$form_state['values']['featureset']]);
  }
  else {
    drupal_set_message(t('The feature set "%featureset" could not be found. Please check the link and try again', array('%featureset' => $form_state['values']['featureset'])), 'error');
  }

  $form_state['redirect'] = 'admin/structure/feature-set';
}
