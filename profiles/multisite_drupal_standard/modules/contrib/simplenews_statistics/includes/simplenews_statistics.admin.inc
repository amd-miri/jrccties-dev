<?php
/**
 * @file
 * Simplenews statistics file containing all admin settings and functions.
 */

/**
 * Simplenews Google Analytics settings.
 */
function simplenews_statistics_admin_settings_form($form, &$form_state) {
  // General settings for Simplenews Statistics.
  $form['simplenews_statistics'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
  );

  $form['simplenews_statistics']['simplenews_statistics_track_test'] = array(
    '#type' => 'checkbox',
    '#title' => t('Track newsletter test sends'),
    '#description' => t('Disabling this will stop the tracking of opens and clicks for test emails. Links replacements will still be done for those test sends, but no statistics will be recorded.'),
    '#default_value' => variable_get('simplenews_statistics_track_test', 0),
  );

  $form['simplenews_statistics']['simplenews_statistics_track_mailto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Track mailto links'),
    '#description' => t('In some cases tracking clicks on email addresses wil result in a blank browser window. Disabling this options prevents that.'),
    '#default_value' => variable_get('simplenews_statistics_track_mailto', 1),
  );

  $form['simplenews_statistics']['simplenews_statistics_archive_days'] = array(
    '#type' => 'textfield',
    '#title' => t('Days to keep open and click records'),
    '#description' => t('Specify a number of days beyond which the open and click records for newsletters will be deleted. This can help control the growth of the open and click database tables over time. The site cron must be correctly configured. A value of 0 disables this setting.'),
    '#default_value' => variable_get('simplenews_statistics_archive_days', 0),
    '#size' => 4,
    '#maxlength' => 4,
  );

  // Check for HTML formats.
  $categories = simplenews_categories_load_multiple();
  foreach ($categories as $category) {
    if ($category->format !== 'html') {
      drupal_set_message(t('Newsletter category %name format has not been set to HTML. There will be no statistics recorded for this newsletter.', array('%name' => $category->name)), 'warning');
    }
  }

  return system_settings_form($form);
}
