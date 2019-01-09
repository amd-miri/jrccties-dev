<?php
// if there's a {{ sitename }}.conf.d folder settings, use it so :
/**
 * Eg :
 * /var/www/site_01 -> webroot
 * /var/www/site_01.conf.d/settings.php
 * /var/www/site_01.conf.d/settings.post.php
 */
$strippedRoot = rtrim(DRUPAL_ROOT,'/');

if(file_exists($strippedRoot.'.conf.d/settings.php')) {
    // This file was dropped for us by config management :
    // @See : https://github.com/ec-europa/salt-reference/blob/master/sites/drupal7/settings.php.jinja
    putenv('DRUPAL_LOCAL_SETTINGS_LOCATION='.$strippedRoot.'.conf.d/settings.php');
    if(!defined("FPFIS_SALT_CONFIG_USED"))
        define('FPFIS_SALT_CONFIG_USED', true);
} else {
    // Old behavior :
    if (!getenv("DRUPAL_LOCAL_SETTINGS_LOCATION")){
      putenv('DRUPAL_LOCAL_SETTINGS_LOCATION=' . $strippedRoot . '/../settings.common.php');
    }
    if(!defined("FPFIS_SALT_CONFIG_USED"))
      define('FPFIS_SALT_CONFIG_USED', false);
}
if(!defined("FPFIS_ENV_RUNNING"))
  define('FPFIS_ENV_RUNNING', strlen(getenv('FPFIS_ENVIRONMENT')) > 0);

/**
 * FPFIS easy conf for CI and dev
 */
if(preg_match('/ci.fpfis.tech.ec.europa.eu$/',$_SERVER['HTTP_HOST'])) {
  global $base_url;
  $base_url = 'https://'.$_SERVER['HTTP_HOST'];
  putenv('FPFIS_ENVIRONMENT=ci');
} elseif (preg_match('/web$/',$_SERVER['HTTP_HOST']) || preg_match('/localhost$/',$_SERVER['HTTP_HOST'])) {
  global $base_url;
  $base_url = 'http://'.$_SERVER['HTTP_HOST'].':'.$_SERVER['SERVER_PORT'];
  putenv('FPFIS_ENVIRONMENT=dev');
}
