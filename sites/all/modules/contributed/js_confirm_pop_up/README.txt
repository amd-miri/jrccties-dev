*********************************************************
-----------------------JS Confirm Pop Up-------------------
*********************************************************

Introduction
------------
This module help site builder or developer to add "Custom JS confirm box" to 
form used within site, when user fills form and without complete it want 
redirect from that page, Shows the confirm box with warns to save form or leave 
the page. 


Requirements
------------
None


Installation & Use
-------------------
* Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.
* 1. Download project from https://www.drupal.org/js_confirm_pop_up and unzip
the project.
* 2. Place the project under '/sites/all/modules/contrib' directory.
* 3. Install it from module installation page.

Configuration
-------------
 * Configure user permissions in Administration » People » Permissions:
 * Find permission "Perform administration tasks JS confirm pop up."
 * This is permission for access the menu link used to "JS confirm pop up".
 * Access link Administration » Configuration » User Interface » JS confirm pop 
   up setting.
  1. Enter comma(,) separated form id's(machine name) of drupal form eg. 
  'node_edit_form' in first text area label with "Machine name of drupal forms".
  2. Enter comma(,) separated HTML id's of form i.e DOM ID's.
     eg. 'node-edit-form'.
  3. Submit form.
  
Limitation
------------
None 

Features
--------
* Use to warn site user to saved changes before leave any unsaved page.

CONTACT :
---------

Current maintainers:
  * Sandip Auti (sandipauti) - https://www.drupal.org/u/sandipauti
  * Gmail contact: sandip.auti11@gmail.com
 