<?php
/**
 * @file
 * Theme implementation to display feature set.
 *
 * Available variables:
 * - $feature_set_category: list of features, grouped by category
 * - $feature_set_row: raw list of features, ungrouped
 * - $feature_set_input: rendered form input (submit and hidden fields)
 */
?>
<?php foreach ($feature_set_category['category'] as $category => $features) : ?>
<fieldset class="collapsible form-wrapper collapsed">
  <legend>
    <span class="fieldset-legend"><?php print $category; ?></span>
  </legend>
  <div class="fieldset-wrapper">
  <table>
    <?php $i = 0; foreach ($features as $key => $item) : ?>
      <tr class="<?php $i % 2 ? print 'even' : print 'odd';?>">
        <td>
          <?php
            if (!empty($item['#featuresetinfo']['featureset'])) :
              print '<strong>' . $item['#featuresetinfo']['featureset'] . '</strong>';
            endif;
            if (!empty($item['#featuresetinfo']['description'])) :
              print '<br /><small>' . $item['#featuresetinfo']['description'] . '</small>';
            endif;
            if (!empty($item['#featuresetinfo']['description'])) :
              print '<br /><small>' .
                l(t('See @name documentation', array('@name' => $item['#featuresetinfo']['featureset'])),
                  $item['#featuresetinfo']['documentation'],
                  array('attributes' => array('target' => '_blank')))
                . '</small>';
            endif;
          ?>
        </td>
        <td>
          <?php print render($item); ?>
        </td>
      </tr>
    <?php $i++; endforeach ?>
  </table>
  </div>
</fieldset>
<?php endforeach; ?>

<?php
  print $feature_set_input;
?>
