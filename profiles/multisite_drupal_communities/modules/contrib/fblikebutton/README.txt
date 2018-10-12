README.txt
==========

Drupal Facebook Like Button module:
------------------------
Requires - Drupal 7
License - GPL (see LICENSE)


Overview:
--------
Rather than having to manually copy/paste the "Like this on Facebook" code for
each piece of content you (or your users) create, this module will automatically
add that code to the end of each chosen node type. You are able to add a Like
button which likes a given URL (static, e.g. your homepage) or/and put a dynamic
Like button on your page to like the page you are actually visiting.


Features:
---------
The Facebook like button module:

* Adds a like button on your site (static)
* Add more like buttons to your site (dynamic)
* Control the position of the buttons
* Integrates with display suite.
* Overrideable output through templates and preprocess functions.


Installation:
------------
Install this module in the usual way (drop the file into your site's contributed modules directory).


Configuration:
-------------
Go to "Configuration" -> "FB LIKE BUTTON" to find
all the configuration options.


Overriding Output:
-----------------
Copy the fblikebutton.tpl.php to your theme's directory and alter at will. This
should be necessary unless the like button stops working because Facebook has
changed their service. You can also override the output by creating a
preprocess function in your theme's template.php file.


Display Suite Integration:
-------------------------
When using display suite to display the node's content the normal Facebook like
button configuration settings for the dynamic Facebook like button become
somewhat irrelevant.
