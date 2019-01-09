<?php

namespace Drupal\Tests\nexteuropa_poetry\Behat;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Class FeatureContext.
 *
 * @package Drupal\nexteuropa_poetry\Tests\Behat
 */
class FeatureContext extends RawDrupalContext {

  /**
   * Restores the initial values of the Drupal variables.
   *
   * @BeforeScenario @watchdog
   */
  public function resetWatchdog() {
    db_truncate('watchdog')->execute();
  }

  /**
   * Assert message in Watchdog.
   *
   * @When the following message should be in the watchdog :message
   */
  public function assertWatchdogMessagePresence($message) {
    if ($this->countWatchdogMessageOccurrences($message) === 0) {
      throw new \Exception("Message '{$message}' not found in Watchdog.");
    }
  }

  /**
   * Assert message not in Watchdog.
   *
   * @When the following message should not be in the watchdog :message
   */
  public function assertWatchdogMessageAbsence($message) {
    if ($this->countWatchdogMessageOccurrences($message) > 0) {
      throw new \Exception("Message '{$message}' found in Watchdog.");
    }
  }

  /**
   * Count number of message occurrences in watchdog.
   *
   * @param string $message
   *   Message.
   *
   * @return int
   *   Occurrences.
   */
  protected function countWatchdogMessageOccurrences($message) {
    return (int) db_select('watchdog', 'w')
      ->fields('w')
      ->condition('message', $message)
      ->countQuery()
      ->execute()
      ->fetchField();
  }

}
