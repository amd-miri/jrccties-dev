-- SUMMARY --

The API Tokens module provides an input filter that allows to replace custom
parametric tokens with rendered content. Each declared token binds to its
handler function, that returns content, token will be replaced with. Token may
contain parameters that will be passed to its handler function.

For example, you can declare a token which will render a current date on each
page reload as follows:
  [api:date/],
or render blocks:
  [api:block["module", "delta"]/],
or even views:
  [api:view["view_name", "display_id"]/] - without arguments
  [api:view["view_name", "display_id", ["arg1", "arg2"]]/] - with arguments.

Each module is able to define its own parametric tokens and corresponding
render functions. Module provides flexible caching mechanism.

Since API tokens accept parameters, it is highly advisable to add all required
checks to your render functions to avoid performance impact and fatal errors.

Note that API Tokens module does not provide any visible functions to the user
on its own, it just provides handling services for other modules.


For a full description of the module, visit the project page:
  http://drupal.org/project/api_tokens

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/api_tokens


-- REQUIREMENTS --

None.


-- INSTALLATION --

* Install as usual, see https://drupal.org/node/895232 for further information.


-- CONFIGURATION --

* Go to /admin/config/content/formats and enable the API Tokens filter for any
  of your existing text formats or create a new one.

* List of all registered tokens available at admin/config/content/api-tokens.


-- CONTACT --

Current maintainers:
* Alex Zhulin (Alex Zhulin) - https://drupal.org/user/2659881

This project has been sponsored by:
* Blink Reaction
  A leader in Enterprise Drupal Development, delivering robust,
  high-performance websites for dynamic companies. Blink creates scalable and
  flexible web solutions that provide the best in customer experience and meet
  brand, marketing, and business goals.
