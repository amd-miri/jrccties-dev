<?php

/**
 * @file media_tableau/includes/themes/media-tableau-video.tpl.php
 *
 * Template file for theme('media_tableau_visualization').
 */
?>
<script src="<?php print $script_url; ?>"></script>
<div class="media-tableau-outer-wrapper" id="media-tableau-<?php print $id; ?>" style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
	<div class="media-tableau-preview-wrapper"
		id="<?php print $wrapper_id; ?>">
		<div class="tableauPlaceholder" style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
			<noscript>
				<a href="#"><img alt=""
					src="<?php print $image_url_noscript; ?>"
					style="border: none" /> </a>
			</noscript>
			<object class="tableauViz" width="<?php print $width; ?>" height="<?php print $height; ?>"
				style="display: none;">
				<param name="host_url"
					value="<?php print urlencode($server . '/'); ?>" />
				<param name="site_root" value="" />
				<param name="name" value="<?php print $visualization_decoded; ?>" />
				<param name="tabs" value="yes" />
				<param name="toolbar" value="yes" />
				<param name="static_image"
					value="<?php print urlencode($image_url_static); ?>" />
				<param name="animate_transition" value="yes" />
				<param name="display_static_image" value="yes" />
				<param name="display_spinner" value="yes" />
				<param name="display_overlay" value="yes" />
			</object>
		</div>
		<div
			style="width: <?php print $width; ?>px; height: 22px; padding: 0px 10px 0px 0px; color: black; font: normal 8pt verdana, helvetica, arial, sans-serif;">
			<div style="float: right; padding-right: 8px;"></div>
		</div>
	</div>
</div>
