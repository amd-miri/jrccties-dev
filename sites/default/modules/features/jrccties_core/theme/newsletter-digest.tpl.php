<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
</head>

<body bgcolor="#ffffff" style="background-color: #ffffff !important;">

<div>&nbsp;</div>
<div>&nbsp;</div>
<div>&nbsp;</div>

<table cellpadding="0" cellspacing="0" height="100%" id="bodytable" style="width: 100%; height: 100%; margin: 0px; padding: 0px; min-width: 320px" width="100%">
  <tr>
    <td align="center" bgcolor="#eaeaea" style="background-color: #ffffff; vertical-align: top" valign="top">
      <table border="0" cellpadding="0" cellspacing="0" class="container" style="width: 650px" width="650">
        <tr>
          <td>
            <div class="newsletter-intro">
              <p><b>Dear <?php echo $realname; ?>,</b></p>
              <p>
                Welcome to our monthly community newsletter. Your fellow
                community members create, discuss and share new comments, ideas,
                event information and news.
                We hope to keep you updated just in case you missed what
                happened last month in your community.
              </p>
              <p> Kindest regards, </p>
              <p>The JRC community support team</p>
            </div>
            <div>&nbsp;</div>
          </td>
        </tr>
      </table>

      <?php foreach ($content_per_user as $community): ?>
      <table valign="top" border="1" bordercolor="#e3e1d9" cellpadding="0" cellspacing="0" class="container" style="border: 1px solid #eaeaea; width: 650px" width="650">
        <tr>
          <td>
            <table border="0" cellpadding="0" cellspacing="0" style="width: 100%" width="100%">
              <tr>
                <td style="background-color: #ffffff;">
                  <table class="table" border="0" cellpadding="0" cellspacing="0" style="width: 80%; background-color: #e3e1d9;" width="80%" align="right">
                    <tr>
                      <td class="cell" style="padding-left: 10px">
                        <table border="0" cellpadding="0" cellspacing="0" style="width: 100% !important;" width="100%">
                          <tr>
                            <td style="height: 100px;">
                              <h2> <?php echo $community['title']; ?>  </h2>
                            </td>
                          </tr>
                        </table>
                      </td>
                    </tr>
                  </table>

                  <table class="table" border="0" valign="top" cellpadding="0" cellspacing="0" style="width: 20%; vertical-align: top; background-color: #e3e1d9;" width="20%" align="left";>
                    <tr>
                      <td valign="top" class="cell" style="padding-right: 10px; vertical-align:top;">
                        <table border="0" cellpadding="0" cellspacing="0" valign="top" style="width: 100% !important" width="100%">
                          <tr valign="top">
                            <td style="padding: 0px 0px 0px 0px" valign="middle" align="center">
                              <?php echo $community['logo']; ?>
                            </td>
                          </tr>
                        </table>
                      </td>
                    </tr>
                  </table>

                </td>
              </tr>
            </table>

            <table cellpadding="0" cellspacing="0" width="80%" align="right">
              <tr>
                <td style="padding-top: 20px;">
                  <?php foreach ($community['links'] as $key => $value): ?>
                    <p> <?php echo $value; ?> </p>
                  <?php endforeach; ?>
                  <div>&nbsp;</div>
                </td>
              </tr>
            </table>

          </td>

        </tr>
      </table>
      <?php endforeach; ?>
    </td>
  </tr>
</table>

<table cellpadding="0" cellspacing="0" height="100%" id="bodytable" style="width: 100%; height: 100%; margin: 0px; padding: 0px; min-width: 320px" width="100%">
  <tr>
    <td align="center" bgcolor="#ffffff" style="background-color: #ffffff; vertical-align: top" valign="top">
      <table cellpadding="0" cellspacing="0" class="container" style="background: red !important; width: 650px" width="650">
        <tr>
          <td>
            <div class="newsletter-footer">
              <div>&nbsp;</div>
              <p> You are receiving this newsletter because you previously ticked that box when becoming a member of the community. While you can unsubscribe, we hope you continue to subscribe to our monthly newsletter.
              </p>
              <div>&nbsp;</div>
            </div>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

</body>
</html>
