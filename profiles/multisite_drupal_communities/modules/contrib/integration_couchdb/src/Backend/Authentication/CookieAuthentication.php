<?php

namespace Drupal\integration_couchdb\Backend\Authentication;

use Drupal\integration\Backend\Authentication\AbstractAuthentication;
use Drupal\integration\Exceptions\BackendException;
use GuzzleHttp\Client as GuzzleClient;
use GuzzleHttp\Cookie\CookieJar as CookieJar;
use GuzzleHttp\Exception\RequestException;

/**
 * Class CookieAuthentication.
 *
 * @package Drupal\integration_couchdb\Backend\Authentication
 */
class CookieAuthentication extends AbstractAuthentication {

  /**
   * {@inheritdoc}
   */
  public function authenticate() {
    // We store the session cookie in the cache for future requests
    // but need to make sure it has not expired, which is not checked
    // by cache_get.
    $cache_available = TRUE;
    if ($cache = cache_get('integration_couchdb_authentication', 'cache')) {
      if ($cache->expire < REQUEST_TIME) {
        $cache_available = FALSE;
      }
    }
    else {
      $cache_available = FALSE;
    }
    // The cookie is not available; do authentication.
    if (!$cache_available) {
      $configuration = $this->getConfiguration();
      $username = $configuration->getComponentSetting('authentication_handler', 'username');
      $password = $configuration->getComponentSetting('authentication_handler', 'password');
      $base_url = $configuration->getPluginSetting('backend.base_url');
      $loginpath = $configuration->getComponentSetting('authentication_handler', 'loginpath');

      // Use the context to pass the cookiejar to the backend.
      $context = $this->getContext();
      $cookies = new CookieJar();

      $client = new GuzzleClient([
        'headers' => [
          'content-type' => 'application/x-www-form-urlencoded',
        ],
      ]);

      try {
        $options = [
          'body' => "name=$username&password=$password",
          'cookies' => $cookies,
        ];
        if (variable_get('integration_couchdb_debug', FALSE)) {
          $options['debug'] = TRUE;
        }
        $response = $client->request('POST', $base_url . $loginpath, $options);
      }
      catch (RequestException $e) {
        throw $e;
      }

      // If correctly authentified, store the cookie and
      // use a short expiration delay.
      // @todo: the delay should be configurable.
      if ($response->getStatusCode() === 200) {
        cache_set('integration_couchdb_authentication', $cookies, 'cache', REQUEST_TIME + 600);
        $context['cookies'] = $cookies;
        $this->setContext($context);
        return TRUE;
      }
      else {
        throw new BackendException("Could not authenticate.");
      }
    }
    else {
      // Cookie is available in the cache, simply retrieve it.
      $context['cookies'] = $cache->data;
      $this->setContext($context);
      return TRUE;
    }
  }

}
