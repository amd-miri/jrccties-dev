<?php

/**
 * @file
 * Code for the NexteuropaNewsroomBlockAgenda class.
 */

/**
 * NexteuropaNewsroomBlockAgenda class base class.
 */
class NexteuropaNewsroomBlockAgenda extends NexteuropaNewsroomBlockBase {

  /**
   * NexteuropaNewsroomBlockAgenda constructor.
   */
  public function __construct($type, $topics, $operator) {
    $this->setIsAgenda(TRUE);
    parent::__construct($type, $topics, $operator);
  }

  /**
   * Gets block title.
   *
   * @return string
   *   Block title.
   */
  public function getTitle() {
    return t('Agenda');
  }

  /**
   * Generates Agenda block content.
   *
   * @return string
   *   Agenda block content.
   */
  public function generateContent() {
    $agenda = new NexteuropaNewsroomAgendaBlockSchedule($this->getType(), $this->getTopics(), new DateTime(), $this->getOperator());
    $content = theme('newsroom_summary_block_wrapper', [
      'content' => $agenda->getBlockAgenda(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => 'agenda',
      'url' => 'newsroom-agenda/' . $this->getTypeUrl() . '/' . $this->getTopicUrl(),
    ]);
    return $content;
  }

}
