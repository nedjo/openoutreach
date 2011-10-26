<?php

class MediaBrowserView extends MediaBrowserPlugin {

  function view() {
    $view = views_get_view($this->info['view_name']);
    return array(
      '#markup' => $view->preview($this->info['view_display_id']) . '<div class="form-actions form-wrapper"></div>',
    );
  }

}
