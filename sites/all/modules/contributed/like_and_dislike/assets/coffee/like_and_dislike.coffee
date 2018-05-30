(($) ->

  Drupal.behaviors.LikeDislike = attach: (context, settings) ->
    #This is handling the click on the Like link
    $('.like-and-dislike-container.like a').click ->
      unless $(@).hasClass 'disable-status'
        entity_id = $(this).data 'entity-id'
        entity_type = $(this).data 'entity-type'
        $('#like-container-' + entity_type + '-' + entity_id + ' .throbber').show()
        LikeDislikeService.vote entity_id, entity_type, 'like'
      return

    #This is handling the click on the Dislike link
    $('.like-and-dislike-container.dislike a').click ->
      unless $(@).hasClass 'disable-status'
        entity_id = $(this).data 'entity-id'
        entity_type = $(this).data 'entity-type'
        $('#dislike-container-' + entity_type + '-' + entity_id + ' .throbber').show()
        LikeDislikeService.vote entity_id, entity_type, 'dislike'
      return
    return
  return

) jQuery