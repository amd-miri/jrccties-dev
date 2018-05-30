GELF Log
========

Gelf log is a light Drupal module sending errors formatted with 
the GELF protocol.

Using UDP prevents any locking to occur when sending errors and 
will not block processing if the logging server is down.

This projects is different from https://www.drupal.org/project/gelf 
since it embeds its own method for formating Gelf packets and doesn't 
require external libs or install hooks.

You can also configure an additional group field to better 
split/group your errors in your final logging solution.

GELF Log let you select the MTU for UDP packet as well, 
this will help on pesky networks.

Recommended stacks are :

 - ELK
 - Graylog
