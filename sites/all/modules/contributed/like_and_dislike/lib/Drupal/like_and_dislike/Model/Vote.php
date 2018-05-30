<?php

namespace Drupal\like_and_dislike\Model;

/**
 * @file
 */
class Vote {

  /**
   * Manage the real like or dislike event for nodes or comments.
   * If the user has permission to vote it checks that the user has not made this
   * vote already.
   * When registers a vote it will remove all votes from user for that entity and
   * register the new vote.
   * 
   * This function is to be used with AJAX so just prints like this:
   * likecount/dislikecount/message
   * Example: 3/2/The user can't vote
   * 
   * @global type $user
   * @param type $entity_type
   * @param type $entity_id
   * @param type $vote_tag
   * @return type
   */
  static public function add($entity_id, $entity_type, $vote_tag) {

    global $user;
    $message = '';

    $entities = entity_load($entity_type, array($entity_id));

    $Entity = new \Drupal\like_and_dislike\Model\Entity(current($entities));

    $can_vote = $Entity->userCanVote();
    if ($can_vote) {
      //Check if disliked
      $checkCriteria = array(
        'entity_id' => $entity_id,
        'tag' => $vote_tag == 'like' ? 'dislike' : 'like',
        'uid' => $user->uid,
        'entity_type' => $entity_type,
      );
      if ($user->uid == 0) {
        $checkCriteria['vote_source'] = ip_address();
      }
      $search_previous_vote = votingapi_select_votes($checkCriteria);
      $previous_vote = count($search_previous_vote);

      if ($previous_vote == 1) {
        votingapi_delete_votes($search_previous_vote);
      }

      $vote = array(
        'entity_id' => $entity_id,
        'value' => 1,
        'tag' => $vote_tag,
        'entity_type' => $entity_type,
        'value_type' => 'points',
      );
      $setVote = votingapi_set_votes($vote);
    } else {
      $message = t(variable_get('like_and_dislike_vote_' . $entity_type . '_denied_msg', "You don't have permission to vote"));
    }

    // Get the updated like/dislike counts and print them with a message if any
    $criteriaLike = array(
      'entity_id' => $entity_id,
      'tag' => 'like',
      'entity_type' => $entity_type,
    );
    $criteriaDislike = array(
      'entity_id' => $entity_id,
      'tag' => 'dislike',
      'entity_type' => $entity_type,
    );

    entity_get_controller('node')->resetCache(array($entity_id));

    $likeCount = sizeof(votingapi_select_votes($criteriaLike));
    $dislikeCount = sizeof(votingapi_select_votes($criteriaDislike));
    return array(
      'likes' => $likeCount,
      'dislikes' => $dislikeCount,
      'message' => $message,
    );
  }

}
