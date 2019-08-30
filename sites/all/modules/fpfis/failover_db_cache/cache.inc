<?php
/**
 * @file
 * Include file for FailoverDrupalDatabaseCache, to be used in settings.php.
 */

/**
 * Defines a failover cache implementation.
 *
 * This is a slight variant of Drupal's default cache implementation: cache
 * entries older than a configurable maximum lifetime are considered
 * non-existent.
 */
class FailoverDrupalDatabaseCache extends DrupalDatabaseCache {

  /**
   * Implements DrupalCacheInterface::getMultiple().
   */
  public function getMultiple(&$cids) {
    try {
      // Garbage collection necessary when enforcing a minimum cache lifetime.
      $this->garbageCollection($this->bin);

      $result = db_query(
        'SELECT cid, data, created, expire, serialized FROM {' . db_escape_table($this->bin) . '} WHERE cid IN (:cids) AND (UNIX_TIMESTAMP() - created) <= (:max_life)',
        array(
          ':cids' => $cids,
          ':max_life' => variable_get('failover_maxlifetime_' . $this->bin, variable_get('failover_maxlifetime_default', 1200)),
        )
      );
      $cache = array();
      foreach ($result as $item) {
        $item = $this->prepareItem($item);
        if ($item) {
          $cache[$item->cid] = $item;
        }
      }
      $cids = array_diff($cids, array_keys($cache));
      return $cache;
    }
    catch (Exception $e) {
      // If the database is never going to be available, cache requests should
      // return FALSE in order to allow exception handling to occur.
      return array();
    }
  }

}
