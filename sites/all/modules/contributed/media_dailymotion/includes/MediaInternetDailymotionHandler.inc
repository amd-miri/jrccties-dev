<?php
/**
 * @file
 *   media_internet handler for dailymotion.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetDailymotionHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $patterns = array(
      '@dailymotion\.com/swf/([^"\&]+)@i',
      '@dailymotion\.com/video/([^/_]+)_@i',
      '@dailymotion\.com/video/([^/_]+)@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1])) {
        return file_stream_wrapper_uri_normalize('dailymotion://video_id/' . $matches[1]);
      }
    }
    return FALSE;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    return file_uri_to_object($uri);
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }
}
