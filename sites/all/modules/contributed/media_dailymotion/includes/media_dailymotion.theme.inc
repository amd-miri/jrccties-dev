<?php
/**
 * @file
 *
 * Theme and preprocess functions for Media: Dailymotion.
 */

/**
 * Preprocess function for theme('media_dailymotion_video').
 */
function media_dailymotion_preprocess_media_dailymotion_video(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parameters = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parameters['video_id']);

  $variables['width'] = isset($variables['width']) ? $variables['width'] : media_dailymotion_variable_get('width');
  $variables['height'] = isset($variables['height']) ? $variables['height'] : media_dailymotion_variable_get('height');
  $variables['autoplay'] = isset($variables['autoplay']) ? $variables['autoplay'] : media_dailymotion_variable_get('autoplay');
  $variables['fullscreen'] = isset($variables['fullscreen']) ? $variables['fullscreen'] : media_dailymotion_variable_get('fullscreen');
  $variables['iframe'] = isset($variables['iframe']) ? $variables['iframe'] : media_dailymotion_variable_get('iframe');
  $variables['autoplay'] = $variables['autoplay'] ? 1 : 0;
  $variables['fullscreen'] = $variables['fullscreen'] ? 'true' : 'false';

  $variables['wrapper_id'] = 'media_dailymotion_' . $variables['video_id'] . '_' . $variables['id'];

  //TODO support background, foreground and highlight parameters?
  // For users with JavaScript, these object and embed tags will be replaced
  // by an iframe, so that we can support users without Flash.
  if(!$variables['iframe']) {
    $variables['output'] = <<<OUTPUT
    <object width="{$variables['width']}" height="{$variables['height']}">
      <param name="movie" value="http://www.dailymotion.com/swf/video/{$variables['video_id']}?autoPlay={$variables['autoplay']}"></param>
      <param name="allowFullScreen" value="{$variables['fullscreen']}"></param>
      <param name="allowScriptAccess" value="always"></param>
      <embed type="application/x-shockwave-flash" src="http://www.dailymotion.com/swf/video/{$variables['video_id']}?autoPlay={$variables['autoplay']}" width="{$variables['width']}" height="{$variables['height']}" allowfullscreen="{$variables['fullscreen']}" allowscriptaccess="always"></embed>
    </object>
OUTPUT;
  }
  else {
    $variables['output'] = <<<OUTPUT
    <iframe frameborder="0" width="{$variables['width']}" height="{$variables['height']}" src="http://www.dailymotion.com/embed/video/{$variables['video_id']}?logo=0&autoPlay={$variables['autoplay']}"></iframe>
OUTPUT;
  }
}
