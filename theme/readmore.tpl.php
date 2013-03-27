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
<div class="readmore-wrapp">
  <?php print $summary; ?>
  <?php if ($ellipsis): ?>
    <span class="readmore-ellipsis"><?php print t('...'); ?></span>
  <?php endif; ?>
  <a class="readmore-link" href="#"><?php print t('read more'); ?></a>
  <div class="readmore-other" style="display:none;"><?php print $other; ?></div>
</div>
