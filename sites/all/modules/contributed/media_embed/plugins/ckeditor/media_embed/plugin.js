/**
 * @file
 * Media Embed plugin definition.
 */

(function($) {

  function MediaEmbed(conf) {
    this.conf = conf;
    this.command = 'media_embed';
    this.class = 'media-embed-widget';
    this.content = {};
    this.data = {};
    this.current = null;
  }


  MediaEmbed.prototype.process = function(text) {
    var self = this;
    text = text.replace(new RegExp(this.conf.pattern, 'g'), function(token) {
      var content = self.getContent(token);
      return self.widget(token, null !== content ? content : self.conf.broken);
    });

    return text;
  };


  MediaEmbed.prototype.getContent = function(token) {
    if (!(token in this.content)) {
      var data = this.parseToken(token);
      if (data) {
        var map = {
          ID: data.id,
          FORMAT: data.format,
          PARAMS: data.params ? encodeURIComponent(data.params) : ''
        };
        var self = this
          , url = this.conf.url;
        Object.keys(map).forEach(function(key) {
          url = url.replace(key, map[key]);
        });
        $.ajax({
          type: 'GET',
          url: url,
          dataType: 'json',
          async: false,
          success: function(data) {
            if ('OK' === data.status) {
              self.content[token] = data.content;
            }
            else {
              console.warn(data.content.replace('{token}', token));
              self.content[token] = null;
            }
          },
          error: function() {
            self.content[token] = null;
          }
        });
      }
      else {
        this.content[token] = null;
      }
    }

    return this.content[token];
  };


  MediaEmbed.prototype.parseToken = function(token) {
    if (!(token in this.data)) {
      var self = this
        , data = null
        , match = token.match(new RegExp(this.conf.pattern));
      if (match) {
        data = {};
        Object.keys(this.conf.map).forEach(function(key) {
          data[key] = match[self.conf.map[key]];
        });
        if (data.params) {
          try {
            JSON.parse(data.params);
          }
          catch (e) {
            console.warn(e);
            data = null;
          }
        }
        else {
          data.params = null;
        }
      }
      this.data[token] = data;
    }

    return this.data[token];
  };


  MediaEmbed.prototype.widget = function(token, content) {
    var element = CKEDITOR.dom.element.createFromHtml(content);
    if (CKEDITOR.NODE_TEXT === element.type) {
      element = new CKEDITOR.dom.element('span');
      element.appendText(content);
    }
    element.addClass(plugin.class);
    element.setAttribute(plugin.command, encodeURIComponent(token));

    return element.getOuterHtml();
  };


  MediaEmbed.prototype.isWidget = function(element) {
    return element.hasClass(this.class);
  };


  var plugin = new MediaEmbed(Drupal.settings.mediaEmbed);

  CKEDITOR.plugins.add('media_embed', {
    requires: 'widget',
    init: function(editor) {
      editor.addCommand(plugin.command, {
        exec: function(editor) {
          if (plugin.current) {
            Drupal.media.popups.mediaFormatSelector(plugin.current, function(response) {
              var token = response.token;
              plugin.content[token] = response.content;
              plugin.data[token] = response.data;
              editor.insertHtml(plugin.process(token));
            });
          }
          else {
            Drupal.media.popups.mediaBrowser(function(files) {
              Drupal.media.popups.mediaFormatSelector(files[0].fid, function(response) {
                var token = response.token;
                plugin.content[token] = response.content;
                plugin.data[token] = response.data;
                editor.insertHtml(plugin.process(token));
              });
            }, plugin.conf.browser);
          }
        }
      });

      editor.widgets.add('media_embed_widget', {
        upcast: function(element) {
          if (!plugin.isWidget(element) && 'ul' !== element.name) {
            var original = element.getHtml()
              , processed = plugin.process(original);
            original !== processed && element.setHtml(processed);
          }

          return plugin.isWidget(element);
        },

        downcast: function(widgetElement) {
          return new CKEDITOR.htmlParser.text(decodeURIComponent(widgetElement.attributes[plugin.command]));
        },

        init: function() {
          var token = decodeURIComponent(this.element.getAttribute(plugin.command));
          this.data.data = plugin.getContent(token) ? plugin.parseToken(token) : null;

          this.on('focus', function() {
            plugin.current = this.data.data;
            editor.getCommand(plugin.command).setState(CKEDITOR.TRISTATE_ON);
          });

          this.on('blur', function() {
            plugin.current = null;
            editor.getCommand(plugin.command).setState(CKEDITOR.TRISTATE_OFF);
          });

          this.on('doubleclick', function() {
            plugin.current = this.data.data;
            editor.execCommand(plugin.command);
          });
        }
      });

      editor.ui.addButton('media_embed', {
        label: Drupal.t('Media Embed'),
        command: plugin.command,
        icon: this.path + 'images/icon.png'
      });
    },

    onLoad: function() {
      var c = '.' + plugin.class;
      CKEDITOR.addCss('.cke_widget_wrapper:hover > ' + c + ' { outline: 2px solid #f90; }'
        + '.cke_widget_wrapper.cke_widget_focused > ' + c + ' { outline: 2px solid #ace; }'
        + c + ' a > img, a' + c + ' > img { display: block; }');
    }
  });

})(jQuery);
