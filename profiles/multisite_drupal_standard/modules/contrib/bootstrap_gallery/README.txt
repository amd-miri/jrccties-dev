
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation & Usage
 * Overriding Templates
 * Credits

INTRODUCTION
------------

Bootstrap Gallery is a views plugin that creates appealing Photo Galleries from any content type.

Features:
    - Content type independent. It doesn't require it's own content type.
    - Displays images in a responsive grid format.
    - Provides different options for controlling gallery Modal and Lightbox
    - Easily themed and overridden.
    - Contains a sample Gallery feature that would save you some effort in node and view creation. However, you still need to do steps 7-9 in the usage section.


INSTALLATION & USAGE
--------------------

Bootstrap Gallery has few dependencies. You obviously need to have bootstrap library installed,
whether through Bootstrap Theme, or Bootstrap API module in order for the gallery to be displayed correctly.

Views, and (Preferably) Views UI need to be installed. So that the Views plugin can be functional.

JQuery Update module is required, which would include a newer version of JQuery to Drupal. jQuery 1.8 is recommended.

1. Download module, extract and copy "bootstrap_gallery" directory to your sites/SITENAME/modules directory.

3. Enable the module from the Admin > Modules page.

4. Create a view from Admin > Structure > Views page.

5. In the Format section, click on Show and Select "Fields" option.

6. In the Fields section, add the Image field and an optional title field; so that both can be used in the gallery.

7. In the Format section again, click on Format and select "Bootstrap Gallery" as the view display format.

8. In Bootstrap Gallery settings, specify the image field to be used and title field that will be used as an Image Caption.

9. Save view.


OVERRIDING TEMPLATES
--------------------

Bootstrap Gallery output can be controlled easily by overriding the template files included in the "theme" folder.
Which exists in the same module directory. The theme folder contains the following files:

1. views-view-bootstrap-gallery.tpl.php : A normal Views template file contains the HTML for the gallery grid.
2. bootstrap-gallery-item.tpl.php : Template file for a single gallery item.
3. bootstrap-gallery-modal.tpl.php : Template file for the gallery Modal.

To override any of these files, simply copy to your default theme directory and modify HTML as desired.


CREDITS
-------

This module is bundled with couple of Javascript libraries that were developed by:

Sebastian Tschan
https://blueimp.net

Javascript libraries has been shaped and modified to integrate with this module for Drupal use by:

Ahmad Kharbat
http://kharbat.me

