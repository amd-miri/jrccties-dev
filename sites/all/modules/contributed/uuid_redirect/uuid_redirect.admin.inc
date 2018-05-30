<?php

/**
 * @file
 * Administrative page callbacks for the UUID redirect module.
 */

/**
 * Form constructor for the UUID redirect settings form.
 *
 * @see uuid_redirect_settings_form_validate()
 * @ingroup forms
*/
function uuid_redirect_settings_form($form, &$form_state) {
  $form['uuid_redirect_external_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL of external site to redirect to'),
    '#description' => t('If a URL is provided, the paths below will be redirected to the corresponding paths on this site.'),
    '#default_value' => variable_get('uuid_redirect_external_base_url'),
  );
  $form['uuid_redirect_menu_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths to redirect'),
    '#description' => t('Specify pages by using their paths. Enter one path per line. For entity URLs that contain an ID in them, use the appropriate wildcard loader from the menu system in order for the redirect to work correctly. To limit the redirect to particular "bundles" of the entity (e.g., particular node types), add the bundle name after the loader (separated by "--").  For example, %node-delete will cause all node deletion pages to redirect to the corresponding node deletion page on the external site, whereas %node-delete-article will only do so for article nodes. Similarly, %user-edit will redirect all user edit pages.', array(
      '%node-delete' => 'node/%node/delete',
      '%node-delete-article' => 'node/%node--article/delete',
      '%user-edit' => 'user/%user/edit',
    )),
    '#default_value' => variable_get('uuid_redirect_menu_paths'),
  );

  return system_settings_form($form);
}

/**
 * Form validation handler for uuid_redirect_settings_form().
 */
function uuid_redirect_settings_form_validate($form, &$form_state) {
  $url_provided = !empty($form_state['values']['uuid_redirect_external_base_url']);
  if ($url_provided && !valid_url($form_state['values']['uuid_redirect_external_base_url'], TRUE)) {
    form_set_error('uuid_redirect_external_base_url', t('An invalid external site URL was provided.'));
  }
  // Force system_settings_form_submit() to trigger a menu rebuild only if the
  // paths we will be altering have changed.
  $alteration_status_changed = ($url_provided xor variable_get('uuid_redirect_external_base_url'));
  $paths_changed = ($form_state['values']['uuid_redirect_menu_paths'] != variable_get('uuid_redirect_menu_paths'));
  if ($alteration_status_changed || ($url_provided && $paths_changed)) {
    $form_state['values']['menu_rebuild_needed'] = TRUE;
  }
}
