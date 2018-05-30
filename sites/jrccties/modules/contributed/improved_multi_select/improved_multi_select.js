(function ($) {
  Drupal.behaviors.improved_multi_select = {
    attach: function(context, settings) {

      if (settings.improved_multi_select && settings.improved_multi_select.selectors) {

        var selectors = settings.improved_multi_select.selectors;

        for (var key in selectors) {
          var selector = selectors[key];
          $(selector, context).once('improvedselect', function() {
            $(this).parent().append('<div class="improvedselect" sid="'+ $(this).attr('id') +'" id="improvedselect-'+ $(this).attr('id') +'"><div class="improvedselect-text-wrapper"><input type="text" class="improvedselect_filter" sid="'+ $(this).attr('id') +'" prev="" /></div><ul class="improvedselect_sel"></ul><ul class="improvedselect_all"></ul><div class="improvedselect_control"><span class="add" sid="'+ $(this).attr('id') +'">&gt;</span><span class="del" sid="'+ $(this).attr('id') +'">&lt;</span><span class="add_all" sid="'+ $(this).attr('id') +'">&raquo;</span><span class="del_all" sid="'+ $(this).attr('id') +'">&laquo;</span></div><div class="clear" /></div>');
            var improvedselect_id = $(this).attr('id');
            $(this).find('option').each(function(){
              if ($(this).attr('selected')) {
                $('#improvedselect-'+ improvedselect_id +' .improvedselect_sel', context).append('<li so="'+ $(this).attr('value') +'">'+ $(this).text() +'</li>');
              }
              else {
                $('#improvedselect-'+ improvedselect_id +' .improvedselect_all', context).append('<li so="'+ $(this).attr('value') +'">'+ $(this).text() +'</li>');
              }
            });
            $('#improvedselect-'+ improvedselect_id +' li', context).click(function(){
              $(this).toggleClass('selected');
            });
            $(this).hide();
          });
        }

        $('.improvedselect_filter', context).keyup(function(){
          var text = $(this).val();
          if (text.length && text != $(this).attr('prev')) {
            $(this).attr('prev', text);
            var patt = new RegExp(text,'i');
            $('#improvedselect-'+ $(this).attr('sid') +' .improvedselect_all li', context).each(function(){
              var str = $(this).text();
              if (str.match(patt)){
                $(this).show();
              }
              else{
                $(this).hide();
              }
            });
          }
          else {
            $(this).attr('prev', '')
            $('#improvedselect-'+ $(this).attr('sid') +' .improvedselect_all li', context).each(function(){
              $(this).show();
            });
          }
        });

        // Add selected items.
        $('.improvedselect .add', context).click(function(){
          var sid = $(this).attr('sid');
          $('#improvedselect-'+ sid +' .improvedselect_all .selected', context).each(function(){
            $(this).removeClass('selected');
            $(this).show();
            $('#improvedselect-'+ sid +' .improvedselect_sel', context).append($(this));
          });
          improvedselectUpdate(sid, context);
        });

        // Remove selected items.
        $('.improvedselect .del', context).click(function(){
          var sid = $(this).attr('sid');
          $('#improvedselect-'+ sid +' .improvedselect_sel .selected', context).each(function(){
            $(this).removeClass('selected');
            $('#improvedselect-'+ sid +' .improvedselect_all', context).append($(this));
          });
          improvedselectUpdate(sid, context);
        });

        // Remove all filtered items.
        $('.improvedselect .add_all', context).click(function(){
          var sid = $(this).attr('sid');
          $('#improvedselect-'+ sid +' .improvedselect_all li', context).each(function(){
            if ($(this).css('display') != 'none') {
              $(this).removeClass('selected');
              $('#improvedselect-'+ sid +' .improvedselect_sel', context).append($(this));
            }
          });
          improvedselectUpdate(sid, context);
        });

        // Remove all items.
        $('.improvedselect .del_all', context).click(function(){
          var sid = $(this).attr('sid');
          $('#improvedselect-'+ sid +' input', context).val('');
          $('#improvedselect-'+ sid +' input', context).attr('prev', '');
          $('#improvedselect-'+ sid +' .improvedselect_sel li', context).each(function(){
            $(this).removeClass('selected');
            $('#improvedselect-'+ sid +' .improvedselect_all', context).append($(this));
          });
          $('#improvedselect-'+ sid +' .improvedselect_all li', context).each(function(){
            $(this).show();
          });
          improvedselectUpdate(sid, context);
        });

      }
    }
  };

  function improvedselectUpdate(sid, context) {
    $('#'+ sid +' option:selected', context).attr("selected", "");
    $('#improvedselect-'+ sid +' .improvedselect_sel li', context).each(function(){
      $('#'+ sid +' [value="'+ $(this).attr('so') +'"]', context).attr("selected", "selected");
    });

    $('#' + sid, context).find('option').each(function() {
      if ($(this).attr("selected")) {
        $('#improvedselect-'+ sid +' .improvedselect_sel', context).append($('#improvedselect-'+ sid +' .improvedselect_sel [so="'+ $(this).attr('value') +'"]', context));
      }
      else {
        $('#improvedselect-'+ sid +' .improvedselect_all', context).append($('#improvedselect-'+ sid +' .improvedselect_all [so="'+ $(this).attr('value') +'"]', context));
      }
    });
  }

})(jQuery, Drupal);
