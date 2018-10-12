Drupal.behaviors.bounce = {
  attach: function(context, settings) {
    
    /**
     * Obtain the new port value for a given protocol and encryption mode.
     * 
     * @param encryption
     *   Encryption mode, one of "", "tls", "ssl".
     * @param protocol
     *   Protocol used, one of "pop3", "imap".
     *   
     * @return
     *   The port number.
     */
    var getPort = function(encryption, protocol) {
      var port = "";
      if (protocol == "pop3") {
        if (encryption == "ssl") {
          port = 995;
        }
        else {
          port = 110;
        }
      }
      else if (protocol == 'imap') {
        if (encryption == "ssl") {
          port = 993;
        }
        else {
          port = 143;
        }
      }
      
      return port;
    };
    
    jQuery("#edit-bounce-connector-protocol", context).change(function(e) {
      var encryption = jQuery("#edit-bounce-connector-encryption", context).val();
      var protocol = jQuery(this).val();
      jQuery("#edit-bounce-connector-port", context).val(getPort(encryption, protocol));
    });
    
    jQuery("#edit-bounce-connector-encryption", context).change(function(e) {
      var encryption = jQuery(this).val();
      var protocol = jQuery("#edit-bounce-connector-protocol", context).val();
      jQuery("#edit-bounce-connector-port", context).val(getPort(encryption, protocol));
    });
  }
};
