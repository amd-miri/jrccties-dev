<?php
/**
 * @file
 * Migration of the custom file fields from The old JRC database.
 */

/**
 * Migration class to modify the original migrate_d2d class.
 */
class D2DModifierMigration extends DrupalNode7Migration {

  /**
   * Class construct function.
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->softDependencies = array('71582fc13Nodeimage_gallery');
  }

  /**
   * Class prepareRow function.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    /*************** Replace the expand tags *****************/
    if (strpos($row->body[0], '<div class="start_expand_editor">START_EXPAND</div>') !== FALSE) {
      $row->body[0] = str_replace('<div class="start_expand_editor">START_EXPAND</div>', '[collapsed title=view details]', $row->body[0]);
      $row->body[0] = str_replace('<div class="end_expand_editor">END_EXPAND</div>', '[/collapse]', $row->body[0]);
    }

    /*************** Replace the node_embed tags by ckeditor ones *****************/
    if (($count = substr_count($row->body[0], '[[nid:')) > 0) {
      // Fetch all embeded nids from the row body.
      preg_match_all('/\[\[nid\:([0-9]+)(\s([^\]]*))?\]\]/i', $row->body[0], $matches);
      if (!empty($matches)) {
        foreach ($matches[1] as $old_nid) {
          $new_nid = '';
          // Fetch the equivalent nid in Multisite.
          $query = db_select('migrate_map_71582fc13nodeimage_gallery', 'm')
                  ->fields('m')
                  ->condition('m.sourceid1', $old_nid, '=')
                  ->execute()
                  ->fetch();
          $new_nid = $query->destid1;

          if (!empty($new_nid) && $new_nid != '') {
            // Get the node title.
            $found_node = node_load($new_nid, NULL, TRUE);
            $new_node_title = $found_node->title;

            // Replace the first found embed nid code.
            $search = '/\[\[nid\:([0-9]+)(\s([^\]]*))?\]\]/i';
            $replace = '<p>[node:' . $new_nid . ':view-mode:full]{' . $new_node_title . '}</p>';
            $row->body[0] = preg_replace($search, $replace, $row->body[0], 1);
          }
        }
      }
    }

