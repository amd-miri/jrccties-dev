
Dear <?php echo $realname; ?>,

Welcome to our monthly community newsletter.
Your fellow community members create, discuss and share new comments, ideas, event information and news.
We hope to keep you updated just in case you missed what happened last month in your community.

Kindest regards,

The JRC community support team

You are receiving this newsletter because you previously ticked that box when becoming a member of the community.
While you are welcome to unsubscribe through the link at the bottom of this email, we hope you continue to subscribe to our monthly newsletter.


<?php foreach ($content_per_user as $community): ?>
  <?php echo $community['logo']; ?>
  <h2> <?php echo $community['title']; ?> </h2>
  <ul>
  <?php foreach ($community['links'] as $a => $b): ?>
    <li> <?php echo $b; ?> </li>
  <?php endforeach; ?>
  </ul>
<?php endforeach; ?>