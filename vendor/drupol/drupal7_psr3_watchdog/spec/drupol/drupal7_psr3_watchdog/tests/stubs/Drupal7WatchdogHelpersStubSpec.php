<?php

namespace spec\drupol\drupal7_psr3_watchdog\tests\stubs;

use drupol\drupal7_psr3_watchdog\tests\stubs\Drupal7WatchdogHelpersStub;
use PhpSpec\ObjectBehavior;

class Drupal7WatchdogHelpersStubSpec extends ObjectBehavior
{
    public function it_is_initializable()
    {
        $this->shouldHaveType(Drupal7WatchdogHelpersStub::class);
    }

    public function it_is_detecting_if_watchdog_is_available()
    {
        $this->shouldThrow(\Exception::class)->during('checkWatchdogAvailability', []);

        require_once 'drupal7bootstrap.inc';

        $this->checkWatchdogAvailability()->shouldNotBeAnInstanceOf(\Exception::class);
    }

    public function it_is_converting_psr3_levels()
    {
        require_once 'drupal7bootstrap.inc';

        $mappings = [
            'emergency' => 0,
            'alert' => 1,
            'critical' => 2,
            'error' => 3,
            'warning' => 4,
            'notice' => 5,
            'info' => 6,
            'debug' => 7,
        ];

        foreach ($mappings as $key => $level) {
            $this->psr3ToDrupal7($key)->shouldReturn($level);
        }

        $this->shouldThrow(\UnexpectedValueException::class)->during('psr3ToDrupal7', ['3.14']);
    }

    public function it_is_formatting_record()
    {
        $input = [
            'message' => 'This is a log message of level {level}',
            'context' => [
                'level' => 3,
                'foo' => 'bar',
                'link' => '<a href="https://google.com/">Google</a>'
            ],
            'level_name' => 'error',
            'channel' => 'drupal',
        ];

        $expected = [
            'message' => 'This is a log message of level @level [level: @level, foo: @foo]',
            'context' => [
                'variables' => [
                    '@level' => '3',
                    '@foo' => 'bar',
                ],
                'link' => '<a href="https://google.com/">Google</a>',
            ],
            'level_name' => 'error',
            'channel' => 'drupal',
            'level' => 3
        ];

        $this->formatRecord($input)->shouldBeArray();
        $this->formatRecord($input)->shouldBe($expected);

        $input = [
            'message' => 'This is a log {message} of level',
            'context' => [
                'variables' => 'var',
                'link' => [],
                'message' => 'message',
                'object' => ['exception'],
            ],
            'level_name' => 'error',
            'channel' => 'drupal',
        ];

        $expected = [
            'message' => 'This is a log @message of level [message: @message]',
            'context' => [
                'variables' => [
                  '@message' => 'message',
                ],
                'link' => null,
            ],
            'level_name' => 'error',
            'channel' => 'drupal',
            'level' => 3
        ];

        $this->formatRecord($input)->shouldBeArray();
        $this->formatRecord($input)->shouldBe($expected);

        $input = [
          'message' => 'This is a log {message} of level',
          'context' => '',
          'level_name' => 'error',
          'channel' => 'drupal',
        ];

        $expected = [
          'message' => 'This is a log {message} of level',
          'context' => [
            'variables' => [],
              'link' => '',
          ],
          'level_name' => 'error',
          'channel' => 'drupal',
          'level' => 3
        ];

        $this->formatRecord($input)->shouldBeArray();
        $this->formatRecord($input)->shouldBe($expected);
    }
}
