<?php

/**
 * @file
 * Administrative report for the OG Linkchecker module.
 */

/**
 * Generates the OG Linkchecker groups summary report.
 */
function og_linkchecker_report() {
  // Begin code adapted from the Linkchecker module.
  $links_unchecked = db_select('linkchecker_link', 'll')
    ->condition('ll.last_checked', 0)
    ->condition('ll.status', 1)
    ->countQuery()
    ->execute()
    ->fetchField();
  if ($links_unchecked > 0) {
    $links_all = db_select('linkchecker_link', 'll')
      ->condition('ll.status', 1)
      ->countQuery()
      ->execute()
      ->fetchField();
    drupal_set_message(format_plural($links_unchecked,
      'There is 1 unchecked link of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      'There are @count unchecked links of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      array('@links_all' => $links_all)), 'warning');
  }
  // End code adapted from the Linkchecker module.


  $gids = db_select('og_membership', 'ogm')
    ->fields('ogm', array('gid'))
    ->condition('entity_type', 'node')
    ->condition('state', array(OG_STATE_ACTIVE))
    ->execute()
    ->fetchAll(PDO::FETCH_COLUMN);

  $header = array(
    'group' => t('Group'),
    'content' => t('Group Content Types'),
    'roles' => t('Group Roles'),
    'broken' => t('# Broken Links'),
  );

  $rows = array();

  if (empty($gids)) {
    $output['field_table']  = array('#markup' => '<em>' . t('No organic groups for which to show broken links data.') . '</em>');
  }
  else {
    // Build rows.
    foreach ($gids as $gid) {
      // Load the group entity.
      $group = node_load($gid);

      // Query for Group Content Types column.
      $content_query = db_select('og_membership', 'om');
      $content_query->innerJoin('node', 'n', 'n.nid = om.etid');
      $content_query->innerJoin('node_type', 'nt', 'nt.type = n.type');
      $content_query->condition('om.gid', $gid);
      $content_query->condition('om.entity_type', 'node');
      $content_query->fields('nt', array('type', 'name'));
      $content_query->distinct();
      $content_data = $content_query->execute();

      $content = '';
      foreach ($content_data as $data) {
        // Display content types as Human Readable Name (machine_name).
        $content .= "<p>" . check_plain($data->name) . " ($data->type)</p>";
      }

      // Determine whether this group uses generic roles or has group-specific
      // roles.
      $role_gid_query = db_select('og_role', 'orl');
      $role_gid_query->condition('orl.gid', $gid);
      $role_gid_query->fields('orl', array('name'));
      $role_gid = $role_gid_query->countQuery()->execute()->fetchField() ? $gid : 0;

      // Query for Group Roles column.
      $role_subquery = db_select('og_role', 'orl');
      $role_subquery->innerJoin('og_role_permission', 'orlp', 'orl.rid = orlp.rid');
      $role_subquery->condition('orl.gid', $role_gid);
      $role_subquery->condition('orlp.permission', OG_LC_PERM);
      $role_subquery->fields('orl', array('name'));

      $role_query = db_select('og_role', 'orl');
      $role_query->leftJoin($role_subquery, 'q', 'q.name = orl.name');
      $role_query->condition('orl.gid', $role_gid);
      $role_query->condition('orl.name', OG_ANONYMOUS_ROLE, '<>');
      $role_query->addField('orl', 'name', 'role');
      $role_query->addField('q', 'name', 'has_perm');
      $role_data = $role_query->execute();

      $roles = '';
      foreach ($role_data as $data) {
        // If the role has permission to view the broken links report for this
        // group, display the role in green.
        $color = $data->has_perm ? "green" : "red";
        $roles .= "<p style=\"color: $color\">$data->role</p>";
      }

      // Query for # Broken Links column.
      $broken_query = db_select('linkchecker_node', 'ln');
      $broken_query->innerJoin('linkchecker_link', 'll', 'll.lid = ln.lid');
      $broken_query->condition('ll.code', array('200', '-1'), 'NOT IN');
      $broken_query->innerJoin('og_membership', 'om', 'om.etid = ln.nid');
      $broken_query->condition('om.entity_type', 'node');
      $broken_query->condition('om.gid', $gid);
      $broken_query->fields('ln');

      // Convert to a count query to get the number of rows, i.e. the number of
      // broken links.
      $broken = $broken_query->countQuery()->execute()->fetchField();

      $rows[$gid] = array(
        'group' => t('@title (!type) [<a href="!report">report</a>]',
          array(
            '@title' => $group->title,
            '!type' => $group->type,
            '!report' => url("node/{$group->nid}/linkchecker"),
          )
        ),
        'content' => $content,
        'roles' => $roles,
        'broken' => $broken,
      );
    }

    $vars = array(
      'header' => $header,
      'rows' => $rows,
    );
    $output = theme('table', $vars);
  }
  return $output;
}
