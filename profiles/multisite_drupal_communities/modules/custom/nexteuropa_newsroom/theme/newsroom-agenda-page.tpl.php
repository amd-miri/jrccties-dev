<?php

/**
 * @file
 * Agenda page.
 */
?>
<div class="<?php echo !$is_block ? 'newsroomAgenda-container' : NULL; ?>">
  <?php if (!empty($items['visible_items']) || !empty($next_event_items['visible_items']) || !empty($past_event_items['visible_items'])): ?>
    <?php if ($is_today): ?>
        <?php if (!empty($items['visible_items'])) : ?>
          <div class="currentDate">
            <h2 class="newsroom_title"><?php echo t('Current'); ?></h2>
            <?php echo $items['visible_items']; ?>
          </div>
        <?php else: ?>
            <div class="newsroom-message"><?php echo t('No events for current date'); ?></div>
        <?php endif; ?>
    <?php endif; ?>
    <?php if (!empty($next_event_items['visible_items'])) : ?>
      <div class="furtherDates">
        <h2 class="newsroom_title"><?php echo t('Upcoming'); ?></h2>
        <?php echo $next_event_items['visible_items']; ?>
        <?php if (!empty($next_link)): ?>
            <div class="agendaPagination"><div class="agenda-next"><?php echo $next_link; ?></div></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($past_event_items['visible_items'])) : ?>
      <div class="pastDates">
        <h2 class="newsroom_title"><?php echo t('In the past'); ?></h2>
        <?php echo $past_event_items['visible_items']; ?>
        <?php if (!empty($previous_link)): ?>
            <div class="agendaPagination"><div class="agenda-previous"><?php echo $previous_link; ?></div></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>
  <?php elseif(!$is_block): ?>
    <div class="newsroom-message"><?php echo t('No results'); ?></div>
  <?php endif; ?>
</div>
