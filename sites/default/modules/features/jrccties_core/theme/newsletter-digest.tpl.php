<?php foreach ($content_per_user as $c): ?>
  <h2> <?php echo $c['title']; ?> </h2>
  <ul>
  <?php foreach ($c['links'] as $a => $b): ?>
    <li> <?php echo $b; ?> </li>
  <?php endforeach; ?>
  </ul>
<?php endforeach; ?>