<?php

/**
 * @file
 * Code for the NexteuropaNewsroomBuilder class.
 */

/**
 * NexteuropaNewsroomBuilder class.
 */
class NexteuropaNewsroomBuilder {

  /**
   * Builds agenda base on url params.
   *
   * @param string $type_name
   *   Type url name.
   * @param string $topic_name
   *   Topic url name.
   * @param string $arg1
   *   Date param.
   * @param string $arg2
   *   Date param.
   * @param string $arg3
   *   Date param.
   *
   * @return object
   *   Agenda item.
   */
  public static function buildPageAgenda($type_name = NEXTEUROPA_NEWSROOM_ALL, $topic_name = NEXTEUROPA_NEWSROOM_ALL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {

    $current_date = new DateTime();
    $type = self::getType($type_name);
    $topic = self::getTopic($topic_name);

    $day = self::getDay($arg1);
    $month = self::getMonth($arg2);
    $year = self::getYear($arg3);
    $current_date->setDate($year, $month, $day);

    return new NexteuropaNewsroomAgenda($type, $topic, $current_date);
  }

  /**
   * Validates and returns day number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Day number.
   */
  public static function getDay($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NexteuropaNewsroomHelper::getFormatedDate('d');
  }

  /**
   * Validates and returns month number.
   *
   * @param string $value
   *   Month number.
   *
   * @return int
   *   Month number.
   */
  public static function getMonth($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NexteuropaNewsroomHelper::getFormatedDate('n');
  }

  /**
   * Validates and returns year number.
   *
   * @param string $value
   *   Year number.
   *
   * @return int
   *   Year number.
   */
  public static function getYear($value) {
    return preg_match('/^\d{4}$/', $value) ? (int) $value : NexteuropaNewsroomHelper::getFormatedDate('Y');
  }

  /**
   * Gets taxonomy term topic from url name.
   *
   * @param string $topic_url
   *   Topic taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  public static function getTopic($topic_url) {
    return self::getTaxonomyTerm($topic_url, NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
  }

  /**
   * Validates date.
   *
   * @param string $value
   *   Date string.
   *
   * @return string|null
   *   Date string.
   */
  public static function getDate($value) {
    return NexteuropaNewsroomHelper::checkDateFormat($value);
  }

  /**
   * Gets taxonomy term type from url name.
   *
   * @param string $type_url
   *   Type taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  public static function getType($type_url) {
    return self::getTaxonomyTerm($type_url, NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
  }

  /**
   * Gets taxonomy term from url name.
   *
   * @param string $taxonomy_term_url
   *   Taxonomy term url name.
   * @param string $vocabulary_name
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getTaxonomyTerm($taxonomy_term_url, $vocabulary_name) {
    return $taxonomy_term_url == NEXTEUROPA_NEWSROOM_ALL ? NULL : NexteuropaNewsroomHelper::getTermFromRequest($taxonomy_term_url, $vocabulary_name);
  }

  /**
   * Builds newsroom page object.
   *
   * @param string|int $type_url
   *   Newsroom type url part or tid.
   * @param string|int $topic_url
   *   Newsroom topic url or tid.
   * @param string|null $start_date
   *   Start date.
   * @param string|null $end_date
   *   End date.
   *
   * @return NexteuropaNewsroomPage
   *   NexteuropaNewsroomPage object.
   */
  public static function buildNewsroomPage($type_url = NULL, $topic_url = NULL, $start_date = NULL, $end_date = NULL) {
    $type = self::getType($type_url);
    $topic = self::getTopic($topic_url);
    $start_date = self::getDate($start_date);
    $end_date = self::getDate($end_date);
    return new NexteuropaNewsroomPage($type, $topic, $start_date, $end_date);
  }

}
