<?php

/**
 * @file
 * Service items template.
 */
?>

<?php if (!empty($items)) : ?>
    <h2><?php echo $title; ?></h2>
    <div class="listing__wrapper">
        <ul class="listing ">
        <?php foreach ($items as $item) : ?>
            <li class="listing__item">
                <div class="listing__item__wrapper">
                    <div class="listing__column-second">
                      <?php if($item->image || $item->service_id): ?>
                          <div class="image">
                            <?php if ($item->image): ?>
                              <?php echo $item->image; ?>
                            <?php endif; ?>
                          </div>
                      <?php endif; ?>
                      <?php if ($item->service_sample): ?>
                          <div class="sample">
                            <?php echo $item->service_sample; ?>
                          </div>
                      <?php endif; ?>
                    </div>
                    <div class="listing__column-main">
                        <h3><?php echo check_plain($item->title); ?></h3>
                        <p class="description">
                          <?php echo $item->description; ?>
                        </p>
                      <?php if ($item->form): ?>
                          <div class="form">
                            <?php echo $item->form; ?>
                          </div>
                      <?php endif; ?>
                    </div>
                </div>
            </li>
        <?php endforeach; ?>
        </ul>
    </div>
<?php endif; ?>
