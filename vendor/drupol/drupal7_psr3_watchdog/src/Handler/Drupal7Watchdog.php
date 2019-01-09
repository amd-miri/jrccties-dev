<?php

namespace drupol\drupal7_psr3_watchdog\Handler;

use drupol\drupal7_psr3_watchdog\Traits\Drupal7WatchdogHelpers;
use Monolog\Handler\AbstractProcessingHandler;

/**
 * Class Drupal7Watchdog.
 *
 * @codeCoverageIgnore
 */
class Drupal7Watchdog extends AbstractProcessingHandler
{
    use Drupal7WatchdogHelpers;

    /**
     * {@inheritdoc}
     */
    protected function write(array $record)
    {
        $this->checkWatchdogAvailability();

        $record = $this->formatRecord($record);

        watchdog(
            $record['channel'],
            $record['message'],
            $record['context']['variables'],
            $record['level'],
            $record['context']['link']
        );
    }
}
