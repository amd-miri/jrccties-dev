<?php



function tweetbutton_admin_settings() {
	$form = array();
  
  $form['button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings for tweetbutton'),
  );
  
  $form['button']['tweetbutton_button'] = array(
    '#type' => 'select',
    '#options' => array(
      'vertical' => t('Vertical Count'),
      'horizontal' => t('Horizontal Count'),
      'none'   => t('No count'),
    ),
    '#default_value' => variable_get('tweetbutton_button', 'vertical'),
    '#id' => 'tweetbutton-button',
  );
  
  
  $form['button']['tweetbutton_tweet_text'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Tweet Text'),
    '#default_value' => variable_get('tweetbutton_tweet_text'),
    '#description'  => t('Tweet text to use as a default text, if no values are passed, leave this to blank to use page title as tweet text.')
  );

  $form['button']['tokens'] = array(
    '#token_types' => array('node'),
    '#theme' => 'token_tree',
  );  

  $form['button']['tweetbutton_size'] = array(
    '#title' => t('Tweetbutton size'),
    '#type' => 'select',
    '#options' => array(
      'medium' => t('Medium'),
      'large' => t('Large'),
    ),
    '#default_value' => variable_get('tweetbutton_size'),
  );
  
  $form['button']['tweetbutton_hashtags'] = array(
    '#title' => t('Hashtags'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tweetbutton_hashtags'),
    '#description' => t('Comma separated hashtags to be used in every tweet'),
  );
  
  $form['button']['tweetbutton_language'] = array(
    '#title' => t('Language'),
    '#description' => t('This is the language that the button will render in on your website. People will see the Tweet dialog in their selected language for Twitter.com.'),
    '#type' => 'select',
    '#options' => array(
      'en'   => t('English'),
      'fr'   => t('French'),
      'de'   => t('German'),
      'es'   => t('Spanish'),
      'ja'   => t('Japanese'),
      'auto' => t('Automatic'),
    ),
    '#default_value' => variable_get('tweetbutton_language'),
  );
  
  if (module_exists('shorten')) {

    $services = array();
    $services[0] = t('Use t.co twitter default url shortener');
    $all_services = module_invoke_all('shorten_service');
    foreach (array_keys($all_services) as $value) {
      $services[$value] = $value;
    }
    
    $form['button']['tweetbutton_shorten_service'] = array(
      '#title' => t('Shorten service to use to add custom url'),
      '#type' => 'select',
      '#options' => $services,
      '#default_value' => variable_get('tweetbutton_shorten_service', 0),
    );
  }
  
  $form['button']['follow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Recommend people to follow'),
  );
  
  $form['button']['follow']['tweetbutton_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter account to follow'),
    '#description' => t('This user will be @mentioned in the suggested. Will be used as default if tweetbutton fields author twitter account is not set'),
    '#default_value' => variable_get('tweetbutton_account'),
    '#id' => 'tweetbutton-account',
  );
  
  $form['button']['follow']['tweetbutton_rel_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Related Account'),
    '#default_value' => variable_get('tweetbutton_rel_account_name'),
    '#description' => t('This should be site default twitter account'),
  );
  
  $form['button']['follow']['tweetbutton_rel_account_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Related Account Description'),
    '#default_value' => variable_get('tweetbutton_rel_account_description'),
  );

  
  
  $form['follow_button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Follow button settings'),
  );
  
  $form['follow_button']['tweetbutton_follow_show_count'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show follow count'),
    '#default_value' => variable_get('tweetbutton_follow_show_count', TRUE),
  );
  
  $form['follow_button']['tweetbutton_follow_screen_name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Screen name to follow'),
    '#default_value'  => variable_get('tweetbutton_follow_screen_name'),
  );
  
  $form['follow_button']['tweetbutton_follow_size'] = array(
    '#title' => t('Tweetbutton size'),
    '#type' => 'select',
    '#options' => array(
      'medium' => t('Medium'),
      'large' => t('Large'),
    ),
    '#default_value' => variable_get('tweetbutton_follow_size'),
  );
  
  return system_settings_form($form);
}