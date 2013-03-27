(function ($) {
  Drupal.behaviors.moreText = {
    attach : function(context, settings) {
      $('.more-text .read-more').click(function(e) {
        e.preventDefault();
        $(this).hide();
        var parent = $(this).closest('.more-text');
        parent.find('.more-text-ellips').hide();
        parent.find('.other-text').slideDown(300);
      });
    }
  };
})(jQuery);
