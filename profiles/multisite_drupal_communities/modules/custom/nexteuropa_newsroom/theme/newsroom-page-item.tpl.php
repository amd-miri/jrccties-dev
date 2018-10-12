<?php

/**
 * @file
 * Page item.
 */
?>
<?php if (!empty($items)): ?>
<div class="listing__wrapper">
  <ul class="listing listing--teaser">
    <?php foreach($items as $item): ?>
    <li class="listing__item">
      <div class="listing__item__wrapper">
        <?php $node_view = node_view($item, 'newsroom_teaser'); ?>
        <?php echo drupal_render($node_view); ?>
        <?php echo $item->related_items; ?>
      </div>
    </li>
    <?php endforeach; ?>
  </ul>
</div>
<?php endif; ?>
