<?php

/**
 * @file
 * Default theme implementation to display a divided text.
 *
 * Available variables:
 * - $summary: Truncated string.
 * - $ellipsis: Flags true when need to add ellipsis.
 * - $other: Text that will be displayed after click 'read more' link.
 */
?>
<div class="more-text">
  <?php print $summary; ?>
  <?php if ($ellipsis): ?>
    <span class="more-text-ellips"><?php print t('...'); ?></span>
  <?php endif; ?>
  <a class="read-more" href="#"><?php print t('read more'); ?></a>
  <div class="other-text" style="display:none;"><?php print $other; ?></div>
</div>
