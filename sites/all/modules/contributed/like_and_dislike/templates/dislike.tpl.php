<?php
/**
 * This tpl handles the like link and its look and feel.
 * Variables avaiable:
 * @entity_id: the entity id of the entity on which the link is getting printed.
 * @likes: the number is likes that is casted to the node/comment.
 */
?>
<div class="like-and-dislike-container dislike type-<?php print $entity_type ?>" id="dislike-container-<?php print $entity_type ?>-<?php print $entity_id ?>">
  <a title="Dislike" 
     data-entity-id="<?php print $entity_id ?>"
     data-entity-type="<?php print $entity_type ?>"
     class="<?php if ($dislikestatus == 1) print ' disable-status' ?>">
    Dislike
  </a>
  <span class="count"><?php print $dislikes; ?></span>
  <span style="display:none" class="throbber">Loading...</span>
</div>