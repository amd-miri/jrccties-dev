<?php

/**
 * @file
 * Pages content for menu callbacks.
 */

/**
 * Agenda menu callback.
 *
 * @param string $type
 *   Type name.
 * @param string $topic
 *   Topic name.
 * @param string $arg1
 *   Date param.
 * @param string $arg2
 *   Date param.
 * @param string $arg3
 *   Date param.
 *
 * @return string
 *   Agenda content,
 */
function _nexteuropa_newsroom_agenda($type = NULL, $topic = NULL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
  $build['#markup'] = NexteuropaNewsroomBuilder::buildPageAgenda($type, $topic, $arg1, $arg2, $arg3)->getAgenda();
  $build['#attached']['js'][] = [
    'type' => 'file',
    'data' => drupal_get_path('module', 'nexteuropa_newsroom') . '/js/agenda.js',
    'weight' => -1000,
  ];
  return $build;
}

/**
 * Newsroom page menu callback.
 *
 * @param string $type_url
 *   Type url part.
 * @param string $topic_url
 *   Topic url part.
 * @param string $start_date
 *   Start date.
 * @param string $end_date
 *   End date.
 *
 * @return string
 *   Newsroom page content,
 */
function _nexteuropa_newsroom_page($type_url = NULL, $topic_url = NULL, $start_date = NULL, $end_date = NULL) {
  return NexteuropaNewsroomBuilder::buildNewsroomPage($type_url, $topic_url, $start_date, $end_date)->getContent();
}

/**
 * Newsroom page menu callback.
 *
 * @param string $type_url
 *   Type url part.
 * @param string $topic_url
 *   Topic url part.
 */
function _nexteuropa_newsroom_rss($type_url = NULL, $topic_url = NULL) {
  $newsroom_page = NexteuropaNewsroomBuilder::buildNewsroomPage($type_url, $topic_url);
  drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
  echo $newsroom_page->getRssContent();
  module_invoke_all('exit');
  exit();
}

/**
 * Returns render array for the access newsletters page.
 *
 * @return array
 *   Array of markup.
 */
function _nexteuropa_newsroom_newsletters_page() {
  $view = views_get_view('newsroom_services');
  $build = [];
  $basic_display = 'basic';
  $central_display = 'central';

  if ($view) {
    $subscriptions = _nexteuropa_newsroom_get_user_subscriptions();
    $universe_id = NexteuropaNewsroomHelper::getUniverseId();
    global $user;

    if (user_access(NEXTEUROPA_NEWSROOM_ADMIN_ACCESS, $user) && (empty(variable_get('nexteuropa_newsroom_subscription_url')) || empty(variable_get('nexteuropa_newsroom_app')) || empty(variable_get('nexteuropa_newsroom_app_key')))) {
      drupal_set_message(t('Please setup newsroom settings: app, key and subscription URL !url.', ['!url' => l(t('Newsroom settings'), 'admin/config/content/newsroom')]), 'warning');
    }

    $view->set_display($basic_display);
    $view->pre_execute();
    $view->execute();
    $basic_newsletters = $view->result;
    $view->destroy();

    $view = views_get_view('newsroom_services');
    $view->set_display($central_display);
    $view->pre_execute();
    $view->execute();
    $central_newsletters = $view->result;
    $content = theme('newsroom_services_page', [
      'central_items' => theme('newsroom_services_items',
        [
          'items' => _nexteuropa_newsroom_prepare_newsletters($central_newsletters, $subscriptions),
          'title' => variable_get('nexteuropa_newsroom_central_newsletter_title', t('Central newsletters')),
          'css_class' => $central_display,
          'universe_id' => $universe_id,
        ]),
      'basic_items' => theme('newsroom_services_items',
        [
          'items' => _nexteuropa_newsroom_prepare_newsletters($basic_newsletters, $subscriptions),
          'title' => variable_get('nexteuropa_newsroom_other_newsletter_title', t('Other newsletters')),
          'css_class' => $basic_display,
          'universe_id' => $universe_id,
        ]),
      'privacy_text' => variable_get('nexteuropa_newsroom_newsletter_privacy', NULL),
    ]);

    $build['#markup'] = $content;
    $build['#attached']['js'][] = [
      'type' => 'setting',
      'data' => ['nexteuropa_newsroom' => ['error_message' => t('Wrong e-mail address.'), 'user_is_logged_in' => user_is_logged_in()]],
    ];
    $build['#attached']['js'][] = [
      'type' => 'file',
      'data' => drupal_get_path('module', 'nexteuropa_newsroom') . '/js/newsletter_list.js',
    ];
  }

  return $build;
}

/**
 * Prepares newsletters for presentation.
 *
 * @param array $newsletters
 *   Items from view.
 * @param array $subscriptions
 *   Current user subscriptions.
 *
 * @return array
 *   Newsletter items prepared for output.
 */
function _nexteuropa_newsroom_prepare_newsletters(array $newsletters = [], array $subscriptions = []) {
  $output = [];
  if (!empty($newsletters)) {
    foreach ($newsletters as $newsletter) {
      $item = new stdClass();
      $item->title = $newsletter->taxonomy_term_data_name;
      $item->description = $newsletter->taxonomy_term_data_description;
      $item->service_sample = !empty($newsletter->field_field_newsroom_service_sample_et[0]) ? drupal_render($newsletter->field_field_newsroom_service_sample_et[0]['rendered']) : NULL;
      $item->service_id = !empty($newsletter->field_field_newsroom_service_id[0]) ? $newsletter->field_field_newsroom_service_id[0]['raw']['value'] : NULL;
      $item->image = !empty($newsletter->field_field_newsroom_service_image[0]) ? drupal_render($newsletter->field_field_newsroom_service_image[0]['rendered']) : NULL;
      $item->form = NULL;
      if (!empty($item->service_id)) {
        $subscription_url = NULL;
        foreach ($subscriptions as $user_subscription) {
          if ($user_subscription['NEWSLETTERID'] == $item->service_id) {
            $subscription_url = $user_subscription['UNSUBSCRIPTIONLINK'];
            break;
          }
        }
        if ($subscription_url) {
          $form = drupal_get_form('nexteuropa_newsroom_unsubscription_newsletter_form', $subscription_url);
        }
        else {
          $form = drupal_get_form('nexteuropa_newsroom_subscription_newsletter_form', $item->service_id);
        }

        $item->form = drupal_render($form);
      }
      $output[] = $item;
    }
  }
  return $output;
}

/**
 * Returns user subscriptions from the newsroom side.
 *
 * @return array
 *   User subscriptions response.
 */
function _nexteuropa_newsroom_get_user_subscriptions() {
  $subscriptions = [];
  if (user_is_logged_in()) {
    global $user;
    $input = [
      'user_email' => $user->mail,
      'universe_acronym' => NexteuropaNewsroomHelper::getUniverseId(),
      'app' => variable_get('nexteuropa_newsroom_app'),
      'key' => NexteuropaNewsroomHelper::getEmailHash($user->mail),
      'response_type' => 'json',
    ];
    $url = variable_get('nexteuropa_newsroom_subscription_url');
    if ($url) {
      $request = drupal_http_request($url . '?' . drupal_http_build_query($input));
      if (!empty($request->data)) {
        $subscriptions = drupal_json_decode($request->data);
      }
    }
  }

  return $subscriptions;
}
