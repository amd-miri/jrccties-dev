<?php

/**
 * @file
 * Styles class implementation for Media: Tableau.
 */

class MediaTableauStyles extends FileStyles {
  function getImageUri() {
    if ($image_uri = $this->get('imageUri')) {
      return $image_uri;
    }
    $object = $this->getObject();
    if ($object->uri) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($object->uri);
      return $wrapper->getLocalThumbnailPath();
    }
  }
  function video($effect) {
    $variables = array(
      'uri' => $this->getUri(),
      'width' => $this->getWidth(),
      'height' => $this->getHeight(),
    );
    $this->setOutput(theme('media_tableau_video', $variables));
  }
}
