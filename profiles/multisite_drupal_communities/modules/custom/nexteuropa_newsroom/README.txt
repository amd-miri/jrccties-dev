Readme file for the nexteuropa newsroom feature.
---------------------------------------------


The [FPFIS] Newsroom feature provides an integration between
your project in the FPFIS CMS and the Newsroom service.
Newsroom project stores and manages Newsroom items and related data
and it also provides lists of Newsroom types, Newsroom services,
Newsroom items, Newsroom topics accessible via RSS feeds.
[FPFIS] Newsroom feature allows users to quickly setup feed imports
in order to import all necessary data from the Newsroom service,
it also provides the business logic defining a basic configuration
of default blocks showing the imported contents. In addition, users
of the site can access the main Newsroom page listing all the items,
which can be filtered by Newsroom type and topic.
This default configuration can be completely customized
since the result of the Newsroom feature usage implies the
import of nodes and entities in general, they are available in the project
they've been imported into and the site-builders can easily use them
to create the desired configuration. There also tools available
in the Newsroom admin interface to create relationships between
the newsroom entities and the pre-existing content types in a simplified way,
one of the main configuration of the feature is the addition
of two relational fields to existing content types and this
is possible directly from the admin interface of the newsroom.


Required contributed modules not in the platform:
FEEDS Entity translation
https://www.drupal.org/project/feeds_et

patched with this to support linkfields.
https://www.drupal.org/files/issues/feeds_et_link_support-2078069-3.patch
