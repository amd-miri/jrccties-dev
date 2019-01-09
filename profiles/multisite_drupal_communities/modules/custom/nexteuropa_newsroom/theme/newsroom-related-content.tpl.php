<?php

/**
 * @file
 * Related content tree presentation.
 */
?>
<?php $cnt_children = count($children_items); ?>
<?php $cnt_brother = count($brother_items); ?>
<?php if ($parent_item || $cnt_children > 0 || $cnt_brother > 0): ?>
  <ul>
      <?php if ($parent_item): ?>
      <li>
        <?php $title_text = check_plain($parent_item->title); ?>
        <?php echo l($title_text, 'node/' . $parent_item->id); ?>
        <?php if ($cnt_children > 0 || $cnt_brother > 0): ?>
        <ul>
        <?php endif; ?>
      <?php endif; ?>

      <?php if ($cnt_children > 0): ?>
      <li>
        <span><?php echo check_plain($current_item->title); ?></span>
        <ul>
          <?php foreach ($children_items as $item): ?>
            <li>
                <?php $title_text = check_plain($item->title); ?>
                <?php echo l($title_text, 'node/' . $item->id); ?>
            </li>
          <?php endforeach; ?>
        </ul>
      </li>
      <?php endif; ?>

      <?php if ($cnt_brother > 0): ?>
        <?php foreach ($brother_items as $brother_id => $item): ?>
          <li>
            <?php $title_text = check_plain($item->title); ?>
            <?php echo l($title_text, 'node/' . $item->id); ?>
          </li>
        <?php endforeach; ?>
      <?php endif; ?>

  <?php if ($parent_item): ?>
    <?php if ($cnt_children > 0 || $cnt_brother > 0): ?>
    </ul>
    <?php endif; ?>
  </li>
  <?php endif; ?>
</ul>
<?php endif; ?>
