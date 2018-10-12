<?php

/**
 * @file
 * Default view template to display a item in an RSS feed.
 */
?>
<?php foreach($items as $item): ?>
    <item>
        <title><?php echo check_plain($item->title); ?></title>
        <link><?php echo url($item->nid); ?></link>
        <?php $field = field_get_items('node', $item, 'field_newsroom_teaser'); ?>
        <?php $teaser = field_view_value('node', $item, 'field_newsroom_teaser', $field[0]); ?>
        <description><?php echo drupal_render($teaser); ?></description>
        <guid isPermaLink="true"><?php echo url($item->nid); ?></guid>
    </item>
<?php endforeach; ?>
