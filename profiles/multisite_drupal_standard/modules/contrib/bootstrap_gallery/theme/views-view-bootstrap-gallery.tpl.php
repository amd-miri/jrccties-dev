<?php

/**
 * @file
 * Default simple view template to display a rows in a grid.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */

$options = bootstrap_gallery_get_options($view->style_plugin->options);
?>

<?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="<?php print $class; ?>"<?php print $attributes; ?>>
    <?php if (!empty($caption)) : ?>
        <caption><?php print $caption; ?></caption>
    <?php endif; ?>

    <div>
        <?php foreach ($rows as $row_number => $columns): ?>
            <?php $columns_count = count($columns); $span_number = round(12 / $columns_count); ?>
            <div <?php if ($row_classes[$row_number]) { print 'class="row-fluid ' . $row_classes[$row_number] .'"';  } ?>>
                <?php foreach ($columns as $column_number => $item): ?>
                    <div <?php if ($column_classes[$row_number][$column_number]) { print 'class="col-sm-' . $span_number . ' ' . $column_classes[$row_number][$column_number] .'"';  } ?>>
                        <?php print $item; ?>
                    </div>
                <?php endforeach; ?>
                <div class="clearfix"></div>
            </div>
        <?php endforeach; ?>
    </div>
</div>

<?php /* Print bootstrap gallery modal */ ?>
<?php print theme('bootstrap_gallery_modal', array('options' => $options)); ?>