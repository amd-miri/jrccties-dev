<?php

/**
 * @file
 * Agenda content items.
 */
?>
<?php if (!empty($items)): ?>
  <h3><?php echo $item_type; ?></h3>
  <?php foreach ($items as $item): ?>
    <?php if (!$item['visible']) : ?>
      <div id="display-more-container" class="newsroom-<?php echo drupal_strtolower(sprintf('%s-%s', $agenda_block, str_replace(' ', '_', $item_type))); ?>" style="display: none;">
        <?php echo $item['output']; ?>
      </div>
    <?php else: ?>
      <?php echo $item['output']; ?>
    <?php endif; ?>
  <?php endforeach; ?>
  <?php if (count($items) > $items_number_to_show_more_button) : ?>
      <div id="display-more-link" onclick="return Drupal.behaviors.nexteuropa_newsroom.showHiddenAgendaItems('<?php echo drupal_strtolower(sprintf('newsroom-%s-%s', $agenda_block, str_replace(' ', '_', $item_type))); ?>', this)" class="newsroom-display-more btn btn-ctn">
        <?php echo t('Display more !agenda_block !item_type items', ['!agenda_block' => $agenda_block, '!item_type' => drupal_strtolower($item_type)]); ?>
      </div>
  <?php endif; ?>
<?php endif; ?>
