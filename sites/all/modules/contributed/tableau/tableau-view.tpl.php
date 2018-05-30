<?php

/**
 * @file tableau-view.tpl.php
 * Template file for theme('tableau_view_interactive').
 */
?>

<script type="text/javascript" src="<?php print $script_url; ?>"></script>
<div id="tableau-<?php print $id; ?>" class="tableauPlaceholder" style="width:<?php print $width; ?>; height:<?php print $height; ?>;">
  <object class="tableauViz" width="<?php print $width; ?>" height="<?php print $height; ?>" style="display:none;">
    <param name="host_url" value="<?php print urlencode($host_url); ?>" />
    <param name="site_root" value="<?php print urlencode($site); ?>" />
    <param name="name" value="<?php print urlencode($name); ?>" />
    <param name="tabs" value="<?php print $tabs; ?>" />
    <param name="toolbar" value="<?php print $toolbar; ?>" />
    <param name='static_image' value='<?php print urlencode($static_image); ?>' / >
    <param name='animate_transition' value='yes' />
    <param name='display_static_image' value='yes' />
    <param name='display_spinner' value='yes' />
    <param name='display_overlay' value='yes' />
    <param name='display_count' value='yes' />
    <?php if (isset($render)): ?><param name='render' value='<?php print $render; ?>' /><?php endif; ?>
  </object>
</div>