    /*************** Replace the old hardcoded host by a global token *****************/
    if (($count = substr_count($row->body[0], 'sites/default/files/')) > 0 ||
        ($count = substr_count($row->body[0], 'class="file media-element file-default"')) > 0) {

      // 1. Fetch all "http" urls from the row body.
      preg_match_all('/(http\:\/\/ec\.europa\.eu\/jrc\/sites\/default\/files\/)/i', $row->body[0], $http_matches);
      if (!empty($http_matches)) {
        $search = '/(http\:\/\/ec\.europa\.eu\/jrc\/sites\/default\/files\/)/i';
        $replace = 'https://[custom:base-url-without-lang]/sites/jrcsh/files/';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 2. Fetch all "https" urls from the row body.
      preg_match_all('/(https\:\/\/ec\.europa\.eu\/jrc\/sites\/default\/files\/)/i', $row->body[0], $https_matches);
      if (!empty($https_matches)) {
        $search = '/(https\:\/\/ec\.europa\.eu\/jrc\/sites\/default\/files\/)/i';
        $replace = 'https://[custom:base-url-without-lang]/sites/jrcsh/files/';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 3. Fetch all jrc-irmm urls with https.
      preg_match_all('/(https:\/\/jrc-irmm\.ec\.europa\.eu\/jrc)/i', $row->body[0], $jrc_irmm_matches);
      if (!empty($jrc_irmm_matches)) {
        $search = '/(https:\/\/jrc-irmm\.ec\.europa\.eu\/jrc)/i';
        $replace = '';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 4. Fetch all jrc-itu urls with https.
      preg_match_all('/(https:\/\/jrc-itu\.ec\.europa\.eu\/jrc)/i', $row->body[0], $jrc_itu_matches);
      if (!empty($jrc_itu_matches)) {
        $search = '/(https:\/\/jrc-itu\.ec\.europa\.eu\/jrc)/i';
        $replace = '';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 5. Fetch all jrc-ipts urls with https.
      preg_match_all('/(https:\/\/jrc-ipts\.ec\.europa\.eu\/jrc)/i', $row->body[0], $jrc_ipts_matches);
      if (!empty($jrc_ipts_matches)) {
        $search = '/(https:\/\/jrc-ipts\.ec\.europa\.eu\/jrc)/i';
        $replace = '';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 6. Fetch all short urls with starting slash from the row body.
      preg_match_all('/(\/sites\/default\/files\/)/i', $row->body[0], $short_url_ss_matches);
      if (!empty($short_url_ss_matches)) {
        $search = '/(\/sites\/default\/files\/)/i';
        $replace = 'https://[custom:base-url-without-lang]/sites/jrcsh/files/';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 7. Fetch all short urls from the row body.
      preg_match_all('/(sites\/default\/files\/)/i', $row->body[0], $short_url_matches);
      if (!empty($short_url_matches)) {
        $search = '/(sites\/default\/files\/)/i';
        $replace = 'https://[custom:base-url-without-lang]/sites/jrcsh/files/';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 8. Romove the old media css classes.
      preg_match_all('/(class=\"file media-element file-default\"[[:blank:]])/i', $row->body[0], $media_matches);
      if (!empty($media_matches)) {
        $search = '/(class=\"file media-element file-default\"[[:blank:]])/i';
        $replace = '';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }
    }

    /*************** Replace the old broken PDF image url *****************/
    if (($count = substr_count($row->body[0], 'f_pdf_16.gif')) > 0 ||
        ($count = substr_count($row->body[0], 'application-pdf.png')) > 0) {
      $path_to_theme = drupal_get_path('theme', 'jrc_multisite_subtheme');
      $replace = 'https://[custom:base-url-without-lang]/' . $path_to_theme . '/images/f_pdf_16.gif';

      // 1. Fetch all "http" urls from the row body.
      preg_match_all('/(http:\/\/ec\.europa\.eu\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i', $row->body[0], $pdf_http_matches);
      if (!empty($pdf_http_matches)) {
        $search = '/(http:\/\/ec\.europa\.eu\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 2. Fetch all "https" urls from the row body.
      preg_match_all('/(https:\/\/ec\.europa\.eu\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i', $row->body[0], $pdf_https_matches);
      if (!empty($pdf_https_matches)) {
        $search = '/(https:\/\/ec\.europa\.eu\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 3. Fetch an other url from the row body.
      preg_match_all('/(http:\/\/www\.cc.cec\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i', $row->body[0], $short_pdf_matches);
      if (!empty($short_pdf_matches)) {
        $search = '/(http:\/\/www\.cc.cec\/wel\/images\/doc_icons\/f_pdf_16\.gif)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 4. Fetch all short urls with starting slash from the row body.
      preg_match_all('/(\/wel\/images\/doc_icons\/f_pdf_16.gif)/i', $row->body[0], $short_pdf_ss_matches);
      if (!empty($short_pdf_ss_matches)) {
        $search = '/(\/wel\/images\/doc_icons\/f_pdf_16.gif)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 5. Fetch all short urls from the row body.
      preg_match_all('/(wel\/images\/doc_icons\/f_pdf_16.gif)/i', $row->body[0], $short_wel_matches);
      if (!empty($short_wel_matches)) {
        $search = '/(wel\/images\/doc_icons\/f_pdf_16.gif)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 6. Fetch all application-pdf.png urls from the row body.
      preg_match_all('/(\/jrc\/modules\/file\/icons\/application-pdf.png)/i', $row->body[0], $long_app_matches);
      if (!empty($long_app_matches)) {
        $search = '/(\/jrc\/modules\/file\/icons\/application-pdf.png)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }

      // 7. Fetch all application-pdf.png urls from the row body.
      preg_match_all('/(\/modules\/file\/icons\/application-pdf.png)/i', $row->body[0], $short_app_matches);
      if (!empty($short_app_matches)) {
        $search = '/(\/modules\/file\/icons\/application-pdf.png)/i';
        $row->body[0] = preg_replace($search, $replace, $row->body[0]);
      }
    }
    return TRUE;
  }

  /**
   * Class prepare function.
   */
  public function prepare(stdClass $entity, stdClass $row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    /*************** Make sure that a published node is also imported as published *****************/
    if ($row->status == 1) {
      $entity->workbench_moderation_state_current = 'draft';
      $entity->workbench_moderation_state_new = 'published';
    }
  }

}
