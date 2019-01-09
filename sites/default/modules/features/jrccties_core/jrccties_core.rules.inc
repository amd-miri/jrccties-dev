<?php

/**
 * @file
 * Custom Rules action for Organic Groups.
 */

/**
 * Implements hook_rules_action_info().
 */
function jrccties_core_rules_action_info() {
  return array(
    'og_get_members_fixed' => array(
      'label' => t('The fixed Get group members from group audience'),
      'group' => t('Organic Groups extras'),
      'parameter' => array(
        'group_content' => array(
          'type' => 'entity',
          'label' => t('Group content'),
          'description' => t('The group content determining the group audience.'),
        ),
        'states' => array(
          'type' => 'list<integer>',
          'label' => t('Membership states'),
          'options list' => 'og_group_content_states',
          'optional' => TRUE,
          'allow null' => TRUE,
          'description' => t('Filter group members by membership state. If no states are selected all members are loaded.'),
        ),
        'not_states' => array(
          'type' => 'boolean',
          'label' => t('Negate membership states'),
          'optional' => TRUE,
          'allow null' => FALSE,
          'description' => t('When checked only users not in the selected states will be loaded.'),
          'restriction' => 'input',
        ),
        'roles' => array(
          'type' => 'list<text>',
          'label' => t('Group roles'),
          'options list' => 'og_rules_group_roles_options_list',
          'optional' => TRUE,
          'allow null' => TRUE,
          'restriction' => 'input',
        ),
        'not_roles' => array(
          'type' => 'boolean',
          'label' => t('Negate group roles'),
          'optional' => TRUE,
          'allow null' => FALSE,
          'description' => t('When checked only users not in the selected roles will be loaded.'),
          'restriction' => 'input',
        ),
      ),
      'provides' => array(
        'group_members' => array('type' => 'list<user>', 'label' => t('List of group members')),
      ),
      'base' => 'jrccties_core_rules_get_members',
      'access callback' => 'og_rules_integration_access',
    ),
    '_jrccties_core_action_skill_search' => array(
      'label' => t('Notify experts in the field'),
      'group' => t('Organic Groups extras'),
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Skills')),
      ),
      'provides' => array(
        'user_list' => array(
          'label' => 'User list',
          'type' => 'list<user>',
        ),
      ),
      'module' => 'jrccties_core',
    ),
  );
}

/**
 * Action: Get group members from a group content.
 */
function jrccties_core_rules_get_members($group_content, $states = NULL, $not_states = FALSE, $roles = NULL, $not_roles = FALSE) {
  if (!isset($group_content->og_membership)) {
    // Not a group content.
    return;
  }

  $members = array();
  foreach ($group_content->og_membership->value() as $og_membership) {
    // Get the group members the group content belongs to.
    $query = db_select('og_membership', 'om')
      ->fields('om', array('etid'))
      ->condition('om.gid', $og_membership->gid)
      ->condition('om.group_type', $og_membership->group_type)
      ->condition('om.entity_type', 'user');

    if (!empty($states)) {
      $op = $not_states ? 'NOT IN' : 'IN';
      $query->condition('om.state', $states, $op);
    }

    if (!empty($roles)) {
      $group_roles = og_roles($og_membership->group_type, NULL, $og_membership->gid);
      $rids = array();
      foreach ($roles as $role) {
        $rid = array_search($role, $group_roles);
        if ($rid !== FALSE) {
          $rids[] = $rid;
        }
      }
      if (!empty($rids)) {
        if ($not_roles) {
          // Use a subquery to find members with the roles we want to exclude,
          // since members may have multiple roles or no roles at all.
          $subquery = db_select('og_users_roles', 'our')
            ->fields('our', array('uid'))
            ->condition('our.gid', $og_membership->gid)
            ->condition('our.group_type', $og_membership->group_type)
            ->condition('our.rid', $rids);
          $query->condition('om.etid', $subquery, 'NOT IN');
        }
        else {
          $query->innerJoin('og_users_roles', 'our', 'om.etid=our.uid AND om.gid=our.gid AND om.group_type=our.group_type');
          $query->condition('our.rid', $rids);
        }
      }
    }

    $current_members = $query
      ->execute()
      ->fetchCol();

    $members = array_merge($members, $current_members);
  }
  // Remove duplicate items.
  $members = array_keys(array_flip($members));
  return array('group_members' => $members);
}
