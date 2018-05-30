<?php

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetTableauHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $patterns = array(
      'name' => '/src=["\']https?:\/\/([\w\/:\.]*?)\/javascripts\/api\/viz_v1\.js.*?width[:=]["\']?\s?(\d+).*?height[:=]["\']?\s?(\d+).*?\<param name=["\']name["\'] value=["\'](.*?)["\']\s/i',
      'path' => '/src=["\']https?:\/\/([\w\/:\.]*?)\/javascripts\/api\/viz_v1\.js.*?width[:=]["\']?\s?(\d+).*?height[:=]["\']?\s?(\d+).*?\<param name=["\']path["\'] value=["\'](.*?)["\']\s/i'
    );
    foreach ($patterns as $version => $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (TRUE === isset($matches[1]) && TRUE === isset($matches[4])) {
        return file_stream_wrapper_uri_normalize('tableau://s/' . $matches[1] . '/w/' . $matches[2] . '/h/' . $matches[3] . '/t/' . $version . '/v/' . $matches[4]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    //@todo: this is terribly broken in some ways because the function is really
    // made for local files which are 'real'
    return file_uri_to_object($uri);
  }
}
