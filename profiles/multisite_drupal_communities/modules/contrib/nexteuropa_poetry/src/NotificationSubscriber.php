<?php

namespace Drupal\nexteuropa_poetry;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use EC\Poetry\Events\Notifications\TranslationReceivedEvent;
use EC\Poetry\Events\Notifications\StatusUpdatedEvent;

/**
 * Class NotificationSubscriber.
 *
 * @package Drupal\nexteuropa_poetry
 */
class NotificationSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return array(
      TranslationReceivedEvent::NAME => 'onTranslationReceivedEvent',
      StatusUpdatedEvent::NAME       => 'onStatusUpdatedEvent',
    );
  }

  /**
   * Notification handler.
   *
   * @param \EC\Poetry\Events\Notifications\TranslationReceivedEvent $event
   *   Event object.
   */
  public function onTranslationReceivedEvent(TranslationReceivedEvent $event) {
    module_invoke_all('nexteuropa_poetry_notification_translation_received', $event->getMessage());
  }

  /**
   * Notification handler.
   *
   * @param \EC\Poetry\Events\Notifications\StatusUpdatedEvent $event
   *   Event object.
   */
  public function onStatusUpdatedEvent(StatusUpdatedEvent $event) {
    module_invoke_all('nexteuropa_poetry_notification_status_updated', $event->getMessage());
  }

}
