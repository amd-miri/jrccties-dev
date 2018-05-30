<?php
/**
 * @file
 * Context plugin file to provide changing the active theme as a context
 * reaction.
 */

/**
 * Expose themes as context reactions.
 */
class context_reaction_active_theme extends context_reaction {

  /**
   * Grab the available themes and provide them as a reaction for context.
   *
   * @param $context
   *   The context as passed from context module.
   *
   * @return array
   *   The FAPI array as read by context module.
   */
  function options_form($context) {

    $options = array();
    $themes = list_themes();

    foreach ($themes as $name => $theme) {
      // only allow active themes
      if ($theme->status == 1) {
        $options[$name] = $name;
      }
    }
    
    $settings = $this->fetch_from_context($context);
    
    $form = array(
      '#tree' => TRUE,
      '#title' => t('Theme'),

      'theme' => array(
        '#title' => t('Active theme'),
        '#description' => t('Choose a theme to activate when this context is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($settings['theme']) ? $settings['theme'] : variable_get('theme_default', ''),
      ),
    );
    return $form;
  }

  /**
   * Return the active theme based on the context
   *
   * @return string | null
   *   String of the theme name, or NULL if not to be altered.
   */
  function execute() {
    $theme = NULL;

    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['active_theme']['theme'])) {
        $theme = $context->reactions['active_theme']['theme'];
      }
    }

    return $theme;
  }
}
