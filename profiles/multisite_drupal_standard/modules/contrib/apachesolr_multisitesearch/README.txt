This module allows facetting to happen across multiple Drupal sites.

1. Enable the module

2. Enable the search environment:
   Edit the  default environment and select multisite support in
   the settings.

3. Existing facets
All your existing facets will still work but they are indexed using
a numeric ID that will not work across sites.

The base Apache Solr Search Integration module is designed to support
multiste search and this also always indexes them using the string
name (e.g. the taxonomy term name, the user name) and this module
already ships with 3 default multisite enabled facets
- Tags
- Authors
- Content Types (Bundles)

- It also ships with a facet for each site (Hash/Site)

4. Custom Facets
Create a custom module that enables extra cross-site facets. In case of a
a custom vocabulary this will be named sm_vid_NAME. You can view all the fields
in solr by going to your Drupal reports and select Solr Search Index
Copy the apachesolr_multisitesearch_facetapi_facet_info into your module and
get started.

