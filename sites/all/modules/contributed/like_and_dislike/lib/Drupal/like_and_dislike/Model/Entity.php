<?php

namespace Drupal\like_and_dislike\Model;

/**
 * @file
 */
class Entity {

  var $entity_id;
  var $entity_type;
  var $bundle;
  static $available_entity_types = array(
    'node',
    'comment',
  );

  /**
   * @param stdclass $entity
   */
  public function __construct($entity) {

    if (isset($entity->nid)) {
      if (isset($entity->node_type)) {
        $this->entity_id = $entity->cid;
        $this->entity_type = 'comment';
        $this->bundle = $entity->node_type;
      } else {
        $this->entity_id = $entity->nid;
        $this->entity_type = 'node';
        $this->bundle = $entity->type;
      }
    }
  }

  /**
   * @param type $uid
   * @param type $ip
   * @return type
   */
  public function getLikesAmount($uid = NULL, $ip = NULL) {
    return \Drupal\like_and_dislike\Services\VoteService::getEntityVoteAmount($this->entity_id, 'like', $this->entity_type, $uid, $ip);
  }

  /**
   * @param type $uid
   * @param type $ip
   * @return type
   */
  public function getDislikesAmount($uid = NULL, $ip = NULL) {
    return \Drupal\like_and_dislike\Services\VoteService::getEntityVoteAmount($this->entity_id, 'dislike', $this->entity_type, $uid, $ip);
  }

  public function voteIsAvailable() {
    /*
     * I don't see any reason to allow Votes on other than these entity types.
     * If you think of an Entity Type that should be considered here, please 
     * open an issue.
     */
    if (isset($this->bundle) && in_array($this->entity_type, self::$available_entity_types)) {
      return variable_get('like_and_dislike_vote_' . $this->bundle . '_available', FALSE);
    }
    return FALSE;
  }

  public function userCanVote($account = NULL) {
    if ($this->entity_type == 'node') {
      $access = user_access('like/dislike any ' . $this->bundle . ' nodes', $account);
    } else if ($this->entity_type == 'comment') {
      $access = user_access('like/dislike any ' . $this->bundle . ' comments', $account);
    }
    return $access;
  }

  public function userCanViewVotes($account = NULL) {
    if ($this->entity_type == 'node') {
      $access = user_access('view likes/dislikes from every ' . $this->bundle . ' nodes', $account);
    } else if ($this->entity_type == 'comment') {
      $access = user_access('view likes/dislikes from every ' . $this->bundle . ' comments', $account);
    }
    return $access;
  }

}
