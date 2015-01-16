<div class="flex-container">
  <div class="flexslider">
    <ul class="slides">
      <?php foreach ($items as $delta => $item): ?>
        <li>
          <?php print render($item); ?>
          <?php if ($show_slideshow_caption == TRUE): ?>
            <div class="slideshow-caption"><p><?php print $item['#item']['title']; ?></p></div>
          <?php endif; ?>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
