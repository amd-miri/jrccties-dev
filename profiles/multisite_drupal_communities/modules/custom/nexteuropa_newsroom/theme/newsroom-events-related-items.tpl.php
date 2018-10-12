<?php

/**
 * @file
 * Agenda content items.
 */
?>
<?php if ($related_items): ?>
    <div class="listing__wrapper small newsroom-agenda-related-items">
        <ul class="listing listing--teaser">
          <?php foreach ($related_items as $item): ?>
              <li class="listing__item">
                  <div class="listing__item__wrapper">
                      <div class="listing__column-main">
                          <span class="label label--default"><?php echo $item->type_name; ?></span>
                          <h3 class="listing__title">
                            <?php echo $item->link; ?>
                          </h3>
                      </div>
                  </div>
              </li>
          <?php endforeach; ?>
        </ul>
    </div>
<?php endif; ?>
