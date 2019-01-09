<?php

/**
 * @file
 * API file.
 */

use EC\Poetry\Messages\Notifications\TranslationReceived;
use EC\Poetry\Messages\Notifications\StatusUpdated;

/**
 * Fired when a new translation has been received by the Poetry service.
 *
 * @param \EC\Poetry\Messages\Notifications\TranslationReceived $message
 *   Poetry message object.
 */
function hook_nexteuropa_poetry_notification_translation_received(TranslationReceived $message) {

}

/**
 * Fired when a new translation has been received by the Poetry service.
 *
 * @param \EC\Poetry\Messages\Notifications\StatusUpdated $message
 *   Poetry message object.
 */
function hook_nexteuropa_poetry_notification_status_updated(StatusUpdated $message) {

}
