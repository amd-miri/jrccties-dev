-----------------
FileField Sources Plupload
-----------------

Description
-----------
FileField Sources is a module that enhances the generic file and image upload
fields in Drupal. This module adds Plupload as a source through
Plupload Integration module, and thus enabling multiple file uploads across a
wide range of browsers.

Since FileField Sources does not have its own widget, but rather extends the
core File field and other contributed widgets, this offers great flexibility
in widget selections.

Author: Atle Andersen (atlea)

Installation
------------
1) Place this module directory in your modules folder (this will usually be
   "sites/all/modules/").

2) Enable this and required modules within your Drupal site.

3) Add or configure an existing file or image field. To configure a typical node
   field, visit Admin -> Structure -> Content types and click "manage fields"
   on a type you'd like to modify. Add a new file field or edit an existing one.

   While editing the file or image field, you'll have new options available
   under a "File sources" fieldset. You can enable the Multi upload (Plupload)
   source for that particular field.

   Make sure the field can have more than one file. See "Number of values".

4) Create a piece of content that uses your file field and try it out.

Suhosin limitations
-------------------
Plupload-widget can in some circumstances exceed Suhosins default post-variable limit of 64, resulting in misc errors. To solve this, the folowing needs to be added to your php.ini-file:

suhosin.request.max_varname_length = 128
suhosin.post.max_name_length = 128

Support
-------
Please file bug reports in the FileField Sources Plupload issue queue.
Do not use the Drupal.org forums or send bug reports via e-mail.
