The Drupal  community provides numerous  modules to move Drupal  cache_bins from
MySQL  to another  kind  of storage  (Memcached, Redis,  APC,  etc.). How  those
alternate storage  solutions are actually  made highly-available is a  matter of
infrastructure.  As failure  is always  an option,  some people  customize their
settings.php  to  ensure the  alternate  backend  is actually  available  before
configuring $conf['cache_default_class']  (or other,  similar variables  such as
$conf['cache_class_cache_page']).

But what to do if none of the alternate backend are available?

It is possible to tell Drupal  not to cache anything, but performance-wise, this
approach is very risky in case the alternate storage is down for a long time.

It is  also possible to fall  back on the default,  MySQL-based cache mechanism.
However,  this approach  yields  another  risk: some  MySQL  tables may  contain
obsolete data; bootstrapping with months-old cache_bootstrap entries can quickly
lead to a White Screen of  Death (typically by referencing obsolete filepaths to
be included).
Truncating those  tables beforehand is  rather tricky, as  it must be  done only
once, when  falling back to MySQL  (this is not that  easy to track in  case the
alternate storage service is flapping).

To  address this  problematic, this  project provides  a slight  variant of  the
"DrupalDatabaseCache" class:  FailoverDrupalDatabaseCache ignores  cache entries
older than a configurable  age (20 minutes by default). That  way, a failover to
MySQL-based  caching will  never hit  too old  entries and  limit the  amount of
entries that need to be computed again.
