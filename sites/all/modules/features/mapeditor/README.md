Mapeditor
=========

Description
-----------
Mapeditor provides a content types (Mapeditor Map) for creating EC Webtools MAP maps (based on the webtool maps JS library) in 2 or 3 simple steps as a node. Mapeditor is a simplification of Leaflet Views so that it does not expose the user to the Views UI. This also limits its possibilities and makes it less flexible. Mapeditor is a simplification of the functionality proposed in Web maps (https://webgate.ec.europa.eu/fpfis/wikis/x/DuZQBQ)

Webtools maps JS library
------------------------
https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/MAP

Features
--------
- Content type with 'flexible' fields.
- Webtools map output.
- Can map users, nodes or taxonomy terms
- Admin UI to define mappable content types.

Pre-requisites
--------------
To use webtools js libraries several conditions must be met.
- Webtools load.js must be loaded as https:// . http:// will result in access denied.
- The domain names should contain ec.europa.eu . E.g. http://mapper.val.ec.europa.eu. Other domain names will reuslt in access denied.
- Include acce parameters wtenv=acc in the url. E.g. http://mapper.val.ec.europa.eu/node/12?wtenv=acc . If missing it results in access denied.
- Login through browser with htaccess username and password. Otherwise, you know what happens.
- ...

Mock data
---------
Mapeditor contains a sub module Mapmock that provides fake users and content for generating and testing maps. This module is not needed on production websites.

Configuration and usage
-----------------------
- Enable the module. This creates a content type called Map
- Configure the module at http://example.com/admin/config/system/mapeditor/settings
-- Enter the correct url for the webtool javascript map library
-- Enter the names of the fields in the website that hold geographical data
-- Choose entity bundles that will be available in the map node as filters.
-- Choose terms that will be available in the map node as filters.
- Create a map node
-- Cross fingers

User stories
------------
- As a anonymous user I can view maps
- As a contributor I can create a maps (as ordinary content items (nodes)) in a 2 or 3 simple steps.
- As an editor I can moderate & publish maps
- As an administrator I can configure the map content type

Limitations
-----------
- Custom fields can be created through the Mapeditor config screen but not deleted
- The map does not verify field values (possibly results in broken maps)

Contact persons
---------------
Role, Name, Dept.
Product owner, ,DG Connect
Coordinator, Luca Arnaudo, DG Connect
Implementor, Boris Doesborg, DG Connect

Contributed modules
-------------------
Mapeditor use the following contributed modules:
- Geofield http://drupal.org/project/geofield
- Geophp
- Features
- Ctools
- Strongarm
- Entity
