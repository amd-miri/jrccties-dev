-- SUMMARY --

The Object log module allows developers to store objects, arrays and other
variables to a log table so that they may be inspected later. Multiple stored
variables may be displayed side-by-side in the Object log under admin/reports.

The usage is similar to Devel module's dpm() or kprint_r() functions, but is
particularly suited for debugging server-to-server requests, such as cron runs
and web services, or for requests from anonymous and other unprivileged users.

-- REQUIREMENTS --

The Object log module depends on Devel module:
  http://drupal.org/project/devel

-- USAGE --

When you reach a point in a code at which you would like to store a variable,
call the object_log() function...

  object_log($label, $data);

...where $label is a string representing a name to give the object in the log,
and $data is the variable you wish to store. If there is already a stored object
with the same $label, that entry will be overwritten in the log.

Stored objects may be inspected by any user with the "access devel information"
permission by going to admin/reports/object_log.  While inspecting an object,
a second object may be selected to display both objects side-by-side.
