<?php

/**
 * @file
 * Contains template file.
 */
?>
<button<?php print $atomium['attributes']['element']->append('class', 'ecl-button--secondary'); ?>>
  <?php print render($element['#value']); ?><?php print render($element['#children']); ?>
</button>
