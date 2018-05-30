<?php
/**
 * @file
 * Template file for fblikebutton.
 *
 * The variable of primary importance is $src. This is generated and sanitized
 * the preprocess function. As facebook's services change frequently you can
 * override these settings without altering this module by overriding the
 * preprocess function in your theme's template.php file. The overriding
 * preprocessor should be a function named MYTHEME_preprocess_fblikebutton. You
 * can also override the output of this file by copying it into your own theme
 * directory. For maintainability you should not alter this file on your site as
 * it will lead to complications when updating the module later.
 *
 */
?>

<iframe src="//www.facebook.com/plugins/like.php?<?php print $src; ?>" scrolling="no" frameborder="0" style="border: none; overflow: hidden; width: <?php print $width; ?>px; height: <?php print $height; ?>px; <?php $other_css; ?>" allowTransparency="true"></iframe>
