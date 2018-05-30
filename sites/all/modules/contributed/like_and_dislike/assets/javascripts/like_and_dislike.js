(function() {
  (function($) {
    Drupal.behaviors.LikeDislike = {
      attach: function(context, settings) {
        $('.like-and-dislike-container.like a').click(function() {
          var entity_id, entity_type;
          if (!$(this).hasClass('disable-status')) {
            entity_id = $(this).data('entity-id');
            entity_type = $(this).data('entity-type');
            $('#like-container-' + entity_type + '-' + entity_id + ' .throbber').show();
            LikeDislikeService.vote(entity_id, entity_type, 'like');
          }
        });
        $('.like-and-dislike-container.dislike a').click(function() {
          var entity_id, entity_type;
          if (!$(this).hasClass('disable-status')) {
            entity_id = $(this).data('entity-id');
            entity_type = $(this).data('entity-type');
            $('#dislike-container-' + entity_type + '-' + entity_id + ' .throbber').show();
            LikeDislikeService.vote(entity_id, entity_type, 'dislike');
          }
        });
      }
    };
  })(jQuery);

}).call(this);
