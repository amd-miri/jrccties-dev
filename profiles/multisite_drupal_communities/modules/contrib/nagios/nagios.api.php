<?php
// $Id;

/**
 * Provide a way to enabled/disable a certain module from being included in Nagios reports and alerts.
 */
function hook_nagios_info() {
  return array(
    'name'   => 'Your module name',
    'id'     => 'IDENTIFIER',
  );
}

/**
 * Does the actual work of checking something.
 *
 * @param $id
 *   Optional, an identifier which is the 2nd argument passed via the URL.
 *   this is useful when you just want nagios to check a single function.
 *   example: http://mysite.com/nagios/mymodule/myId.
 *
 *   "myId" would be send to mymodule_nagios.
 *
 *   http://mysite.com/nagios/mymodule would not send any id, but would not
 *   run hook_nagios for any other modules.
 *
 * @return array
 * The data returned is an associative array as follows:
 *
    array(
      'key'  => 'IDENTIFIER',
      'data' => array(
        'status' => STATUS_CODE,
        'type    => 'state', // Can be a 'state' for OK, Warning, Critical, Unknown) or can be 'perf', which does
                             // Cause an alert, but can be processed later by custom programs
        'text'   => 'Text description for the problem',
      ),
    );

  STATUS_CODE must be one of the following, defined in nagios.module:

    NAGIOS_STATUS_OK
    NAGIOS_STATUS_UNKNOWN
    NAGIOS_STATUS_WARNING
    NAGIOS_STATUS_CRITICAL

  Here is an example:
*
* @return <type>
*/
function yourmodule_nagios($id) {
  $data = array();

  // Check something ...
  $count = 10;
  if (!$count) {
    $data = array(
      'status' => NAGIOS_STATUS_WARNING,
      'type'   => 'state',
      'text'   => t('A very brief description of the warning'),
    );
  }
  else {
    $data = array(
      'status' => NAGIOS_STATUS_OK,
      'type'   => 'state',
      'text'   => '',
    );
  }

  return array(
    'key' => 'IDENTIFIER', // This identifier will appear on Nagios' monitoring pages and alerts.
    'data' => $data,
  );
}

/**
 * Form API elements to be included at admin/settings/nagios
 */
function hook_nagios_settings() {
  $form = array();

  $form['size_of_file'] = array(
    '#type' => 'textfield',
    '#title' => 'Max file size',
    '#desciption' => 'If file is over this size, tell nagios it is an error',
  );

  return $form;
}



?>
