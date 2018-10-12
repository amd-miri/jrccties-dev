<?php
/**
 * @file
 *
 * Template file for theme('media_dailymotion_video').
 *
 * Variables available:
 *  $uri - The uri to the Dailymotion video, such as dailymotion://video_id/xsy7x8c9.
 *  $video_id - The unique identifier of the Dailymotion video.
 *  $width - The width to render.
 *  $height - The height to render.
 *  $autoplay - If TRUE, then start the player automatically when displaying.
 *  $fullscreen - Whether to allow fullscreen playback.
 *  $output - The object/embed code
 *
 * Note that we set the width & height of the outer wrapper manually so that
 * the JS will respect that when resizing later.
 */
?>
<div class="media-dailymotion-outer-wrapper" id="media-dailymotion-<?php print $id; ?>" style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
  <div class="media-dailymotion-preview-wrapper" id="<?php print $wrapper_id; ?>">
    <?php print $output; ?>
  </div>
</div>
