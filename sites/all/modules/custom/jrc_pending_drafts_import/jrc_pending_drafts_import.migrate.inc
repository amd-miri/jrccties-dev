<?php
/**
 * @file
 * Migration of the custom file fields from The old JRC database.
 */

/**
 * Implements hook_migrate_api().
 */
function jrc_pending_drafts_import_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'jrc_pending_drafts' => array(
        'title' => t('JRC pending drafts'),
      ),
    ),
    'migrations' => array(
      'JRCPendingDrafts' => array(
        'class_name' => 'JRCPendingDraftsMigration',
        'group_name' => 'jrc_pending_drafts',
      ),
    ),
  );
  return $api;
}

/**
 * Migration of the JRC main menu links.
 */
class JRCPendingDraftsMigration extends Migration {
  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('JRC Pending Drafts Migration');
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Node ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select('menu_links', 'm')
            ->fields('m')
      		->condition('menu_name', 'main-menu', '=')
            ->orderBy('depth', 'ASC');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationMenuLinks();

    $this->addFieldMapping('menu_name')->defaultValue('menu-jrc-main-menu');
    $this->addFieldMapping('plid', 'plid')->sourceMigration($this->getMachineName());
    $this->addFieldMapping('link_path', 'link_path');
    $this->addFieldMapping('router_path', 'router_path')->defaultValue('node/%');;
    $this->addFieldMapping('link_title', 'link_title');
    $this->addFieldMapping('module')->defaultValue('menu');
    $this->addFieldMapping('hidden', 'hidden');
    $this->addFieldMapping('external', 'external');
    $this->addFieldMapping('has_children', 'has_children');
    $this->addFieldMapping('expanded', 'expanded');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('depth', 'depth');
    $this->addFieldMapping('customized', 'customized');
    $this->addFieldMapping('p1', 'p1');
    $this->addFieldMapping('p2', 'p2');
    $this->addFieldMapping('p3', 'p3');
    $this->addFieldMapping('p4', 'p4');
    $this->addFieldMapping('p5', 'p5');
    $this->addFieldMapping('p6', 'p6');
    $this->addFieldMapping('p7', 'p7');
    $this->addFieldMapping('p8', 'p8');
    $this->addFieldMapping('p9', 'p9');
    $this->addFieldMapping('updated', 'updated');
    $this->addFieldMapping('language')->defaultValue('und');
  }

  /**
   * Class prepareRow function.
   */
  public function prepareRow($row) {
    $query = Database::getConnection('default', 'jrc_legacy_db')
            ->select('url_alias', 'ua')
              ->fields('ua', array('alias'))
      ->condition('source', $row->link_path, '=')
      ->execute()
      ->fetchAssoc();

    if (isset($query[alias]) && $row->router_path == "node/%") {
      $row->link_path = drupal_get_normal_path($query[alias]);
    }

    if (substr($row->link_path, 0, 15) == "mega-menu-item/") {
      $row->link_path = "<front>";
      $row->external = 1;
    }

    if ($row->link_title == "<show_parent>") {
      $node_id = substr($row->link_path, 5);
      $node = node_load($node_id);
      $row->link_title = $node->title;
    }
  }

}
