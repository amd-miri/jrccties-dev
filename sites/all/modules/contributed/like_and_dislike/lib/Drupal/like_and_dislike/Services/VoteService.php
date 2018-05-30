<?php

namespace Drupal\like_and_dislike\Services;

/**
 * @file
 */
class VoteService {

  /**
   * This function gives back the number of votes for a particular entit with a particular type of voting.
   * For example it can be used to get number of likes and also dislikes. Just need to change the type.
   * 
   * @param type $entity_id the node id of the node for which number of votes is requited.
   * @param type $vote_tag the category of vote: like/dislike etc.
   * @param type $entity_type
   * @param type $uid
   * @param type $ip
   * @return int
   */
  static public function getEntityVoteAmount($entity_id, $vote_tag, $entity_type, $uid = NULL, $ip = NULL) {
    if ($uid === NULL) {
      $criteria = array(
        'entity_id' => $entity_id,
        'tag' => $vote_tag,
        'entity_type' => $entity_type,
      );
    }
    else {
      $criteria = array(
        'entity_id' => $entity_id,
        'tag' => $vote_tag,
        'uid' => $uid,
        'entity_type' => $entity_type,
      );
      if ($ip != NULL) {
        $criteria['vote_source'] = $ip;
      }
    }
    $count = sizeof(votingapi_select_votes($criteria));
    if (!isset($count)) {
      $count = 0;
    }
    return $count;
  }

}
