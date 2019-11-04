<div class="newsletter-body">
    <div class="newsletter-intro">
        Dear <?php echo $realname; ?>,
        Welcome to our monthly community newsletter.
        Your fellow community members create, discuss and share new comments, ideas, event information and news.
        We hope to keep you updated just in case you missed what happened last month in your community.
        Kindest regards,

        The JRC community support team

        You are receiving this newsletter because you previously ticked that box when becoming a member of the community.
        While you are welcome to unsubscribe through the link at the bottom of this email, we hope you continue to subscribe to our monthly newsletter.
    </div>
  <?php foreach ($content_per_user as $community): ?>
    <div class="newsletter-community">
        <div class="newsletter-community-left">
            <div class="newsletter-community-logo">
              <?php echo $community['logo']; ?>
            </div>
        </div>

        <div class="newsletter-community-right">
            <div class="newsletter-community-title">
                <h2> <?php echo $community['title']; ?> </h2>
            </div>

            <div class="newsletter-community-content">
                <ul>
                  <?php foreach ($community['links'] as $a => $b): ?>
                      <li> <?php echo $b; ?> </li>
                  <?php endforeach; ?>
                </ul>
            </div>
        </div>
    </div>
  <?php endforeach; ?>

    <div class="newsletter-outro">
        If you want to unsubscribe, please <?php echo $unsubscribe_link; ?>.
    </div>
</div>

<table>
    <tr>
        <td></td>
    </tr>
</table>





