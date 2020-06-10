<?php

/**
 * @file
 * jrccties_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function jrccties_rules_default_rules_configuration() {
  $items = array();
  $items['rules_validate_user_gets_role'] = entity_import('rules_config', '{ "rules_validate_user_gets_role" : {
      "LABEL" : "Validate user gets role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [
        { "NOT user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "14" : "14" } } } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "14" : "14" } } } }
      ]
    }
  }');
  return $items;
}
