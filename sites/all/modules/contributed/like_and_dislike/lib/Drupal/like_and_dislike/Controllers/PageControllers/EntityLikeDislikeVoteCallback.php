<?php

namespace Drupal\like_and_dislike\Controllers\PageControllers;

/**
 * @file
 */
class EntityLikeDislikeVoteCallback implements \Drupal\cool\Controllers\PageController {

  /**
   * %1 = entity_type
   * %2 = tag
   * %3 = entity_id
   */
  static public function getPath() {
    return 'like_and_dislike/%/%/%';
  }

  static public function accessCallback() {
    return TRUE;
  }

  static public function getDefinition() {
    return array(
      'type' => MENU_CALLBACK,
    );
  }

  /**
   * Handles the when a node or comment is voted with a like.
   * This functions uses a general function to register the vote
   * This function is to be used with AJAX so just prints the counts and message
   */
  static public function pageCallback() {
    $entity_type = arg(1);
    $vote_tag = arg(2);
    $entity_id = arg(3);
    if (isset($entity_type) && isset($vote_tag) && isset($entity_id)) {
      $return = \Drupal\like_and_dislike\Model\Vote::add($entity_id, $entity_type, $vote_tag);
      print $return['likes'] . "/" . $return['dislikes'] . "/" . $return['message'];
    }
  }

}
