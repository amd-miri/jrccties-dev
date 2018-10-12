<?php
/**
 * @file
 *   Create a Dailymotion Stream Wrapper class for the Media/Resource module.
 */

/**
 * Stream Wrapper class for Dailymotion.
 */
class MediaDailymotionStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://www.dailymotion.com/video';

  protected function getTarget($uri = NULL) {
    // It's a read-only stream wrapper for now.
    return FALSE;
  }

  function interpolateUrl() {
    $parameters = $this->get_parameters();
    return $this->base_url .'/'. check_plain($parameters['video_id']);
  }

  public static function getMimeType($uri, $mapping = NULL) {
    return 'video/dailymotion';
  }

  public function getOriginalThumbnailPath() {
    $parameters = $this->get_parameters();
    $result = drupal_http_request('https://api.dailymotion.com/video/'. check_plain($parameters['video_id']) . '?fields=thumbnail_url');
    if (isset($result->error)) {
      return FALSE;
    }
    $data = drupal_json_decode($result->data);
    return $data['thumbnail_url'];
  }

  public function getLocalThumbnailPath() {
    $parameters = $this->get_parameters();
    $local_path = 'public://media-dailymotion/' . check_plain($parameters['video_id']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($this->getOriginalThumbnailPath());
      if (!isset($response->error)) {
        file_unmanaged_save_data($response->data, $local_path, TRUE);
      }
      else {
        @copy($this->getOriginalThumbnailPath(), $local_path);
      }
    }
    return $local_path;
  }
}
