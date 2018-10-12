<?php

/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 * In a multisite set up, these variables should be set for the
 * tpl to be used/
 * $conf['install_profile'] = 'multisite_drupal_XXX';
 * $conf['maintenance_theme'] = 'ec_resp';
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see ec_resp_process_maintenance_page()
 */
?>
<!DOCTYPE html>
<html lang="<?php print (isset($language) ? $language->language : "") ?>">
<head>
  <meta http-equiv="X-UA-Compatible" content="IE=edge" />
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>

  <div id="layout-header">
    <div class="container">
      <img alt="European Commission logo" id="banner-flag" src="<?php print $logo; ?>" />

      <div id="main-title">Site Offline</div>
      <div id="sub-title"></div>
    </div>
  </div><!-- /#layout-header -->

  <div class="panel panel-default">
    <div class="container">
      <div class="page-header">
        <?php if ($title): ?>
          <h1>The website is currently under maintenance</h1>
        <?php endif; ?>
      </div>

      <div class="jumbotron">
        <p>We should be back shortly. Thank you for your patience.</p>
      </div>
    </div>
  </div>

</body>
</html>
