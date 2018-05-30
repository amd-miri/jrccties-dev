<?php

/**
 * @file media_tableau/includes/media_tableau.styles.inc
 * Styles definitions for Media: Tableau.
 */

/**
 * Implementation of Styles module hook_styles_register().
 */
function media_tableau_styles_register() {
  return array(
    'MediaTableauStyles' => array(
      'field_types' => 'file',
      'name' => t('MediaTableau'),
      'description' => t('Media Tableau styles.'),
      'path' => drupal_get_path('module', 'media_tableau') .'/includes',
      'file' => 'media_tableau.styles.inc',
    ),
  );
}

/**
 *  Implements hook_styles_containers(). (Deprecated in version 2)
 */
function media_tableau_styles_containers() {
  return array(
    'file' => array(
      'containers' => array(
        'media_tableau' => array(
          'label' => t('Tableau Styles'),
          'data' => array(
            'streams' => array(
              'tableau',
            ),
            'mimetypes' => array(
              'application/tableau',
            ),
          ),
          'weight' => 0,
          'filter callback' => 'media_tableau_formatter_filter',
          'themes' => array(
            'field_formatter_styles' => 'media_tableau_field_formatter_styles',
            'styles' => 'media_tableau_styles',
            'preview' => 'media_tableau_preview_style',
          ),
          'description' => t('Tableau Styles will display embedded Tableau visualizations and thumbnails to your choosing. You can !manage.', array('!manage' => l(t('manage your Tableau styles here'), 'admin/config/media/media-tableau-styles'))),
        ),
      ),
    ),
  );
}

function media_tableau_formatter_filter($variables) {
  if (isset($variables['object'])) {
    $object = isset($variables['object']->file) ? $variables['object']->file : $variables['object'];
    return (file_uri_scheme($object->uri) == 'tableau') && ($object->filemime == 'application/tableau');
  }
}

/**
 * Implementation of the File Styles module's hook_file_styles_filter().
 */
function media_tableau_file_styles_filter($object) {
  $file = isset($object->file) ? $object->file : $object;
  if ((file_uri_scheme($file->uri) == 'tableau') && ($file->filemime == 'application/tableau')) {
    return 'media_tableau';
  }
}

/**
 *  Implements hook_styles_styles().
 */
function media_tableau_styles_styles() {
  $styles = array(
    'file' => array(
      'containers' => array(
        'media_tableau' => array(
          'styles' => array(
            'tableau_thumbnail' => array(
              'name' => 'tableau_thumbnail',
              'effects' => array(
                array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 100, 'height' => 75)),
              ),
            ),
            'tableau_preview' => array(
              'name' => 'tableau_preview',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 220, 'height' => 165)),
              ),
            ),
            'tableau_full' => array(
              'name' => 'tableau_full',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 640, 'height' => 480)),
                array('label' => t('Full screen'), 'name' => 'fullscreen', 'data' => array('fullscreen' => 1)),
              ),
            ),
          ),
        ),
      ),
    ),
  );

  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $styles['file']['containers']['media_tableau']['styles']['tableau_thumbnail_' . $style_name] = array(
      'name' => 'tableau_thumbnail_' . $style_name,
      'image_style' => $style_name,
      'effects' => array(
        array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
      ),
    );
  }

  return $styles;
}

/**
 *  Implements hook_styles_presets().
 */
function media_tableau_styles_presets() {
  $presets = array(
    'file' => array(
      'square_thumbnail' => array(
        'media_tableau' => array(
          'tableau_thumbnail_square_thumbnail',
        ),
      ),
      'thumbnail' => array(
        'media_tableau' => array(
          'tableau_thumbnail',
        ),
      ),
      'small' => array(
        'media_tableau' => array(
          'tableau_preview',
        ),
      ),
      'large' => array(
        'media_tableau' => array(
          'tableau_full',
        ),
      ),
      'original' => array(
        'media_tableau' => array(
          'tableau_full',
        ),
      ),
    ),
  );
  return $presets;
}

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_tableau_styles_default_containers() {
  // We append Tableau to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_tableau' => array(
          'class' => 'MediaTableauStyles',
          'name' => 'media_tableau',
          'label' => t('Tableau'),
          'preview' => 'media_tableau_preview_style',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_tableau_styles_default_presets() {
  $presets = array(
    'file' => array(
      'containers' => array(
        'media_tableau' => array(
          'default preset' => 'unlinked_thumbnail',
          'styles' => array(
            'original' => array(
              'default preset' => 'visualization',
            ),
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'linked_medium',
            ),
            'large' => array(
              'default preset' => 'large_video',
            ),
          ),
          'presets' => array(
            'visualization' => array(
              array(
                'name' => 'visualization',
                'settings' => array(),
              ),
            ),
            'large_video' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 640,
                  'height' => 390,
                ),
              ),
              array(
                'name' => 'visualization',
                'settings' => array(),
              ),
            ),
          ),
        ),
      ),
    ),
  );
  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $presets['file']['containers']['media_tableau']['presets']['linked_' . $style_name] = array(
      array(
        'name' => 'linkToMedia',
        'settings' => array(),
      ),
      array(
        'name' => 'imageStyle',
        'settings' => array(
          'image_style' => $style_name,
        ),
      ),
      array(
        'name' => 'thumbnail',
        'settings' => array(),
      ),
    );
    $presets['file']['containers']['media_tableau']['presets']['unlinked_' . $style_name] = $presets['file']['containers']['media_tableau']['presets']['linked_' . $style_name];
    array_shift($presets['file']['containers']['media_tableau']['presets']['unlinked_' . $style_name]);
    foreach ($image_style['effects'] as $effect) {
      if (in_array($effect['name'], array('image_scale', 'image_scale_and_crop', 'image_resize', 'image_crop'))) {
        $presets['file']['containers']['media_tableau']['presets']['visualization_' . $style_name] = array(
          array(
            'name' => 'resize',
            'settings' => $effect['data'],
          ),
          array(
            'name' => 'visualization',
            'settings' => array(),
          ),
        );
      }
    }
  }
  return $presets;
}
