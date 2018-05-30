<?php

/**
 * @file
 * Definition of tableau_views_handler_field_view_tags.
 */

/**
 * Field handler to display all tags of a view.
 *
 * @ingroup views_field_handlers
 */
class tableau_views_handler_field_view_tags extends views_handler_field_prerender_list {

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_tag'] = array('default' => '');
    return $options;
  }

  /**
   * Provide "link to tag" option.
   */
  function options_form(&$form, &$form_state) {
    $form['link_to_tag'] = array(
      '#title' => t('Link this field to its tag page'),
      '#description' => t('Use <em>[tag_id]</em> or <em>[tag_name]</em> to substitute the corresponding value'),
      '#type' => 'textfield',
      '#default_value' => $this->options['link_to_tag'],
    );
    parent::options_form($form, $form_state);
  }

  function pre_render(&$values) {
    foreach ($values as $result) {
      if (!empty($result->{$this->field_alias})) {
        $result->tags = tableau_tag_load_multiple(FALSE, array('object_id' => $result->{$this->field_alias}));
        if (!empty($result->tags)) {
          foreach ($result->tags as $tag) {
            $this->items[$result->{$this->field_alias}][$tag->tag_id]['tag_id'] = check_plain($tag->tag_id);
            $this->items[$result->{$this->field_alias}][$tag->tag_id]['tag_name'] = check_plain($tag->tag_name);

            // Add link to tag
            if (!empty($this->options['link_to_tag'])) {
              $this->items[$result->{$this->field_alias}][$tag->tag_id]['make_link'] = TRUE;
              $this->items[$result->{$this->field_alias}][$tag->tag_id]['path'] = $this->options['link_to_tag'];
            }
          }
        }
      }
    }
  }

  function render_item($count, $item) {
    return $item['tag_name'];
  }

  function document_self_tokens(&$tokens) {
    unset($tokens['[tags]']);
    $tokens['[tag_id]'] = t('The tag ID for the tag entity.');
    $tokens['[tag_name]'] = t('The tag name for the tag entity.');
  }

  function add_self_tokens(&$tokens, $item) {
    foreach(array('tag_id', 'tag_name') as $token) {
      $tokens['[' . $token . ']'] = isset($item[$token]) ? $item[$token] : '';
    }
  }

}
