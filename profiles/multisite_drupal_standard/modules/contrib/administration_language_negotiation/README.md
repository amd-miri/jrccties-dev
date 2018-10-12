# Installation
Install as usual, see http://drupal.org/node/895232 for further information.

# Configuration
The module provides an additional language negotiation mechanism that can be
enabled on admin/config/regional/language/configure

 ![Language detection screen](https://www.drupal.org/files/project-images/admin-screen-1.JPG "Language detection screen")

Click the "Configure" link facing the Administration path method.

Select the language and paths where you want the language to appear
![Path configuration screen](https://www.drupal.org/files/project-images/admin-screen-2.JPG "Path configuration screen")

If you use language suffix mechanisme, make sure you add a `*` in front of your path definition.
The module provides a default configuration working for prefix and suffix detection.

# Permissions
The module does not provide permissions. The configuration applies sitewide.
