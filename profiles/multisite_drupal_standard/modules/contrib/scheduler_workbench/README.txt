Introduction
------------
This module provides integration between the Scheduler module [1] and the
Workbench Moderation module [2]. It allows to set a moderation state when
Scheduler triggers automatic publication or unpublication of a node. It also
adds a field to capture a default value for unpublication and adds a permission
to determine which users can override this default value.


Requirements
------------
 * Scheduler (version 7.x-1.1 or higher) [1]
 * Workbench Moderation [2]


Installation
------------
1. Download the latest recommended release from the project page [3].
2. Extract the archive in your modules folder (eg. sites/all/modules/contrib).
3. Log in as administrator and enable the module at admin/modules.


Usage
-----
1. Edit the content type for which you want to enable moderated scheduling at
   Structure > Content Types.
2. Manage the settings in the "Scheduler" vertical tab:
    * Make sure "Enable scheduled publishing for this content" is enabled.
    * It is a good practice to enable "Create a new revision on publishing".
    * Set the "Moderation State" to your desired state. In most cases the
      default setting "Published" is fine.
3. If you would like to have scheduled unpublishing of content you can set
   similar settings under the "Unpublishing" section.
4. If desired you can set a default offset between scheduled publishing and
   unpublishing by filling in the "Default Time" option.
5. Go to People > Permissions and grant the permission "Override default
   scheduler time" to all user roles that should be able to enter a custom
   unpublish time.


References
----------
[1] Scheduler module: http://drupal.org/project/scheduler
[2] Workbench Moderation module: http://drupal.org/project/workbench_moderation
[3] Project page: http://drupal.org/project/scheduler_workbench
