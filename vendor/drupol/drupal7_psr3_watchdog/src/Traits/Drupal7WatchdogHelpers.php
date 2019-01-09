<?php

namespace drupol\drupal7_psr3_watchdog\Traits;

use Psr\Log\LogLevel;

trait Drupal7WatchdogHelpers
{
    /**
     * Format record to be compliant with PSR-3 and Drupal's watchdog function
     * signature.
     *
     * @param $record
     *   A log record.
     *
     * @return array
     *   A record array.
     */
    public function formatRecord($record)
    {
        $context_message = [];

        // Make sure the $record variable contains everything needed.
        $record += [
          'context' => [],
          'message' => '',
          'level_name' => 0,
        ];

        // Make sure the 'context' key is an array
        if (!is_array($record['context'])) {
            $record['context'] = [];
        }

        // Complete the array with keys that we need.
        $record['context'] += [
          'variables' => [],
          'link' => '',
        ];

        // Convert the level_name to a watchdog level.
        $record['level'] = $this->psr3ToDrupal7($record['level_name']);

        // Make sure the message can be converted to a string.
        $record['message'] = (string) $record['message'];

        // Make sure the 'link' key is a string.
        if (!is_string($record['context']['link'])) {
            $record['context']['link'] = null;
        }

        // Make sure the 'variables' key is an array
        if (!is_array($record['context']['variables'])) {
            $record['context']['variables'] = [];
        }

        // Store them for later use and delete them from the 'context' key.
        $variables = $record['context']['variables'];
        $link = $record['context']['link'];
        unset($record['context']['variables'], $record['context']['link']);

        // Convert PSR-3 placeholders to Drupal's placeholders and convert
        // 'context' variables.
        $replace = [];
        foreach ($record['context'] as $key => $value) {
            // check that the value can be casted to string
            if (!is_array($value) && (!is_object($value) || method_exists($value, '__toString'))) {
                $replace['{' . $key . '}'] = '@' . $key;
            } else {
                continue;
            }

            $variables['@' . $key] = (string) $value;
            $context_message[] = $key;
        }
        $record['message'] = strtr($record['message'], $replace);

        // If any 'context_message', add it to the original record message.
        if (!empty($context_message)) {
            $record['message'] .= ' [' . implode(', ', array_map(function ($item) {
                return sprintf('%s: @%s', $item, $item);
            }, $context_message)) . ']';
        }

        // Add back variables to the context.
        $record['context'] = [
          'variables' => $variables,
          'link' => $link
        ];

        return $record;
    }

    /**
     * Convert PSR-3 log level to Drupal 7 log level.
     *
     * @param int $level
     *   The log level.
     *
     * @return int
     *   The Drupal level.
     */
    public function psr3ToDrupal7($level)
    {
        $level = strtolower($level);

        switch ($level) {
            case LogLevel::EMERGENCY:
                return WATCHDOG_EMERGENCY;
            case LogLevel::ALERT:
                return WATCHDOG_ALERT;
            case LogLevel::CRITICAL:
                return WATCHDOG_CRITICAL;
            case LogLevel::ERROR:
                return WATCHDOG_ERROR;
            case LogLevel::WARNING:
                return WATCHDOG_WARNING;
            case LogLevel::NOTICE:
                return WATCHDOG_NOTICE;
            case LogLevel::INFO:
                return WATCHDOG_INFO;
            case LogLevel::DEBUG:
                return WATCHDOG_DEBUG;
        }

        throw new \UnexpectedValueException(sprintf('Invalid log level: %s', $level));
    }

    /**
     * Check if the watchdog function is available.
     *
     * @throws \Exception
     */
    public function checkWatchdogAvailability()
    {
        if (!function_exists('watchdog')) {
            throw new \Exception("The watchdog() function hasn't been found.");
        }
    }
}
