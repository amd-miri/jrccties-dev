<?php

/**
 * @file
 * Agenda date.
 */
?>
<?php if ($isPast): ?>
<div class="date-block event past">
    <span class="date-block__day"><?php echo $day; ?></span>
    <span class="date-block__month"><?php echo $month; ?></span>
    <span class="date-block__year"><?php echo $year; ?></span>
</div>
<?php else: ?>
<div class="date-block event">
    <span class="date-block__day-text"><?php echo $weekDay; ?></span>
    <span class="date-block__day"><?php echo $day; ?></span>
    <span class="date-block__month"><?php echo $month; ?></span>
</div>
<?php endif; ?>
