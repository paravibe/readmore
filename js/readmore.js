(function ($) {
  Drupal.behaviors.readmore = {
    attach : function(context, settings) {
      $('.readmore-summary .readmore-link').click(function(e) {
        e.preventDefault();
        var summary = $(this).closest('.readmore-summary');
        summary.hide();
        summary.next('.readmore-text').slideDown(300);
      });
    }
  };
})(jQuery);
