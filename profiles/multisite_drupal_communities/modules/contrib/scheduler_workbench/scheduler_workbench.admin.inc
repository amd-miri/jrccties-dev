<?php

/**
 * Form callback for the settings form.
 *
 * @see system_settings_form()
 */
function scheduler_workbench_allowed_status_form($form, &$form_state) {
  $options = workbench_moderation_state_labels();
  $form['scheduler_workbench_allowed_status'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allowed Workbench Moderation status for scheduling publication'),
    '#options' => $options,
    '#default_value' => _scheduler_workbench_allowed_status(),
    '#description' => t('This is a list of status from Workbench Moderation. By default, the status enabled are those with a transition to the publish status, currently (@status). You can choose what status to allow revisions for scheduling publication. When Scheduler Workbench tries to publish a revision it will check if the current state is one of the selected from this list.', array('@status' => implode(',', _scheduler_workbench_allowed_status()))),
  );
  return system_settings_form($form);
}
