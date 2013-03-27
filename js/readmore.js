(function ($) {
  Drupal.behaviors.readmore = {
    attach : function(context, settings) {
      $('.readmore-wrapp .readmore-link').click(function(e) {
        e.preventDefault();
        $(this).hide();
        var parent = $(this).closest('.readmore-wrapp');
        parent.find('.readmore-ellipsis').hide();
        parent.find('.readmore-other').slideDown(300);
      });
    }
  };
})(jQuery);
