<?php

/**
 * @file
 * Page wrapper.
 */
?>
<div id="newsroom-page-content" class="newsroomPage-container">
    <div class="newsroom-page view-content">
    <?php echo $featured_item; ?>
    <?php if ($items): ?>
      <?php echo $items; ?>
    <?php else: ?>
      <div class="no-result"><?php echo t("No results"); ?></div>
    <?php endif; ?>
    </div>
</div>
