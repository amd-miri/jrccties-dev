INTRODUCTION
------------

A CouchDB backend implementation for the Integration module
(https://www.drupal.org/project/integration).

This module allows storing and retrieving content using the Integration module
and a CouchDB database, while sharing this content with other Drupal instances
or other systems.

REQUIREMENTS
------------

This module requires the following modules:

* Integration and Integration UI (https://www.drupal.org/project/integration)
* Registry Autoload (https://www.drupal.org/project/registry_autoload)
* Guzzle HTTP Client (https://github.com/guzzle/guzzle)

INSTALLATION
------------

Install as you would normally install a contributed Drupal module. See:
https://drupal.org/documentation/install/modules-themes/modules-7
for further information.

The Guzzle HTTP Client can be downloaded and installed using Composer Manager
(https://www.drupal.org/project/composer_manager).

CONFIGURATION
-------------

Create a new backend at admin/config/integration/backend/add
Choose the 'CouchDB backend' backend plugin, and select the applicable resource
schema(s).

- Backend settings

* Base URL: enter the base URL of your CouchDB database,
e.g. http://localhost:5984/mydatabase
* ID endpoint: if your setup provides an endpoint which can translate
producer IDs to backend IDs, enter its URI here, e.g. /uuid

- Resource schemas settings

* Resource endpoint: enter the base endpoint to get documents for this resource,
while providing an ID, e.g. /articles
* Resource _all_docs endpoint: enter the endpoint which returns the list of all
documents for this resource, e.g. /articles/all (default: /_all_docs)
* Changes endpoint: enter the endpoint which returns the history of changes
for this resource, e.g. /articles/changes

- Authentication

Basic HTTP authentication and Cookie authentication are supported.
The login path is required for the Cookie authentication only,
enter its URI, e.g. /_session

TROUBLESHOOTING
---------------

In order to see debug information, add the line below to your settings.php.

$conf['integration_couchdb_debug'] = TRUE;
