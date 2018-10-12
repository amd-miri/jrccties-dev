<?php

/**
 * @file
 * Code for the NexteuropaNewsroomAgendaBlockSchedule class.
 */

/**
 * NexteuropaNewsroomAgendaBlockSchedule class.
 */
class NexteuropaNewsroomAgendaBlockSchedule extends NexteuropaNewsroomAgenda {
  private $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;

  /**
   * NexteuropaNewsroomAgendaBlockSchedule constructor.
   *
   * @param object $type
   *   Newsroom type taxonomy term.
   * @param array $topics
   *   Newsroom topic taxonomy term.
   * @param object $current_day
   *   Current date.
   * @param string $operator
   *   Operator.
   */
  public function __construct($type, array $topics, $current_day, $operator) {
    $this->setIsBlock(TRUE);
    $this->setOperator($operator);
    parent::__construct($type, $topics, $current_day);
  }

  /**
   * Returns the number of items per block.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return NexteuropaNewsroomHelper::getBlockItemsNumber(FALSE);
  }

  /**
   * Gets query operator.
   *
   * @return string
   *   Query operator: OR or AND.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Sets query operator.
   *
   * @param string $value
   *   Query operator: OR or AND.
   */
  public function setOperator($value) {
    $this->operator = $value;
  }

  /**
   * Preprocessing of the query before the execution.
   *
   * @param object $query
   *   Query object.
   *
   * @return object
   *   Query object.
   */
  protected function processQuery($query) {

    if (empty($this->getTopics())) {
      return $query;
    }

    if ($this->getOperator() == NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
      $query->condition('topic_data.tid', $this->getTopicsId());

    }
    elseif ($nids = NexteuropaNewsroomHelper::getNodeRelatedToTopic($this->getTopicsId())) {
      $query->condition('nid', $nids, 'IN');
    }

    return $query;
  }

}
