<?php

/**
 *  @file
 *  Create a Tableau Stream Wrapper class for the Media/Resource module.
 */

class MediaTableauStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://tableau.com/watch';

  function getTarget($f) {
    return FALSE;
  }

  /**
   * Returns the MIME type for the visualization
   * 
   * @param string $uri
   * @param string $mapping
   * 
   * @return string
   */
  static function getMimeType($uri, $mapping = NULL) {
    return 'application/tableau';
  }

  /**
   * Returns the basic path to the static image for the visualization
   * 
   * @return string
   */
  function getOriginalThumbnailPath() {
    $parts = $this->get_parameters();

    $visualization_decoded = $this->getVisualizationPath();
    //FIXME: Need a better way of doing this
    $visualization_decoded = str_replace('shared/', '', $visualization_decoded);
    return 'http://' . $this->getServer() . '/static/images/' . substr($visualization_decoded, 0, 2) . '/' . $visualization_decoded . '/1.png';
  }

  /**
   * Try to get the background image from the hosted version of the visualizations
   * 
   * @return string
   */
  function getEmbeddedThumbnailPath() {
    $image_url = '';
    
    $parts = $this->get_parameters();
    $visualization_decoded = $this->getVisualizationPath();
    
    // First get the hosted visualization
    $url = 'http://' . $this->getServer() . '/' . $visualization_decoded;
    $visualization_include = drupal_http_request($url);
    if (200 == $visualization_include->code) {
      // Then pull the image from the OpenGraph image meta attribute
      preg_match('/<meta property="og:image" content="(.*?)"/i', $visualization_include->data, $matches);
      if (TRUE === isset($matches[1])) {
        $image_url = html_entity_decode($matches[1]);
        $image_url_parts = parse_url($image_url);
        $image_url_paths = explode('/', trim($image_url_parts['path'], '/'));
        
        // Next try to construct the underlying saved image from the path of the og:image
        if (2 < sizeof($image_url_paths)) {
          $good_path_parts = array_slice($image_url_paths, 2);
          $image_prefix = substr($good_path_parts[0], 0, 2);
          array_unshift($good_path_parts, $image_prefix);
          $image_url = $image_url_parts['scheme'] . '://' . $image_url_parts['host'] . '/static/images/' . implode('/', $good_path_parts) . '/1.png';
        }
      }
    }
    
    return $image_url;
  }

  /**
   * Returns the server for the visualization
   * 
   * @return string
   */
  function getServer() {
    $parts = $this->get_parameters();
    return $parts['s'];
  }

  /**
   * Returns the path to the visualization
   * 
   * @return string
   */
  function getVisualizationPath() {
    $parts = $this->get_parameters();
    $visualization_decoded = html_entity_decode($parts['v']);

    return $visualization_decoded;
  }

  /**
   * Gets the static image path for the visualization
   * 
   * @return string
   */
  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $hash = md5($this->uri);
    $local_path = 'public://media-tableau/' . $hash . '.png';

    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      try {
        $default_thumbnail_url = $this->getOriginalThumbnailPath();
        
        // Try to get the static image from Tableau, but do not allow redirects
        // otherwise we may get the 302 to their page not found page
        $default_thumbnail_request = drupal_http_request($default_thumbnail_url, array('max_redirects' => 0));

        if (200 == $default_thumbnail_request->code) {
          copy($default_thumbnail_url, $local_path);
        }
        else {
          copy($this->getEmbeddedThumbnailPath(), $local_path);
        }
      }
      catch (Exception $e) {
        watchdog('Tableau', $e->getMessage());
      }
    }
    return $local_path;
  }
}
