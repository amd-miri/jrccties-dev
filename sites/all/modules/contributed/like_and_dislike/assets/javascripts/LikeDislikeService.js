(function() {
  window.LikeDislikeService = (function() {
    function LikeDislikeService() {}

    LikeDislikeService.vote = function(entity_id, entity_type, tag) {
      return jQuery.ajax({
        type: "GET",
        url: Drupal.settings.basePath + 'like_and_dislike/' + entity_type + '/' + tag + '/' + entity_id,
        success: function(msg) {
          var arrLikeCount, dislikeCount, likeCount, message;
          arrLikeCount = msg.split("/");
          likeCount = arrLikeCount[0];
          dislikeCount = arrLikeCount[1];
          message = '';
          if (arrLikeCount.length > 2) {
            message = arrLikeCount[2];
          }
          jQuery('#like-container-' + entity_type + '-' + entity_id + ' .count').html(likeCount);
          jQuery('#dislike-container-' + entity_type + '-' + entity_id + ' .count').html(dislikeCount);
          jQuery('#like-container-' + entity_type + '-' + entity_id + ' a').toggleClass('disable-status');
          jQuery('#dislike-container-' + entity_type + '-' + entity_id + ' a').toggleClass('disable-status');
          jQuery('#' + tag + '-container-' + entity_type + '-' + entity_id + ' .throbber').hide();
          if (typeof message === "string" && message.length > 0) {
            return alert(message);
          }
        }
      });
    };

    return LikeDislikeService;

  })();

}).call(this);
