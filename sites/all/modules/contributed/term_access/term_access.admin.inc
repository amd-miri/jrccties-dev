<?php

/**
 * @file
 * Admin page callbacks for the Term Access module.
 *
 */

/**
 * Form builder; Configure the Term Access settings.
 *
 * @see system_settings_form()
 */
function term_access_settings_form($form, &$form_state) {
	$form['#theme'] = 'term_access_settings_form';
	
	$tas = variable_get('term_access_settings', array()); // We will keep this variable name short for aesthetic reasons
	$term_access_field = variable_get('term_access_field', 'taxonomy_term_reference');
	
	$form['term_access_settings'] = array(
		'#type' => 'fieldset',
		'#title' => t('Node types'),
		'#tree' => TRUE,
	);
	
	$types = node_type_get_names();	
	$actions = array(t('Do nothing'), t('Manage access'));
	$permissions = array(
		TERM_ACCESS_VIEW => t('View'),
		TERM_ACCESS_UPDATE => t('Update'),
		TERM_ACCESS_DELETE => t('Delete'),
	);
	
	foreach ($types as $type => $name) {
		// Query {field_config_instance} for fields for this node type that are also used in the user entity.
		$query = db_select('field_config_instance', 'fi');
		$query->join('field_config', 'f', 'fi.field_id = f.id');
		$query->join('field_config_instance', 'fi2', 'fi.field_id = fi2.field_id');		
		$result = $query
			->condition('fi.entity_type', 'node')
			->condition('fi.bundle', $type)
			->condition('f.type', $term_access_field)
			->condition('fi2.entity_type', 'user')
			->fields('f', array('field_name'))
			->execute();
		
		// Build our term reference field instances array
		$fields = array();
		foreach ($result as $field) {
			$fields[$field->field_name] = $field->field_name;
		}
		
		// Determine if the 'manage access' option for this node type is selected
		if (isset($form_state['values'])) {
			$access = $form_state['values']['term_access_settings'][$type]['action'] ? TRUE : FALSE;
		}
		elseif (isset($tas[$type]['action'])) {
			$access = $tas[$type]['action'] ? TRUE : FALSE;
		}
		else {
			$access = FALSE;
		}
		
		$form['term_access_settings'][$type] = array(
			'#type' => 'fieldset',
			'#title' => $name,
			'#collapsed' => !$access,
			'#collapsible' => TRUE,
			'#tree' => TRUE,
			'#prefix' => '<div id="' . $type . '-manage-fieldset-wrapper">',
			'#suffix' => '</div>',
		);
		if (empty($fields)) {
			$form['term_access_settings'][$type]['#description'] = t('There were no relavant field instances found of type <strong>@field_name</strong>. Make sure that the field is attached to node type <a href="@type_url">@type</a> and that the <em>same field instance</em> is attached to <a href="@user_url">User</a>.', array('@field_name' => $term_access_field, '@type' => $name, '@user_url' => url('admin/config/people/accounts/fields'), '@type_url' => url('admin/structure/types/manage/' . $type . '/fields')));
		}
		$form['term_access_settings'][$type]['action'] = array(
			'#type' => 'radios',
			'#title' => t('Action'),
			'#options' => $actions,
	    '#ajax' => array(
	      'wrapper' => $type . '-manage-fieldset-wrapper',
	      'callback' => 'term_access_settings_form_manage_callback',
	      'effect' => 'fade',
	    ),
	    '#default_value' => $access ? 1 : 0,
	    '#access' => !empty($fields),
	    '#description' => !$access ? t('This node type is currently being ignored. To manage its access, select <strong>Manage access</strong> from the Action list above.') : '',
		);
		$form['term_access_settings'][$type]['manage'] = array(
			'#type' => 'fieldset',
			'#title' => t('Manage access'),
			'#access' => $access,
		);
		$form['term_access_settings'][$type]['manage']['fields'] = array(
			'#type' => 'fieldset',
			'#title' => t('Fields'),
			'#theme' => 'term_access_settings_form_fields',
			'#description' => t('Select the <strong>@field_name</strong> fields that reference the taxonomy terms that this module should manage. Node access will <em>not</em> be altered by fields not checked here. If <strong>Ignore when empty</strong> is checked then when the user does not have any terms in that field, they will still get elevated permissions if other fields match.', array('@field_name' => $term_access_field)),
		);
		foreach ($fields as $field) {
			$form['term_access_settings'][$type]['manage']['fields'][$field]['status'] = array(
				'#type' => 'checkbox',
				'#title' => $field,
				'#default_value' => isset($tas[$type]['manage']['fields'][$field]['status']) ? $tas[$type]['manage']['fields'][$field]['status'] : 0,
			);
			$form['term_access_settings'][$type]['manage']['fields'][$field]['ignore'] = array(
				'#type' => 'checkbox',
				'#title' => t('Ignore when empty'),
				'#default_value' => isset($tas[$type]['manage']['fields'][$field]['ignore']) ? $tas[$type]['manage']['fields'][$field]['ignore'] : 0,
			  '#states' => array(
			    // Only show this field when the 'status' checkbox is enabled.
			    'disabled' => array(
			      ':input[name="term_access_settings[article][manage][fields][' . $field . '][status]"]' => array('checked' => FALSE),
			    ),
			  ),
			);
		}
		$form['term_access_settings'][$type]['manage']['permissions'] = array(
			'#type' => 'checkboxes',
			'#title' => t('Permissions'),
			'#options' => $permissions,
			'#description' => t('These permissions will be used for users who have the same taxonomy terms as the node they are trying to access. For users who do not have the same terms, access is ignored which allows other modules to determine the node access. If no permissions are checked, users who have the same terms will be denied access.'),
			'#default_value' => isset($tas[$type]['manage']['permissions']) ? $tas[$type]['manage']['permissions'] : array(),
		);		
	}

	$form['advanced'] = array(
		'#type' => 'fieldset',
		'#title' => t('Advanced'),
	);
	$form['advanced']['term_access_field'] = array(
		'#type' => 'textfield',
		'#title' => t('Field type'),
		'#description' => t('This is the field type name used to make term references to nodes and users. It is usually best to leave this as <em>taxonomy_term_reference</em> which is the default term reference field type provided by the Taxonomy module.'),
		'#default_value' => $term_access_field,
	);
	
	return system_settings_form($form);
}

/**
 * Callback for term_access_settings_form.
 *
 * @return renderable array (the manage access fieldset)
 */
function term_access_settings_form_manage_callback($form, $form_state) {
	// Get the type from the element that triggered this AJAX callback
	$type = $form_state['triggering_element']['#array_parents'][1];
	// Return only the specific fieldset for it to get updated
	return $form['term_access_settings'][$type];
}

 /**
 * Returns HTML for the term access settings form 'fields' fieldset.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element representing the form element.
 *
 */
function theme_term_access_settings_form_fields($variables) {
  $element = $variables['element'];
	
  $header = array(
    t('Name'),
    t('Empty Ignore'),
  );
	
	foreach (element_children($element) as $field) {
		$row = array();
		foreach (element_children($element[$field]) as $key) {
			$row[] = drupal_render($element[$field][$key]);
		}
		$rows[] = $row;	
 	}
 
  $output = theme('table', array('header' => $header, 'rows' => $rows));
	
  return $output;
}