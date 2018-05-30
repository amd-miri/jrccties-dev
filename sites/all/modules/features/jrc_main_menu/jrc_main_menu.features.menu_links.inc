<?php
/**
 * @file
 * jrc_main_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function jrc_main_menu_menu_default_menu_links() {
  $menu_links = array();
  
  // 1.Exported menu link: jrc-main-menu_home:<front>.
  $menu_links['jrc-main-menu_home:<front>'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'identifier' => 'jrc-main-menu_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
  );
  // 2.Exported menu link: jrc-main-menu_about-us:node/105.
  $menu_links['jrc-main-menu_about-us:<front>'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About us',
    'options' => array(
      'identifier' => 'jrc-main-menu_about-us:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
  );
  // 3.Exported menu link: jrc-main-menu_jrc-in-brief:node/360.
  $menu_links['jrc-main-menu_jrc-in-brief:about'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about'),
    'router_path' => 'about',
    'link_title' => 'JRC in brief',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC in brief',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-in-brief:about',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_about-us:<front>',
  );
  // 4.Exported menu link: jrc-main-menu_contact-the-jrc:node/28005.
  $menu_links['jrc-main-menu_contact-the-jrc:contact'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('contact'),
    'router_path' => 'contact',
    'link_title' => 'Contact the JRC',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Contact the JRC',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact-the-jrc:contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_about-us:<front>',
  );
  // 5.Exported menu link: jrc-main-menu_contact-form:node/9911.
  $menu_links['jrc-main-menu_contact-form:contact/form'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('contact/form'),
    'router_path' => 'contact/form',
    'link_title' => 'Contact form',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Contact form',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact-form:contact/form',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_contact-the-jrc:'.drupal_get_normal_path('contact'),
  );
  // 6.Exported menu link: jrc-main-menu_media-contacts:node/369.
  $menu_links['jrc-main-menu_media-contacts:contact-press-media'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('contact/press-media'),
	'router_path' => 'contact/%',
    'link_title' => 'Media contacts',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Media contacts',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_media-contacts:contact-press-media',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_contact-the-jrc:'.drupal_get_normal_path('contact'),
  );
  // 7.Exported menu link: jrc-main-menu_institutes-and-directorates:node/27998.
   $menu_links['jrc-main-menu_institutes-and-directorates:about/institutes-and-directorates'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/institutes-and-directorates'),
    'router_path' => 'about/institutes-and-directorates',
    'link_title' => 'Institutes and Directorates',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'JRC Institutes and Directorates',
      ),
      'identifier' => 'jrc-main-menu_institutes-and-directorates:about/institutes-and-directorates',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_about-us:<front>',
  );
  // 8.Exported menu link: jrc-main-menu_jrc-ies:node/28014.
  $menu_links['jrc-main-menu_jrc-ies:about/ies'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ies'),
    'router_path' => 'about/ies',
    'link_title' => 'JRC-IES',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Environment and Sustainability (JRC-IES)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ies:about/ies',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 9.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/ies/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ies/what-we-do'),
    'router_path' => 'about/ies/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IES activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/ies/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ies:'.drupal_get_normal_path('about/ies'),
  );
  // 10.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/ies/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ies/organisation'),
    'router_path' => 'about/ies/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IES organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/ies/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ies:'.drupal_get_normal_path('about/ies'),
  );
  // 11.Exported menu link: jrc-main-menu_jrc-iet:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/iet'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/iet'),
    'router_path' => 'about/iet',
    'link_title' => 'JRC-IET',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-IET)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-iet:about/iet',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 12.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/iet/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/iet/what-we-do'),
    'router_path' => 'about/iet/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IET activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/ies/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-iet:'.drupal_get_normal_path('about/iet'),
  );
  // 13.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/iet/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/iet/organisation'),
    'router_path' => 'about/iet/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IET organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/iet/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-iet:'.drupal_get_normal_path('about/iet'),
  );
  // 14.Exported menu link: jrc-main-menu_history:node/29628.
  $menu_links['jrc-main-menu_history:about/iet/history'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/iet/history'),
    'router_path' => 'about/iet/history',
    'link_title' => 'History',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'History of JRC-IET',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_history:about/iet/history',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-iet:'.drupal_get_normal_path('about/iet'),
  );
  // 15.Exported menu link: jrc-main-menu_jrc-ihcp:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/ihcp'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ihcp'),
    'router_path' => 'about/ihcp',
    'link_title' => 'JRC-IHCP',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-IHCP)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ihcp:about/ihcp',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 16.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/ihcp/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ihcp/what-we-do'),
    'router_path' => 'about/ihcp/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IHCP activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/ihcp/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ihcp:'.drupal_get_normal_path('about/ihcp'),
  );
  // 17.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/ihcp/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ihcp/organisation'),
    'router_path' => 'about/ihcp/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IHCP organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/ihcp/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ihcp:'.drupal_get_normal_path('about/ihcp'),
  );
  // 18.Exported menu link: jrc-main-menu_jrc-ihcp:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/ipsc'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipsc'),
    'router_path' => 'about/ipsc',
    'link_title' => 'JRC-IPSC',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-IPSC)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ipsc:about/ipsc',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 19.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/ipsc/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipsc/what-we-do'),
    'router_path' => 'about/ipsc/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPSC activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/ipsc/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipsc:'.drupal_get_normal_path('about/ipsc'),
  );
  // 20.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/ipsc/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipsc/organisation'),
    'router_path' => 'about/ipsc/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPSC organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/ipsc/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipsc:'.drupal_get_normal_path('about/ipsc'),
  );
  // 21.Exported menu link: jrc-main-menu_quality-management-system:node/33465.
  $menu_links['jrc-main-menu_quality-management-system:about/ipsc/quality-management'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipsc/quality-management'),
    'router_path' => 'about/ipsc/quality-management',
    'link_title' => 'Quality management system',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_quality-management-system:about/ipsc/quality-management',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipsc:'.drupal_get_normal_path('about/ipsc/quality-management'),
  );
    // 22.Exported menu link: jrc-main-menu_jrc-ihcp:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/ipts'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts'),
    'router_path' => 'about/ipts',
    'link_title' => 'JRC-IPTS',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-IPTS)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ipts:about/ipts',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 23.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/ipts/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts/what-we-do'),
    'router_path' => 'about/ipts/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPTS activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/ipts/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:'.drupal_get_normal_path('about/ipts'),
  );
  // 24.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/ipts/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts/organisation'),
    'router_path' => 'about/ipts/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPTS organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/ipts/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:'.drupal_get_normal_path('about/ipts'),
  );
   // 25.Exported menu link: jrc-main-menu_scientific-units:node/28302.
  $menu_links['jrc-main-menu_scientific-units:about/ipts/organisation/scientific-units'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts/organisation/scientific-units'),
    'router_path' => 'about/ipts/organisation/scientific-units',
    'link_title' => 'Scientific Units',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_scientific-units:about/ipts/organisation/scientific-units',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_organisation:'.drupal_get_normal_path('about/ipts/organisation'),
  );
  // 26.Exported menu link: jrc-main-menu_collaboration:node/310.
  $menu_links['jrc-main-menu_collaboration:about/ipts/collaboration'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts/collaboration'),
    'router_path' => 'about/ipts/collaboration',
    'link_title' => 'Collaboration',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_collaboration:about/ipts/collaboration',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:'.drupal_get_normal_path('about/ipts'),
  );
  // 27.Exported menu link: jrc-main-menu_external-evaluation:node/9807.
  $menu_links['jrc-main-menu_external-evaluation:about/ipts/external-evaluation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ipts/external-evaluation'),
    'router_path' => 'about/ipts/external-evaluation',
    'link_title' => 'External evaluation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPTS External evaluation',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_external-evaluation:about/ipts/external-evaluation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:'.drupal_get_normal_path('about/ipts'),
  );
  // 28.Exported menu link: jrc-main-menu_jrc-ihcp:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/irmm'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/irmm'),
    'router_path' => 'about/irmm',
    'link_title' => 'JRC-IRMM',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-IRMM)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-irmm:about/irmm',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 29.Exported menu link: jrc-main-menu_more-about-irmm:node/28154.
  $menu_links['jrc-main-menu_more-about-irmm:about/irmm/more'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/irmm/more'),
    'router_path' => 'about/irmm/more',
    'link_title' => 'More about IRMM',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_more-about-irmm:about/irmm/more',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:'.drupal_get_normal_path('about/irmm'),
  );
  // 30.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/irmm/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/irmm/what-we-do'),
    'router_path' => 'about/irmm/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IRMM activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/irmm/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:'.drupal_get_normal_path('about/irmm'),
  );
  // 31.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/irmm/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/irmm/organisation'),
    'router_path' => 'about/irmm/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IRMM organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/irmm/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:'.drupal_get_normal_path('about/irmm'),
  );
  // 32.Exported menu link: jrc-main-menu_quality-assurance:node/2882.
  $menu_links['jrc-main-menu_quality-assurance:about/irmm/quality-assurance'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/irmm/quality-assurance',
    'router_path' => 'about/irmm/quality-assurance',
    'link_title' => 'Quality assurance',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_quality-assurance:about/irmm/quality-assurance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:'.drupal_get_normal_path('about/irmm'),
  );
   // 33.Exported menu link: jrc-main-menu_work-at-jrc-irmm:node/28131.
  $menu_links['jrc-main-menu_work-at-jrc-irmm:about/irmm/work'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/irmm/work',
    'router_path' => 'about/irmm/work',
    'link_title' => 'Work at JRC-IRMM',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_work-at-jrc-irmm:about/irmm/work',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:about/irmm/work',
  );
  // 34.Exported menu link: jrc-main-menu_jrc-ihcp:node/28013.
  $menu_links['jrc-main-menu_jrc-iet:about/itu'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu'),
    'router_path' => 'about/itu',
    'link_title' => 'JRC-ITU',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Energy and Transport (JRC-ITU)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-itu:about/itu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 35.Exported menu link: jrc-main-menu_what-we-do:node/28169.
  $menu_links['jrc-main-menu_what-we-do:about/itu/what-we-do'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu/what-we-do'),
    'router_path' => 'about/itu/what-we-do',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-ITU activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:about/itu/what-we-do',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:'.drupal_get_normal_path('about/itu'),
  );
  // 36.Exported menu link: jrc-main-menu_organisation:node/28336.
  $menu_links['jrc-main-menu_organisation:about/itu/organisation'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu/organisation'),
    'router_path' => 'about/itu/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-ITU organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:about/itu/organisation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:'.drupal_get_normal_path('about/itu'),
  );
  // 37.Exported menu link: jrc-main-menu_galleries--videos:node/28194.
  $menu_links['jrc-main-menu_galleries--videos:about/itu/galleries-videos'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu/galleries-videos'),
    'router_path' => 'about/itu/galleries-videos',
    'link_title' => 'Galleries & Videos',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_galleries--videos:about/itu/galleries-videos',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 7,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:'.drupal_get_normal_path('about/itu'),
  );
  // 38.Exported menu link: jrc-main-menu_collaboration:node/451.
  $menu_links['jrc-main-menu_collaboration:about/itu/collaboration'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu/collaboration'),
    'router_path' => 'about/itu/collaboration',
    'link_title' => 'Collaboration',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_collaboration:about/itu/collaboration',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:'.drupal_get_normal_path('about/itu'),
  );
  // 39.Exported menu link: jrc-main-menu_integrated-management-system:node/2893.
  $menu_links['jrc-main-menu_integrated-management-system:about/itu/integrated-management-system'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/itu/integrated-management-system'),
    'router_path' => 'about/itu/integrated-management-system',
    'link_title' => 'Integrated Management System',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_integrated-management-system:about/itu/integrated-management-system',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 20,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:'.drupal_get_normal_path('about/itu'),
  );
  // 40.Exported menu link: jrc-main-menu_ispra-site-management:node/3248.
  $menu_links['jrc-main-menu_ispra-site-management:about/ispra-site-management'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ispra-site-management'),
    'router_path' => 'about/ispra-site-management',
    'link_title' => 'Ispra site management',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_ispra-site-management:about/ispra-site-management',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:'.drupal_get_normal_path('about/institutes-and-directorates'),
  );
  // 41.Exported menu link: jrc-main-menu_key-services:node/6062.
  $menu_links['jrc-main-menu_key-services:about/ispra-site-management/key-services'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/ispra-site-management/key-services'),
    'router_path' => 'about/ispra-site-management/key-services',
    'link_title' => 'Key services',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_key-services:about/ispra-site-management/key-services',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_ispra-site-management:'.drupal_get_normal_path('about/ispra-site-management'),
  );
  // 42.Exported menu link: jrc-main-menu_jrc-sites:node/365.
  $menu_links['jrc-main-menu_jrc-sites:about/jrc-sites'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-sites'),
    'router_path' => 'about/jrc-sites',
    'link_title' => 'JRC sites',
    'options' => array(
      'attributes' => array(
        'title' => 'The JRC sites in Europe',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-sites:about/jrc-sites',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_about-us:'.drupal_get_normal_path('about'),
  );
  // 43.Exported menu link: jrc-main-menu_jrc-visitors-centre:node/33349.
  $menu_links['jrc-main-menu_jrc-visitors-centre:about/jrc-sites/visitors-centre'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-sites/visitors-centre'),
    'router_path' => 'about/jrc-sites/visitors-centre',
    'link_title' => 'JRC Visitors\' Centre',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Visit us',
      ),
      'identifier' => 'jrc-main-menu_jrc-visitors-centre:about/jrc-sites/visitors-centre',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -11,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-sites'),
  );
  // 44.Exported menu link: jrc-main-menu_teacher-and-schools-corner:node/35300.
  $menu_links['jrc-main-menu_teacher-and-schools-corner:about/jrc-sites/visitors-centre/schools'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-sites/visitors-centre/schools'),
    'router_path' => 'about/jrc-sites/visitors-centre/schools',
    'link_title' => 'Teacher and schools corner',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_teacher-and-schools-corner:about/jrc-sites/visitors-centre/schools',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-visitors-centre:'.drupal_get_normal_path('about/jrc-sites/visitors-centre'),
  );
  // 45.Exported menu link: jrc-main-menu_brussels:node/3158.
  $menu_links['jrc-main-menu_brussels:about/jrc-site/brussels'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/brussels'),
    'router_path' => 'about/jrc-site/brussels',
    'link_title' => 'Brussels',
    'options' => array(
      'attributes' => array(
        'title' => 'The JRC in Brussels (Belgium)',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_brussels:about/jrc-site/brussels',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 46.Exported menu link: jrc-main-menu_geel:node/28009.
  $menu_links['jrc-main-menu_geel:about/jrc-site/geel'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/geel'),
    'router_path' => 'about/jrc-site/geel',
    'link_title' => 'Geel',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'The JRC in Geel (Belgium)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_geel:about/jrc-site/geel',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 47.Exported menu link: jrc-main-menu_directions:node/28132.
  $menu_links['jrc-main-menu_directions:about/jrc-site/geel/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/geel/directions'),
    'router_path' => 'about/jrc-site/geel/directions',
    'link_title' => 'Directions',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'How to get to the JRC-Geel site',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_directions:about/jrc-site/geel/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_geel:'.drupal_get_normal_path('about/jrc-site/geel'),
  );
  // 48.Exported menu link: jrc-main-menu_life-in-geel:node/28130.
  $menu_links['jrc-main-menu_life-in-geel:about/jrc-site/geel/life'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/geel/life'),
    'router_path' => 'about/jrc-site/geel/life',
    'link_title' => 'Life in Geel',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_life-in-geel:about/jrc-site/geel/life',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_geel:'.drupal_get_normal_path('about/jrc-site/geel'),
  );
  // 49.Exported menu link: jrc-main-menu_ispra:node/3244.
  $menu_links['jrc-main-menu_ispra:about/jrc-site/ispra'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/ispra'),
    'router_path' => 'about/jrc-site/ispra',
    'link_title' => 'Ispra',
    'options' => array(
      'attributes' => array(
        'title' => 'The JRC in Ispra (Italy)',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_ispra:about/jrc-site/ispra',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 50.Exported menu link: jrc-main-menu_directions:node/3245.
  $menu_links['jrc-main-menu_directions:about/jrc-site/ispra/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/ispra/directions'),
    'router_path' => 'about/jrc-site/ispra/directions',
    'link_title' => 'Directions',
    'options' => array(
      'attributes' => array(
        'title' => 'How to get to JRC-Ispra',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_directions:about/jrc-site/ispra/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_ispra:'.drupal_get_normal_path('about/jrc-site/ispra'),
  );
  // 51.Exported menu link: jrc-main-menu_life-in-ispra:node/3246.
  $menu_links['jrc-main-menu_life-in-ispra:about/jrc-site/ispra/life'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/ispra/life'),
    'router_path' => 'about/jrc-site/ispra/life',
    'link_title' => 'Life in Ispra',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_life-in-ispra:about/jrc-site/ispra/life',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_ispra:'.drupal_get_normal_path('about/jrc-site/ispra'),
  );
  // 52.Exported menu link: jrc-main-menu_karlsruhe:node/28011.
  $menu_links['jrc-main-menu_karlsruhe:about/jrc-site/karlsruhe'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/karlsruhe'),
    'router_path' => 'about/jrc-site/karlsruhe',
    'link_title' => 'Karlsruhe',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'The JRC in Karlsruhe (Germany)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_karlsruhe:about/jrc-site/karlsruhe',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 53.Exported menu link: jrc-main-menu_how-to-get-to-jrc-karlsruhe:node/28139.
  $menu_links['jrc-main-menu_how-to-get-to-jrc-karlsruhe:about/jrc-site/karlsruhe/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/karlsruhe/directions'),
    'router_path' => 'about/jrc-site/karlsruhe/directions',
    'link_title' => 'How to get to JRC-Karlsruhe',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'How to get to the JRC-Karlsruhe site',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_how-to-get-to-jrc-karlsruhe:about/jrc-site/karlsruhe/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_karlsruhe:'.drupal_get_normal_path('about/jrc-site/karlsruhe'),
  );
  // 54.Exported menu link: jrc-main-menu_newcomer-information:node/30471.
  $menu_links['jrc-main-menu_newcomer-information:jrc-site/karlsruhe/newcomer-information'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('jrc-site/karlsruhe/newcomer-information'),
    'router_path' => 'jrc-site/karlsruhe/newcomer-information',
    'link_title' => 'Newcomer Information',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_newcomer-information:jrc-site/karlsruhe/newcomer-information',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_karlsruhe:'.drupal_get_normal_path('jrc-site/karlsruhe'),
  );
  // 55.Exported menu link: jrc-main-menu_petten:node/28010.
  $menu_links['jrc-main-menu_petten:about/jrc-site/petten'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/petten'),
    'router_path' => 'about/jrc-site/petten',
    'link_title' => 'Petten',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'The JRC in Petten (the Netherlands)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_petten:about/jrc-site/petten',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 56.Exported menu link: jrc-main-menu_directions:node/29613.
  $menu_links['jrc-main-menu_directions:about/jrc-site/petten/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/petten/directions'),
    'router_path' => 'about/jrc-site/petten/directions',
    'link_title' => 'Directions',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'How to get to the JRC-Petten site',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_directions:about/jrc-site/petten/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_petten:'.drupal_get_normal_path('about/jrc-site/petten'),
  );
  // 57.Exported menu link: jrc-main-menu_seville:node/28012.
  $menu_links['jrc-main-menu_seville:about/jrc-site/seville'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/seville'),
    'router_path' => 'about/jrc-site/seville',
    'link_title' => 'Seville',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'The JRC in Seville (Spain)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_seville:about/jrc-site/seville',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-sites:'.drupal_get_normal_path('about/jrc-site'),
  );
  // 58.Exported menu link: jrc-main-menu_directions:node/28135.
  $menu_links['jrc-main-menu_directions:about/jrc-site/seville/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/seville/directions'),
    'router_path' => 'about/jrc-site/seville/directions',
    'link_title' => 'Directions',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'How to get to the JRC-Seville site',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_directions:about/jrc-site/seville/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_seville:'.drupal_get_normal_path('about/jrc-site/seville'),
  );
  // 59.Exported menu link: jrc-main-menu_life-in-seville:node/28136.
  $menu_links['jrc-main-menu_life-in-seville:about/jrc-site/seville/directions'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => drupal_get_normal_path('about/jrc-site/seville/directions'),
    'router_path' => 'about/jrc-site/seville/directions',
    'link_title' => 'Life in Seville',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_life-in-seville:about/jrc-site/seville/directions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_seville:'.drupal_get_normal_path('about/jrc-site/seville'),
  );
  // 60.Exported menu link: jrc-main-menu_resources:node/366.
  $menu_links['jrc-main-menu_resources:about/resources'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/resources',
    'router_path' => 'about/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_resources:about/resources',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_about-us:about',
  );
  // 61.Exported menu link: jrc-main-menu_people:people.
  $menu_links['jrc-main-menu_people:people'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'people',
    'router_path' => 'people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'People',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_people:people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_about-us:about',
  );
  // 62.Exported menu link: jrc-main-menu_commissioner:node/2951.
  $menu_links['jrc-main-menu_commissioner:about/people/commissioner'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/people/commissioner',
    'router_path' => 'about/people/commissioner',
    'link_title' => 'Commissioner',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_commissioner:about/people/commissioner',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_people:about/people',
  );
  // 63.Exported menu link: jrc-main-menu_board-of-governors:node/3240.
  $menu_links['jrc-main-menu_board-of-governors:about/people/board-of-governors'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/people/board-of-governors',
    'router_path' => 'about/people/board-of-governors',
    'link_title' => 'Board of Governors',
    'options' => array(
      'attributes' => array(
        'title' => 'JRC\'s Board of Governors',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_board-of-governors:about/people/board-of-governors',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_people:about/people',
  );
  // 64.Exported menu link: jrc-main-menu_members:node/3241.
  $menu_links['jrc-main-menu_members:about/people/board-of-governors/members'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/people/board-of-governors/members',
    'router_path' => 'about/people/board-of-governors/members',
    'link_title' => 'Members',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_members:about/people/board-of-governors/members',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_board-of-governors:about/people/board-of-governors',
  );
  // 65.Exported menu link: jrc-main-menu_director-general:node/28243.
  $menu_links['jrc-main-menu_director-general:person/vladimír-šucha' = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'person/vladimír-šucha',
    'router_path' => 'person/vladimír-šucha',
    'link_title' => 'Director-General',
    'options' => array(
      'attributes' => array(
        'title' => 'JRC Director-General',
      ),
      'alter' => TRUE,
      'node_type' => 'jrc_staff',
      'identifier' => 'jrc-main-menu_director-general:person/vladimír-šucha',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_people:about/people',
  );
  // 66.Exported menu link: jrc-main-menu_senior-management:node/3239.
  $menu_links['jrc-main-menu_senior-management:about/people/senior-management'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/people/senior-management',
    'router_path' => 'about/people/senior-management',
    'link_title' => 'Senior management',
    'options' => array(
      'attributes' => array(
        'title' => 'JRC senior management',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_senior-management:about/people/senior-management',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_people:about/people',
  );
  // 67.Exported menu link: jrc-main-menu_what-is-the-science-hub:node/28127.
  $menu_links['jrc-main-menu_what-is-the-science-hub:about/science-hub'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'about/science-hub',
    'router_path' => 'about/science-hub',
    'link_title' => 'What is the Science Hub',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-is-the-science-hub:about/science-hub',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_about-us:about',
  );
  // 68.Exported menu link: jrc-main-menu_home:<front>.
  $menu_links['jrc-main-menu_research:<front>'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Research',
    'options' => array(
      'identifier' => 'jrc-main-menu_research:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 0,
  );
  // 69.Exported menu link: jrc-main-menu_science-areas:node/259.
  $menu_links['jrc-main-menu_science-areas:science-areas'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-areas',
    'router_path' => 'science-areas',
    'link_title' => 'Science areas',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_science-areas:science-areas',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_research:<front>',
  );
  // 70.Exported menu link: jrc-main-menu_agriculture-and-food-security:node/9.
  $menu_links['jrc-main-menu_agriculture-and-food-security:science-area/agriculture-and-food-security'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/agriculture-and-food-security',
    'router_path' => 'science-area/agriculture-and-food-security',
    'link_title' => 'Agriculture and food security',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_agriculture-and-food-security:science-area/agriculture-and-food-security',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 71.Exported menu link: jrc-main-menu_economic-and-monetary-union:node/10215.
  $menu_links['jrc-main-menu_economic-and-monetary-union:science-area/economic-and-monetary-union'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/economic-and-monetary-union',
    'router_path' => 'science-area/economic-and-monetary-union',
    'link_title' => 'Economic and Monetary Union',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_economic-and-monetary-union:science-area/economic-and-monetary-union',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area/economic-and-monetary-union',
  );
  // 72.Exported menu link: jrc-main-menu_energy-and-transport:node/17.
  $menu_links['jrc-main-menu_energy-and-transport:science-area/economic-and-monetary-union'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/economic-and-monetary-union',
    'router_path' => 'science-area/economic-and-monetary-union',
    'link_title' => 'Energy and transport',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_energy-and-transport:science-area/economic-and-monetary-union',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 73.Exported menu link: jrc-main-menu_environment-and-climate-change:node/244.
  $menu_links['jrc-main-menu_environment-and-climate-change:science-area/environment-and-climate-change'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/environment-and-climate-change',
    'router_path' => 'science-area/environment-and-climate-change',
    'link_title' => 'Environment and climate change',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_environment-and-climate-change:science-area/environment-and-climate-change',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 74.Exported menu link: jrc-main-menu_health-and-consumer-protection:node/245.
  $menu_links['jrc-main-menu_health-and-consumer-protection:science-area/health-and-consumer-protection'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/health-and-consumer-protection',
    'router_path' => 'science-area/health-and-consumer-protection',
    'link_title' => 'Health and consumer protection',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_health-and-consumer-protection:science-area/health-and-consumer-protection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 75.Exported menu link: jrc-main-menu_information-society:node/246.
  $menu_links['jrc-main-menu_information-society:science-area/information-society'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/information-society',
    'router_path' => 'science-area/information-society',
    'link_title' => 'Information Society',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_information-society:science-area/information-society',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area/information-society',
  );
  // 76.Exported menu link: jrc-main-menu_innovation-and-growth:node/247.
  $menu_links['jrc-main-menu_innovation-and-growth:science-area/innovation-and-growth'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/innovation-and-growth',
    'router_path' => 'science-area/innovation-and-growth',
    'link_title' => 'Innovation and growth',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_innovation-and-growth:science-area/innovation-and-growth',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 77.Exported menu link: jrc-main-menu_nuclear-safety-and-security:node/249.
  $menu_links['jrc-main-menu_nuclear-safety-and-security:science-area/nuclear-safety-and-security'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/nuclear-safety-and-security',
    'router_path' => 'science-area/nuclear-safety-and-security',
    'link_title' => 'Nuclear safety and security',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_nuclear-safety-and-security:science-area/nuclear-safety-and-security',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 78.Exported menu link: jrc-main-menu_safety-and-security:node/250.
  $menu_links['jrc-main-menu_safety-and-security:science-area/safety-and-security'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/safety-and-security',
    'router_path' => 'science-area/safety-and-security',
    'link_title' => 'Safety and Security',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_safety-and-security:science-area/safety-and-security',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 79.Exported menu link: jrc-main-menu_standards:node/248.
  $menu_links['jrc-main-menu_standards:science-area/standards'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'science-area/standards',
    'router_path' => 'science-area/standards',
    'link_title' => 'Standards',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_standards:science-area/standards',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:science-area',
  );
  // 80.Exported menu link: jrc-main-menu_jrc-research-topics:research-topics.
  $menu_links['jrc-main-menu_jrc-research-topics:research-topics'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research-topics',
    'router_path' => 'research-topics',
    'link_title' => 'JRC research topics',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_jrc-research-topics:research-topics',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_research:<front>',
  );
  // 81.Exported menu link: jrc-main-menu_laboratories--facilities:research-facilities.
  $menu_links['jrc-main-menu_laboratories--facilities:research-facilities'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research-facilities',
    'router_path' => 'research-facilities',
    'link_title' => 'Laboratories & facilities',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_laboratories--facilities:research-facilities',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_research:<front>',
  );
  // 82.Exported menu link: jrc-main-menu_crosscutting-activities:node/376.
  $menu_links['jrc-main-menu_crosscutting-activities:research/crosscutting-activities'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities',
    'router_path' => 'research/crosscutting-activities',
    'link_title' => 'Crosscutting activities',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_research:research',
  );
  // 83.Exported menu link: jrc-main-menu_behavioural-insights:node/33382.
  $menu_links['jrc-main-menu_behavioural-insights:research/crosscutting-activities/behavioural-insights'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/behavioural-insights',
    'router_path' => 'research/crosscutting-activities/behavioural-insights',
    'link_title' => 'Behavioural Insights',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_behavioural-insights:research/crosscutting-activities/behavioural-insights',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
  );
  // 84.Exported menu link: jrc-main-menu_application-in-the-commission:node/33383.
  $menu_links['jrc-main-menu_application-in-the-commission:research/crosscutting-activities/behavioural-insights/commission'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/behavioural-insights/commission',
    'router_path' => 'research/crosscutting-activities/behavioural-insights/commission',
    'link_title' => 'Application in the Commission',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Application in the Commission',
      ),
      'identifier' => 'jrc-main-menu_application-in-the-commission:research/crosscutting-activities/behavioural-insights/commission',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_behavioural-insights:research/crosscutting-activities/behavioural-insights',
  );
  // 85.Exported menu link: jrc-main-menu_publications:node/28459.
  $menu_links['jrc-main-menu_publications:node/28459'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/behavioural-insights/publications',
    'router_path' => 'research/crosscutting-activities/behavioural-insights/publications',
    'link_title' => 'Publications',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_publications:research/crosscutting-activities/behavioural-insights/publications',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:research/crosscutting-activities/behavioural-insights',
  );
  // 86.Exported menu link: jrc-main-menu_foresight--horizon-scanning:node/6085.
  $menu_links['jrc-main-menu_foresight--horizon-scanning:research/crosscutting-activities/foresight'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/foresight',
    'router_path' => 'research/crosscutting-activities/foresight',
    'link_title' => 'Foresight & horizon scanning',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_foresight--horizon-scanning:research/crosscutting-activities/foresight',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
  );
  // 87.Exported menu link: jrc-main-menu_industrial-landscape-vision-2025:node/30470.
  $menu_links['jrc-main-menu_industrial-landscape-vision-2025:research/foresight/ilv2025'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/foresight/ilv2025',
    'router_path' => 'research/foresight/ilv2025',
    'link_title' => 'Industrial Landscape Vision 2025',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_industrial-landscape-vision-2025:research/foresight/ilv2025',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_foresight--horizon-scanning:research/foresight',
  );
  // 88.Exported menu link: jrc-main-menu_industrial-landscape-vision-2025:node/30470.
  $menu_links['jrc-main-menu_industrial-landscape-vision-2025:research/foresight/ses'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/foresight/ses',
    'router_path' => 'research/foresight/ses',
    'link_title' => 'Scenario Exploration System (SES)',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_industrial-landscape-vision-2025:research/foresight/ses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_foresight--horizon-scanning:research/foresight',
  );
  // 89.Exported menu link: jrc-main-menu_publications:publications-list/.
  $menu_links['jrc-main-menu_publications:publications-list/?f[0]=im_field_identities%3A575'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'publications-list/?f[0]=im_field_identities%3A575',
    'router_path' => 'publications-list/%',
    'link_title' => 'Publications',
    'options' => array(
      'query' => array(
        'f[0]' => 'im_field_identities:575',
      ),
      'attributes' => array(
        'title' => 'Foresight and horizon scanning publications',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_publications:publications-list/?f[0]=im_field_identities%3A575',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 11,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_foresight--horizon-scanning:research/foresight',
  );
  // 90.Exported menu link: jrc-main-menu_impact-assessment:node/371.
  $menu_links['jrc-main-menu_impact-assessment:research/crosscutting-activities/impact-assessment'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/impact-assessment',
    'router_path' => 'research/crosscutting-activities/impact-assessment',
    'link_title' => 'Impact assessment',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_impact-assessment:research/crosscutting-activities/impact-assessment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
  );
  // 91.Exported menu link: jrc-main-menu_impact-assessment:node/371.
  $menu_links['jrc-main-menu_impact-assessment:research/crosscutting-activities/impact-assessment'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/impact-assessment',
    'router_path' => 'research/crosscutting-activities/impact-assessment',
    'link_title' => 'Impact assessment',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_impact-assessment:research/crosscutting-activities/impact-assessment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
  );
  // 92.Exported menu link: jrc-main-menu_impact-assessment:node/371.
  $menu_links['jrc-main-menu_impact-assessment:research/crosscutting-activities/intellectual-property'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/intellectual-property',
    'router_path' => 'research/crosscutting-activities/intellectual-property',
    'link_title' => 'Intellectual property & technology transfer',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_impact-assessment:research/crosscutting-activities/intellectual-property',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activities:research/crosscutting-activities',
  );
  // 93.Exported menu link: jrc-main-menu_central-ip-service:node/413.
  $menu_links['jrc-main-menu_central-ip-service:research/crosscutting-activities/intellectual-property/central-ip-service'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/intellectual-property/central-ip-service',
    'router_path' => 'research/crosscutting-activities/intellectual-property/central-ip-service',
    'link_title' => 'Central IP service',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_central-ip-service:research/crosscutting-activities/intellectual-property/central-ip-service',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_intellectual-property--technology-transfer:research/crosscutting-activities/intellectual-property',
  );
  // 94.Exported menu link: jrc-main-menu_technology-transfer:node/414.
  $menu_links['jrc-main-menu_technology-transfer:research/crosscutting-activities/intellectual-property/technology-transfer'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/intellectual-property/technology-transfer',
    'router_path' => 'research/crosscutting-activities/intellectual-property/technology-transfer',
    'link_title' => 'Technology transfer',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_technology-transfer:research/crosscutting-activities/intellectual-property/technology-transfer',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_intellectual-property--technology-transfer:research/crosscutting-activities/intellectual-property',
  );
  // 95.Exported menu link: jrc-main-menu_licensing-policy:node/30055.
  $menu_links['jrc-main-menu_licensing-policy:research/crosscutting-activities/intellectual-property/licensing-policy'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/intellectual-property/licensing-policy',
    'router_path' => 'research/crosscutting-activities/intellectual-property/licensing-policy',
    'link_title' => 'Licensing policy',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_licensing-policy:research/crosscutting-activities/intellectual-property/licensing-policy',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_intellectual-property--technology-transfer:research/crosscutting-activities/intellectual-property',
  );
  // 96.Exported menu link: jrc-main-menu_scientific-support-to-danube-strategy:node/29731.
  $menu_links['jrc-main-menu_scientific-support-to-danube-strategy:research/crosscutting-activities/danube-strategy'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/danube-strategy',
    'router_path' => 'research/crosscutting-activities/danube-strategy',
    'link_title' => 'Scientific support to Danube strategy',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_scientific-support-to-danube-strategy:research/crosscutting-activities/danube-strategy',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_crosscutting-activitiesresearch/crosscutting-activities',
  );
  // 97.Exported menu link: jrc-main-menu_innovation-partnership:node/30284.
  $menu_links['jrc-main-menu_innovation-partnership:research/crosscutting-activities/danube-strategy/innovation-partnership'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'research/crosscutting-activities/danube-strategy/innovation-partnership',
    'router_path' => 'research/crosscutting-activities/danube-strategy/innovation-partnership',
    'link_title' => 'Innovation Partnership',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Danube Innovation Partnership (DIP)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_innovation-partnership:research/crosscutting-activities/danube-strategy/innovation-partnership',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_scientific-support-to-danube-strategy:research/crosscutting-activities/danube-strategy',
  );
   // 98.Exported menu link: jrc-main-menu_home:<front>.
  $menu_links['jrc-main-menu_knowledge:<front>'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Knowledge',
    'options' => array(
      'identifier' => 'jrc-main-menu_knowledge:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 0,
  );
  // 99.Exported menu link: jrc-main-menu_reference--measurement:node/398.
  $menu_links['jrc-main-menu_reference--measurement:knowledge/reference-measurement'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'knowledge/reference-measurement',
    'router_path' => 'knowledge/reference-measurement',
    'link_title' => 'Reference & measurement',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_reference--measurement:knowledge/reference-measurement',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:<front>',
  );
  // 100.Exported menu link: jrc-main-menu_measurements-matter:node/28141.
  $menu_links['jrc-main-menu_measurements-matter:providing-reference/measurements-matter'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'providing-reference/measurements-matter',
    'router_path' => 'providing-reference/measurements-matter',
    'link_title' => 'Measurements matter',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Selected examples of areas where the JRC has expertise in measurements that matter to all of us.',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_reference--measurement:knowledge/reference-measurement',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference--measurement:providing-reference/measurements-matter',
  );
  
  
  
  // Exported menu link: jrc-main-menu_about-imep:node/6067.
  $menu_links['jrc-main-menu_about-imep:node/6067'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6067',
    'router_path' => 'node/%',
    'link_title' => 'About IMEP',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_about-imep:node/6067',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
  );
  // Exported menu link: jrc-main-menu_accreditation:node/439.
  $menu_links['jrc-main-menu_accreditation:node/439'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/439',
    'router_path' => 'node/%',
    'link_title' => 'Accreditation',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_accreditation:node/439',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_rm-development:node/438',
  );
  
  // Exported menu link: jrc-main-menu_alexander:node/3265.
  $menu_links['jrc-main-menu_alexander:node/3265'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3265',
    'router_path' => 'node/%',
    'link_title' => 'Alexander',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_alexander:node/3265',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -6,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_all-comparisons:interlaboratory-comparisons/list.
  $menu_links['jrc-main-menu_all-comparisons:interlaboratory-comparisons/list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'interlaboratory-comparisons/list',
    'router_path' => 'interlaboratory-comparisons/list',
    'link_title' => 'All comparisons',
    'options' => array(
      'attributes' => array(
        'title' => 'List all interlaboratory comparisons',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_all-comparisons:interlaboratory-comparisons/list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
  );
  
  // Exported menu link: jrc-main-menu_application-notes:reference-materials/application-notes.
  $menu_links['jrc-main-menu_application-notes:reference-materials/application-notes'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'reference-materials/application-notes',
    'router_path' => 'reference-materials/application-notes',
    'link_title' => 'Application notes',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_application-notes:reference-materials/application-notes',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_user-support:node/435',
  );
  // Exported menu link: jrc-main-menu_available-positions:node/464.
  $menu_links['jrc-main-menu_available-positions:node/464'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/464',
    'router_path' => 'node/%',
    'link_title' => 'Available Positions',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_available-positions:node/464',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:node/28018',
  );
  
  
  
  
  // Exported menu link: jrc-main-menu_call-for-collaborators:node/441.
  $menu_links['jrc-main-menu_call-for-collaborators:node/441'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/441',
    'router_path' => 'node/%',
    'link_title' => 'Call for collaborators',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_call-for-collaborators:node/441',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -35,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_rm-development:node/438',
  );
  // Exported menu link: jrc-main-menu_call-for-expressions-of-interest-researchers:node/31985.
  $menu_links['jrc-main-menu_call-for-expressions-of-interest-researchers:node/31985'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/31985',
    'router_path' => 'node/%',
    'link_title' => 'Call for expressions of interest: Researchers',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Function group IV - COM/1/2015/GFIV - Research',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_call-for-expressions-of-interest-researchers:node/31985',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_vacancies:node/31997',
  );
  // Exported menu link: jrc-main-menu_calls-for-tender:node/362.
  $menu_links['jrc-main-menu_calls-for-tender:node/362'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/362',
    'router_path' => 'node/%',
    'link_title' => 'Calls for tender',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_calls-for-tender:node/362',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  
  // Exported menu link: jrc-main-menu_certification--accreditation:node/6063.
  $menu_links['jrc-main-menu_certification--accreditation:node/6063'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6063',
    'router_path' => 'node/%',
    'link_title' => 'Certification & accreditation',
    'options' => array(
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_certification--accreditation:node/6063',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_ispra-site-management:node/3248',
  );
  // Exported menu link: jrc-main-menu_citizens-and-travellers:node/28145.
  $menu_links['jrc-main-menu_citizens-and-travellers:node/28145'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28145',
    'router_path' => 'node/%',
    'link_title' => 'Citizens and travellers',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_citizens-and-travellers:node/28145',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_measurements-matter:node/28141',
  );
  // Exported menu link: jrc-main-menu_collaboration-with-member-states:node/3253.
  $menu_links['jrc-main-menu_collaboration-with-member-states:node/3253'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3253',
    'router_path' => 'node/%',
    'link_title' => 'Collaboration with Member States',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_collaboration-with-member-states:node/3253',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );

  
  
  // Exported menu link: jrc-main-menu_competitive-activities:node/3252.
  $menu_links['jrc-main-menu_competitive-activities:node/3252'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3252',
    'router_path' => 'node/%',
    'link_title' => 'Competitive activities',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_competitive-activities:node/3252',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_resources:node/366',
  );
  // Exported menu link: jrc-main-menu_concepts:node/6068.
  $menu_links['jrc-main-menu_concepts:node/6068'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6068',
    'router_path' => 'node/%',
    'link_title' => 'Concepts',
    'options' => array(
      'attributes' => array(
        'title' => 'IMEP concepts',
      ),
      'alter' => TRUE,
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_concepts:node/6068',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
  );
  // Exported menu link: jrc-main-menu_consumers:node/28142.
  $menu_links['jrc-main-menu_consumers:node/28142'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28142',
    'router_path' => 'node/%',
    'link_title' => 'Consumers',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_consumers:node/28142',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_measurements-matter:node/28141',
  );
  // Exported menu link: jrc-main-menu_contact-form:node/9911.
  $menu_links['jrc-main-menu_contact-form:node/9911'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9911',
    'router_path' => 'node/%',
    'link_title' => 'Contact form',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_contact-form:node/9911',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_contact-the-jrc:node/28005',
  );
  // Exported menu link: jrc-main-menu_contact-the-jrc:node/28005.
  $menu_links['jrc-main-menu_contact-the-jrc:node/28005'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28005',
    'router_path' => 'node/%',
    'link_title' => 'Contact the JRC',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Contact the JRC',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact-the-jrc:node/28005',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_about-us:node/105',
  );
  // Exported menu link: jrc-main-menu_contact:node/6071.
  $menu_links['jrc-main-menu_contact:node/6071'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6071',
    'router_path' => 'node/%',
    'link_title' => 'Contact',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact:node/6071',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 16,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
  );
  // Exported menu link: jrc-main-menu_contact:node/6074.
  $menu_links['jrc-main-menu_contact:node/6074'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6074',
    'router_path' => 'node/%',
    'link_title' => 'Contact',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact:node/6074',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 8,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_nusimep:interlaboratory-comparisons/NUSIMEP',
  );
  // Exported menu link: jrc-main-menu_contact:node/6083.
  $menu_links['jrc-main-menu_contact:node/6083'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6083',
    'router_path' => 'node/%',
    'link_title' => 'Contact',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contact:node/6083',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reimep:interlaboratory-comparisons/REIMEP',
  );
  // Exported menu link: jrc-main-menu_contract-staff-members:node/3272.
  $menu_links['jrc-main-menu_contract-staff-members:node/3272'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3272',
    'router_path' => 'node/%',
    'link_title' => 'Contract staff members',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -5,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  // Exported menu link: jrc-main-menu_contracts-and-working-conditions:node/30483.
  $menu_links['jrc-main-menu_contracts-and-working-conditions:node/30483'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30483',
    'router_path' => 'node/%',
    'link_title' => 'Contracts and working conditions',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC Grantholder contracts and working conditions',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_contracts-and-working-conditions:node/30483',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_grantholders:node/3275',
  );
  // Exported menu link: jrc-main-menu_control-authorities:node/28144.
  $menu_links['jrc-main-menu_control-authorities:node/28144'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28144',
    'router_path' => 'node/%',
    'link_title' => 'Control authorities',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_control-authorities:node/28144',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_measurements-matter:node/28141',
  );
  // Exported menu link: jrc-main-menu_course-content:node/7736.
  $menu_links['jrc-main-menu_course-content:node/7736'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/7736',
    'router_path' => 'node/%',
    'link_title' => 'Course content',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_course-content:node/7736',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  
  // Exported menu link: jrc-main-menu_data-protection:node/3277.
  $menu_links['jrc-main-menu_data-protection:node/3277'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3277',
    'router_path' => 'node/%',
    'link_title' => 'Data protection',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_data-protection:node/3277',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  // Exported menu link: jrc-main-menu_development-of-gmo-rm:node/440.
  $menu_links['jrc-main-menu_development-of-gmo-rm:node/440'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/440',
    'router_path' => 'node/%',
    'link_title' => 'Development of GMO RM',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_development-of-gmo-rm:node/440',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -30,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_rm-development:node/438',
  );
  
  
  
  
  
  
  // Exported menu link: jrc-main-menu_eia-activities:node/3507.
  $menu_links['jrc-main-menu_eia-activities:node/3507'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3507',
    'router_path' => 'node/%',
    'link_title' => 'E&IA Activities',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eia-activities:node/3507',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_enlargement--integration:node/3256',
  );
  // Exported menu link: jrc-main-menu_eia-archives:node/3508.
  $menu_links['jrc-main-menu_eia-archives:node/3508'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3508',
    'router_path' => 'node/%',
    'link_title' => 'E&IA Archives',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eia-archives:node/3508',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_enlargement--integration:node/3256',
  );
  // Exported menu link: jrc-main-menu_eia-vacancies:node/3506.
  $menu_links['jrc-main-menu_eia-vacancies:node/3506'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3506',
    'router_path' => 'node/%',
    'link_title' => 'E&IA Vacancies',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eia-vacancies:node/3506',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_enlargement--integration:node/3256',
  );
  
  // Exported menu link: jrc-main-menu_enlargement--integration:node/3256.
  $menu_links['jrc-main-menu_enlargement--integration:node/3256'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3256',
    'router_path' => 'node/%',
    'link_title' => 'Enlargement & integration',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_enlargement--integration:node/3256',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  
  // Exported menu link: jrc-main-menu_erik:node/3269.
  $menu_links['jrc-main-menu_erik:node/3269'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3269',
    'router_path' => 'node/%',
    'link_title' => 'Erik',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_erik:node/3269',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_eurl-food-contact-materials:node/407.
  $menu_links['jrc-main-menu_eurl-food-contact-materials:node/407'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/407',
    'router_path' => 'node/%',
    'link_title' => 'EURL Food Contact Materials',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eurl-food-contact-materials:node/407',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -25,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
  );
  // Exported menu link: jrc-main-menu_eurl-for-alternatives-to-animal-testing:node/9906.
  $menu_links['jrc-main-menu_eurl-for-alternatives-to-animal-testing:node/9906'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9906',
    'router_path' => 'node/%',
    'link_title' => 'EURL for alternatives to animal testing',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'European Union Reference Laboratory for alternatives to animal testing',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eurl-for-alternatives-to-animal-testing:node/9906',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
  );
  // Exported menu link: jrc-main-menu_eurl-gm-food-and-feed:node/406.
  $menu_links['jrc-main-menu_eurl-gm-food-and-feed:node/406'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/406',
    'router_path' => 'node/%',
    'link_title' => 'EURL GM Food and Feed',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_eurl-gm-food-and-feed:node/406',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
  );
  // Exported menu link: jrc-main-menu_european-solar-test-installation:node/408.
  $menu_links['jrc-main-menu_european-solar-test-installation:node/408'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/408',
    'router_path' => 'node/%',
    'link_title' => 'European Solar Test Installation',
    'options' => array(
      'attributes' => array(
        'title' => 'European Solar Test Installation (ESTI)',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_european-solar-test-installation:node/408',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
  );
  // Exported menu link: jrc-main-menu_european-union-reference-laboratories:node/27983.
  $menu_links['jrc-main-menu_european-union-reference-laboratories:node/27983'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/27983',
    'router_path' => 'node/%',
    'link_title' => 'European Union Reference Laboratories',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference--measurement:node/398',
  );
  // Exported menu link: jrc-main-menu_event-websites:node/335.
  $menu_links['jrc-main-menu_event-websites:node/335'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/335',
    'router_path' => 'node/%',
    'link_title' => 'Event websites',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_event-websites:node/335',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_events:events',
  );
  // Exported menu link: jrc-main-menu_events:events.
  $menu_links['jrc-main-menu_events:events'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'events',
    'router_path' => 'events',
    'link_title' => 'Events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_events:events',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_news--events:node/110',
  );

  // Exported menu link: jrc-main-menu_facilities-and-laboratories:node/28147.
  $menu_links['jrc-main-menu_facilities-and-laboratories:node/28147'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28147',
    'router_path' => 'node/%',
    'link_title' => 'Facilities and laboratories',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IRMM\'s facilities and laboratories',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_facilities-and-laboratories:node/28147',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -5,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:node/28017',
  );
  // Exported menu link: jrc-main-menu_faq:reference-materials-faq.
  $menu_links['jrc-main-menu_faq:reference-materials-faq'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'reference-materials-faq',
    'router_path' => 'reference-materials-faq',
    'link_title' => 'FAQ',
    'options' => array(
      'attributes' => array(
        'title' => 'Frequently asked questions on Reference materials',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_faq:reference-materials-faq',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_user-support:node/435',
  );
  
  // Exported menu link: jrc-main-menu_francesca:node/3264.
  $menu_links['jrc-main-menu_francesca:node/3264'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3264',
    'router_path' => 'node/%',
    'link_title' => 'Francesca',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_francesca:node/3264',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -7,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_frequently-asked-questions:faq-list/.
  $menu_links['jrc-main-menu_frequently-asked-questions:faq-list/'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'faq-list/',
    'router_path' => 'faq-list/%',
    'link_title' => 'Frequently Asked Questions',
    'options' => array(
      'attributes' => array(
        'title' => 'List all FAQs related to Enlargement and integration',
      ),
      'query' => array(
        'f[0]' => 'im_field_tags:233',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_frequently-asked-questions:faq-list/',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_enlargement--integration:node/3256',
  );
  // Exported menu link: jrc-main-menu_function-group-i:node/4028.
  $menu_links['jrc-main-menu_function-group-i:node/4028'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/4028',
    'router_path' => 'node/%',
    'link_title' => 'Function group I',
    'options' => array(
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_function-group-i:node/4028',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
  );
  // Exported menu link: jrc-main-menu_function-group-ii:node/4027.
  $menu_links['jrc-main-menu_function-group-ii:node/4027'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/4027',
    'router_path' => 'node/%',
    'link_title' => 'Function group II',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_function-group-ii:node/4027',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
  );
  // Exported menu link: jrc-main-menu_function-group-iii:node/4026.
  $menu_links['jrc-main-menu_function-group-iii:node/4026'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/4026',
    'router_path' => 'node/%',
    'link_title' => 'Function group III',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_function-group-iii:node/4026',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
  );
  // Exported menu link: jrc-main-menu_function-group-iv:node/4025.
  $menu_links['jrc-main-menu_function-group-iv:node/4025'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/4025',
    'router_path' => 'node/%',
    'link_title' => 'Function group IV',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_function-group-iv:node/4025',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
  );
  
  
  // Exported menu link: jrc-main-menu_grantholders:node/3275.
  $menu_links['jrc-main-menu_grantholders:node/3275'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3275',
    'router_path' => 'node/%',
    'link_title' => 'Grantholders',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_grantholders:node/3275',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  // Exported menu link: jrc-main-menu_guidance:node/437.
  $menu_links['jrc-main-menu_guidance:node/437'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/437',
    'router_path' => 'node/%',
    'link_title' => 'Guidance',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_guidance:node/437',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_user-support:node/435',
  );
  
  
  // Exported menu link: jrc-main-menu_history:node/363.
  $menu_links['jrc-main-menu_history:node/363'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/363',
    'router_path' => 'node/%',
    'link_title' => 'History',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_history:node/363',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_about-us:node/105',
  );
  
  // Exported menu link: jrc-main-menu_how-to-order:node/433.
  $menu_links['jrc-main-menu_how-to-order:node/433'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/433',
    'router_path' => 'node/%',
    'link_title' => 'How to order',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'How to order reference materials',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_how-to-order:node/433',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_rm-catalogue:node/432',
  );
  // Exported menu link: jrc-main-menu_imep:interlaboratory-comparisons/IMEP.
  $menu_links['jrc-main-menu_imep:interlaboratory-comparisons/IMEP'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'interlaboratory-comparisons/IMEP',
    'router_path' => 'interlaboratory-comparisons/IMEP',
    'link_title' => 'IMEP',
    'options' => array(
      'attributes' => array(
        'title' => 'International Measurement Evaluation Programme',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
  );
  
  
  // Exported menu link: jrc-main-menu_industry:node/28146.
  $menu_links['jrc-main-menu_industry:node/28146'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28146',
    'router_path' => 'node/%',
    'link_title' => 'Industry',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_industry:node/28146',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_measurements-matter:node/28141',
  );
  
  
  
  // Exported menu link: jrc-main-menu_institute-for-energy-and-transport-iet:node/378.
  $menu_links['jrc-main-menu_institute-for-energy-and-transport-iet:node/378'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/378',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Energy and Transport (IET)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_institute-for-energy-and-transport-iet:node/378',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -5,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-environment-and-sustainability-ies:node/377.
  $menu_links['jrc-main-menu_institute-for-environment-and-sustainability-ies:node/377'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/377',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Environment and Sustainability (IES)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_institute-for-environment-and-sustainability-ies:node/377',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -6,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-health-and-consumer-protection-ihcp:node/379.
  $menu_links['jrc-main-menu_institute-for-health-and-consumer-protection-ihcp:node/379'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/379',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Health and Consumer Protection (IHCP)',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_institute-for-health-and-consumer-protection-ihcp:node/379',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -4,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-prospective-technological-studies-ipts:node/381.
  $menu_links['jrc-main-menu_institute-for-prospective-technological-studies-ipts:node/381'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/381',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Prospective Technological Studies (IPTS)',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_institute-for-prospective-technological-studies-ipts:node/381',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -2,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-reference-materials-and-measurements-irmm:node/382.
  $menu_links['jrc-main-menu_institute-for-reference-materials-and-measurements-irmm:node/382'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/382',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Reference Materials and Measurements (IRMM)',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_institute-for-reference-materials-and-measurements-irmm:node/382',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-the-protection-and-security-of-the-citizen-ipsc:node/380.
  $menu_links['jrc-main-menu_institute-for-the-protection-and-security-of-the-citizen-ipsc:node/380'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/380',
    'router_path' => 'node/%',
    'link_title' => 'Institute for the Protection and Security of the Citizen (IPSC)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_institute-for-the-protection-and-security-of-the-citizen-ipsc:node/380',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -3,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institute-for-transuranium-elements-itu:node/383.
  $menu_links['jrc-main-menu_institute-for-transuranium-elements-itu:node/383'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/383',
    'router_path' => 'node/%',
    'link_title' => 'Institute for Transuranium Elements (ITU)',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_institute-for-transuranium-elements-itu:node/383',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_institutes-and-directorates:node/27998.
  $menu_links['jrc-main-menu_institutes-and-directorates:node/27998'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/27998',
    'router_path' => 'node/%',
    'link_title' => 'Institutes and Directorates',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'JRC Institutes and Directorates',
      ),
      'identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_about-us:node/105',
  );
  // Exported menu link: jrc-main-menu_integrated-management-system:node/2893.
  $menu_links['jrc-main-menu_integrated-management-system:node/2893'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/2893',
    'router_path' => 'node/%',
    'link_title' => 'Integrated Management System',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_integrated-management-system:node/2893',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 20,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:node/28018',
  );
  
  // Exported menu link: jrc-main-menu_interlaboratory-comparisons:node/28128.
  $menu_links['jrc-main-menu_interlaboratory-comparisons:node/28128'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28128',
    'router_path' => 'node/%',
    'link_title' => 'Interlaboratory comparisons',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference--measurement:node/398',
  );
  // Exported menu link: jrc-main-menu_international-cooperation:node/3160.
  $menu_links['jrc-main-menu_international-cooperation:node/3160'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3160',
    'router_path' => 'node/%',
    'link_title' => 'International cooperation',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_international-cooperation:node/3160',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  
  
  // Exported menu link: jrc-main-menu_itu-training--education:node/458.
  $menu_links['jrc-main-menu_itu-training--education:node/458'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/458',
    'router_path' => 'node/%',
    'link_title' => 'ITU Training & Education',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_itu-training--education:node/458',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  // Exported menu link: jrc-main-menu_jobs:node/385.
  $menu_links['jrc-main-menu_jobs:node/385'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/385',
    'router_path' => 'node/%',
    'link_title' => 'Jobs',
    'options' => array(
      'attributes' => array(
        'title' => 'Working at the JRC',
      ),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jobs:node/385',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  // Exported menu link: jrc-main-menu_journalists-visits-to-jrcs-research-sites:node/394.
  $menu_links['jrc-main-menu_journalists-visits-to-jrcs-research-sites:node/394'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/394',
    'router_path' => 'node/%',
    'link_title' => 'Journalists visits to JRC\'s research sites',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_journalists-visits-to-jrcs-research-sites:node/394',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-centre:node/392',
  );
  // Exported menu link: jrc-main-menu_jrc-alumni-network:http://ec.europa.eu/jrc/communities/community/jrc-alumni-network.
  $menu_links['jrc-main-menu_jrc-alumni-network:http://ec.europa.eu/jrc/communities/community/jrc-alumni-network'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'http://ec.europa.eu/jrc/communities/community/jrc-alumni-network',
    'router_path' => '',
    'link_title' => 'JRC Alumni network',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-alumni-network:http://ec.europa.eu/jrc/communities/community/jrc-alumni-network',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_our-communities:node/32061',
  );
  // Exported menu link: jrc-main-menu_jrc-communities-homepage:http://ec.europa.eu/jrc/communities/.
  $menu_links['jrc-main-menu_jrc-communities-homepage:http://ec.europa.eu/jrc/communities/'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'http://ec.europa.eu/jrc/communities/',
    'router_path' => '',
    'link_title' => 'JRC Communities homepage',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-communities-homepage:http://ec.europa.eu/jrc/communities/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_our-communities:node/32061',
  );
  
  
  // Exported menu link: jrc-main-menu_jrc-ihcp:node/28015.
  $menu_links['jrc-main-menu_jrc-ihcp:node/28015'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28015',
    'router_path' => 'node/%',
    'link_title' => 'JRC-IHCP',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Health and Consumer Protection (JRC-IHCP)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ihcp:node/28015',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  
  // Exported menu link: jrc-main-menu_jrc-institutes:node/28260.
  $menu_links['jrc-main-menu_jrc-institutes:node/28260'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28260',
    'router_path' => 'node/%',
    'link_title' => 'JRC Institutes',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-institutes:node/28260',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_our-institutes:node/109',
  );
  // Exported menu link: jrc-main-menu_jrc-ipsc:node/28019.
  $menu_links['jrc-main-menu_jrc-ipsc:node/28019'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28019',
    'router_path' => 'node/%',
    'link_title' => 'JRC-IPSC',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for the Protection and Security of the Citizen (JRC-IPSC)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ipsc:node/28019',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_jrc-ipts:node/28016.
  $menu_links['jrc-main-menu_jrc-ipts:node/28016'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28016',
    'router_path' => 'node/%',
    'link_title' => 'JRC-IPTS',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Prospective Technological Studies (JRC-IPTS)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-ipts:node/28016',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_jrc-irmm:node/28017.
  $menu_links['jrc-main-menu_jrc-irmm:node/28017'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28017',
    'router_path' => 'node/%',
    'link_title' => 'JRC-IRMM',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Reference Materials and Measurements (JRC-IRMM)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-irmm:node/28017',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_jrc-itu:node/28018.
  $menu_links['jrc-main-menu_jrc-itu:node/28018'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28018',
    'router_path' => 'node/%',
    'link_title' => 'JRC-ITU',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC\'s Institute for Transuranium Elements (JRC-ITU)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-itu:node/28018',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_institutes-and-directorates:node/27998',
  );
  // Exported menu link: jrc-main-menu_jrc-news:news-feed.
  $menu_links['jrc-main-menu_jrc-news:news-feed'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'news-feed',
    'router_path' => 'news-feed',
    'link_title' => 'JRC News',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_jrc-news:news-feed',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_news--events:node/110',
  );
  // Exported menu link: jrc-main-menu_jrc-newsletter:node/391.
  $menu_links['jrc-main-menu_jrc-newsletter:node/391'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/391',
    'router_path' => 'node/%',
    'link_title' => 'JRC Newsletter',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-newsletter:node/391',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_news--events:node/110',
  );
  
  
  // Exported menu link: jrc-main-menu_jrc-trainees:node/3276.
  $menu_links['jrc-main-menu_jrc-trainees:node/3276'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3276',
    'router_path' => 'node/%',
    'link_title' => 'JRC Trainees',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_jrc-trainees:node/3276',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  
  // Exported menu link: jrc-main-menu_karlsruhe-nuclide-chart:node/460.
  $menu_links['jrc-main-menu_karlsruhe-nuclide-chart:node/460'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/460',
    'router_path' => 'node/%',
    'link_title' => 'Karlsruhe Nuclide Chart',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_karlsruhe-nuclide-chart:node/460',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_itu-training--education:node/458',
  );
  
  
  // Exported menu link: jrc-main-menu_knowledge:node/107.
  $menu_links['jrc-main-menu_knowledge:node/107'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/107',
    'router_path' => 'node/%',
    'link_title' => 'Knowledge',
    'options' => array(
      'node_type' => 'mega_menu_item',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_knowledge:node/107',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  
  
  
  
  
  // Exported menu link: jrc-main-menu_lunchtime-science-lectures:node/34594.
  $menu_links['jrc-main-menu_lunchtime-science-lectures:node/34594'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/34594',
    'router_path' => 'node/%',
    'link_title' => 'Lunchtime science lectures',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Lunchtime science lectures',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_lunchtime-science-lectures:node/34594',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_events:events',
  );
  // Exported menu link: jrc-main-menu_marc:node/3263.
  $menu_links['jrc-main-menu_marc:node/3263'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3263',
    'router_path' => 'node/%',
    'link_title' => 'Marc',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_marc:node/3263',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -8,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_measurements-fields:node/6987.
  $menu_links['jrc-main-menu_measurements-fields:node/6987'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6987',
    'router_path' => 'node/%',
    'link_title' => 'Measurements fields',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_measurements-fields:node/6987',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_facilities-and-laboratories:node/28147',
  );
  
  // Exported menu link: jrc-main-menu_media-contacts:node/369.
  $menu_links['jrc-main-menu_media-contacts:node/369'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/369',
    'router_path' => 'node/%',
    'link_title' => 'Media contacts',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_media-contacts:node/369',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_contact-the-jrc:node/28005',
  );
  // Exported menu link: jrc-main-menu_meet-the-researchers:node/389.
  $menu_links['jrc-main-menu_meet-the-researchers:node/389'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/389',
    'router_path' => 'node/%',
    'link_title' => 'Meet the researchers',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jobs:node/385',
  );

  // Exported menu link: jrc-main-menu_method-database:node/421.
  $menu_links['jrc-main-menu_method-database:node/421'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/421',
    'router_path' => 'node/%',
    'link_title' => 'Method database',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_method-database:node/421',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -3,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_european-union-reference-laboratories:node/27983',
  );
  // Exported menu link: jrc-main-menu_monte-carlo:node/10208.
  $menu_links['jrc-main-menu_monte-carlo:node/10208'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/10208',
    'router_path' => 'node/%',
    'link_title' => 'MONTE CARLO',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_monte-carlo:node/10208',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 6,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_itu-training--education:node/458',
  );

  // Exported menu link: jrc-main-menu_national-contact-points:node/368.
  $menu_links['jrc-main-menu_national-contact-points:node/368'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/368',
    'router_path' => 'node/%',
    'link_title' => 'National Contact Points',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_national-contact-points:node/368',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  // Exported menu link: jrc-main-menu_networks--bureaus:networks-bureaus.
  $menu_links['jrc-main-menu_networks--bureaus:networks-bureaus'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'networks-bureaus',
    'router_path' => 'networks-bureaus',
    'link_title' => 'Networks & bureaus',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_networks--bureaus:networks-bureaus',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  // Exported menu link: jrc-main-menu_newcomer-information:node/30471.
  $menu_links['jrc-main-menu_newcomer-information:node/30471'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30471',
    'router_path' => 'node/%',
    'link_title' => 'Newcomer Information',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_newcomer-information:node/30471',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_karlsruhe:node/28011',
  );
  // Exported menu link: jrc-main-menu_news--events:node/110.
  $menu_links['jrc-main-menu_news--events:node/110'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/110',
    'router_path' => 'node/%',
    'link_title' => 'News & events',
    'options' => array(
      'node_type' => 'mega_menu_item',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_news--events:node/110',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: jrc-main-menu_news-highlights:news-feed/.
  $menu_links['jrc-main-menu_news-highlights:news-feed/'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'news-feed/',
    'router_path' => 'news-feed/%',
    'link_title' => 'News highlights',
    'options' => array(
      'query' => array(
        'f[0]' => 'im_field_highlighted:1',
      ),
      'attributes' => array(
        'title' => 'Shows highlighted news only',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_news-highlights:news-feed/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-news:news-feed',
  );
  // Exported menu link: jrc-main-menu_news:node/7734.
  $menu_links['jrc-main-menu_news:node/7734'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/7734',
    'router_path' => 'node/%',
    'link_title' => 'News',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_news:node/7734',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  // Exported menu link: jrc-main-menu_nigel:node/3271.
  $menu_links['jrc-main-menu_nigel:node/3271'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3271',
    'router_path' => 'node/%',
    'link_title' => 'Nigel',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_nigel:node/3271',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_nuclear-safety-and-security:node/249.
  $menu_links['jrc-main-menu_nuclear-safety-and-security:node/249'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/249',
    'router_path' => 'node/%',
    'link_title' => 'Nuclear safety and security',
    'options' => array(
      'node_type' => 'research_area',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_nuclear-safety-and-security:node/249',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_science-areas:node/259',
  );
  // Exported menu link: jrc-main-menu_nusimep:interlaboratory-comparisons/NUSIMEP.
  $menu_links['jrc-main-menu_nusimep:interlaboratory-comparisons/NUSIMEP'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'interlaboratory-comparisons/NUSIMEP',
    'router_path' => 'interlaboratory-comparisons/NUSIMEP',
    'link_title' => 'NUSIMEP',
    'options' => array(
      'attributes' => array(
        'title' => 'Nuclear Signatures Interlaboratory Measurement Evaluation Programme',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_nusimep:interlaboratory-comparisons/NUSIMEP',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
  );
  // Exported menu link: jrc-main-menu_order-on-line:node/431.
  $menu_links['jrc-main-menu_order-on-line:node/431'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/431',
    'router_path' => 'node/%',
    'link_title' => 'Order on-line',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Reference materials on-line ordering',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_order-on-line:node/431',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_rm-catalogue:node/432',
  );
  // Exported menu link: jrc-main-menu_organisation:node/28140.
  $menu_links['jrc-main-menu_organisation:node/28140'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28140',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IRMM\'s organisational chart',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/28140',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:node/28017',
  );
  // Exported menu link: jrc-main-menu_organisation:node/28316.
  $menu_links['jrc-main-menu_organisation:node/28316'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28316',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/28316',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipsc:node/28019',
  );
  // Exported menu link: jrc-main-menu_organisation:node/29605.
  $menu_links['jrc-main-menu_organisation:node/29605'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/29605',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/29605',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ihcp:node/28015',
  );
  // Exported menu link: jrc-main-menu_organisation:node/29818.
  $menu_links['jrc-main-menu_organisation:node/29818'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/29818',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/29818',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-iet:node/28013',
  );
  // Exported menu link: jrc-main-menu_organisation:node/305.
  $menu_links['jrc-main-menu_organisation:node/305'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/305',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPTS Scientific units',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/305',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:node/28016',
  );
  // Exported menu link: jrc-main-menu_organisation:node/444.
  $menu_links['jrc-main-menu_organisation:node/444'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/444',
    'router_path' => 'node/%',
    'link_title' => 'Organisation',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-ITU\'s Organisation',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_organisation:node/444',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:node/28018',
  );
  // Exported menu link: jrc-main-menu_other-comparisons:interlaboratory-comparisons/other.
  $menu_links['jrc-main-menu_other-comparisons:interlaboratory-comparisons/other'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'interlaboratory-comparisons/other',
    'router_path' => 'interlaboratory-comparisons/other',
    'link_title' => 'Other comparisons',
    'options' => array(
      'attributes' => array(
        'title' => 'Other interlaboratory comparisons',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_other-comparisons:interlaboratory-comparisons/other',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
  );
  // Exported menu link: jrc-main-menu_other-news:news-feed/.
  $menu_links['jrc-main-menu_other-news:news-feed/'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'news-feed/',
    'router_path' => 'news-feed/%',
    'link_title' => 'Other news',
    'options' => array(
      'query' => array(
        'f[0]' => 'im_field_highlighted:2',
      ),
      'attributes' => array(
        'title' => 'Shows non-highlighted news only',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_other-news:news-feed/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-news:news-feed',
  );
  // Exported menu link: jrc-main-menu_our-accellerators:node/6942.
  $menu_links['jrc-main-menu_our-accellerators:node/6942'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6942',
    'router_path' => 'node/%',
    'link_title' => 'Our accellerators',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_our-accellerators:node/6942',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_facilities-and-laboratories:node/28147',
  );
  // Exported menu link: jrc-main-menu_our-communities:node/32061.
  $menu_links['jrc-main-menu_our-communities:node/32061'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/32061',
    'router_path' => 'node/%',
    'link_title' => 'Our Communities',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'node_type' => 'mega_menu_item',
      'identifier' => 'jrc-main-menu_our-communities:node/32061',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: jrc-main-menu_our-institutes:node/109.
  $menu_links['jrc-main-menu_our-institutes:node/109'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/109',
    'router_path' => 'node/%',
    'link_title' => 'Our Institutes',
    'options' => array(
      'node_type' => 'mega_menu_item',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_our-institutes:node/109',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: jrc-main-menu_overview:node/367.
  $menu_links['jrc-main-menu_overview:node/367'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/367',
    'router_path' => 'node/%',
    'link_title' => 'Overview',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_overview:node/367',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_working-with-us:node/27997',
  );
  // Exported menu link: jrc-main-menu_past-events:past-events-list.
  $menu_links['jrc-main-menu_past-events:past-events-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'past-events-list',
    'router_path' => 'past-events-list',
    'link_title' => 'Past events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_past-events:past-events-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_events:events',
  );
  // Exported menu link: jrc-main-menu_patents--technologies:patents.
  $menu_links['jrc-main-menu_patents--technologies:patents'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'patents',
    'router_path' => 'patents',
    'link_title' => 'Patents & technologies',
    'options' => array(
      'attributes' => array(
        'title' => 'JRC patents',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_patents--technologies:patents',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
  // Exported menu link: jrc-main-menu_patients-and-doctors:node/28143.
  $menu_links['jrc-main-menu_patients-and-doctors:node/28143'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28143',
    'router_path' => 'node/%',
    'link_title' => 'Patients and doctors',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_patients-and-doctors:node/28143',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_measurements-matter:node/28141',
  );
  
  // Exported menu link: jrc-main-menu_permanent-positions:node/386.
  $menu_links['jrc-main-menu_permanent-positions:node/386'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/386',
    'router_path' => 'node/%',
    'link_title' => 'Permanent positions',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_permanent-positions:node/386',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jobs:node/385',
  );
  
  // Exported menu link: jrc-main-menu_photos:photo-galleries-list.
  $menu_links['jrc-main-menu_photos:photo-galleries-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'photo-galleries-list',
    'router_path' => 'photo-galleries-list',
    'link_title' => 'Photos',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_photos:photo-galleries-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
  // Exported menu link: jrc-main-menu_press-centre:node/392.
  $menu_links['jrc-main-menu_press-centre:node/392'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/392',
    'router_path' => 'node/%',
    'link_title' => 'Press centre',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_press-centre:node/392',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_news--events:node/110',
  );
  // Exported menu link: jrc-main-menu_press-packs:node/395.
  $menu_links['jrc-main-menu_press-packs:node/395'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/395',
    'router_path' => 'node/%',
    'link_title' => 'Press packs',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_press-packs:node/395',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-centre:node/392',
  );
  // Exported menu link: jrc-main-menu_press-releases:press-releases-list.
  $menu_links['jrc-main-menu_press-releases:press-releases-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'press-releases-list',
    'router_path' => 'press-releases-list',
    'link_title' => 'Press releases',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_press-releases:press-releases-list',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-centre:node/392',
  );
  // Exported menu link: jrc-main-menu_press:node/7735.
  $menu_links['jrc-main-menu_press:node/7735'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/7735',
    'router_path' => 'node/%',
    'link_title' => 'Press',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_press:node/7735',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  // Exported menu link: jrc-main-menu_principles:node/6072.
  $menu_links['jrc-main-menu_principles:node/6072'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6072',
    'router_path' => 'node/%',
    'link_title' => 'Principles',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_principles:node/6072',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_nusimep:interlaboratory-comparisons/NUSIMEP',
  );
  // Exported menu link: jrc-main-menu_principles:node/6081.
  $menu_links['jrc-main-menu_principles:node/6081'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6081',
    'router_path' => 'node/%',
    'link_title' => 'Principles',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_principles:node/6081',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reimep:interlaboratory-comparisons/REIMEP',
  );
  // Exported menu link: jrc-main-menu_project-reports:node/7737.
  $menu_links['jrc-main-menu_project-reports:node/7737'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/7737',
    'router_path' => 'node/%',
    'link_title' => 'Project reports',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_project-reports:node/7737',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  
  // Exported menu link: jrc-main-menu_publications:node/34472.
  $menu_links['jrc-main-menu_publications:node/34472'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/34472',
    'router_path' => 'node/%',
    'link_title' => 'Publications',
    'options' => array(
      'attributes' => array(
        'title' => 'Behavioural insights publications',
      ),
      'alter' => TRUE,
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_publications:node/34472',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 6,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_behavioural-insights:node/33382',
  );
  
  
  
  // Exported menu link: jrc-main-menu_reference--measurement:node/398.
  $menu_links['jrc-main-menu_reference--measurement:node/398'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/398',
    'router_path' => 'node/%',
    'link_title' => 'Reference & measurement',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_reference--measurement:node/398',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
  // Exported menu link: jrc-main-menu_reference-materials-rm:node/2892.
  $menu_links['jrc-main-menu_reference-materials-rm:node/2892'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/2892',
    'router_path' => 'node/%',
    'link_title' => 'Reference Materials (RM)',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference--measurement:node/398',
  );
  // Exported menu link: jrc-main-menu_regional-coordinators:node/6069.
  $menu_links['jrc-main-menu_regional-coordinators:node/6069'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6069',
    'router_path' => 'node/%',
    'link_title' => 'Regional coordinators',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_regional-coordinators:node/6069',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 8,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
  );
  // Exported menu link: jrc-main-menu_reimep:interlaboratory-comparisons/REIMEP.
  $menu_links['jrc-main-menu_reimep:interlaboratory-comparisons/REIMEP'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'interlaboratory-comparisons/REIMEP',
    'router_path' => 'interlaboratory-comparisons/REIMEP',
    'link_title' => 'REIMEP',
    'options' => array(
      'attributes' => array(
        'title' => 'Regular European Interlaboratory Measurement Evaluation Programme',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_reimep:interlaboratory-comparisons/REIMEP',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_interlaboratory-comparisons:node/28128',
  );
  // Exported menu link: jrc-main-menu_research-assistants-ast3-competition:node/3278.
  $menu_links['jrc-main-menu_research-assistants-ast3-competition:node/3278'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3278',
    'router_path' => 'node/%',
    'link_title' => 'Research Assistants (AST3) competition',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_research-assistants-ast3-competition:node/3278',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_permanent-positions:node/386',
  );
  // Exported menu link: jrc-main-menu_research:node/106.
  $menu_links['jrc-main-menu_research:node/106'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/106',
    'router_path' => 'node/%',
    'link_title' => 'Research',
    'options' => array(
      'node_type' => 'mega_menu_item',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_research:node/106',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  
  // Exported menu link: jrc-main-menu_rm-catalogue:node/432.
  $menu_links['jrc-main-menu_rm-catalogue:node/432'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/432',
    'router_path' => 'node/%',
    'link_title' => 'RM catalogue',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Reference materials catalogue',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_rm-catalogue:node/432',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -6,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
  );
  // Exported menu link: jrc-main-menu_rm-development:node/438.
  $menu_links['jrc-main-menu_rm-development:node/438'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/438',
    'router_path' => 'node/%',
    'link_title' => 'RM Development',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Reference materials development',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_rm-development:node/438',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
  );
  // Exported menu link: jrc-main-menu_rm-releases:reference-materials/releases.
  $menu_links['jrc-main-menu_rm-releases:reference-materials/releases'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'reference-materials/releases',
    'router_path' => 'reference-materials/releases',
    'link_title' => 'RM Releases',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_rm-releases:reference-materials/releases',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -8,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
  );
  
  
  // Exported menu link: jrc-main-menu_science-for-food---eu-at-expo-milano:node/33389.
  $menu_links['jrc-main-menu_science-for-food---eu-at-expo-milano:node/33389'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/33389',
    'router_path' => 'node/%',
    'link_title' => 'Science for food - EU at Expo Milano',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_science-for-food---eu-at-expo-milano:node/33389',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_science-without-borders:node/30321.
  $menu_links['jrc-main-menu_science-without-borders:node/30321'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30321',
    'router_path' => 'node/%',
    'link_title' => 'Science without Borders',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Science without Borders - Ciência sem Fronteiras',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_science-without-borders:node/30321',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_international-cooperation:node/3160',
  );
  
  // Exported menu link: jrc-main-menu_scientific-tools--databases:scientific-tools.
  $menu_links['jrc-main-menu_scientific-tools--databases:scientific-tools'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'scientific-tools',
    'router_path' => 'scientific-tools',
    'link_title' => 'Scientific tools & databases',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Explore the wealth of JRC’s scientific databases and information systems.',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_scientific-tools--databases:scientific-tools',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
 
  // Exported menu link: jrc-main-menu_search-publications:publications-list.
  $menu_links['jrc-main-menu_search-publications:publications-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'publications-list',
    'router_path' => 'publications-list',
    'link_title' => 'Search publications',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_search-publications:publications-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_publications:node/28459',
  );
  // Exported menu link: jrc-main-menu_seconded-national-experts:node/3274.
  $menu_links['jrc-main-menu_seconded-national-experts:node/3274'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3274',
    'router_path' => 'node/%',
    'link_title' => 'Seconded national experts',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_seconded-national-experts:node/3274',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -3,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  // Exported menu link: jrc-main-menu_selection-procedure:node/4029.
  $menu_links['jrc-main-menu_selection-procedure:node/4029'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/4029',
    'router_path' => 'node/%',
    'link_title' => 'Selection procedure',
    'options' => array(
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_selection-procedure:node/4029',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_contract-staff-members:node/3272',
  );
  
  
  // Exported menu link: jrc-main-menu_showparent:node/30061.
  $menu_links['jrc-main-menu_showparent:node/30061'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30061',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/30061',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/32965.
  $menu_links['jrc-main-menu_showparent:node/32965'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/32965',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/32965',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9245.
  $menu_links['jrc-main-menu_showparent:node/9245'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9245',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9245',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9246.
  $menu_links['jrc-main-menu_showparent:node/9246'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9246',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9246',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9249.
  $menu_links['jrc-main-menu_showparent:node/9249'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9249',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9249',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9250.
  $menu_links['jrc-main-menu_showparent:node/9250'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9250',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9250',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9251.
  $menu_links['jrc-main-menu_showparent:node/9251'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9251',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9251',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9252.
  $menu_links['jrc-main-menu_showparent:node/9252'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9252',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9252',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9254.
  $menu_links['jrc-main-menu_showparent:node/9254'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9254',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9254',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9256.
  $menu_links['jrc-main-menu_showparent:node/9256'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9256',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9256',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9261.
  $menu_links['jrc-main-menu_showparent:node/9261'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9261',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9261',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9262.
  $menu_links['jrc-main-menu_showparent:node/9262'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9262',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9262',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9263.
  $menu_links['jrc-main-menu_showparent:node/9263'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9263',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9263',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9302.
  $menu_links['jrc-main-menu_showparent:node/9302'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9302',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9302',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9303.
  $menu_links['jrc-main-menu_showparent:node/9303'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9303',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9303',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9306.
  $menu_links['jrc-main-menu_showparent:node/9306'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9306',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9306',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9307.
  $menu_links['jrc-main-menu_showparent:node/9307'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9307',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9307',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9324.
  $menu_links['jrc-main-menu_showparent:node/9324'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9324',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9324',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9329.
  $menu_links['jrc-main-menu_showparent:node/9329'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9329',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9329',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9332.
  $menu_links['jrc-main-menu_showparent:node/9332'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9332',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9332',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9335.
  $menu_links['jrc-main-menu_showparent:node/9335'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9335',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9335',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9341.
  $menu_links['jrc-main-menu_showparent:node/9341'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9341',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9341',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9344.
  $menu_links['jrc-main-menu_showparent:node/9344'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9344',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9344',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9347.
  $menu_links['jrc-main-menu_showparent:node/9347'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9347',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9347',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9349.
  $menu_links['jrc-main-menu_showparent:node/9349'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9349',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9349',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9350.
  $menu_links['jrc-main-menu_showparent:node/9350'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9350',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9350',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  // Exported menu link: jrc-main-menu_showparent:node/9352.
  $menu_links['jrc-main-menu_showparent:node/9352'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/9352',
    'router_path' => 'node/%',
    'link_title' => '<show_parent>',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_showparent:node/9352',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-packs:node/395',
  );
  
  // Exported menu link: jrc-main-menu_stephan:node/3267.
  $menu_links['jrc-main-menu_stephan:node/3267'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3267',
    'router_path' => 'node/%',
    'link_title' => 'Stephan',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_stephan:node/3267',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  
  
  // Exported menu link: jrc-main-menu_temporary-agents:node/3273.
  $menu_links['jrc-main-menu_temporary-agents:node/3273'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3273',
    'router_path' => 'node/%',
    'link_title' => 'Temporary agents',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_temporary-agents:node/3273',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_temporary-positions:node/387',
  );
  // Exported menu link: jrc-main-menu_temporary-positions:node/387.
  $menu_links['jrc-main-menu_temporary-positions:node/387'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/387',
    'router_path' => 'node/%',
    'link_title' => 'Temporary positions',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_temporary-positions:node/387',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jobs:node/385',
  );
  // Exported menu link: jrc-main-menu_teresa:node/3268.
  $menu_links['jrc-main-menu_teresa:node/3268'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3268',
    'router_path' => 'node/%',
    'link_title' => 'Teresa',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_teresa:node/3268',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -3,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_test:node/32061.
  $menu_links['jrc-main-menu_test:node/32061'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/32061',
    'router_path' => 'node/%',
    'link_title' => 'test',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_test:node/32061',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 1,
  );
  // Exported menu link: jrc-main-menu_thomas:node/3266.
  $menu_links['jrc-main-menu_thomas:node/3266'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3266',
    'router_path' => 'node/%',
    'link_title' => 'Thomas',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_thomas:node/3266',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -5,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );
  // Exported menu link: jrc-main-menu_training-programmes:training-programmes.
  $menu_links['jrc-main-menu_training-programmes:training-programmes'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'training-programmes',
    'router_path' => 'training-programmes',
    'link_title' => 'Training programmes',
    'options' => array(
      'attributes' => array(
        'title' => 'List of the JRC Training programmes',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_training-programmes:training-programmes',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  // Exported menu link: jrc-main-menu_training:node/28184.
  $menu_links['jrc-main-menu_training:node/28184'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28184',
    'router_path' => 'node/%',
    'link_title' => 'Training',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Education and Training Activities of the JRC',
      ),
      'identifier' => 'jrc-main-menu_training:node/28184',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
  // Exported menu link: jrc-main-menu_transuranus:node/10207.
  $menu_links['jrc-main-menu_transuranus:node/10207'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/10207',
    'router_path' => 'node/%',
    'link_title' => 'TRANSURANUS',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_transuranus:node/10207',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_itu-training--education:node/458',
  );
  // Exported menu link: jrc-main-menu_upcoming-training-events:training-events-list.
  $menu_links['jrc-main-menu_upcoming-training-events:training-events-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'training-events-list',
    'router_path' => 'training-events-list',
    'link_title' => 'Upcoming training events',
    'options' => array(
      'attributes' => array(
        'title' => 'List of ongoing and upcoming JRC training events',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_upcoming-training-events:training-events-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_training:node/28184',
  );
  // Exported menu link: jrc-main-menu_useful-links:node/442.
  $menu_links['jrc-main-menu_useful-links:node/442'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/442',
    'router_path' => 'node/%',
    'link_title' => 'Useful Links',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Reference materials useful links',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_useful-links:node/442',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
  );
  // Exported menu link: jrc-main-menu_user-support:node/435.
  $menu_links['jrc-main-menu_user-support:node/435'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/435',
    'router_path' => 'node/%',
    'link_title' => 'User support',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_user-support:node/435',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -4,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_reference-materials-rm:node/2892',
  );
  // Exported menu link: jrc-main-menu_users-and-partners:node/6070.
  $menu_links['jrc-main-menu_users-and-partners:node/6070'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/6070',
    'router_path' => 'node/%',
    'link_title' => 'Users and partners',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_users-and-partners:node/6070',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 12,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_imep:interlaboratory-comparisons/IMEP',
  );
  // Exported menu link: jrc-main-menu_vacancies:node/31997.
  $menu_links['jrc-main-menu_vacancies:node/31997'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/31997',
    'router_path' => 'node/%',
    'link_title' => 'Vacancies',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_vacancies:node/31997',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jobs:node/385',
  );
  // Exported menu link: jrc-main-menu_vacancy-driver-and-logistic-support:node/30253.
  $menu_links['jrc-main-menu_vacancy-driver-and-logistic-support:node/30253'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30253',
    'router_path' => 'node/%',
    'link_title' => 'Vacancy: Driver and Logistic Support',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'Contract Staff (Function Group I) JRC vacancy in Petten (NL) - Deadline for expression of interest: 31/07/2014, 12 noon (Brussels time)',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_vacancy-driver-and-logistic-support:node/30253',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_function-group-i:node/4028',
  );
  // Exported menu link: jrc-main-menu_vacancy-seconded-national-expert:node/30060.
  $menu_links['jrc-main-menu_vacancy-seconded-national-expert:node/30060'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/30060',
    'router_path' => 'node/%',
    'link_title' => 'Vacancy: Seconded National Expert',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Vacancy in the area of nuclear power plants / JRC-Petten',
      ),
      'identifier' => 'jrc-main-menu_vacancy-seconded-national-expert:node/30060',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_vacancies:node/31997',
  );
  // Exported menu link: jrc-main-menu_videos:video-galleries-list.
  $menu_links['jrc-main-menu_videos:video-galleries-list'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'video-galleries-list',
    'router_path' => 'video-galleries-list',
    'link_title' => 'Videos',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_videos:video-galleries-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_knowledge:node/107',
  );
  // Exported menu link: jrc-main-menu_visual-identity:node/396.
  $menu_links['jrc-main-menu_visual-identity:node/396'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/396',
    'router_path' => 'node/%',
    'link_title' => 'Visual identity',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'jrc-main-menu_visual-identity:node/396',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_press-centre:node/392',
  );
  // Exported menu link: jrc-main-menu_vittorio:node/3270.
  $menu_links['jrc-main-menu_vittorio:node/3270'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/3270',
    'router_path' => 'node/%',
    'link_title' => 'Vittorio',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'identifier' => 'jrc-main-menu_vittorio:node/3270',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_meet-the-researchers:node/389',
  );

  // Exported menu link: jrc-main-menu_what-we-do:node/28148.
  $menu_links['jrc-main-menu_what-we-do:node/28148'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28148',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'JRC-IRMM activities',
      ),
      'identifier' => 'jrc-main-menu_what-we-do:node/28148',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-irmm:node/28017',
  );
  // Exported menu link: jrc-main-menu_what-we-do:node/28153.
  $menu_links['jrc-main-menu_what-we-do:node/28153'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28153',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPTS activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:node/28153',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipts:node/28016',
  );
  // Exported menu link: jrc-main-menu_what-we-do:node/28161.
  $menu_links['jrc-main-menu_what-we-do:node/28161'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28161',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'JRC-ITU activities',
      ),
      'identifier' => 'jrc-main-menu_what-we-do:node/28161',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jrc-itu:node/28018',
  );
  // Exported menu link: jrc-main-menu_what-we-do:node/28170.
  $menu_links['jrc-main-menu_what-we-do:node/28170'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28170',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IET activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:node/28170',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-iet:node/28013',
  );
  // Exported menu link: jrc-main-menu_what-we-do:node/28171.
  $menu_links['jrc-main-menu_what-we-do:node/28171'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28171',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IHCP activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:node/28171',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ihcp:node/28015',
  );
  // Exported menu link: jrc-main-menu_what-we-do:node/28172.
  $menu_links['jrc-main-menu_what-we-do:node/28172'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/28172',
    'router_path' => 'node/%',
    'link_title' => 'What we do',
    'options' => array(
      'node_type' => 'page',
      'attributes' => array(
        'title' => 'JRC-IPSC activities',
      ),
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_what-we-do:node/28172',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
    'parent_identifier' => 'jrc-main-menu_jrc-ipsc:node/28019',
  );
 
  // Exported menu link: jrc-main-menu_working-with-us:node/27997.
  $menu_links['jrc-main-menu_working-with-us:node/27997'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/27997',
    'router_path' => 'node/%',
    'link_title' => 'Working with us',
    'options' => array(
      'node_type' => 'mega_menu_item',
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'jrc-main-menu_working-with-us:node/27997',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: jrc-main-menu_workplace:node/388.
  $menu_links['jrc-main-menu_workplace:node/388'] = array(
    'menu_name' => 'jrc-main-menu',
    'link_path' => 'node/388',
    'router_path' => 'node/%',
    'link_title' => 'Workplace',
    'options' => array(
      'attributes' => array(),
      'node_type' => 'page',
      'alter' => TRUE,
      'identifier' => 'jrc-main-menu_workplace:node/388',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'jrc-main-menu_jobs:node/385',
  );

  return $menu_links;
}
