This is a tiny module that basically extends Drupal's core statistics module by
adding node counts for week, month and year. It also integrates with Views and
you can use it to select, filter, order the content as well.

--------------------------------------------------------------------------------
Integration
--------------------------------------------------------------------------------

This module plays well and has been tested with Views. You can use these fields
in Content statistics group
- Views this week
- Views this month
- Views this year

You can also use those fields to order and filter content.

If you want to filter the hits from particular user roles or from crawlers, you
need the module Statistics Filter.

--------------------------------------------------------------------------------
Dependencies
--------------------------------------------------------------------------------

- Statistics (Drupal Core)
- Views 3.x (optional)

--------------------------------------------------------------------------------
Installation
--------------------------------------------------------------------------------

Download the module and simply copy it into your contributed modules folder:
[for example, your_drupal_path/sites/all/modules] and enable it from the
modules administration/management page.
More information at: Installing contributed modules (Drupal 7).

--------------------------------------------------------------------------------
Configuration
--------------------------------------------------------------------------------

You need to set up cron in order to reset the counters.
