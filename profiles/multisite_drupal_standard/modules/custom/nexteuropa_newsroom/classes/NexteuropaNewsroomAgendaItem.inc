<?php

/**
 * @file
 * Code for the NexteuropaNewsroomAgendaItem class.
 */

/**
 * NexteuropaNewsroomAgendaItem class.
 */
class NexteuropaNewsroomAgendaItem {

  public $item = NULL;
  public $date = NULL;
  public $isPast = FALSE;

  /**
   * Gets agenda items.
   *
   * @return array
   *   Agenda items.
   */
  public function getItem() {
    return $this->item;
  }

  /**
   * Sets agenda items.
   *
   * @param array $value
   *   Agenda items.
   */
  public function setItem(array $value) {
    $this->item = $value;
  }

  /**
   * Gets agenda date.
   *
   * @return Datetime
   *   Agenda date.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Sets agenda date.
   *
   * @param string $value
   *   Agenda date.
   */
  public function setDate($value) {
    $this->date = $value;
  }

  /**
   * Adds item to items array.
   *
   * @param object $value
   *   DB result value.
   */
  public function addItem($value) {
    $node = node_load($value->nid);
    $value->title = $node->title;
    $value->related_items = NexteuropaNewsroomRelatedItemHelper::getRelatedItems($value->nid);
    $value->url = NexteuropaNewsroomHelper::getNodeMainUrl($node);
    $value->prepared_start_date = $value->start_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
    $value->prepared_end_date = $value->end_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
    $this->item = $value;
  }

  /**
   * Checks if agenda items is empty.
   *
   * @return bool
   *   Is empty.
   */
  public function isEmpty() {
    return empty($this->getItem());
  }

}
