<?php
/**
 * @file
 * Allow new revisions to be schedule even if there is a published revision.
 */

/**
 * Check whether we should add a field to schedule publishing of a new revision.
 *
 * @param array $form
 *   A form API form.
 */
function scheduler_workbench_add_revision_publish_on_field_check($form) {
  // First, check that this is a scheduler form, and that the node type we
  // are dealing with is workbench moderated.
  if (TRUE === isset($form['scheduler_settings']) && isset($form['#node']) &&
    workbench_moderation_node_type_moderated($form['#node']->type)
  ) {

    $node = $form['#node'];
    // There are 2 cases for which we have different condition.
    // Scheduler settings in the node-edit form.
    if (isset($form['#node_edit_form']) && $form['#node_edit_form'] == TRUE) {

      // In this case, we add the the field if we have a published revision
      // already.
      if (isset($node->workbench_moderation['published'])) {
        return TRUE;
      }
    }
    // Scheduler settings in scheduler tab form, or in any other instance
    // that is not in the node-edit form, or a direct clone of that form.
    else {
      // Since we are not in the node-edit form where we know a new draft is
      // being created, we must check that there is a published revision, and
      // that the current revision is not the same as the published (a new
      // draft).
      $published_vid = $node->workbench_moderation['published']->vid;
      $current_vid = $node->workbench_moderation['current']->vid;
      if (isset($node->workbench_moderation['published']) &&
        ($current_vid != $published_vid)
      ) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
 * Add the revision_publish_on field to the forms with scheduler settings.
 *
 * @param array $form
 *   A form API form.
 */
function scheduler_workbench_add_revision_publish_on_field(&$form) {
  if (scheduler_workbench_add_revision_publish_on_field_check($form)) {
    // The revision_publish_on field is a copy of the publish_on field, so it
    // is safest to check that publish_on exists.
    if (isset($form['scheduler_settings']['publish_on'])) {
      unset($form['#node']->publish_on);

      $form['scheduler_settings']['revision_publish_on'] = $form['scheduler_settings']['publish_on'];
      $form['scheduler_settings']['revision_publish_on']['#weight'] = 0;
      $form['scheduler_settings']['revision_publish_on']['#title'] = t('Publish this revision on');
      $form['scheduler_settings']['revision_publish_on']['#disabled'] = FALSE;
      $description = $form['scheduler_settings']['revision_publish_on']['#description'];
      $description = t('Provide date and time when you want this draft to be automatically published. ') . $description;
      $form['scheduler_settings']['revision_publish_on']['#description'] = $description;

      // If this scheduler node form comes from a non-node-edit form, no
      // node hooks will be called. We need to fake the node calls by
      // adding our own validate and submit callbacks to the form.
      if (!isset($form['#node_edit_form'])) {
        $form['#submit'][] = "scheduler_workbench_scheduler_node_form_submit";
        $form['#validate'][] = "scheduler_workbench_scheduler_node_form_validate";
      }

      // Load js.
      $path = drupal_get_path('module', 'scheduler_workbench');
      drupal_add_js($path . '/js/scheduler_workbench.js', array('weight' => 99));
    }
  }
}
