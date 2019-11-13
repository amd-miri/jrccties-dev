<?php

/**
 * @file
 * Newsletter template.
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
  <meta http-equiv="Content-Type" content="text/html charset=UTF-8" />
</head>

<body bgcolor="#ffffff" style="background-color: #ffffff !important;">

  <table style="width: 100%; height: 100%; margin: 0px; padding: 0px; min-width: 320px" cellpadding="0" cellspacing="0" height="100%" class="bodytable" width="100%">
    <tr>
      <td style="background-color: #ffffff;" align="center" bgcolor="#eaeaea">
        <table style="width: 650px" border="0" cellpadding="0" cellspacing="0" class="container" width="650">
          <tr>
            <td>
              <table cellpadding="0" cellspacing="0" border="0">
                <tr>
                  <td class="newsletter-text">
                    <p style="margin: 10px;"> &nbsp; </p>
                    <p style="margin:0;"><b>Dear <?php echo $realname; ?>,</b></p>
                    <p style="margin-top: 10px;">
                      Welcome to our monthly community newsletter. Your fellow community members create, discuss and share new comments, ideas, event information and news. We hope to keep you updated just in case you missed what happened last month in your community.
                    </p>
                    <p style="margin-top: 10px;"> Kindest regards, </p>
                    <p style="margin-top: 10px;">The JRC community support team</p>
                    <p style="margin: 5px;"> &nbsp; </p>
                  </td>
                </tr>
              </table>
            </td>
          </tr>
        </table>

        <?php foreach ($content_per_user as $community): ?>
        <table style="width: 650px" width="650" valign="top" cellpadding="0" cellspacing="0" class="container" border="1" bordercolor="#e3e3e3">
          <tr>
            <td>
              <table style="width: 100%" width="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#e3e3e3">
                <tr>
                  <td>
                    <table width="80%" class="table" border="0" cellpadding="0" cellspacing="0" align="right">
                      <tr>
                        <td style="padding-left: 10px" class="cell">
                          <table style="width: 100% !important;" border="0" cellpadding="0" cellspacing="0" width="100%">
                            <tr>
                              <td style="height: 100px">
                                <h2> <?php echo $community['title']; ?></h2>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                    </table>

                    <table style="background-color: #e3e1d9;" class="table" border="0" valign="top" cellpadding="0" cellspacing="0"  width="19%" align="left";>
                      <tr>
                        <td style="vertical-align:top;" valign="top" class="cell">
                          <table style="width: 100% !important" border="0" cellpadding="0" cellspacing="0" valign="top" width="100%">
                            <tr valign="top">
                              <td style="padding: 0px" valign="middle" align="center">
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
                  <td style="padding-top: 20px; padding-left: 10px; padding-right: 10px;">
                    <?php foreach ($community['links'] as $key => $value): ?>
                      <p style="margin-bottom: 10px;"> <?php echo $value; ?> </p>
                    <?php endforeach; ?>
                    <p style="margin: 10px;"> &nbsp; </p>
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

  <table style="width: 100%; height: 100%; margin: 0px; padding: 0px; min-width: 320px" cellpadding="0" cellspacing="0" height="100%" class="bodytable" width="100%">
    <tr>
      <td align="center" bgcolor="#ffffff" style="background-color: #ffffff; vertical-align: top" valign="top">
        <table cellpadding="0" cellspacing="0" class="container" style="margin-top: 20px; width: 650px" width="650">
          <tr>
            <td>
              <table cellpadding="0" cellspacing="0" border="0">
                <tr>
                  <td class="newsletter-text">
                    <p style="margin-top: 30px;"> You are receiving this newsletter because you previously ticked that box when becoming a member of the community. While you can <?php echo $unsubscribe_link; ?>, we hope you continue to subscribe to our monthly newsletter. </p>
                  </td>
                </tr>
              </table>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>

</body>
</html>
