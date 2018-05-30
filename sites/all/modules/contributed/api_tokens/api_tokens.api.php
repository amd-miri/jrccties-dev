<?php

/**
 * @file
 * Hooks provided by the API Tokens module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Declare API tokens.
 *
 * Token example:
 *   Non-parametric: [api:demo/]
 *       Parametric: [api:demo["param1", {"param2": {"key1": "value1"}}]/]
 * Parameters part must be a valid JSON array. Extra spaces are allowed.
 *
 * @return array
 *   Array of tokens to register.
 */
function hook_api_tokens_info() {
  // Token key must be lowercase, may contain
  // following characters: "a-z", "-", "_", ":"
  $tokens['demo'] = array(
    // Title of the token
    // If omitted, token key will be used
    // Optional.
    'title' => t('Demo'),

    // Description of the token
    // Optional.
    'description' => t('Description of the Demo API token'),

    // Name of the token process function
    // Must be defined within the module or its include file
    // If omitted, will be set to [%module_name]_apitoken_[%token_name]
    // ("-" and ":" characters are replaced with "_")
    // Optional
    'handler' => 'modulename_apitoken_demo',

    // Relative path to the token process function without extension.
    // If omitted, means that the process function located in .module file
    // Optional
    // modulename/includes/handlers.inc
    'inc' => 'includes/handlers',

    // Number of required parameters of the process function
    // If omitted, api_tokens_param_info() will be used to
    // determine the number of required parameters
    // Optional.
    'params' => 2,

    // Determines caching method for the output of the token process function
    // Allowed values:
    // - DRUPAL_NO_CACHE [default]
    // - DRUPAL_CACHE_PER_ROLE
    // - DRUPAL_CACHE_PER_USER
    // - DRUPAL_CACHE_PER_PAGE
    // - DRUPAL_CACHE_GLOBAL
    // If omitted, DRUPAL_NO_CACHE will be used
    // Optional.
    'cache' => DRUPAL_CACHE_PER_PAGE | DRUPAL_CACHE_PER_ROLE,

    // Makes sence when cache is set to other then DRUPAL_NO_CACHE
    // Allowed values:
    // - CACHE_PERMANENT (0)
    // - CACHE_TEMPORARY (-1) [default]
    // - Cache lifetime number in seconds
    // If omitted, CACHE_TEMPORARY will be used
    // Optional
    // 5 minutes.
    'cache_expire' => 300,
  );

  return $tokens;
}

/**
 * Alters API token definitions.
 *
 * @param array $tokens
 *   Associative array of API token definitions.
 */
function hook_api_tokens_info_alter(&$tokens) {
  // Override "demo" token handler.
  $tokens['demo']['handler'] .= '_override';
}

/**
 * Alter the output of rendered API token.
 *
 * @param string $rendered
 *   Rendered API token.
 * @param array $info
 *   An associative array containing following keys:
 *   - key: API token key;
 *   - params: an array of API token parameters;
 *   - token: original API token that will be replaced with rendered content;
 *   - parents: an array of parent tokens (if rendered content for token "A"
 *   contains token "B", parents array of token "B" will contain token "A").
 *
 * @see api_tokens_render()
 */
function hook_api_tokens_render_alter(&$rendered, $info) {
  if ('demo' == $info['key'] && 'wrap' == $info['params'][0]) {
    $rendered = '<div class="' . $info['params'][1] . '">' . $rendered . '</div>';
  }
}

/**
 * @} End of "addtogroup hooks".
 */

/**
 * Process function for the Demo API Token.
 */
function modulename_apitoken_demo($arg1, $arg2) {
  $result = some_processing($arg1, $arg2);

  return $result;
}
