Tableau
=======
Tableau gives site builders access to components of a Tableau server. These
components are exposed as entities to Drupal, where you can render them in
several different ways, as well as from within Views.

This module is specifically for licensed Tableau installations for which you
have database access.

Installation
------------
Tableau can be installed like any other Drupal module -- place it in
the modules directory for your site and enable it on the `admin/build/modules`
page.

To configure, you need to have the Tableau database configured in your
`settings.php` file. This database (typically PostgreSQL) should have the key
`tableau`. Refer to this [how-to][1] for more information on how to configure
external databases on Drupal.

More configuration options are available by going to `admin/config/tableau`.

Usage
-----
The Tableau module defines several Tableau components as Drupal entities.
Specifically, it exposes elements from the following Tableau database tables:

- `_users` as `tableau_owner`
- `_projects` as `tableau_project`
- `_sites` as `tableau_site`
- `_tags` as `tableau_tag`
- `_views` as `tableau_view`
- `_workbooks` as `tableau_workbook`

The basic usage of this module is to use the [Views][2] module for querying and
rendering Tableau components.

To load any of these entities programmatically, you can do something similar to

````
    $view = tableau_view_load($view_id);
````

This code will load the corresponding view, as well as any sub-components that
are associated to it (based on fields like `site_id`, `workbook_id`, etc.).

Tableau views can be rendered by using `theme('tableau_view', $options);`, where
`$options` is an associative array:

````
$options = array(
    'view' => $view, // Tableau view entity
    'width' => '320px', // Width in pixels or percentage
    'height' => '240px', // Height in pixels or percentage
    'tabs' => TRUE | FALSE, // Whether to show workbook tabs at the top
    'toolbar' => TRUE | FALSE, // Whether to show view toolbar at the bottom
    'format' => 'static' | 'interactive' | 'thumbnail',
);
````

Access control
--------------
Tableau provides basic access control through permissions for accessing Tableau
content. It also provides access control based on Tableau Sites. By configuring
the list of available sites, the module will verify that only components
belonging to the enabled sites can be loaded.

Caching
-------
This module provides two types of cache. The first one is for the actual Tableau
entities, which will save on trips to the Tableau server database by storing
loaded entities in the `cache` bin provided by Drupal.

The other one is for rendered static views (by using `$format = 'static'` in the
`theme()` function, or selecting the "Static" format when rendering through
Views), which will download the generated `.png` files and store them in the
default files directory. The cached images expire whenever the corresponding
workbook is updated.

Both caches are configurable from within the Tableau configuration page
(`admin/config/tableau`).

Maintainers
-----------
This module was created by [Victor Kareh][3] and is sponsored by the
[Microfinance Information Exchange][4].


[1]: http://drupal.org/node/18429
[2]: http://drupal.org/project/views
[3]: http://drupal.org/user/144520
[4]: http://www.themix.org
